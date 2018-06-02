#include "ScoreState.h"

ScoreState::ScoreState(void)
: BaseState(ID_SCORE_STATE.getStr().c_str())
{
	m_pController = NULL;
	m_pSoundsystem = NULL;
	if(!LoadScoreInfo())
	{
		// If file not found load default values
		LoadDefaultScores();
	}
}

ScoreState::~ScoreState(void)
{
}

void ScoreState::start()
{
	m_pController = Engine::GetInstance()->getControllerInput();
	// show the exit title ui page
	Engine::GetInstance()->getGuiSystem()->SelectPage(ID_SCORE_PAGE.getStr());
	
	LoadCurrentScores();
	if(m_nGameMode == 1)
	{
		CheckforHighScore(m_Player1, m_EasyModeScoreP1);
		CheckforHighScore(m_Player2, m_EasyModeScoreP2);
	}
	else
	{
		CheckforHighScore(m_Player1, m_NormalModeScoreP1);
		CheckforHighScore(m_Player2, m_NormalModeScoreP2);
	}
}

void ScoreState::stop()
{
	m_pController = NULL;
}

void ScoreState::update()
{
	UpdateScores();
	processInput();
}

void ScoreState::processInput()
{
	if(m_pController != NULL)
	{
		m_pController->Update();
		if(m_pController->ActionKeysActive(ACTIONS_QUIT ,false))
		{
			// go back to title screen
			StateManager::GetInstance()->makeCurrentState(ID_TITLE_STATE.getHashValue());
			Engine::GetInstance()->loadState();
		}
	}
}

void ScoreState::LoadCurrentScores()
{
	m_CurrentScoreP1.SetScore(m_Player1.GetScore());
	m_CurrentScoreP1.SetScoreString(NumtoString(m_Player1.GetScore(), false));

	m_CurrentScoreP1.SetRound(m_Player1.GetRound());
	m_CurrentScoreP1.SetRoundString(NumtoString(m_Player1.GetRound(), true));

	m_CurrentScoreP2.SetScore(m_Player2.GetScore());
	m_CurrentScoreP2.SetScoreString(NumtoString(m_Player2.GetScore(), false));

	m_CurrentScoreP2.SetRound(m_Player2.GetRound());
	m_CurrentScoreP2.SetRoundString(NumtoString(m_Player2.GetRound(), true));
}

void ScoreState::LoadDefaultScores()
{
	m_NormalModeScoreP1.SetScore(11999);
	m_NormalModeScoreP1.SetScoreString(NumtoString(11999, false));

	m_NormalModeScoreP1.SetRound(6);
	m_NormalModeScoreP1.SetRoundString(NumtoString(6, true));

	m_NormalModeScoreP2.SetScore(8967);
	m_NormalModeScoreP2.SetScoreString(NumtoString(8967, false));

	m_NormalModeScoreP2.SetRound(4);
	m_NormalModeScoreP2.SetRoundString(NumtoString(4, true));


	m_EasyModeScoreP1.SetScore(45678);
	m_EasyModeScoreP1.SetScoreString(NumtoString(45678, false));

	m_EasyModeScoreP1.SetRound(8);
	m_EasyModeScoreP1.SetRoundString(NumtoString(8, true));

	m_EasyModeScoreP2.SetScore(23567);
	m_EasyModeScoreP2.SetScoreString(NumtoString(23567, false));

	m_EasyModeScoreP2.SetRound(5);
	m_EasyModeScoreP2.SetRoundString(NumtoString(5, true));
}

void ScoreState::UpdateScores()
{
	ostringstream opStr;
	opStr<<"PLAYER 1 > "<<m_CurrentScoreP1.GetScoreString();
	GUI::GUISystem::GetInstance()->GetPage(ID_SCORE_PAGE.getStr())->GetComponent("score2")->SetLabel(opStr.str());

	opStr.str("");
	opStr<<"PLAYER 2 > "<<m_CurrentScoreP2.GetScoreString();
	GUI::GUISystem::GetInstance()->GetPage(ID_SCORE_PAGE.getStr())->GetComponent("score3")->SetLabel(opStr.str());
	opStr.str("");
	opStr<<"ROUND REACHED > "<<m_CurrentScoreP1.GetRoundString();
	GUI::GUISystem::GetInstance()->GetPage(ID_SCORE_PAGE.getStr())->GetComponent("score4")->SetLabel(opStr.str());
	//
	//// high score in Normal mode
	opStr.str("");
	opStr<<"PLAYER 1 > " <<m_NormalModeScoreP1.GetScoreString()<< "(ROUND > "<<m_NormalModeScoreP1.GetRoundString()<< ")";
	GUI::GUISystem::GetInstance()->GetPage(ID_SCORE_PAGE.getStr())->GetComponent("score6")->SetLabel(opStr.str());
	opStr.str("");
	opStr<<"PLAYER 2 > " <<m_NormalModeScoreP2.GetScoreString()<< "(ROUND > "<<m_NormalModeScoreP2.GetRoundString()<< ")";
	GUI::GUISystem::GetInstance()->GetPage(ID_SCORE_PAGE.getStr())->GetComponent("score7")->SetLabel(opStr.str());
	//
	//// High score in Easy mode
	opStr.str("");
	opStr<<"PLAYER 1 > " <<m_EasyModeScoreP1.GetScoreString()<< "(ROUND > "<<m_EasyModeScoreP1.GetRoundString()<< ")";
	GUI::GUISystem::GetInstance()->GetPage(ID_SCORE_PAGE.getStr())->GetComponent("score9")->SetLabel(opStr.str());
	opStr.str("");
	opStr<<"PLAYER 2 > " <<m_EasyModeScoreP2.GetScoreString()<< "(ROUND > "<<m_EasyModeScoreP2.GetRoundString()<< ")";
	GUI::GUISystem::GetInstance()->GetPage(ID_SCORE_PAGE.getStr())->GetComponent("score10")->SetLabel(opStr.str());
}


void ScoreState::CheckforHighScore(PlayerScore &CurrentPlayerScore, PlayerScore &UpdatePlayerScore)
{
	if(CurrentPlayerScore.GetScore() > UpdatePlayerScore.GetScore())
	{
		UpdatePlayerScore.SetScore(CurrentPlayerScore.GetScore());
		UpdatePlayerScore.SetScoreString(NumtoString(CurrentPlayerScore.GetScore(), false));

		UpdatePlayerScore.SetRound(CurrentPlayerScore.GetRound());
		UpdatePlayerScore.SetRoundString(NumtoString(CurrentPlayerScore.GetRound(), true));
	}
}


bool ScoreState::LoadScoreInfo()
{
	ifstream	fin;
	fin.open("ScoreBoard.Rocky", ifstream::in);
	if(!fin.is_open())
	{
		return false;
	}
	while(!fin.eof())
	{
		char cReadChar[256];
		int nLengthOfLine = Readtheline(&fin,cReadChar, sizeof(cReadChar));
		if(nLengthOfLine == 0)continue;
		istrstream streamin (cReadChar, nLengthOfLine);
		string temp="";
		streamin>>temp;
		if(!_stricmp(temp.c_str(), "Scores"))
		{
			AssginCurrentScore(&fin,3, m_CurrentScoreP1, m_CurrentScoreP2, true);
		}
		if(!_stricmp(temp.c_str(), "HighScoreNormal"))
		{
			AssginCurrentScore(&fin,4, m_NormalModeScoreP1, m_NormalModeScoreP2, false);
		}
		if(!_stricmp(temp.c_str(), "HighScoreEasy"))
		{
			AssginCurrentScore(&fin,4, m_EasyModeScoreP1, m_EasyModeScoreP2, false);
		}
	}
	fin.close();
	return true;
}

/*
The function is to read the line from the script
*/
const int ScoreState::Readtheline(ifstream *fin, char *pOutputStr, const int &nStrSize)
{
	char cLineBuffer[256], cFormattedBuff[256];
	int nLengthOfLine, nNewLength;

	fin->getline(cLineBuffer, sizeof(cLineBuffer));
	nLengthOfLine = fin->gcount();

	if (nLengthOfLine==0 || nLengthOfLine==1)return 0;
	nLengthOfLine--;
	if((cLineBuffer[0] == '/') &&(cLineBuffer[1] == '/')) //check for comments
	{
		return 0;
	}
	nNewLength = TrimString(nLengthOfLine, cLineBuffer, cFormattedBuff);
	nLengthOfLine = RemoveSpaces(nNewLength, cFormattedBuff, cLineBuffer);
	strcpy_s(pOutputStr, nStrSize,cLineBuffer);
	return nLengthOfLine;
}

/*
The function check for comments and eliminate from the string // and /*
*/
const int ScoreState::TrimString(const int &nStrlength, const char *pInputStr, char *pOutStr)
{
	int nlen1 =  nStrlength;
	int nlen2 = nStrlength;
	char cComment[] = "/*";
	char cSlash[] = "//";
	char cTemp[256];

	strcpy_s(cTemp, pInputStr);
	if(strstr(pInputStr, cSlash))
	{
		nlen2 = strcspn(cTemp,cSlash);
		if(nlen2 != nlen1)
		{
			strncpy_s(cTemp, pInputStr, nlen2);
			nlen1 = nlen2;
		}
	}

	if(strstr(pInputStr, cComment))
	{
		nlen2 = strcspn(cTemp, "/*");
		if(nlen2 != nlen1)
		{
			strncpy_s(cTemp, pInputStr, nlen2);
		}
	}

	strcpy_s(pOutStr, 256, cTemp);
	return nlen2;

}

/*
The function removes the space from the string 
*/
const int ScoreState::RemoveSpaces(const int &nStrlength, const char *pInputStr, char *pOutStr)
{
	int j=0;
	for (int nIndex =0; nIndex< nStrlength;nIndex++)
	{
		if(pInputStr[nIndex] != ' ')
		{
			pOutStr[j] = pInputStr[nIndex];
			j++;
		}
	}
	pOutStr[j] = '\0' ;
	return j;
}
/*
The function gets the data from the string e.g a =10
*/
const int ScoreState::GetValue(const int &nStrlength, const char *pInputStr, char *pOutStr)
{
	char equal[] ="=";
	int  nPos =0;
	int  nLen =0;

	if(strstr(pInputStr, equal))
	{
		int j=0;
		nPos =strcspn(pInputStr,equal);
		for (int nIndex =(nPos +1); nIndex< nStrlength;nIndex++)
		{
			pOutStr[j] = pInputStr[nIndex];
			j++;
		}
		pOutStr[j] = '\0' ;
		nLen = j;
	}
	return nLen;
}

/*
This function is to convert the string to lower case
*/
void ScoreState::ToLowerCase(const char *pIpStr, char *pOpstr)
{
	if(pIpStr != NULL)
	{
		int i;
		for (i = 0; pIpStr[i] != '\0'; i++)
		{
			pOpstr[i] = tolower(pIpStr[i]);
		}
		pOpstr[i++] = '\0';
	}
}

string ScoreState::NumtoString(const int &val, const bool bTrimStr)
{
	ostringstream opStr;
	if(bTrimStr)
	{
		opStr<<val;
		return (opStr.str());
	}
	if(val >9999)
	{
		opStr<<val;
	}
	else if((val >999) &&(val < 9999))
	{
		opStr<<"0"<<val;
	}
	else if((val >99) &&(val < 999))
	{
		opStr<<"00"<<val;
	}
	else if((val >9) &&(val < 99))
	{
		opStr<<"000"<<val;
	}
	else if(val <10)
	{
		opStr<<"0000"<<val;
	}
	return (opStr.str());
}

const int ScoreState::AssginCurrentScore(ifstream *fin, const int &nTotalParams, PlayerScore &Player1,
										 PlayerScore &Player2, const bool bCurrentScore)
{
	int nCount = 0;
	while (!fin->eof())
	{
		if(nCount == nTotalParams)
		{
			return 1;
		}
		else
		{
			char cReadChar[256], cForMattedOutput[256];
			int nLengthOfLine = Readtheline(fin, cReadChar, sizeof(cReadChar));
			if(nLengthOfLine == 0)continue;
			nLengthOfLine = GetValue(nLengthOfLine, cReadChar, cForMattedOutput);
			istrstream streamin (cForMattedOutput, nLengthOfLine );
			int temp;
			streamin>>temp;
			if(nCount ==0)
			{
				Player1.SetScore(temp);
				Player1.SetScoreString(NumtoString(temp,false));
			}
			else if(nCount ==1)
			{
				if(bCurrentScore)
				{
					Player2.SetScore(temp);
					Player2.SetScoreString(NumtoString(temp, false));
				}
				else
				{
					Player1.SetRound(temp);
					Player1.SetRoundString(NumtoString(temp, true));
				}
			}
			else if(nCount ==2)
			{
				if(bCurrentScore)
				{
					Player1.SetRound(temp);
					Player1.SetRoundString(NumtoString(temp, true));
				}
				else
				{
					Player2.SetScore(temp);
					Player2.SetScoreString(NumtoString(temp, false));
				}
			}
			else if(nCount ==3)
			{
				Player2.SetRound(temp);
				Player2.SetRoundString(NumtoString(temp, true));
			}
			nCount++;
		}
	}
	return 0;
}