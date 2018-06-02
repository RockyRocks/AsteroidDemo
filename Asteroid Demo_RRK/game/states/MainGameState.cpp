#include "MainGameState.h"

// Game play parameters for the game
// Hold global pointers to the players for input control
IEntity *g_pPlayer1;
IEntity *g_pPlayer2;

IEntity *g_AsteroidArray[MAX_AsteroidS];
int g_AsteroidCount = MAX_AsteroidS;

int g_EnemyCount;
int g_CurrentRound;
int g_CurrentLevel;

GameSettings g_Settings;

PlayerScore BaseState::m_Player1;
PlayerScore BaseState::m_Player2;

int BaseState::m_nGameMode = 1;  // 1-> Hard mode 0 -> Easy Mode

int g_Player1Score =0;
int g_Player2Score =0;

/* Levels & Rounds
So my idea is just storing a number of enemies in an array, say 10 but for level 1 we would only use
a small number, say 2. Each level has it's own enemy design which we can change and we also set the max velocity of
the enemies (I think they increase in max velocity in the game, they go faster)

Every round we increase the number the number of enemies. So in round 2 it will be 3 enemies each level. Round 3 there are 4, etc.
Until we hit round 10...=]
*/
void MainGameState::load()
{
}

void MainGameState::unload()
{
	// make pointers null so that other
}

MainGameState::MainGameState(const char * name)
: BaseState(name)
{
	// seed the rng
	//m_Rng.setRandomSeed(5);
	g_Player1Score = 0;
	g_Player2Score = 0;
	g_CurrentRound = 1;
	g_CurrentLevel = 1;
	g_EnemyCount = 2;

	int tNumEnemy = g_EnemyCount;
	float tEnemyAccel = 2.0f;
	float tEnemyMaxSpeed = 350.0f;
	int tPoints = 10;

	// setup the levels and rounds
	for(int i=0; i <6; ++i)
	{
		m_Round[i].NumOfEnemies = tNumEnemy;
		for(int j=0; j < 6; ++j)
		{
			//m_Round[i].rLevels[j].EnemyAcceleration = tEnemyAccel;
			m_Round[i].rLevels[j].EnemyMaxSpeed = tEnemyMaxSpeed;
			m_Round[i].rLevels[j].Points = tPoints;

			tPoints += 10;
			tEnemyMaxSpeed += 10.0f;
		}
		tNumEnemy += 1;
		tPoints = 10;
	}

	g_pPlayer1 = NULL;
	g_pPlayer2 = NULL;

	g_Settings.NumPlayers = 1;
	g_Settings.Difficulty = NORMAL;

	m_pController = NULL;
	m_pSoundsystem = NULL;
	m_bHasAlreadyStarted = false;
	m_bNewGame = true;
}

MainGameState::~MainGameState()
{
//	delete g_Laser;
}

void MainGameState::start()
{
	if(!m_bHasAlreadyStarted)
	{
		g_CurrentLevel = 1;

		m_PlayWidth = (float) Engine::GetInstance()->getRenderer()->getViewWidth();
		m_PlayHeight = (float) Engine::GetInstance()->getRenderer()->getViewHeight();

		// Get the pointer to the sound system
		m_pSoundsystem = Engine::GetInstance()->getSoundSystem();

		// create a new controller instance
		m_pController = Engine::GetInstance()->getControllerInput();

		m_Tex = Engine::GetInstance()->getTextureManager()->getTexture("backdrop.bmp");

		Vector2f pos_player1(m_PlayWidth - 50, m_PlayHeight / 2);
		// build the scene 
		// create the entities
		// create a player
		IEntity *ent = new Player(ID_PLAYER1.getStr().c_str(), pos_player1);
		ent->loadVertexList("data\\player1.txt");

		g_pPlayer1 = ent;
		// add player to the scene
		m_Entities.push_back(ent);
		AIEngine::GetInstance()->addPlayer(ent);

		// add bullets for player1
		addPlayer1Weapons();

		// lets make it a 2-player for more fun 
		if(g_Settings.NumPlayers == 2)
		{
			Vector2f pos_player2(50, m_PlayHeight / 2);

			ent = new Player(ID_PLAYER2.getStr().c_str(), pos_player2);
			ent->loadVertexList("data\\player2.txt");
			ent->setAngle(270.0f); // face the other way
			ent->setVisible(true);
			g_pPlayer2 = ent;
			m_Entities.push_back(ent);

			// add bullets for player2
			addPlayer2Weapons();

			// update the player2 score component
			GUI::GUISystem::GetInstance()->GetPage(ID_MAIN_PAGE.getStr())->GetComponent(ID_SCORE2_CMPNT.getStr())->SetLabel("00000");
		}

		// Messy Code for Testing..
		// TODO: I should Really take them from the Asteroid.txt file like the ones i did for other objects -> tuesday morning 
		// Should randomize the spawning like the enemy ships and make their heading proper...
		Vector2f pos(m_PlayWidth / 2-450 , m_PlayHeight/2+350);

		// add some Asteroids & register some as AI targets to enhance game play :)
		// First row of asteroids !
		ent = new Asteroid(ID_Asteroid1.getStr().c_str(), pos);
		g_AsteroidArray[0] = ent;
		m_Entities.push_back(ent);
		//AIEngine::GetInstance()->addTarget(ent);
		
		pos.x += 300;
		ent = new Asteroid(ID_Asteroid2.getStr().c_str(), pos);
		g_AsteroidArray[1] = ent;
		m_Entities.push_back(ent);
		//AIEngine::GetInstance()->addTarget(ent);

		pos.x += 400;
		ent = new Asteroid(ID_Asteroid3.getStr().c_str(), pos);
		g_AsteroidArray[2] = ent;
		m_Entities.push_back(ent);
		//AIEngine::GetInstance()->addTarget(ent);
		
		// Second row collectibles for the enemy ships ! and they are special ones if the enemies fetch 
		// i have to say game over..
		
		pos.x = m_PlayWidth / 2-470;
		pos.y -= 70;
		ent = new Asteroid(ID_Asteroid4.getStr().c_str(), pos);
		g_AsteroidArray[3] = ent;
		ent->setColour(1.0f,0.0f,0.0f,0.0f);
		m_Entities.push_back(ent);
		AIEngine::GetInstance()->addTarget(ent);

		pos.x += 370;
		ent = new Asteroid(ID_Asteroid5.getStr().c_str(), pos);
		g_AsteroidArray[4] = ent;
		ent->setColour(1.0f,0.0f,0.0f,0.0f);
		m_Entities.push_back(ent);
		AIEngine::GetInstance()->addTarget(ent);

		// third row of asteroids !
		pos.x= m_PlayWidth / 2-350;
		pos.y -= 110;
		ent = new Asteroid(ID_Asteroid6.getStr().c_str(), pos);
		g_AsteroidArray[5] = ent;
		m_Entities.push_back(ent);
	    //AIEngine::GetInstance()->addTarget(ent);

		pos.x += 370;
		ent = new Asteroid(ID_Asteroid7.getStr().c_str(), pos);
		g_AsteroidArray[6] = ent;
		m_Entities.push_back(ent);
	    //AIEngine::GetInstance()->addTarget(ent);

		pos.x += 450;
		ent = new Asteroid(ID_Asteroid8.getStr().c_str(), pos);
		g_AsteroidArray[7] = ent;
		m_Entities.push_back(ent);
		//AIEngine::GetInstance()->addTarget(ent);
		

		// create the array of enemies
		for(int e=0; e < 10; ++e)
		{
			float rx = (m_Rng.random() * 16) + (m_PlayWidth);
			float ry = (m_Rng.random() * 16) + (m_PlayHeight);

			float signx = m_Rng.random();
			if(signx < 0.5)
				rx = -rx;
			
			float signy = m_Rng.random();
			if(signy < 0.5)
				ry = -ry;

			// TODO: Change the positions of the enemies so they spawn at random positions OUTSIDE of the game area
			// for now though, we'll spawn them inside the area
			m_pEnemyArray[e] = new Enemy(ID_ENEMIES[e].getStr().c_str(), Vector2f(rx,ry)); 
			m_pEnemyArray[e]->setVisible(false); // make them invisible and let the round state change them
			m_pEnemyArray[e]->forward();
			m_pEnemyArray[e]->setCurrentState(DEAD);

			// add the enemy laser
			IEntity *laser = new Laser(m_pEnemyArray[e]->getPosition(), (m_pEnemyArray[e]->getHeading() * 135));
			laser->setVisible(false);
			laser->setAngle(m_pEnemyArray[e]->getAngle());
			laser->setPosition(m_pEnemyArray[e]->getPosition());
			m_pEnemyArray[e]->addChild(laser);

			m_Entities.push_back(m_pEnemyArray[e]);
			m_Entities.push_back(laser);
		}

		ent = NULL;
	}

	//add events to components
	// select the title screen gui to render
	Engine::GetInstance()->getGuiSystem()->SelectPage(ID_MAIN_PAGE.getStr());	
	
	// start the round
	changeRound();

	m_bHasAlreadyStarted = true;
}

void MainGameState::addPlayer1Weapons()
{
	// create bullets for the player1
	IEntity * ent = new Bullet(ID_BULLET1_A.getStr(), g_pPlayer1->getPosition());
	ent->setVisible(false);
	m_Entities.push_back(ent);
	// add to player as a child, giving the responsibility of updating the bullet's
	// acceleration & velocity to the player.
	g_pPlayer1->addChild(ent);

	ent = new Bullet(ID_BULLET1_B.getStr(), g_pPlayer1->getPosition());
	ent->setVisible(false);
	m_Entities.push_back(ent);
	// add to player
	g_pPlayer1->addChild(ent);

	ent = new Bullet(ID_BULLET1_C.getStr(), g_pPlayer1->getPosition());
	ent->setVisible(false);
	m_Entities.push_back(ent);
	// add to player
	g_pPlayer1->addChild(ent);

	ent = new Bullet(ID_BULLET1_D.getStr(), g_pPlayer1->getPosition());
	ent->setVisible(false);
	m_Entities.push_back(ent);
	// add to player
	g_pPlayer1->addChild(ent);
	// End bullet creation for player1
}

void MainGameState::addPlayer2Weapons()
{
	// create bullets for the player2
	IEntity * ent = new Bullet(ID_BULLET2_A.getStr(), g_pPlayer2->getPosition());
	ent->setVisible(false);
	m_Entities.push_back(ent);
	// add to player as a child, giving the responsibility of updating the bullet's
	// acceleration & velocity to the player.
	g_pPlayer2->addChild(ent);

	ent = new Bullet(ID_BULLET2_B.getStr(), g_pPlayer2->getPosition());
	ent->setVisible(false);
	m_Entities.push_back(ent);
	// add to player
	g_pPlayer2->addChild(ent);

	ent = new Bullet(ID_BULLET2_C.getStr(), g_pPlayer2->getPosition());
	ent->setVisible(false);
	m_Entities.push_back(ent);
	// add to player
	g_pPlayer2->addChild(ent);

	ent = new Bullet(ID_BULLET2_D.getStr(), g_pPlayer2->getPosition());
	ent->setVisible(false);
	m_Entities.push_back(ent);
	// add to player
	g_pPlayer2->addChild(ent);
	// End bullet creation for player2
}

void MainGameState::addEnemyWeapons()
{
}

void MainGameState::changeRound()
{
	GUI::GUI_Component *pComp = GUI::GUISystem::GetInstance()->GetPage(ID_MAIN_PAGE.getStr())->GetComponent(ID_ROUND_CMPNT.getStr());
	// Update the round gui component
	switch(g_CurrentRound)
	{
	case 1:		
		pComp->SetLabel(ID_ROUND1.getStr());
		break;
	case 2:
		pComp->SetLabel(ID_ROUND2.getStr());
		break;
	case 3:
		pComp->SetLabel(ID_ROUND3.getStr());
		break;
	case 4:
		pComp->SetLabel(ID_ROUND4.getStr());
		break;
	case 5:
		pComp->SetLabel(ID_ROUND5.getStr());
		break;
	case 6:
		pComp->SetLabel(ID_ROUND6.getStr());
		break;
	case 7:
		pComp->SetLabel(ID_ROUND7.getStr());
		break;
	case 8:
		pComp->SetLabel(ID_ROUND8.getStr());
		break;
	case 9:
		pComp->SetLabel(ID_ROUND9.getStr());
		break;
	case 10:
		pComp->SetLabel(ID_ROUND10.getStr());
		break;
	}

	g_EnemyCount = m_Round[g_CurrentRound-1].NumOfEnemies;

	// get the number of enemies for the round
	unsigned int numEnems = m_Round[g_CurrentRound-1].NumOfEnemies;
	// make all the enemies in the array invisible (the enemies from the previous rounds *should* be invisible
	// anyway because they were killed off by the player)
	// This is just a check
	for(int e=0; e < 10; ++e)
	{
		m_pEnemyArray[e]->setVisible(false);
	}

	// Re-Spawning the asteroids too at the same time....
	// reset Asteroid positions 
	// Hacky way of doing this have to change after test....
	Vector2f pos(m_PlayWidth / 2-450 , m_PlayHeight/2+350);
	// First line of asteroids....
	g_AsteroidArray[0]->setPosition(pos);

	pos.x += 300;
	g_AsteroidArray[1]->setPosition(pos);

	pos.x += 400;
	g_AsteroidArray[2]->setPosition(pos);

	// second line of asteroids...
	pos.x = m_PlayWidth / 2-470;
	pos.y -= 70;
	g_AsteroidArray[3]->setPosition(pos);

	pos.x += 370;
	g_AsteroidArray[4]->setPosition(pos);

	// third line of asteroids...
	pos.x= m_PlayWidth / 2-350;
	pos.y -= 110;
	g_AsteroidArray[5]->setPosition(pos);

	pos.x += 370;
	g_AsteroidArray[6]->setPosition(pos);

	pos.x += 450;
	g_AsteroidArray[7]->setPosition(pos);
	
	for(int f=0; f<MAX_AsteroidS; ++f)
	{
		g_AsteroidArray[f]->setDestroyed(false);
		g_AsteroidArray[f]->setMaxSpeed(10.0f);
		g_AsteroidArray[f]->setVisible(true);
		g_AsteroidArray[f]->SetAcceleration(Vector2f(0.0f,0.0f));
		g_AsteroidArray[f]->setVelocity(Vector2f(0.0f,0.0f));
		g_AsteroidArray[f]->ClearForce();
	}

	// reset the Asteroid count
	g_AsteroidCount = MAX_AsteroidS;
	
	// change the level settings for the round
	changeLevel();
}

void MainGameState::changeLevel()
{
	g_EnemyCount = m_Round[g_CurrentRound-1].NumOfEnemies;

	// get the enemy attributes for the level & round
	// Exception is caught here at round 7 due to enemy max speed ... need to look into this .
	float tEnemSpeed = m_Round[g_CurrentRound-1].rLevels[g_CurrentLevel-1].EnemyMaxSpeed;

	// set the enemy attributes to only the number of enemies in the round
	for(int e = 0; e < (int)m_Round[g_CurrentRound-1].NumOfEnemies; ++e)
	{
		// set the enemy's max speed
		m_pEnemyArray[e]->setMaxSpeed(tEnemSpeed);

		// reset their positions
		float rx=m_Rng.random();
		float ry=m_Rng.random();

		float signx = m_Rng.random();
		if(signx < 0.5)
			rx = -rx;
		
		float signy = m_Rng.random();
		if(signy < 0.5)
			ry = -ry;

		// randomly put them somewhere outside the screen
		Vector2f pos=Vector2f(rx,ry);
		pos.normalise();
		pos*=1000;

		m_pEnemyArray[e]->reset();
		m_pEnemyArray[e]->setPosition(pos);
		m_pEnemyArray[e]->setVisible(true);
		
		m_pEnemyArray[e]->setDestroyed(false);
		m_pEnemyArray[e]->setCurrentState(ALIVE); // also set them to alive
	}

	// now change the vertex instances to the current level
	EntityManager::GetInstance()->setCurrentVertexInstance(g_CurrentLevel-1);
	// and change the music to the level
	// since we're always moving up levels, we can take the previous levels background music and stop this.
	// this WON'T work with the debug Y/N though, so be careful!
	int prevLevel = g_CurrentLevel - 1; 
	
	if(prevLevel <= 0)
		prevLevel = 0;

	m_pSoundsystem->stop(prevLevel); // stop the previous level background music
	
	if(g_CurrentLevel == 1)
		m_pSoundsystem->stop(6); // when the level has reached maximum and we reset, we stop level 6 music
	// we don't -1 here because 0 is the beginning music for title.
	// at least, it will be if we can get it to load (it's in mp3 format)
	m_pSoundsystem->play(g_CurrentLevel); 
}

void MainGameState::reset()
{
	// blank the title game over gui
	GUI::GUISystem::GetInstance()->GetPage(ID_TITLE_PAGE.getStr())->GetComponent(ID_GAMEOVER_CMPNT.getStr())->SetLabel("");

	g_Player1Score = 0;
	g_Player2Score = 0;
	g_EnemyCount = 2;
	g_CurrentRound = 1;
	g_CurrentLevel = 1;

	// update gui scores
	updateScores();

	// reset the Asteroid count
	g_AsteroidCount = MAX_AsteroidS;

	Vector2f pos_player1(m_PlayWidth - 50, m_PlayHeight / 2);
	// reset player position
	g_pPlayer1->setCurrentSpeed(0.0f);
	g_pPlayer1->setPosition(pos_player1);
	g_pPlayer1->setAngle(90.0f);

	// if there is a second player
	if(g_Settings.NumPlayers == 2)
	{
		Vector2f pos_player2(50, m_PlayHeight / 2);
		// update the player2 score component
		GUI::GUISystem::GetInstance()->GetPage(ID_MAIN_PAGE.getStr())->GetComponent(ID_SCORE2_CMPNT.getStr())->SetLabel("00000");

		if(g_pPlayer2 != NULL)
		{
			if(g_pPlayer2->isVisible() == false)
				g_pPlayer2->setVisible(true);

			g_pPlayer2->setPosition(pos_player2);
			g_pPlayer2->reset();
			g_pPlayer2->setAngle(270.0f);
		}
		else
		{
			// create a player2
			IEntity * pEnt = new Player(ID_PLAYER2.getStr().c_str(), pos_player2);
			pEnt->loadVertexList("data\\player2.txt");
			pEnt->setAngle(270.0f); // face the other way
			pEnt->setVisible(true);
			g_pPlayer2 = (Player*) pEnt;
			m_Entities.push_back(pEnt);
		}
	}

	if(g_Settings.NumPlayers == 1 && g_pPlayer2 != NULL)
	{
		// we just make the player2 invisible
		g_pPlayer2->setVisible(false);
	}

	// go through the enemies and reset their positions randomly
	for(int e=0; e < 10; ++e)
	{
		float rx = (m_Rng.random() * 16) + (m_PlayWidth);
		float ry = (m_Rng.random() * 16) + (m_PlayHeight);

		float signx = m_Rng.random();
		if(signx < 0.5)
			rx = -rx;
		
		float signy = m_Rng.random();
		if(signy < 0.5)
			ry = -ry;
		
		m_pEnemyArray[e]->reset();
		m_pEnemyArray[e]->setPosition(Vector2f(rx,ry));
	}

	// reset Asteroid positions 
	// Hacky way of doing this have to change after test....
	Vector2f pos(m_PlayWidth / 2-450 , m_PlayHeight/2+350);
	// First line of asteroids....
	g_AsteroidArray[0]->setPosition(pos);

	pos.x += 300;
	g_AsteroidArray[1]->setPosition(pos);

	pos.x += 400;
	g_AsteroidArray[2]->setPosition(pos);

	// second line of asteroids...
	pos.x = m_PlayWidth / 2-470;
	pos.y -= 70;
	g_AsteroidArray[3]->setPosition(pos);

	pos.x += 370;
	g_AsteroidArray[4]->setPosition(pos);

	// third line of asteroids...
	pos.x= m_PlayWidth / 2-350;
	pos.y -= 110;
	g_AsteroidArray[5]->setPosition(pos);

	pos.x += 370;
	g_AsteroidArray[6]->setPosition(pos);

	pos.x += 450;
	g_AsteroidArray[7]->setPosition(pos);

	// this should really be in Asteroid.cpp
	for(int f=0; f<MAX_AsteroidS; ++f)
	{
		g_AsteroidArray[f]->setDestroyed(false);
		g_AsteroidArray[f]->setVisible(true);
		g_AsteroidArray[f]->setMaxSpeed(10.0f);
		g_AsteroidArray[f]->SetAcceleration(Vector2f(0.0f,0.0f));
		g_AsteroidArray[f]->setVelocity(Vector2f(0.0f,0.0f));
		g_AsteroidArray[f]->ClearForce();
	}

	// change the round to the current round
	// the function will call changeLevel for the current level
	changeRound();
}

void MainGameState::stop()
{
	m_pController = NULL;
	g_pPlayer1 = NULL;
}

void MainGameState::checkAsteroids()
{
	// go through the list of Asteroids and see if they're in the game/viewable area.
	// if they are we update their status and the game play.
	// *Note* that we only update Asteroids that are visible, it's obvious that when they aren't
	// visible, the engine/game doesn't update it.
	for(int b = 0; b < MAX_AsteroidS; ++b)
	{
		if(g_AsteroidArray[b]->isVisible())
		{
			const float maxHeight = m_PlayHeight;
			const float maxWidth = m_PlayWidth;

			// clamp the x,y values, we take the 10 either side to take into account the center shift
			if((g_AsteroidArray[b]->getPosition().x-10) > maxWidth || (g_AsteroidArray[b]->getPosition().x+10) < 0.0f 
				|| (g_AsteroidArray[b]->getPosition().y-10) > maxHeight || (g_AsteroidArray[b]->getPosition().y+10) < 0.0f)
			{
				// the positions are outside the viewable area, set the visibility of the Asteroid to 0
				// decrease the Asteroid count
				g_AsteroidArray[b]->setVisible(false);			
				--g_AsteroidCount;
			}
		}
	}
	// if Asteroid count is 0, game over, goto title state
		if(g_AsteroidCount == 0 && (g_AsteroidArray[3]->isDestroyed()!=true ||g_AsteroidArray[4]->isDestroyed()!= true))
		{
			// set the game over gui on the title screen
			GUI::GUISystem::GetInstance()->GetPage(ID_TITLE_PAGE.getStr())->GetComponent(ID_GAMEOVER_CMPNT.getStr())->SetLabel(ID_GAMEOVER.getStr());
			// change to the title screen
			StateManager::GetInstance()->makeCurrentState(ID_TITLE_STATE.getHashValue());
			Engine::GetInstance()->loadState();
		}
}

void MainGameState::checkLevel()
{
	// if the enemy count for the current level is 0, change level
	if(g_EnemyCount == 0 || (g_AsteroidCount == 0 && 
								g_AsteroidArray[3]->isDestroyed()==true && 
									g_AsteroidArray[4]->isDestroyed()==true))
	{
		++g_CurrentLevel;
		if(g_CurrentLevel > 6)
		{
			g_CurrentLevel = 1; // reset the current level to 1
			++g_CurrentRound; // change the round
			if(g_CurrentRound > 10)
			{
				// change to the title screen
				// TODO: i  should really make "You beat the game" state
				StateManager::GetInstance()->makeCurrentState(ID_TITLE_STATE.getHashValue());
				Engine::GetInstance()->loadState();
			}
			else
			{
				changeRound();
			}
		}
		else
		{
			changeLevel();
		}
	}
}

void MainGameState::checkPlayers()
{
	// finally, check if the player is within the viewable area
	// only do this when players are visible and alive
	if(g_pPlayer1->isVisible() && g_pPlayer1->getCurrentState() == ALIVE)
	{
		const float maxHeight = m_PlayHeight;
		const float maxWidth = m_PlayWidth;

		// clamp the x,y values for player 1#
		if(g_pPlayer1->getPosition().x > maxWidth)
		{
			// we apply a force in the opposite direction of travel
			g_pPlayer1->AddForce(Vector2f(-1.0f, 0.0f)*3000);
			g_pPlayer1->turnLeft();
		}
		if(g_pPlayer1->getPosition().x < 0.0f)
		{
			g_pPlayer1->AddForce(Vector2f(1.0f,0.0f)*3000);
			g_pPlayer1->turnLeft();
		}
		if(g_pPlayer1->getPosition().y > maxHeight)
		{
			g_pPlayer1->AddForce(Vector2f(0.0f,-1.0f)*3000);
			g_pPlayer1->turnLeft();
		}
		if(g_pPlayer1->getPosition().y < 0.0f)
		{
			g_pPlayer1->AddForce(Vector2f(0.0f,1.0f)*3000);
			g_pPlayer1->turnLeft();
		}
	
		// update player 2 if the number of players is 2. Like player1, only update if it's visible and alive	
		if(g_Settings.NumPlayers == 2 && g_pPlayer2->isVisible() && g_pPlayer2->getCurrentState() == ALIVE)
		{
			// clamp the x,y values for player 2
			// clamp the x,y values for player 1#
			if(g_pPlayer2->getPosition().x > maxWidth)
			{
				// we apply a force in the opposite direction of travel
				g_pPlayer2->AddForce(Vector2f(-1.0f, 0.0f)*3000);
				g_pPlayer2->turnLeft();
			}
			if(g_pPlayer2->getPosition().x < 0.0f)
			{
				g_pPlayer2->AddForce(Vector2f(1.0f,0.0f)*3000);
				g_pPlayer2->turnLeft();
			}
			if(g_pPlayer2->getPosition().y > maxHeight)
			{
				g_pPlayer2->AddForce(Vector2f(0.0f,-1.0f)*3000);
				g_pPlayer2->turnLeft();
			}
			if(g_pPlayer2->getPosition().y < 0.0f)
			{
				g_pPlayer2->AddForce(Vector2f(0.0f,1.0f)*3000);
				g_pPlayer2->turnLeft();
			}
		}
	}

	// When the player re spawns, move the players towards their eventual positions in the game area
	// and then set their states to ALIVE so the user can control them
	if(g_pPlayer1->getCurrentState() != ALIVE)
	{
		g_pPlayer1->forward();
		if(g_pPlayer1->getPosition().x <= m_PlayWidth -50)
			g_pPlayer1->setCurrentState(ALIVE);
	}
	if(g_Settings.NumPlayers== 2 && g_pPlayer2->getCurrentState() != ALIVE)
	{
		g_pPlayer2->forward();
		if(g_pPlayer2->getPosition().x >= 50)
			g_pPlayer2->setCurrentState(ALIVE);
	}
}

void MainGameState::updateGameLogic()
{
	checkAsteroids();

	checkLevel();

	checkPlayers();
}

void MainGameState::updateScores()
{
	if(g_Player1Score > 99999)
		g_Player1Score = 99999; // maximum score.

	// set the score
	SetPlayer1Score(g_Player1Score, g_CurrentRound);

	// update the player's scores on the UI page
	std::string p1_score;
	if(g_Player1Score < 10)
		p1_score = "0000";
	else if(g_Player1Score < 100)
		p1_score = "000";
	else if(g_Player1Score < 1000)
		p1_score = "00";
	else if(g_Player1Score < 10000)
		p1_score = "0";
	else
		p1_score = "";
	
	p1_score.append(Utils::numberToString(g_Player1Score));
	// update the player1 score
	GUI::GUISystem::GetInstance()->GetPage(ID_MAIN_PAGE.getStr())->GetComponent(ID_SCORE_CMPNT.getStr())->SetLabel(p1_score);

	if(g_Settings.NumPlayers == 2)
	{
		if(g_Player2Score > 99999)
			g_Player2Score = 99999;
		
		SetPlayer2Score(g_Player2Score, g_CurrentRound);

		// update the player's scores on the UI page
		std::string p2_score;
		if(g_Player2Score < 10)
			p2_score = "0000";
		else if(g_Player2Score < 100)
			p2_score = "000";
		else if(g_Player2Score < 1000)
			p2_score = "00";
		else if(g_Player2Score < 10000)
			p2_score = "0";
		else
			p2_score = "";

		p2_score.append(Utils::numberToString(g_Player2Score));
		// update the player1 score
		GUI::GUISystem::GetInstance()->GetPage(ID_MAIN_PAGE.getStr())->GetComponent(ID_SCORE2_CMPNT.getStr())->SetLabel(p2_score);
	}

#ifdef _DEBUG // output PLAYER1 score
	Logger::GetInstance()->printMsg(INFO, p1_score.c_str());
#endif
}

void MainGameState::enemyDestroyedByBullet(IEntity *pEnemy, IEntity *pBullet)
{
	pEnemy->setDestroyed(true);
	pBullet->setVisible(false);
	pEnemy->setCurrentState(DEAD);
	pEnemy->setVisible(false);

	// only set the owning if it isn't null, else we get a error
	// when we use "Get
	IEntity *pOwner = pEnemy->GetOwner();
	if(pOwner != NULL)
	{
		pEnemy->GetOwning()->SetOwner(NULL);
	}

	pEnemy->SetOwning(NULL);

	m_pSoundsystem->play(8); // play the explosion sound

	if(pBullet->getEntityId() == ID_BULLET1_A.getHashValue() || pBullet->getEntityId() == ID_BULLET1_B.getHashValue() ||
		pBullet->getEntityId() == ID_BULLET1_C.getHashValue() || pBullet->getEntityId() == ID_BULLET1_D.getHashValue()) // player1's bullet hit the enemy
	{
		// increase player1's score
		g_Player1Score += m_Round[g_CurrentRound-1].rLevels[g_CurrentLevel-1].Points;
	}
	else // *MUST* be player2's bullet
	{
		// check though
		if(pBullet->getEntityId() == ID_BULLET2_A.getHashValue() || pBullet->getEntityId() == ID_BULLET2_B.getHashValue() ||
			pBullet->getEntityId() == ID_BULLET2_C.getHashValue() || pBullet->getEntityId() == ID_BULLET2_D.getHashValue())
		{
			g_Player2Score += m_Round[g_CurrentRound-1].rLevels[g_CurrentLevel-1].Points;
		}
	}

	--g_EnemyCount;

	updateScores();
}

void MainGameState::playerDestroyedByEnemy(IEntity *pPlayer)
{
	if(pPlayer->getEntityId() == g_pPlayer1->getEntityId())
	{
		pPlayer->setCurrentState(DEAD);
		//reset the player position
		Vector2f pos_player1(m_PlayWidth + 20, m_PlayHeight / 2);
		//// reset player position
		pPlayer->setCurrentSpeed(0.0f);
		pPlayer->setAngle(90.0f);
		pPlayer->setPosition(pos_player1);
		pPlayer->reset(); // re spawn the player
	}
	else // the other player *MUST* be player 2
	{
		// add a further check just in-case though
		if(g_Settings.NumPlayers == 2)
		{
			pPlayer->setCurrentState(DEAD);
			//reset the player position
			Vector2f pos_player2(-20, m_PlayHeight / 2);
			//// reset player position
			pPlayer->setCurrentSpeed(0.0f);
			pPlayer->setAngle(270.0f);
			pPlayer->setPosition(pos_player2);
			pPlayer->reset(); // re spawn the player
		}
	}
}

// TODO: Player collided with Asteroid... Should i leave it empty ? does it improve game play if i make 
// it destructible only by bullet ?
void MainGameState::AsteroidDestroyedByPlayer(IEntity *pAsteroid,IEntity *pPlayer)
{
	pAsteroid->setDestroyed(true);
	pAsteroid->setCurrentState(DEAD);
	pAsteroid->setVisible(false);

	// only set the owning if it isn't null, else we get a error
	// when we use "Get
	IEntity *pOwner = pAsteroid->GetOwner();
	if(pOwner != NULL)
	{
		pAsteroid->GetOwning()->SetOwner(NULL);
	}

	pAsteroid->SetOwning(NULL);

	// test if the player is player1
	if(pPlayer->getEntityId() == g_pPlayer1->getEntityId())
	{
		pPlayer->setCurrentState(DEAD);
		//reset the player position
		Vector2f pos_player1(m_PlayWidth + 20, m_PlayHeight / 2);
		//// reset player position
		pPlayer->setCurrentSpeed(0.0f);
		pPlayer->setAngle(90.0f);
		pPlayer->setPosition(pos_player1);
		pPlayer->reset(); // re spawn the player
	}
	else // the other player *MUST* be player 2
	{
		// add a further check just in-case though
		if(g_Settings.NumPlayers == 2)
		{
			pPlayer->setCurrentState(DEAD);
			//reset the player position
			Vector2f pos_player2(-20, m_PlayHeight / 2);
			//// reset player position
			pPlayer->setCurrentSpeed(0.0f);
			pPlayer->setAngle(270.0f);
			pPlayer->setPosition(pos_player2);
			pPlayer->reset(); // re spawn the player
		}
	}

	// decrease the enemy count
	--g_AsteroidCount;

	Logger::GetInstance()->printMsg(INFO, "Decreasing Asteroid count");
}

// TODO: Handling the collision with Bullet .. 
// When collided separate into two different Asteroids -> do this if there is enough time...
void MainGameState::AsteroidDestroyedByBullet( IEntity *pAsteroid, IEntity *pBullet )
{
	pAsteroid->setDestroyed(true);
	pBullet->setVisible(false);
	pAsteroid->setCurrentState(DEAD);
	pAsteroid->setVisible(false);

	m_pSoundsystem->play(8); // play the explosion sound

	if(pBullet->getEntityId() == ID_BULLET1_A.getHashValue() || pBullet->getEntityId() == ID_BULLET1_B.getHashValue() ||
		pBullet->getEntityId() == ID_BULLET1_C.getHashValue() || pBullet->getEntityId() == ID_BULLET1_D.getHashValue()) // player1's bullet hit the enemy
	{
		// increase player1's score
		g_Player1Score += m_Round[g_CurrentRound-1].rLevels[g_CurrentLevel-1].Points;
	}
	else // *MUST* be player2's bullet
	{
		// check though
		if(pBullet->getEntityId() == ID_BULLET2_A.getHashValue() || pBullet->getEntityId() == ID_BULLET2_B.getHashValue() ||
			pBullet->getEntityId() == ID_BULLET2_C.getHashValue() || pBullet->getEntityId() == ID_BULLET2_D.getHashValue())
		{
			g_Player2Score += m_Round[g_CurrentRound-1].rLevels[g_CurrentLevel-1].Points;
		}
	}

	--g_AsteroidCount;

	updateScores();
}

void MainGameState::enemyDestroyedByPlayer(IEntity *pEnemy, IEntity *pPlayer) 
{
	pEnemy->setDestroyed(true);
	pEnemy->setCurrentState(DEAD);
	pEnemy->setVisible(false);

	// only set the owning if it isn't null, else we get a error
	// when we use "Get
	IEntity *pOwner = pEnemy->GetOwner();
	if(pOwner != NULL)
	{
		pEnemy->GetOwning()->SetOwner(NULL);
	}

	pEnemy->SetOwning(NULL);

	// test if the player is player1
	if(pPlayer->getEntityId() == g_pPlayer1->getEntityId())
	{
		pPlayer->setCurrentState(DEAD);
		//reset the player position
		Vector2f pos_player1(m_PlayWidth + 20, m_PlayHeight / 2);
		//// reset player position
		pPlayer->setCurrentSpeed(0.0f);
		pPlayer->setAngle(90.0f);
		pPlayer->setPosition(pos_player1);
		pPlayer->reset(); // re spawn the player
	}
	else // the other player *MUST* be player 2
	{
		// add a further check just in-case though
		if(g_Settings.NumPlayers == 2)
		{
			pPlayer->setCurrentState(DEAD);
			//reset the player position
			Vector2f pos_player2(-20, m_PlayHeight / 2);
			//// reset player position
			pPlayer->setCurrentSpeed(0.0f);
			pPlayer->setAngle(270.0f);
			pPlayer->setPosition(pos_player2);
			pPlayer->reset(); // re spawn the player
		}
	}

	// decrease the enemy count
	--g_EnemyCount;

	Logger::GetInstance()->printMsg(INFO, "Decreasing enemy count");
//	// DO NOT INCREASE THE SCORE
//#ifdef  _DEBUG // for debug use
//	g_Player1Score += m_Round[g_CurrentRound-1].rLevels[g_CurrentLevel-1].Points;
//	if(g_Settings.NumPlayers == 2)
//	{
//		g_Player2Score += m_Round[g_CurrentRound-1].rLevels[g_CurrentLevel-1].Points;
//	}
//	updateScores();
//#endif
}

void MainGameState::update()
{
	processInput();

	detectCollisions();

	EntityList::iterator it = m_Entities.begin();
	while(it != m_Entities.end())
	{
		(*it)->update();
		++it;
	}

	// update the game logic
	updateGameLogic();
}

void MainGameState::processInput()
{
	if(m_pController != NULL)
	{
		// if there is 2 players
		if(g_Settings.NumPlayers == 2 && g_pPlayer2->getCurrentState() == ALIVE)
		{

			if(m_pController->ActionKeysActive(ACTIONS_PLAYER2_TURNLEFT , true))
			{
				g_pPlayer2->turnLeft();
			}

			if(m_pController->ActionKeysActive(ACTIONS_PLAYER2_TURNRIGHT ,true))
			{
				g_pPlayer2->turnRight();
			}

			if(m_pController->ActionKeysActive(ACTIONS_PLAYER2_MOVEFWD ,true))
			{
				g_pPlayer2->forward();
			}

			if(m_pController->ActionKeysActive(ACTIONS_PLAYER2_FIRE ,false))
			{			
				g_pPlayer2->fire();
			}
		}

		if(g_pPlayer1->getCurrentState() == ALIVE) // restrict control to when the player is in alive state
		{
			if(m_pController->ActionKeysActive(ACTIONS_PLAYER1_TURNLEFT ,true))
			{
				g_pPlayer1->turnLeft();
			}

			if(m_pController->ActionKeysActive(ACTIONS_PLAYER1_TURNRIGHT ,true))

			{
				g_pPlayer1->turnRight();
			}
			if(m_pController->ActionKeysActive(ACTIONS_PLAYER1_MOVEFWD ,true))
			{
				g_pPlayer1->forward();
			}

			if(m_pController->ActionKeysActive(ACTIONS_PLAYER1_FIRE ,false))
			{		
				g_pPlayer1->fire();
			}
		}

		if(m_pController->ActionKeysActive(ACTIONS_QUIT ,false))

		{
			m_pSoundsystem->stopAllSounds();

			//Engine::GetInstance()->doExit(true);
			// instead of quitting out we'll need to change to the "Do you want to quit?" screen/state
			// for now, we'll goto the title screen
			StateManager::GetInstance()->makeCurrentState(ID_EXIT_TO_TITLE_STATE.getHashValue());
			Engine::GetInstance()->loadState();
		}

#ifdef _DEBUG // Test for different levels
		if(m_pController->ActionKeysActive(ACTIONS_YES , false))
		{
			++g_CurrentLevel;
			if(g_CurrentLevel >= 6)
				g_CurrentLevel = 6;
			
			printf("[MainGameState] - Current Level %i\n", g_CurrentLevel);
			changeLevel();
		}
		if(m_pController->ActionKeysActive(ACTIONS_N0 , false))
		{
			--g_CurrentLevel;
			if(g_CurrentLevel <= 1)
				g_CurrentLevel = 1;
			
			printf("[MainGameState] - Current Level %i\n", g_CurrentLevel);

			changeLevel();
		}
#endif

	}
}

void MainGameState::setNewGame(bool ng, GameSettings set)
{
	m_bNewGame = ng;

	g_Settings.NumPlayers = set.NumPlayers;
	g_Settings.Difficulty = set.Difficulty;

	if(g_Settings.Difficulty == NORMAL)
	{
		// modify the AI
		Logger::GetInstance()->printMsg(INFO, "[GameState] - Normal difficulty");
	}
	else if(g_Settings.Difficulty == HARD)
	{		
		Logger::GetInstance()->printMsg(INFO, "[GameState] - Hard difficulty");
	}


	if(ng == true && m_bHasAlreadyStarted == true)
		reset();
	else
		start();
}

void MainGameState::detectCollisions()
{
	// go through the list of entities and test against their collision primitives

	for(int i=0; i < m_Entities.size(); ++i)
	{
		CollisionPrimitive *pPrim1 = m_Entities[i]->getCollisionPrimitive();

		// make sure the collidable is visible & a circle
		if((pPrim1->isVisible() && (pPrim1->getType() == CIRCLE_TYPE)))
		{
			// loop through the list again checking against other circles
			for(int j=i+1; j < m_Entities.size(); ++j)
			{
				CollisionPrimitive *pPrim2 = m_Entities[j]->getCollisionPrimitive();

				// if it's not a circle 
				// do the line test first because these can probably appear out of nowhere from the enemy
				if((pPrim2->isVisible() && (pPrim2->getType() == LINE_TYPE)))
				{
					// perform the circle line test
					const CollisionCircle *t1 = (CollisionCircle*) pPrim1;
					const CollisionLine *t2 = (CollisionLine*) pPrim2;

					bool test = CollisionDetector::circleAndLine(*t1, *t2);
					if(test)
					{
						IEntity *pEnt1 = m_Entities[i];
						IEntity *pEnt2 = m_Entities[j];

						handleCollision(pEnt1, pEnt2);
					}
				}

				if((pPrim2->isVisible() && (pPrim2->getType() == CIRCLE_TYPE)))
				{
					// perform the circle circle test
					// we've established they're circle so it's safe to cast
					const CollisionCircle *t1 = (CollisionCircle*) pPrim1;
					const CollisionCircle *t2 = (CollisionCircle*) pPrim2;

					bool test = CollisionDetector::circleAndCircle(*t1, *t2);
					if(test)
					{
						IEntity *pEnt1 = m_Entities[i];
						IEntity *pEnt2 = m_Entities[j];

						// handle collisions
						handleCollision(pEnt1, pEnt2);
					}
				}
			}
		}
	}
	
}


void MainGameState::handleCollision(IEntity *ent1, IEntity *ent2)
{
	// we're only concerned with enemy-player, laser-player, bullet-enemy collisions	

	// we can put  player 1 as ent1 because player1 is guaranteed to be added to the entity list first
	if(ent1->getEntityId() == ID_PLAYER1.getHashValue())
	{
		if(ent2->getEntityId() == ID_LASER.getHashValue())
		{
			playerDestroyedByEnemy(ent1);
			
			SoundManager::GetInstance()->getSoundSystem()->play(8);
			std::cout << "Player hit by laser!" << std::endl;
		}

		if(ent2->getEntityId() == ID_Asteroid1.getHashValue() ||
			ent2->getEntityId() == ID_Asteroid2.getHashValue() || 
			ent2->getEntityId() == ID_Asteroid3.getHashValue() || 
			ent2->getEntityId() == ID_Asteroid4.getHashValue() || 
			ent2->getEntityId() == ID_Asteroid5.getHashValue() || 
			ent2->getEntityId() == ID_Asteroid6.getHashValue() || 
			ent2->getEntityId() == ID_Asteroid7.getHashValue() ||
			ent2->getEntityId() == ID_Asteroid8.getHashValue()) // don't really care what Asteroid it is
		{
			//rng.randomise();
			// get a random position within the radius of the player
			float posx = m_Rng.random(); // this will give us a value between 0 - 1 to add to the current position of the player
			float posy = m_Rng.random();

			int neg = (int)m_Rng.random();
			if(neg == 1)
			{
				// make the new positions negative
				posx = -posx;
				posy = -posy;
			}

			posx += ent1->getPosition().x;
			posy += ent1->getPosition().y;

			// set the position
			ent1->setPosition(Vector2f(posx, posy));
		}

		// for some reason, find doesn't work!?
		if(ent2->getEntityId() == ID_ENEMIES[0].getHashValue() ||
			ent2->getEntityId() == ID_ENEMIES[1].getHashValue() || 
			ent2->getEntityId() == ID_ENEMIES[2].getHashValue() || 
			ent2->getEntityId() == ID_ENEMIES[3].getHashValue() || 
			ent2->getEntityId() == ID_ENEMIES[4].getHashValue() || 
			ent2->getEntityId() == ID_ENEMIES[5].getHashValue() || 
			ent2->getEntityId() == ID_ENEMIES[6].getHashValue() ||
			ent2->getEntityId() == ID_ENEMIES[7].getHashValue() ||
			ent2->getEntityId() == ID_ENEMIES[8].getHashValue() ||
			ent2->getEntityId() == ID_ENEMIES[9].getHashValue())
		{
			// the player collided with the enemy, tell the main game state about it
			enemyDestroyedByPlayer(ent2, ent1); 
			SoundManager::GetInstance()->getSoundSystem()->play(8);
		}
	}

	// do the collision stuff for player2 & Asteroid
	if(ent1->getEntityId() == ID_PLAYER2.getHashValue() || ent2->getEntityId() == ID_PLAYER2.getHashValue())
	{
		if(ent2->getEntityId() == ID_LASER.getHashValue() || ent1->getEntityId() == ID_LASER.getHashValue())
		{
			if(ent2->getEntityId() == ID_PLAYER2.getHashValue())
			{
				playerDestroyedByEnemy(ent2);
			}
			else
			{
				playerDestroyedByEnemy(ent1);
			}
			
			SoundManager::GetInstance()->getSoundSystem()->play(8);
			std::cout << "Player hit by laser!" << std::endl;
		}

		if(ent2->getEntityId() == ID_Asteroid1.getHashValue() || ent1->getEntityId() == ID_Asteroid1.getHashValue() ||
			ent2->getEntityId() == ID_Asteroid2.getHashValue() || ent1->getEntityId() == ID_Asteroid2.getHashValue() ||
			ent2->getEntityId() == ID_Asteroid3.getHashValue() || ent1->getEntityId() == ID_Asteroid3.getHashValue() ||
			ent2->getEntityId() == ID_Asteroid4.getHashValue() || ent1->getEntityId() == ID_Asteroid4.getHashValue() ||
			ent2->getEntityId() == ID_Asteroid5.getHashValue() || ent1->getEntityId() == ID_Asteroid5.getHashValue() ||
			ent2->getEntityId() == ID_Asteroid6.getHashValue() || ent1->getEntityId() == ID_Asteroid6.getHashValue() ||
			ent2->getEntityId() == ID_Asteroid7.getHashValue() || ent1->getEntityId() == ID_Asteroid7.getHashValue() ||
			ent2->getEntityId() == ID_Asteroid8.getHashValue() || ent1->getEntityId() == ID_Asteroid8.getHashValue())
		{
			//rng.setRandomSeed(1);
			// get a random position within the radius of the player
			float posx = m_Rng.random(); // this will give us a value between 0 - 1 to add to the current position of the player
			float posy = m_Rng.random();

			if(ent2->getEntityId() == ID_PLAYER2.getHashValue())
			{
				posx += ent2->getPosition().x;
				posy += ent2->getPosition().y;
				ent2->setPosition(Vector2f(posx, posy));
			}
			else
			{
				posx += ent1->getPosition().x;
				posy += ent1->getPosition().y;
				ent1->setPosition(Vector2f(posx, posy));
			}
			
		}
		// handle collision with enemies
		if(ent2->getEntityId() == ID_ENEMIES[0].getHashValue() || ent1->getEntityId() == ID_ENEMIES[0].getHashValue() ||
			ent2->getEntityId() == ID_ENEMIES[1].getHashValue() || ent1->getEntityId() == ID_ENEMIES[1].getHashValue() ||
			ent2->getEntityId() == ID_ENEMIES[2].getHashValue() || ent1->getEntityId() == ID_ENEMIES[2].getHashValue() ||
			ent2->getEntityId() == ID_ENEMIES[3].getHashValue() || ent1->getEntityId() == ID_ENEMIES[3].getHashValue() ||
			ent2->getEntityId() == ID_ENEMIES[4].getHashValue() || ent1->getEntityId() == ID_ENEMIES[4].getHashValue() ||
			ent2->getEntityId() == ID_ENEMIES[5].getHashValue() || ent1->getEntityId() == ID_ENEMIES[5].getHashValue() ||
			ent2->getEntityId() == ID_ENEMIES[6].getHashValue() || ent1->getEntityId() == ID_ENEMIES[6].getHashValue() ||
			ent2->getEntityId() == ID_ENEMIES[7].getHashValue() || ent1->getEntityId() == ID_ENEMIES[7].getHashValue() ||
			ent2->getEntityId() == ID_ENEMIES[8].getHashValue() || ent1->getEntityId() == ID_ENEMIES[8].getHashValue() ||
			ent2->getEntityId() == ID_ENEMIES[9].getHashValue() || ent1->getEntityId() == ID_ENEMIES[9].getHashValue())
		{
			// the player collided with the enemy, tell the main game state about it
			if(ent2->getEntityId() == ID_PLAYER2.getHashValue())
				enemyDestroyedByPlayer(ent1, ent2);
			else
				enemyDestroyedByPlayer(ent2, ent1);

			
			SoundManager::GetInstance()->getSoundSystem()->play(8);
		}
#ifdef _DEBUGMSG
		
		if(castEvent.entityIdB == ID_PLAYER2.getHashValue())
		{
			std::cout << "Player2 collided with " << "entity: " << pEnt1->getName() << std::endl;
		}
		else
		{
			std::cout << "Player2 collided with " << "entity: " << pEnt2->getName() << std::endl;
		}
#endif
	}

	// bullet collisions
	if(ent1->getEntityId() == ID_BULLET1_A.getHashValue() || ent1->getEntityId() == ID_BULLET1_B.getHashValue() ||
			ent1->getEntityId() == ID_BULLET1_C.getHashValue() || ent1->getEntityId() == ID_BULLET1_D.getHashValue() ||
			ent1->getEntityId() == ID_BULLET2_A.getHashValue() || ent1->getEntityId() == ID_BULLET2_B.getHashValue() ||
			ent1->getEntityId() == ID_BULLET2_C.getHashValue() || ent1->getEntityId() == ID_BULLET2_D.getHashValue())
	{
		for(int i = 0; i < 10; ++i)
		{
			if(ent2->getEntityId() == ID_ENEMIES[i].getHashValue())
			{
				enemyDestroyedByBullet(ent2, ent1);
				SoundManager::GetInstance()->getSoundSystem()->play(8);
				break;
			}
		}
		// this is for asteroid destroyed by bullet test 
		// TODO: bit messy find another way to do this .....
		for(int i = 0; i < g_AsteroidCount; ++i)
		{
			if( ent2->getEntityId() == ID_Asteroid1.getHashValue() || ent1->getEntityId() == ID_Asteroid1.getHashValue() ||
				ent2->getEntityId() == ID_Asteroid2.getHashValue() || ent1->getEntityId() == ID_Asteroid2.getHashValue() ||
				ent2->getEntityId() == ID_Asteroid3.getHashValue() || ent1->getEntityId() == ID_Asteroid3.getHashValue() ||
				ent2->getEntityId() == ID_Asteroid4.getHashValue() || ent1->getEntityId() == ID_Asteroid4.getHashValue() ||
				ent2->getEntityId() == ID_Asteroid5.getHashValue() || ent1->getEntityId() == ID_Asteroid5.getHashValue() ||
				ent2->getEntityId() == ID_Asteroid6.getHashValue() || ent1->getEntityId() == ID_Asteroid6.getHashValue() ||
				ent2->getEntityId() == ID_Asteroid7.getHashValue() || ent1->getEntityId() == ID_Asteroid7.getHashValue() ||
				ent2->getEntityId() == ID_Asteroid8.getHashValue() || ent1->getEntityId() == ID_Asteroid8.getHashValue())
			{
				AsteroidDestroyedByBullet(ent2, ent1);
				SoundManager::GetInstance()->getSoundSystem()->play(8);
				break;
			}
		}
	}
}

void MainGameState::render(IRenderer *renderer)
{
	float w = (float) renderer->getViewWidth();
	float h = (float) renderer->getViewHeight();

	renderer->bindTexture(m_Tex);
	// create a quad that fills the screen & put a texture on it
	glBegin(GL_QUADS);
	glVertex2f(m_PlayWidth, m_PlayHeight); glTexCoord2f(0.0f, 1.0f);
	glVertex2f(0.0f, m_PlayHeight); glTexCoord2f(0.0f, 0.0f);
	glVertex2f(0.0, 0.0f); glTexCoord2f(1.0f, 0.0f);
	glVertex2f(m_PlayWidth, 0.0f); glTexCoord2f(1.0f, 1.0f);
	glEnd();
	renderer->unbindTexture();

	BaseState::render(renderer);
}

