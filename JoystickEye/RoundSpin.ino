Coordinate_t roundPos[] = {{2, -1}, {1, -2}, {0, -2}, {-1, -2}, {-2, -1}, {-2, 0}, {-2, 1}, {-1, 2}, {0, 2}, {1, 2}, {2, 1}, {2, 0}};

void roundSpinInit(int times)
{
    animReTimes = times;
    specialDelay = 40;
    animLvlIndex = 0;
    animIndex = 0;
    currReTime = 0;
}

void roundSpin()
{
    switch(animLvlIndex)
    {
    case 0:
        moveEyesInit(2, 0, 50, true);
        break;
    case 1:
        moveEyesLoop();
        break;
    case 2:
        nextAnimTime = currTime + 500;
        animLvlIndex++;
        break;
    case 3:
        displayEyes(roundPos[animIndex].x, roundPos[animIndex].y);
        animIndex++;
        if (currReTime == 0 && specialDelay)
        {
            specialDelay -= 10;
        }
        else if (currReTime == (animReTimes - 1) && (animIndex > 5))
        {
            specialDelay += 10;
        }

        if (animIndex == 12)
        {
            currReTime++;
            if (currReTime < animReTimes)
            {
                animIndex = 0;
            }
            else
            {
                animLvlIndex++;
            }
        }
        nextAnimTime = currTime + 40 + specialDelay;
        break;
    case 4:
        nextAnimTime = currTime + 500;
        nextAnim();
        break;
    }
}
