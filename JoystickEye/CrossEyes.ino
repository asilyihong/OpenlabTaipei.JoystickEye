/*
   This method crosses eyes
 */
byte pupilR = eyePupil;
byte pupilL = eyePupil;
void crossEyes()
{
    switch(animLvlIndex)
    {
    case 0:
        pupilR = eyePupil;
        pupilL = eyePupil;
        moveEyesInit(0, 0, 50, true);
        break;
    case 1:
        moveEyesLoop();
        break;
    case 2:
        pupilR = pupilR >> 1;
        setRow(0, 3, pupilR ^ B11111111);
        setRow(0, 4, pupilR ^ B11111111);
#if (EYEBALL_CNT == 2)
        pupilL = pupilL << 1;
        setRow(1, 3, pupilL ^ B11111111);
        setRow(1, 4, pupilL ^ B11111111);
#endif
        nextAnimTime = currTime + 100;
        animIndex++;
        if (animIndex == 2)
        {
            nextAnimTime += 2000;
            animLvlIndex++;
            animIndex = 0;
        }
        break;
    case 3:
        pupilR = pupilR << 1;
        setRow(0, 3, pupilR ^ B11111111);
        setRow(0, 4, pupilR ^ B11111111);
#if (EYEBALL_CNT == 2)
        pupilL = pupilL >> 1;
        setRow(1, 3, pupilL ^ B11111111);
        setRow(1, 4, pupilL ^ B11111111);
#endif
        nextAnimTime = currTime + 100;
        animIndex++;
        if (animIndex == 2)
        {
            nextAnim();
        }
        break;
    }
}
