//Jayden Gardiner

#ifndef HUMANS_H
#define HUMANS_H

typedef struct player {
	int xposition;
	int yposition;
	int lives;
} Player;

typedef struct saxon1 {
	int xposition;
	int yposition;
	int alive;
} Saxon1;

typedef struct saxon2 {
	int xposition;
	int yposition;
	int alive;
} Saxon2;

Player player;
Saxon1 saxon1;
Saxon2 saxon2;

void init_player();
void init_saxon1();
void init_saxon2();
#endif
