#ifndef __GAMESETTINGS_H
#define __GAMESETTINGS_H

static enum DIFFICULTY
{
	NORMAL,
	HARD
};

struct GameSettings
{
	unsigned int NumPlayers;
	DIFFICULTY Difficulty;
};

#endif