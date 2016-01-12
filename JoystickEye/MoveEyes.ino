int startX;
int startY;
/* eval steps */
int stepsX;
int stepsY;
/* eval direction of movement, # of steps, change per X Y step, perform move */
int dirX;
int dirY;
int steps;
int intX, intY;
float changeX;
float changeY;
boolean isCombo;
int stepDelayTime;

/* This method moves both eyes from current position to new position */
void moveEyesInit(int newX, int newY, int stepDelay, boolean combo)
{
    /* set current position as start position */
    startX = currentX;
    startY = currentY;
    /* fix invalid new X Y values */
    newX = getValidValue(newX);
    newY = getValidValue(newY);
    /* eval steps */
    stepsX = abs(currentX - newX);
    stepsY = abs(currentY - newY);
    /* eval direction of movement, # of steps, change per X Y step, perform move */
    stepDelayTime = stepDelay;
    dirX = (newX >= currentX) ? 1 : -1;
    dirY = (newY >= currentY) ? 1 : -1;
    steps = (stepsX > stepsY) ? stepsX : stepsY;
    changeX = (float)stepsX / (float)steps;
    changeY = (float)stepsY / (float)steps;
    isCombo = combo;
    animLvlIndex++;
}

void moveEyesLoop()
{
    intX = startX + round(changeX * animIndex * dirX);
    intY = startY + round(changeY * animIndex * dirY);
    displayEyes(intX, intY);
    nextAnimTime = currTime + stepDelayTime;
    animIndex++;
    if (animIndex > steps)
    {
        if (isCombo)
        {
            animIndex = 0;
            animLvlIndex++;
        }
        else
        {
            nextAnim();
        }
    }
}
