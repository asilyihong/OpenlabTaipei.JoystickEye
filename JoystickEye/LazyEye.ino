/* This method lowers and raises right pupil only */
void lazyEye()
{
    switch(animLvlIndex)
    {
    case 0:
        pupilR = eyePupil;
        pupilL = eyePupil;
        moveEyesInit(0, 1, 50, true);
        break;
    case 1:
        moveEyesLoop();
        break;
    case 2:
        nextAnimTime += 150;
        animLvlIndex++;
        animIndex = 0;
        break;
    case 3:
        /* lower left pupil slowly */
        setRow(0, animIndex+2, eyeBall[animIndex+2]);
        setRow(0, animIndex+3, eyeBall[animIndex+3] ^ eyePupil);
        setRow(0, animIndex+4, eyeBall[animIndex+4] ^ eyePupil);
        nextAnimTime = currTime + 150;
        animIndex++;
        if (animIndex == 3)
        {
            nextAnimTime += 1000;
            animLvlIndex++;
            animIndex = 0;
        }
        break;
    case 4:
        /* raise left pupil quickly */
        setRow(0, 4-animIndex, eyeBall[4-animIndex] ^ eyePupil);
        setRow(0, 5-animIndex, eyeBall[5-animIndex] ^ eyePupil);
        setRow(0, 6-animIndex, eyeBall[6-animIndex]);
        nextAnimTime = currTime + 25;
        animIndex++;
        if (animIndex == 3)
        {
            nextAnim();
        }
        break;
    }
}
