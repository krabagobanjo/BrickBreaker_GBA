typedef unsigned short u16;

#define REG_DISPCNT *(u16 *)0x4000000
#define MODE3 3
#define BG2_ENABLE (1<<10)
#define COLOR(r,g,b) ((r) | (g) << 5 | (b) << 10)
#define RED COLOR(31,0,0)
#define WHITE COLOR(31,31,31)
#define BLUE COLOR(0, 0, 31)
#define GREEN COLOR(0, 31, 0)
#define BLACK 0
#define OFFSET(r,c) ((r)*240+(c))
//#define OFFSET(r, c, rowlen)  ((r)*(rowlen)+(c))

#define BUTTON_A		(1<<0)
#define BUTTON_B		(1<<1)
#define BUTTON_SELECT		(1<<2)
#define BUTTON_START		(1<<3)
#define BUTTON_RIGHT		(1<<4)
#define BUTTON_LEFT		(1<<5)
#define BUTTON_UP		(1<<6)
#define BUTTON_DOWN		(1<<7)
#define BUTTON_R		(1<<8)
#define BUTTON_L		(1<<9)
#define KEY_DOWN_NOW(key)  (~(BUTTONS) & key)
#define BUTTONS *(volatile unsigned int *)0x4000130
#define SCANLINECOUNTER *(volatile unsigned short *)0x4000006

void setPixel(int x, int y, u16 color);
void drawRect(int x, int y, int width, int height, u16 color);
void drawHollowRect(int x, int y, int width, int height, u16 color);
void plotLine(int x0, int y0, int x1, int y1, u16 color);
void drawCircle(int x, int y, int rad, u16 color);
void fillCircle(int x0, int y0, int radius, u16 color);
void delay(int n);
extern const unsigned char fontdata_6x8[12288];
void drawChar(int row, int col, char ch, unsigned short color);
void drawString(int row, int col, char *str, unsigned short color);
void waitForVblank();
int collidesWith(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
int getRow(int x);
int getCol(int y);

