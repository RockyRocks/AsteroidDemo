#ifndef __MAINGAMESTATE_H
#define __MAINGAMESTATE_H

#include "..\..\common\StateManager\BaseState.h"
#include "..\..\common\logger\Logger.h"
#include "..\..\common\utils\Random.h"
#include "..\physics\CollisionDetector.h"
#include "..\physics\CollisionPrimitives.h"
#include "..\GameConstants.h"

#include "..\objects\Player.h"
#include "..\objects\Enemy.h"
#include "..\objects\Laser.h"
#include "..\objects\Asteroid.h"
#include "..\objects\Bullet.h"
#include "..\AsteroidSettings.h"

struct Level
{
	// increase enemies max speed & acceleration each level
	float EnemyMaxSpeed;
	float EnemyAcceleration;
	int Points;
};

struct Round
{
	unsigned int NumOfEnemies;
	Level rLevels[6];
};


class IEntity;
class IController;
class IScene;
class ISoundSystem;

class MainGameState : public BaseState
{
public:
	MainGameState(const char * name);
	virtual ~MainGameState();

	virtual void start();
	virtual void stop();
	virtual void update();
	virtual void load();
	virtual void unload();
	virtual void render(IRenderer *renderer);

	virtual void processInput();

	void setNewGame(bool ng, GameSettings set);

	// The enemy id *should* always be the first parameter to the function
	void enemyDestroyedByBullet(IEntity *pEnemy, IEntity *pBullet);
	void enemyDestroyedByPlayer(IEntity *pEnemy, IEntity *pPlayer);
	void playerDestroyedByEnemy(IEntity *pPlayer);
	void AsteroidDestroyedByPlayer(IEntity *pAsteroid,IEntity *pPlayer);
	void AsteroidDestroyedByBullet(IEntity *pAsteroid, IEntity *pBullet);
private:
	
	// reset to the beginning state
	void reset();

	// updates the player scores & related score GUI
	void updateScores();
	void addPlayer1Weapons();
	void addPlayer2Weapons();
	void addEnemyWeapons();
	void changeRound();
	void changeLevel();

	// updates the game logic
	void updateGameLogic();

	void checkAsteroids();
	void checkLevel();
	void checkPlayers();

	void detectCollisions();

	// handles the collisions for our game
	void handleCollision(IEntity *ent1, IEntity *ent2);
	
private:
	GLuint m_Tex;
	Random m_Rng;
	bool m_bNewGame;

	// 9 rounds, with 6 levels each
	Round m_Round[9];
	// 9 rounds = 10 enemies (because we're starting from 2 enemies each round)
	IEntity * m_pEnemyArray[10];

	typedef std::vector<CollisionPrimitive*> CollisionPrimitiveList;
	CollisionPrimitiveList m_ColPrimList;

	float m_PlayWidth;
	float m_PlayHeight;
};

#endif