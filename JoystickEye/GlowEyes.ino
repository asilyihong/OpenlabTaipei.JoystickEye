/* This method pulsates eye (changes LED brightness) */
void glowEyes(int times)
{
    for (int t=0; t<times; t++)
    {
        for (int i=2; i<=8; i++)
        {
            lc.setIntensity(0,i);
            lc.setIntensity(1,i);
            delay(50);
        }
        delay(250);
        for (int i=7; i>=1; i--)
        {
            lc.setIntensity(0,i);
            lc.setIntensity(1,i);
            delay(25);
        }
        delay(150);
    }
    nextAnim();
}
