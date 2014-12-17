#include "headings.h"

//defines a brick
struct brick
{
    int x;
    int y;
    int width;
    int height;
    int removed;
};

//defines the ball
struct ball
{
    int posX;
    int posY;
    int size;
    int dx;
    int dy;
    int col;
    int row;
    
};

//defines the paddle used by the player
struct paddle
{
    int paddleX;
    int paddleY;
};



int main()
{
	REG_DISPCNT = MODE3 | BG2_ENABLE;
	struct brick bricks[6][7];
    struct ball theBall;
    struct paddle thePaddle;
    theBall.posX = 140;
    theBall.posY = 120;
    theBall.size = 5;
    thePaddle.paddleX = 158;
    thePaddle.paddleY = 110;
    theBall.dx = 0;
    theBall.dy = 0;
    theBall.row = getRow(theBall.posX);
    theBall.col = getCol(theBall.posY);
    drawRect(thePaddle.paddleX, thePaddle.paddleY, 3, 30, RED);
    int numRem=0;
    int ex = 29;
    int why = 50;
    //create array of bricks, accessed by row/col
    for(int i=0; i<6; i++)
    {
        why = 50;
        for(int j=0; j<7; j++)
        {
            bricks[i][j].x = ex;
            bricks[i][j].y = why;
            bricks[i][j].width = 10;
            bricks[i][j].height = 20;
            bricks[i][j].removed = 0;
            drawRect(ex, why, 10, 20, RED);
            why+=21;
        }
        ex+=11;
    }
    ex = 29;
    int running = 0;
	while(1)
	{
		if(KEY_DOWN_NOW(BUTTON_A) && !running)
		{
            theBall.dy = 1;
            theBall.dx = -1;
            running=1;
		}
		if(KEY_DOWN_NOW(BUTTON_LEFT))
        {
			if(thePaddle.paddleY>0) thePaddle.paddleY--;
        }
        if(KEY_DOWN_NOW(BUTTON_RIGHT))
        {
            if(thePaddle.paddleY<239-30+1) thePaddle.paddleY++;
        }
        //reset
        if(KEY_DOWN_NOW(BUTTON_B))
        {
        	struct brick bricks[6][7];
            struct ball theBall;
            struct paddle thePaddle;
            theBall.posX = 140;
            theBall.posY = 120;
            theBall.size = 5;
            thePaddle.paddleX = 158;
            thePaddle.paddleY = 110;
            theBall.dx = 0;
            theBall.dy = 0;
            theBall.row = getRow(theBall.posX);
            theBall.col = getCol(theBall.posY);
            drawRect(thePaddle.paddleX, thePaddle.paddleY, 3, 30, RED);
            numRem=0;
            ex = 29;
            why = 50;
            for(int i=0; i<6; i++)
            {
                why = 50;
                for(int j=0; j<7; j++)
                {
                    bricks[i][j].x = ex;
                    bricks[i][j].y = why;
                    bricks[i][j].width = 10;
                    bricks[i][j].height = 20;
                    bricks[i][j].removed = 0;
                    drawRect(ex, why, 10, 20, RED);
                    why+=21;
                }
                ex+=11;
            }
            ex = 29;
            running=0;
        }
        //game logic
        theBall.posX+=theBall.dx;
        theBall.posY+=theBall.dy;
        if(theBall.posX - theBall.size<0) theBall.dx=-theBall.dx;
        if(theBall.posX>159-theBall.size+1 && collidesWith(theBall.posX, theBall.posY, 3, 3, thePaddle.paddleX, thePaddle.paddleY, 3, 30)) theBall.dx=-theBall.dx;
        //you only get one shot
        else if(theBall.posX>159)
        {
            while(!KEY_DOWN_NOW(BUTTON_B))  drawString(100, 50, "YOU LOSE, press B to restart", WHITE);
            drawRect(100, 50, 50, 170, BLACK);
            theBall.posX = 140;
            theBall.posY = 120;
            theBall.size = 5;
            thePaddle.paddleX = 158;
            thePaddle.paddleY = 110;
            theBall.dx = 0;
            theBall.dy = 0;
            theBall.row = getRow(theBall.posX);
            theBall.col = getCol(theBall.posY);
            drawRect(thePaddle.paddleX, thePaddle.paddleY, 3, 30, RED);
            numRem=0;
            ex = 29;
            why = 50;
            for(int i=0; i<6; i++)
            {
                why = 50;
                for(int j=0; j<7; j++)
                {
                    bricks[i][j].x = ex;
                    bricks[i][j].y = why;
                    bricks[i][j].width = 10;
                    bricks[i][j].height = 20;
                    bricks[i][j].removed = 0;
                    drawRect(ex, why, 10, 20, RED);
                    why+=21;
                }
                ex+=11;
            }
            ex = 29;
            running=0;
        }            
        if(theBall.posY - theBall.size<0) theBall.dy=-theBall.dy;
        if(theBall.posY>239-theBall.size+1) theBall.dy=-theBall.dy;
        theBall.col = getCol(theBall.posY);
        theBall.row = getRow(theBall.posX);
        //collides with brick
        if ((theBall.col > -1 && theBall.col < 7) && (theBall.row > -1 && theBall.row < 6))
        {
            if (collidesWith(theBall.posX, theBall.posY, 3, 3, bricks[theBall.row][theBall.col].x, bricks[theBall.row][theBall.col].y, bricks[theBall.row][theBall.col].width, bricks[theBall.row][theBall.col].height) && !bricks[theBall.row][theBall.col].removed)
            {
                bricks[theBall.row][theBall.col].removed = 1;
                drawRect(bricks[theBall.row][theBall.col].x, bricks[theBall.row][theBall.col].y, bricks[theBall.row][theBall.col].width, bricks[theBall.row][theBall.col].height, BLACK);
                theBall.dx=-theBall.dx;
                theBall.dy=-theBall.dy;
                numRem++;
            }
        }
        //you somehow won
        if (numRem==42)
        {
            while(!KEY_DOWN_NOW(BUTTON_B))  drawString(100, 50, "YOU WIN! Press B to restart", WHITE);
            drawRect(100, 50, 50, 170, BLACK);
            theBall.posX = 140;
            theBall.posY = 120;
            theBall.size = 5;
            thePaddle.paddleX = 158;
            thePaddle.paddleY = 110;
            theBall.dx = 0;
            theBall.dy = 0;
            theBall.row = getRow(theBall.posX);
            theBall.col = getCol(theBall.posY);
            drawRect(thePaddle.paddleX, thePaddle.paddleY, 3, 30, RED);
            numRem=0;
            ex = 29;
            why = 50;
            for(int i=0; i<6; i++)
            {
                why = 50;
                for(int j=0; j<7; j++)
                {
                    bricks[i][j].x = ex;
                    bricks[i][j].y = why;
                    bricks[i][j].width = 10;
                    bricks[i][j].height = 20;
                    bricks[i][j].removed = 0;
                    drawRect(ex, why, 10, 20, RED);
                    why+=21;
                }
                ex+=11;
            }
            ex = 29;
            running=0;
        }
        fillCircle(theBall.posX, theBall.posY, theBall.size, RED);
        drawRect(thePaddle.paddleX, thePaddle.paddleY, 3, 30, RED);
        waitForVblank();
		fillCircle(theBall.posX, theBall.posY, theBall.size, BLACK);
        drawRect(thePaddle.paddleX, thePaddle.paddleY, 3, 30, BLACK);
	}
}
