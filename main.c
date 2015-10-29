// Jayden Gardiner
// Main method for game

#include "myLib.h"
#include <stdlib.h>
#include <stdio.h>
#include "gameover.h"
#include "startscreen.h"
#include "humans.h"
#include "playa.h"
#include "saxonman.h"
#include "LivesImg.h"
#include "one.h"
#include "two.h"
#include "three.h"
#include <string.h>

int frame = 0;
int frame2 = 0;

//Initalises player and two saxon men at a time
void init() {
	init_player();
	init_saxon1();
	init_saxon2();
}

//Checks if there is a collision between the player and a saxon or the exploding wall
//If there is a collision, blood will fill the screen
int checkCollision() {
	if ((player.xposition >= 5 && player.xposition <= 60 && player.yposition >= 45 && player.yposition <= 85)
		|| (player.xposition >= 75 && player.xposition <= 130 && player.yposition >= 45 && player.yposition <= 85)
		|| (player.xposition >= 145 && player.xposition <= 200 && player.yposition >= 45 && player.yposition <= 85)
		|| (player.xposition >= saxon1.xposition - 30 && player.xposition <= saxon1.xposition + 30 && player.yposition >= saxon1.yposition - 30 && player.yposition <= saxon1.yposition + 30)
		|| (player.xposition >= saxon2.xposition - 30 && player.xposition <= saxon2.xposition + 30 && player.yposition >= saxon2.yposition - 30 && player.yposition <= saxon2.yposition + 30) ) {
		drawRect(0, 0, 240, 160, RGB(31, 0, 0));
		blankScreen();
		return 1;
	}
	return 0;
}

//Checks if an attack hits the target
int checkAttackCollision(int row, int col) {
	if (col >= saxon1.xposition - 30 && col <= saxon1.xposition + 30 && row >= saxon1.yposition && row <= saxon1.yposition + 60) {
		return 1;
	} else if (col >= saxon2.xposition - 30 && col <= saxon2.xposition + 30 && row >= saxon2.yposition && row <= saxon2.yposition + 60) {
		return 2;
	}
	return 0;
}

//Resets the game for when a player dies
void nextLife() {
	player.lives--;
	saxon1.xposition = 30;
	saxon1.yposition = 20;
	saxon1.alive = 1;
	saxon2.xposition = 170;
	saxon2.yposition = 20;
	saxon2.alive = 1;
	player.xposition = 100;
	player.yposition = 120;
	frame = 0;
	frame2 = 0;
}

int main(void) {

	*(u16 *) REG_DISPCNT = 1027;
	int start = 0;
	init();

	while (1) {
		waitforVBlank();
		if (!start) {
			drawImage3(0, 0, 240, 160, startscreen);
			init();
		} else {
			blankScreen();
			frame++;

			//If game over
			if (player.lives == 0) {
				drawImage3(0, 0, 240, 160, gameover);
				if (KEY_DOWN_NOW(BUTTON_SELECT) || KEY_DOWN_NOW(BUTTON_START)) {
					start = 0;
				}
				frame = 0;
				frame2 = 0;
				continue;
			}

			//Writes the number of lives remaining -> Brandon Whitehead said on Piazza I could use DMA rather than drawString
			drawImage3(5, 10, 50, 20, LivesImg);
			if (player.lives == 3) {
				drawImage3(5, 60, 15, 20, three);
			} else if (player.lives == 2) {
				drawImage3(5, 60, 15, 20, two);
			} else if (player.lives == 1) {
				drawImage3(5, 60, 15, 20, one);
			}
			
			frame++;
			frame2++;

			//Draw the player
			drawImage3(player.yposition, player.xposition, 30, 30, playa);

			//Draws the Saxons
			if (saxon1.alive) {
				drawImage3(saxon1.yposition, saxon1.xposition, 30, 30, saxonman);
			}
			if (saxon2.alive) {
				drawImage3(saxon2.yposition, saxon2.xposition, 30, 30, saxonman);
			}
			
			if (!saxon1.alive) {
				saxon1.yposition = 20;
				saxon1.xposition = 30;
				drawImage3(saxon1.yposition, saxon1.xposition, 30, 30, saxonman);
				saxon1.alive = 1;
				frame = 0;
			}
			if (!saxon2.alive) {
				saxon2.yposition = 20;
				saxon2.xposition = 170;
				drawImage3(saxon2.yposition, saxon2.xposition, 30, 30, saxonman);
				saxon2.alive = 1;
				frame2 = 0;
			}

			//Draws the exploding walls
			drawRect(75, 35, 25, 10, RGB(31, 0, 0));
			drawRect(75, 105, 25, 10, RGB(31, 0, 0));
			drawRect(75, 175, 25, 10, RGB(31, 0, 0));

			//Movement of the Saxons
			if (frame > 0 && frame <= 60) {
				saxon1.xposition--;
			}
			if (frame > 30 && frame <= 170) {
				saxon1.yposition++;
			}
			if (frame > 170 && frame <= 580) {
				saxon1.xposition++;
			}
			if (frame > 580 && frame <= 740) {
				saxon1.yposition--;
			}
			if (frame > 740 && frame <= 1090) {
				saxon1.xposition--;
			}
			if (frame > 1080 && frame < 1100) {
				saxon1.yposition++;
			}

			if (frame2 > 0 && frame2 <= 40) {
				saxon2.xposition++;
			}

			if (frame2 > 40 && frame2 <= 150) {
				saxon2.yposition++;
			}

			if (frame2 > 150 && frame2 <= 360) {
				saxon2.xposition--;
			}

			if (frame2 > 360 && frame2 <= 450) {
				saxon2.yposition--;
			}

			if (frame2 > 450 && frame2 <= 620) {
				saxon2.xposition++;
			}
			if (frame2 > 1020 && frame2 < 1047) {
				saxon2.yposition--;
			}

			//Resets when it hits a certain counter
			if (frame == 1100) {
				frame = 0;
			}
			if (frame2 == 1100) {
				frame2 = 0;
			}

			//Movement
			if (KEY_DOWN_NOW(BUTTON_LEFT)) {
				if (player.xposition > 0 && checkCollision() == 0) player.xposition--;
				else if (checkCollision() == 1) nextLife();
			} else if (KEY_DOWN_NOW(BUTTON_RIGHT)) {
				if (player.xposition < 210 && checkCollision() == 0) player.xposition++;
				else if (checkCollision() == 1) nextLife();
			} else if (KEY_DOWN_NOW(BUTTON_UP)) {
				if (player.yposition > 0 && checkCollision() == 0) player.yposition--;
				else if (checkCollision() == 1) nextLife();
			} else if (KEY_DOWN_NOW(BUTTON_DOWN)) {
				if (player.yposition < 130 && checkCollision() == 0) player.yposition++;
				else if (checkCollision() == 1) nextLife();
			}

			/*
			A -> Z -> left attacks
			B -> X -> right attacks
			L -> A -> down attacks
			R -> S -> up attacks
			*/
			
			//Attacks
			if (KEY_DOWN_NOW(BUTTON_A)) {
				int row = player.yposition;
				int col = player.xposition - 30;
				drawRect(row, col, 30, 30, RGB(31, 31, 0));
				if (checkAttackCollision(row, col) != 0) {
					if (checkAttackCollision(row, col) == 1) {
						saxon1.alive = 0;
						frame = 0;				
					} else if (checkAttackCollision(row, col) == 2) {
						saxon2.alive = 0;
						frame2 = 0;					
					}
				}				
			}
			if (KEY_DOWN_NOW(BUTTON_B)) {
				int row = player.yposition;
				int col = player.xposition + 30;
				drawRect(row, col, 30, 30, RGB(31, 31, 0));
				if (checkAttackCollision(row, col) != 0) {
					if (checkAttackCollision(row, col) == 1) {
						saxon1.alive = 0;
						frame = 0;				
					} else if (checkAttackCollision(row, col) == 2) {
						saxon2.alive = 0;
						frame2 = 0;					
					}
				}
			}
			if (KEY_DOWN_NOW(BUTTON_L)) {
				int row = player.yposition + 30;
				int col = player.xposition;
				drawRect(row, col, 30, 30, RGB(31, 31, 0));
				if (checkAttackCollision(row, col) != 0) {
					if (checkAttackCollision(row, col) == 1) {
						saxon1.alive = 0;
						frame = 0;				
					} else if (checkAttackCollision(row, col) == 2) {
						saxon2.alive = 0;
						frame2 = 0;					
					}
				}
			}
			if (KEY_DOWN_NOW(BUTTON_R)) {
				int row = player.yposition - 30;
				int col = player.xposition;
				drawRect(row, col, 30, 30, RGB(31, 31, 0));
				if (checkAttackCollision(row, col) != 0) {
					if (checkAttackCollision(row, col) == 1) {
						saxon1.alive = 0;
						frame = 0;			
					} else if (checkAttackCollision(row, col) == 2) {
						saxon2.alive = 0;
						frame2 = 0;					
					}
				}
			}


		}

		//Resets or begins the game
		if (KEY_DOWN_NOW(BUTTON_START)) {
			start = 1;
		} else if (KEY_DOWN_NOW(BUTTON_SELECT)) {
			start = 0;
			frame = 0;
			frame2 = 0;
		}
	}
}
