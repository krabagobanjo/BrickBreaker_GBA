#include "headings.h"

//collision detection
int collidesWith(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
    if (x2 <= x1 && x1<= x2+w2 && y2 <= y1 && y1 <= y2 + y2)
    {
        return 1;
    }
    else
    {
        return 0;
    }   
}

//vblank
void waitForVblank()
{
	while(*(volatile unsigned short *)0x4000006 > 160);
	while(*(volatile unsigned short *)0x4000006 < 160);
}


//get row of ball
int getRow(int x)
{
    if (x < 22) return -1;
    else if (x > 21 && x < 40) return 0;
    else if (x>39 && x<51) return 1;
    else if (x>52 && x<62) return 2;
    else if (x>63 && x<73) return 3;
    else if (x>74 && x<84) return 4;
    else if (x>83 && x<95) return 5;
    else return 6;
}


//get column of ball
int getCol(int y)
{
    if(y<45) return -1;
    else if(y>44 && y<71) return 0;
    else if(y>70 && y<92) return 1;
    else if(y>91 && y<113) return 2;
    else if(y>112 && y<134) return 3;
    else if(y>133 && y<155) return 4;
    else if(y>154 && y<176) return 5;
    else if(y>175 && y<197) return 6;
    else return 7;
}
