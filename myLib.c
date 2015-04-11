// Jayden Gardiner

#include "myLib.h"

u16 *videoBuffer = (u16 *) 0x6000000;

void setPixel(int r, int c, u16 color) {
	videoBuffer[240 * r + c] = color;
}

void drawRect(int r, int c, int width, int height, u16 color) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			setPixel(r + i, j + c, color);
		}
	}
}

void delay(int length) {
	for (volatile int i = 0; i < (length * 1000); i++) {
	}
}


void waitforVBlank() {
	u16 *X = SCANLINECOUNTER;
	while (*X > 160) {;}
	while (*X <= 160) {;}
}

void blankScreen() {
	REG_DMA3SAD = (vu32) RGB(0, 0, 0);
	REG_DMA3DAD = (vu32) videoBuffer;
	REG_DMA3CNT = 38400 | DMA_ON;
}

void drawImage3(int r, int c, int width, int height, const u16* image) {
	for (u16 i = 0; i < height; i++) {
		REG_DMA3SAD = (vu32) (image + (width * i));
		REG_DMA3DAD = (vu32) (videoBuffer + (240 * (r + i) + c));
		REG_DMA3CNT = width | DMA_ON;
	}
}
