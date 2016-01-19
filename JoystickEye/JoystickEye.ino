/* We always have to include the LedControl library */
#include <LedControl.h>
#include <Serial.h>

#include "JoystickEye.h"
LedControl lc = LedControl(PIN_EYES_DIN, PIN_EYES_CLK, PIN_EYES_CS, EYEBALL_CNT);
/* rotation */
bool rotateMatrix0 = false; /* rotate 0 matrix by 180 deg */
bool rotateMatrix1 = false;  /* mirror */ /* rotate 1 matrix by 180 deg */
/* define eye ball without pupil */
byte eyeBall[8]={
    B00111100,
    B01111110,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B01111110,
    B00111100
};
const byte eyePupil = B00011000;
/* stores current state of LEDs */
byte eyeCurrent[8];
int currentX;
int currentY;
int cntLoop = 0;
int cntEffect = 0;
/* min and max positions */
#define MIN -2
#define MAX 2
int prevXPosition = 0;
int prevYPosition = 0;
int xPosition = 0;
int yPosition = 0;
int buttonState = 0;
boolean noMove = false;

unsigned long currTime = 0;
unsigned long lastMoveTime = 0;
unsigned long nextAnimTime = 0;

boolean animMode = false;
int animTypeIndex = -1;
int animLvlIndex = -1;
int animIndex = -1;
int animReTimes = 0;
int specialDelay = 0;
int currReTime = 0;

/* Cross/meth eyes used */
byte pupilR = eyePupil;
byte pupilL = eyePupil;
boolean blinkLeft = false;
boolean blinkRight = false;

/* Arduino setup */
void setup()
{
    /* MAX72XX is in power-saving mode on startup, we have to do a wakeup call */
    lc.shutdown(0,false);
    /* set the brightness to low */
    lc.setIntensity(0,1);
    /* clear both modules */
    lc.clearDisplay(0);
#if (EYEBALL_CNT == 2)
    lc.shutdown(1,false);
    lc.setIntensity(1,1);
    lc.clearDisplay(1);
#endif
    /* LED test vertical line */
    byte b = B10000000;
    for (int c = 0; c <= 7; c++)
    {
        for (int r = 0; r <= 7; r++)
        {
            setRow(0, r, b);
#if (EYEBALL_CNT == 2)
            setRow(1, r, b);
#endif
        }
        b = b >> 1;
        delay(50);
    }
    /* full module */
    b = B11111111;
    for (int r = 0; r <= 7; r++)
    {
        setRow(0, r, b);
#if (EYEBALL_CNT == 2)
        setRow(1, r, b);
#endif
    }
    delay(500);
    /* clear both modules */
    lc.clearDisplay(0);
#if (EYEBALL_CNT == 2)
    lc.clearDisplay(1);
#endif
    delay(500);
    /* random seed */
    randomSeed(analogRead(0));
    /* center eyes, crazy blink */
    displayEyes(0, 0);

    /* initial Joystick */
    pinMode(X_PIN, INPUT);
    pinMode(Y_PIN, INPUT);

    /* activate pull-up resistor on the push-button pin */
    pinMode(BTN_PIN, INPUT_PULLUP); 
    Serial.begin(9600);

    delay(1000);
    currTime = millis();
    lastMoveTime = currTime;
}

/* Arduino loop */
void loop()
{
    xPosition = map(analogRead(X_PIN), 0, 1024, MIN, MAX + 1);
    yPosition = map(analogRead(Y_PIN), 0, 1024, MIN, MAX + 1);
    buttonState = digitalRead(BTN_PIN);

    currTime = millis();

    noMove = (xPosition == prevXPosition) && (yPosition == prevYPosition);
    if (!noMove || !buttonState)
    {
        animMode = false;
        prevXPosition = xPosition;
        prevYPosition = yPosition;
        lastMoveTime = currTime;
    }
    if (animMode)
    {
        if (nextAnimTime < currTime)
        {
            switch (animTypeIndex)
            {
            case ANIM_BLINK_SINGLE:
                blinkEyes();
                break;
            case ANIM_BLINK_TWO:
                blinkEyes();
                break;
            case ANIM_CRAZY_SPIN:
                crazySpin();
                break;
            case ANIM_CROSS_EYES:
                crossEyes();
                break;
            case ANIM_LAZY_EYES:
                lazyEye();
                break;
            case ANIM_METH_EYES:
                methEyes();
                break;
            case ANIM_GLOW_EYES:
                glowEyes(3);
                break;
            case ANIM_MOVE:
                moveEyesLoop();
                break;
            case ANIM_ROUND_SPIN:
                roundSpin();
                break;
            default:
                break;
            }
        }
    }
    else if (!buttonState || currTime - lastMoveTime > IDLE_IVL)
    {
        startAnim();
    } 
    else if (!noMove)
    {
        /* Move via Joystick */
        displayEyes(xPosition, yPosition);
    }
}

/* This method corrects provided coordinate value */
int getValidValue(int value)
{
    if (value > MAX)
        return MAX;
    else if (value < MIN)
        return MIN;
    else
        return value;
}
/*
   This method displays eyeball with pupil offset by X, Y values from center position.
   Valid X and Y range is [MIN,MAX]
   Both LED modules will show identical eyes
 */
void displayEyes(int offsetX, int offsetY)
{
    /* ensure offsets are in valid ranges */
    offsetX = getValidValue(offsetX);
    offsetY = getValidValue(offsetY);
    /* calculate indexes for pupil rows (perform offset Y) */
    int row1 = 3 - offsetY;
    int row2 = 4 - offsetY;
    /* define pupil row */
    byte pupilRow = eyePupil;
    /* perform offset X, bit shift and fill in new bit with 1 */
    if (offsetX > 0) {
        pupilRow = pupilRow >> offsetX;
    }
    else if (offsetX < 0) {
        pupilRow = pupilRow << (-offsetX);
    }
    pupilRow = pupilRow ^ B11111111;
    /* pupil row cannot have 1s where eyeBall has 0s */
    byte pupilRow1 = pupilRow & eyeBall[row1];
    byte pupilRow2 = pupilRow & eyeBall[row2];
    /* display on LCD matrix, update to eyeCurrent */
    for(int r = 0; r < 8; r++)
    {
        if (r == row1)
        {
            setRow(0, r, pupilRow1);
            setRow(1, r, pupilRow1);
            eyeCurrent[r] = pupilRow1;
        }
        else if (r == row2)
        {
            setRow(0, r, pupilRow2);
            setRow(1, r, pupilRow2);
            eyeCurrent[r] = pupilRow2;
        }
        else
        {
            setRow(0, r, eyeBall[r]);
            setRow(1, r, eyeBall[r]);
            eyeCurrent[r] = eyeBall[r];
        }
    }
    /* update current X and Y */
    currentX = offsetX;
    currentY = offsetY;
}

/* This method sets values to matrix row Performs 180 rotation if needed */
void setRow(int addr, int row, byte rowValue)
{
    if (((addr == 0) && (rotateMatrix0)) || (addr == 1 && rotateMatrix1))
    {
        /* row = abs(row - 7); */
        rowValue = bitswap(rowValue);
    }
    lc.setRow(addr, row, rowValue);
}

/* Reverse bits in byte http://www.nrtm.org/index.php/2013/07/25/reverse-bits-in-a-byte/ */
byte bitswap (byte x)
{
    byte result;
    asm("mov __tmp_reg__, %[in] \n\t"
            "lsl __tmp_reg__ \n\t" /* shift out high bit to carry */
            "ror %[out] \n\t" /* rotate carry __tmp_reg__to low bit (eventually) */
            "lsl __tmp_reg__ \n\t" /* 2 */
            "ror %[out] \n\t"
            "lsl __tmp_reg__ \n\t" /* 3 */
            "ror %[out] \n\t"
            "lsl __tmp_reg__ \n\t" /* 4 */
            "ror %[out] \n\t"
            "lsl __tmp_reg__ \n\t" /* 5 */
            "ror %[out] \n\t"
            "lsl __tmp_reg__ \n\t" /* 6 */
            "ror %[out] \n\t"
            "lsl __tmp_reg__ \n\t" /* 7 */
            "ror %[out] \n\t"
            "lsl __tmp_reg__ \n\t" /* 8 */
            "ror %[out] \n\t"
            : [out] "=r" (result) : [in] "r" (x));
    return(result);
}

void startAnim()
{
    animMode = true;
    animTypeIndex = ANIM_IDX_MIN;
    animLvlIndex = 0;
    animIndex = 0;
    nextAnimTime = currTime;
#if (EYEBALL_CNT == 2)
    blinkEyesInit(false, true);
#else
    blinkEyesInit(true, false);
#endif
}

void nextAnim()
{
    animIndex = 0;
    animLvlIndex = 0;
    if (animTypeIndex == ANIM_MOVE)
    {
        animTypeIndex = random(ANIM_IDX_MIN, ANIM_IDX_MAX + 1);
        nextAnimTime = currTime + 500 + random(ANIM_IVL);
        switch (animTypeIndex)
        {
        case ANIM_BLINK_SINGLE:
#if (EYEBALL_CNT == 2)
            blinkEyesInit(false, true);
#else
            blinkEyesInit(true, false);
#endif
            break;
        case ANIM_BLINK_TWO:
            blinkEyesInit(true, true);
            break;
        case ANIM_ROUND_SPIN:
            roundSpinInit(3);
            break;
        case ANIM_CRAZY_SPIN:
            crazySpinInit(3);
            break;
        default:
            break;
        }
    }
#if (EYEBALL_CNT == 2)
    else if (animTypeIndex == ANIM_BLINK_SINGLE && (blinkLeft == false && blinkRight == true))
    { /* blink right eye */
        blinkEyesInit(true, false);
        nextAnimTime = currTime + 100;
    }
#endif
    else
    {
        nextAnimTime = currTime + 500 + random(ANIM_IVL);
        animTypeIndex = ANIM_MOVE;
        moveEyesInit(random(MIN, MAX + 1), random(MIN, MAX + 1), 50, false);
    }

}

