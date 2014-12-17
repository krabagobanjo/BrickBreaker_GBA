#include "headings.h"
#include "font.c"
extern const unsigned char fontdata_6x8[12288];
u16* videoBuffer = (u16 *)0x6000000;

//All functions are relatively self explanatory.

void setPixel(int x, int y, u16 color)
{
		*(videoBuffer + OFFSET(x, y)) = color;
}

void drawChar(int row, int col, char ch, unsigned short color)
{
	int r, c;
	for(r=0; r<8; r++)
	{
		for(c=0; c<6; c++)
		{
			if(fontdata_6x8[((r)*(6)+(c))+ch*48])
			{
				setPixel(row+r, col+c, color);
			}
		}
	}
}

void drawString(int row, int col, char *str, unsigned short color)
{
	while(*str)
	{
		drawChar(row, col, *str++, color);
		col +=6;
	}
}

void drawRect(int x, int y, int width, int height, u16 color)
{
	for(int i=0; i<height; i++)
	{
		for(int j=0; j<width; j++)
		{
			setPixel(x+j, y+i, color);
		}
	}
}

void drawHollowRect(int x, int y, int width, int height, u16 color)
{
    for(int i=x; i<=x+width; i++)
    {
        setPixel(i, y, color);
        setPixel(i, y+height, color);
    }
    for(int j=y; j<=y+height; j++)
    {
        setPixel(x, j, color);
        setPixel(x+width, j, color);
    }
}

void fillCircle(int x0, int y0, int radius, u16 color)
{
    int x = radius;
    int y = 0;
    int dx = 1 - (radius << 1);
    int dy = 0;
    int radiusError = 0;

    while (x >= y)
    {
        for (int i = x0 - x; i <= x0 + x; i++)
        {
            setPixel(i, y0 + y, color);
            setPixel(i, y0 - y, color);
        }
        for (int i = x0 - y; i <= x0 + y; i++)
        {
            setPixel(i, y0 + x, color);
            setPixel(i, y0 - x, color);
        }
        y++;
        radiusError += dy;
        dy += 2;
        if (((radiusError << 1) + dx) > 0)
        {
            x--;
            radiusError += dx;
            dx += 2;
        }
    }
}

void plotLine(int x0, int y0, int x1, int y1, u16 color)
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    int D = (dy << 1) - dx;
    setPixel(x0, y0, color);
    int y = y0;
    
    if (x0 == x1)
    {
        for (int i = y0; i < y1; i++) setPixel(x0, i, color);
    }
    else
    {
        for (int i=x0+1; i <= x1; i++)
        {
            if (D > 0)
            {
                y++;
                setPixel(i,y,color);
                D = D + ((dy << 1) - (dx << 1));
            }
            else
            {
                setPixel(i,y,color);
                D = D + (dy << 1);
            }
        }
    }
}

void drawCircle(int xc, int yc, int rad, u16 color)
{
    int x = 0;
    int y = rad;
    int radErr = 1-x;
    while (x < y)
    {
        if (radErr < 0)
        {
            x++;
            radErr = radErr + (x<<1) + 1;
        }
        else
        {
            x++;
            y--;
            radErr = radErr + (x<<1) - (y<<1) + 1;
        }
        setPixel(x+xc, y+yc, color);
        setPixel(y+xc, x+yc, color);
        setPixel(-x+xc, y+yc, color);
        setPixel(-y+xc, x+yc, color);
        setPixel(-x+xc, -y+yc, color);
        setPixel(-y+xc, -x+yc, color);
        setPixel(x+xc, -y+yc, color);
        setPixel(y+xc, -x+yc, color);
    }
}

void delay(int n)
{
	int i;
	volatile int x = 0;
	for(i=0; i<n*10000; i++)
	{
		x++;
	}
}



