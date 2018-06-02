#ifndef __CONSTANTS_H
#define __CONSTANTS_H

#include <vector>
#include "..\common\utils\HashedString.h"
#include "..\common\utils\Mathlib.h"

static const int MAX_AsteroidS = 8;
static const int MAX_LEVELS = 6;
static const int MAX_ROUNDS = 10;
// Entity ID constants
// Player

static const HashedString ID_PLAYER1("player1");
static const HashedString ID_PLAYER2("player2");

// Bullets
static const HashedString ID_BULLET1_A("bullet1_a"); // p1 bullet
static const HashedString ID_BULLET1_B("bullet1_b"); // p1 bullet
static const HashedString ID_BULLET1_C("bullet1_c"); // p1 bullet
static const HashedString ID_BULLET1_D("bullet1_d"); // p1 bullet

static const HashedString ID_BULLET2_A("bullet2_a"); // p2 bullet
static const HashedString ID_BULLET2_B("bullet2_b"); // p2 bullet
static const HashedString ID_BULLET2_C("bullet2_c"); // p2 bullet
static const HashedString ID_BULLET2_D("bullet2_d"); // p2 bullet

// Laser
static const HashedString ID_LASER("laser");
static const HashedString ID_LASER1("laser1");
static const HashedString ID_LASER2("laser2");
static const HashedString ID_LASER3("laser3");
static const HashedString ID_LASER4("laser4");
static const HashedString ID_LASER5("laser5");
static const HashedString ID_LASER6("laser6");
static const HashedString ID_LASER7("laser7");
static const HashedString ID_LASER8("laser8");
static const HashedString ID_LASER9("laser9");
static const HashedString ID_LASER10("laser10");

// Enemies
static const HashedString ID_ENEMY("enemy");
static const HashedString ID_ENEMY1("enemy1");
static const HashedString ID_ENEMY2("enemy2");
static const HashedString ID_ENEMY3("enemy3");
static const HashedString ID_ENEMY4("enemy4");
static const HashedString ID_ENEMY5("enemy5");
static const HashedString ID_ENEMY6("enemy6");
static const HashedString ID_ENEMY7("enemy7");
static const HashedString ID_ENEMY8("enemy8");
static const HashedString ID_ENEMY9("enemy9");
static const HashedString ID_ENEMY10("enemy10");

static const HashedString ID_ENEMIES[10] = { ID_ENEMY1,ID_ENEMY2,ID_ENEMY3,ID_ENEMY4,ID_ENEMY5,
											ID_ENEMY6,ID_ENEMY7,ID_ENEMY8,ID_ENEMY9,ID_ENEMY10};

// Asteroids
static const HashedString ID_Asteroid("Asteroid");
static const HashedString ID_Asteroid1("Asteroid1");
static const HashedString ID_Asteroid2("Asteroid2");
static const HashedString ID_Asteroid3("Asteroid3");
static const HashedString ID_Asteroid4("Asteroid4");
static const HashedString ID_Asteroid5("Asteroid5");
static const HashedString ID_Asteroid6("Asteroid6");
static const HashedString ID_Asteroid7("Asteroid7");
static const HashedString ID_Asteroid8("Asteroid8");

static const HashedString ID_AsteroidS[MAX_AsteroidS] = { ID_Asteroid1, ID_Asteroid2, ID_Asteroid3, ID_Asteroid4,
													  ID_Asteroid5, ID_Asteroid6, ID_Asteroid7, ID_Asteroid8 };

// States
static const HashedString ID_SETUP_STATE("setup_state");
static const HashedString ID_TITLE_STATE("title_state");
static const HashedString ID_MAIN_STATE("maingame_state");
static const HashedString ID_OPTION_STATE("options_state");
static const HashedString ID_SCORE_STATE("score_state");
static const HashedString ID_EXIT_TO_TITLE_STATE("exit2title_state");
static const HashedString ID_EXIT_TO_WINDOWS_STATE("exit2windows_state");

// UI Page names
static const HashedString ID_TITLE_PAGE("title_page");
static const HashedString ID_MAIN_PAGE("maingame_page");
static const HashedString ID_OPTION_PAGE("options_page");
static const HashedString ID_SCORE_PAGE("score_page");
static const HashedString ID_EXIT_TO_TITLE_PAGE("exit2title_page");
static const HashedString ID_EXIT_TO_WINDOWS_PAGE("exit2windows_page");

// UI Component names
static const HashedString ID_START_CMPNT("start_cmpnt");
static const HashedString ID_SELECT_PLAYER_CMPNT("player_select_cmpnt");
static const HashedString ID_SELECT_DIFFICULTY_CMPNT("diffult_select_cmpnt");
static const HashedString ID_OPTIONS_CMPNT("options_cmpnt");
static const HashedString ID_VIEWSCORES_CMPNT("view_scores_cmpnt");
static const HashedString ID_ROUND_CMPNT("round_cmpnt");
static const HashedString ID_SCORE_CMPNT("score_cmpnt");
static const HashedString ID_SCORE2_CMPNT("score_p2_cmpnt");
static const HashedString ID_EXIT_CMPNT("exit_cmpnt");
static const HashedString ID_GAMEOVER_CMPNT("gameover_cmpnt");

// Game event types
static const HashedString ID_EVT_STATE_CHANGE("change_state");
static const HashedString ID_EVT_NEW_GAME("new_game");

// Constant Strings
static const HashedString ID_ROUND1("ROUND 1");
static const HashedString ID_ROUND2("ROUND 2");
static const HashedString ID_ROUND3("ROUND 3");
static const HashedString ID_ROUND4("ROUND 4");
static const HashedString ID_ROUND5("ROUND 5");
static const HashedString ID_ROUND6("ROUND 6");
static const HashedString ID_ROUND7("ROUND 7");
static const HashedString ID_ROUND8("ROUND 8");
static const HashedString ID_ROUND9("ROUND 9");
static const HashedString ID_ROUND10("ROUND 10");
static const HashedString ID_GAMEOVER("GAME OVER");

// Player firing
static const HashedString ID_PLAYER_FIRE("player_fire");

#endif