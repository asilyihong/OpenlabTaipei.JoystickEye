#define DELAY_BLINK 40
/* This method blinks eyes as per provided params */

void blinkEyesInit(bool left, bool right)
{
    blinkLeft = left;
    blinkRight = right;
    animLvlIndex = 0;
    animIndex = 0;
}

void blinkEyes()
{
    switch(animLvlIndex)
    {
    case 0:
        if (blinkLeft)
        {
            setRow(0, animIndex, 0);
            setRow(0, 7 - animIndex, 0);
        }
#if (EYEBALL_CNT == 2)
        if (blinkRight)
        {
            setRow(1, animIndex, 0);
            setRow(1, 7 - animIndex, 0);
        }
#endif
        nextAnimTime = currTime + DELAY_BLINK;
        animIndex++;
        if (animIndex == 4)
        {
            animLvlIndex++;
            nextAnimTime += DELAY_BLINK * 2;
        }
        break;
    case 1:
        animIndex--;
        if (blinkLeft)
        {
            setRow(0, animIndex, eyeCurrent[animIndex]);
            setRow(0, 7 - animIndex, eyeCurrent[7 - animIndex]);
        }
#if (EYEBALL_CNT == 2)
        if (blinkRight)
        {
            setRow(1, animIndex, eyeCurrent[animIndex]);
            setRow(1, 7 - animIndex, eyeCurrent[7 - animIndex]);
        }
#endif
        nextAnimTime = currTime + DELAY_BLINK;
        if (animIndex == 0)
        {
            nextAnim();
        }
        break;
    default:
        return;
    }
}
