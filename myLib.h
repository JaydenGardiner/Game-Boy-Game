// Jayden Gardiner

#ifndef MYLIB_H
#define MYLIB_H

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef volatile unsigned char vu8;
typedef volatile unsigned short vu16;
typedef volatile unsigned int vu32;

#define REG_DISPCNT 0x4000000
#define RGB(r, g, b) ((r) | ((g) << 5) | ((b) << 10))
#define SCANLINECOUNTER ((unsigned short *) 0x4000006)
#define MAXROW 160
#define MAXCOL 240
#define OFFSET(r, c, numcols) ((r) * (numcols) + (c))

#define BUTTONS (*(unsigned int *) 0x4000130)
#define BUTTON_A (1 << 0)
#define BUTTON_B (1 << 1)
#define BUTTON_SELECT (1 << 2)
#define BUTTON_START (1 << 3)
#define BUTTON_RIGHT (1 << 4)
#define BUTTON_LEFT (1 << 5)
#define BUTTON_UP (1 << 6)
#define BUTTON_DOWN (1 << 7)
#define BUTTON_R (1 << 8)
#define BUTTON_L (1 << 9)
#define KEY_DOWN_NOW(key) (~(BUTTONS) & key)

#define REG_DMA3SAD *(vu32*) 0x40000D4
#define REG_DMA3DAD *(vu32*) 0x40000D8
#define REG_DMA3CNT *(vu32*) 0x40000DC
#define DMA_ON (1 << 31)

void setPixel(int r, int c, u16 color);
void drawRect(int r, int c, int width, int height, u16 color);
void delay(int length);
void waitforVBlank();
void drawImage3(int r, int c, int width, int height, const u16* image);
void blankScreen();

extern u16 *videoBuffer;
#endif
