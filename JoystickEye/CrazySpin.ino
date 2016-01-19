void crazySpinInit(int times)
{
    animReTimes = times;
    specialDelay = 50;
    animLvlIndex = 0;
    animIndex = 0;
    currReTime = 0;
    pupilR = eyePupil;
}

void crazySpin()
{
    switch(animLvlIndex)
    {
    case 0:
        moveEyesInit(0, 0, 50, true);
        break;
    case 1:
        moveEyesLoop();
        break;
    case 2:
        nextAnimTime = currTime + 500;
        animLvlIndex++;
        animIndex = 0;
        break;
    case 3:
        pupilR = pupilR >> 1;
        setRow(0, 3, pupilR ^ B11111111);
        setRow(0, 4, pupilR ^ B11111111);
#if (EYEBALL_CNT == 2)
        setRow(1, 3, pupilR ^ B11111111);
        setRow(1, 4, pupilR ^ B11111111);
#endif
        nextAnimTime = currTime + 50 + specialDelay;
        if (currReTime == 0 && specialDelay)
        {
            specialDelay -= 10;
        }
        animIndex++;
        if (animIndex == 5)
        {
            animLvlIndex++;
            animIndex = 0;
        }
        break;
    case 4:
        pupilR = pupilR >> 1;
        if (animIndex < 2)
            pupilR |= B10000000;
        setRow(0, 3, pupilR ^ B11111111);
        setRow(0, 4, pupilR ^ B11111111);
#if (EYEBALL_CNT == 2)
        setRow(1, 3, pupilR ^ B11111111);
        setRow(1, 4, pupilR ^ B11111111);
#endif
        animIndex++;
        if (currReTime == (animReTimes - 1))
        {
            specialDelay += 10;
        }
        if (animIndex == 5)
        {
            currReTime++;
            if (currReTime < animReTimes)
            {
                animLvlIndex = 3;
                animIndex = 0;
            }
            else
            {
                animLvlIndex++;
                animIndex = 0;
            }
        }
        nextAnimTime = currTime + 50 + specialDelay;
        break;
    case 5:
        nextAnimTime = currTime + 500;
        nextAnim();
        break;
    }

}
