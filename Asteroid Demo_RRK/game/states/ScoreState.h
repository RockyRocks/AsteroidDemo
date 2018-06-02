#ifndef __SCORESTATE_H
#define __SCORESTATE_H

#include "..\..\common\statemanager\basestate.h"
#include "..\GameConstants.h"
#include "PlayerScore.h"


class ScoreState :
	public BaseState
{
public:
	ScoreState();
	virtual ~ScoreState(void);

	virtual void start();
	virtual void stop();
	virtual void update();
	virtual void processInput();
	virtual void load() {}
	virtual void unload() {}
private:
	bool LoadScoreInfo();
	const int TrimString(const int &nStrlength, const char *pInputStr, char *pOutStr);
	const int Readtheline(ifstream *fin, char *pOutputStr, const int &nStrSize);
	const int RemoveSpaces(const int &nStrlength, const char *pInputStr, char *pOutStr);
	const int GetValue(const int &nStrlength, const char *pInputStr, char *pOutStr);
	void ToLowerCase(const char *pIpStr, char *pOpstr);
	const int AssginCurrentScore(ifstream *fin, const int &nTotalParams, PlayerScore &Player1,
								 PlayerScore &Player2, const bool bCurrentScore);
	string NumtoString(const int &val, const bool bTrimStr);
	void UpdateScores();
	void CheckforHighScore(PlayerScore &CurrentPlayerScore, PlayerScore &UpdatePlayerScore);
	void LoadCurrentScores();
	void LoadDefaultScores();
	PlayerScore m_CurrentScoreP1;
	PlayerScore m_CurrentScoreP2;
	PlayerScore m_NormalModeScoreP1;
	PlayerScore m_NormalModeScoreP2;
	PlayerScore m_EasyModeScoreP1;
	PlayerScore m_EasyModeScoreP2;
};

#endif
