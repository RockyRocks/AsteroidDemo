#pragma once
// Lifted this up from my previous Project..
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>

#include "IController.h"
#include "..\..\common\logger\Logger.h"
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif
#include<d3d9.h>
#include<d3dx9.h>
#define DIRECTINPUT_VERSION 0x0800
#include<dinput.h>
#include <InitGuid.h>

using namespace std;

#define	AXIS_THRESHOLD	 20
#define	INPUT_DATA_LIMIT 20
enum ActionKeys
{
	ACTIONS_PLAYER2LEFTRIGHT,  // for gamepad
	ACTIONS_PLAYER2UPDOWN,		//for gamepad
	ACTIONS_PLAYER1_TURNLEFT,	
	ACTIONS_PLAYER1_TURNRIGHT,
	ACTIONS_QUIT,
	ACTIONS_PLAYER1_MOVEFWD,
	ACTIONS_PLAYER1_MOVEDOWN,
	ACTIONS_PLAYER1_FIRE,
	ACTIONS_PLAYER2_MOVEFWD,
	ACTIONS_PLAYER2_MOVEDOWN,
	ACTIONS_PLAYER2_FIRE,
	ACTIONS_PLAYER2_TURNLEFT,	
	ACTIONS_PLAYER2_TURNRIGHT,
	ACTIONS_F1,
	ACTIONS_F2,
	ACTIONS_F3,
	ACTIONS_F4,
	ACTIONS_F5,
	ACTIONS_F6,
	ACTIONS_F7,
	ACTIONS_F8,
	ACTIONS_F9,
	ACTIONS_F10,
	ACTIONS_F11,
	ACTIONS_F12,

	ACTIONS_ENTER,
	ACTIONS_TAB,
	ACTIONS_SPACE,
	ACTIONS_YES,
	ACTIONS_N0,
	ACTIONS_RSHIFT,
	ACTIONS_PLAYER2ATTACK,

	ACTIONS_NONE
};

struct CustomKeys
{
	string keys;
	DWORD dwSemantics;
	CustomKeys(){};
	CustomKeys(const string &sKey, const DWORD dw)
	{
		keys = sKey;
		dwSemantics= dw;
	}
};
class PCInputcontroller : public IController
{
public :

	~PCInputcontroller();
	PCInputcontroller();

	void Start();

	void Stop();

	bool KeyDown(Key key);

	bool KeyUP(Key key);

	bool KeyPressed(int Key);

	void Update();
	void CheckInput();
	
	bool ActionKeysActive(UINT nAction, bool IsContinousKeyPress);
	

private:

	LPDIRECTINPUT8			m_pDI;
	bool					InitDirectInput(void);

	bool					bKeyBuffer[33];  // 32 key mappings
	vector<CustomKeys> m_customKeys;

	bool					bDiscreteKeyBuffer[34];  // 32 key mappings
	bool					bKeyPress[34];  // 32 key mappings

	static	const GUID		m_GuidApp;
	DWORD					m_DwGenre;
	DWORD					m_TotalActions;
	char					m_ActionMapName[20];
	int						m_nDevices;
	DIACTIONFORMAT			m_diaf;
	LPDIRECTINPUTDEVICE8	*m__pDeviceArray;
	static DIACTION			g_RegActions[];
	DIACTION				m_Actions[15];
	int						nP1Keys[4];
	int						nP2Keys[4];
	void					AcquireDevices();
	void					UnacquireDevices();
	void					LoadConfig();
	bool					isPlayer1GamePad;
	bool					isPlayer2GamePad;
	

	static BOOL  CALLBACK statDIEnumDevicesBySemanticsCallback(LPCDIDEVICEINSTANCE lpddi,  
		LPDIRECTINPUTDEVICE8	lpdid, DWORD dwFlags, DWORD dwRemaining, LPVOID pvRef);

	BOOL DIEnumDevicesBySemanticsCallback(LPCDIDEVICEINSTANCE lpddi,  
		LPDIRECTINPUTDEVICE8	lpdid, DWORD dwFlags, DWORD dwRemaining, LPVOID pvRef);
	void ActionKeys(UINT nAction, DWORD dwData);
	void LoadCustomkeys();
	const int TrimString(const int &nStrlength, const char *pInputStr, char *pOutStr);
	const int Readtheline(ifstream *fin, char *pOutputStr, const int &nStrSize);
	const int RemoveSpaces(const int &nStrlength, const char *pInputStr, char *pOutStr);
	const int GetValue(const int &nStrlength, const char *pInputStr, char *pOutStr);
	const int AssginPlayer1contols(ifstream *fin, const int &nTotalParams);
	const int AssginPlayer2contols(ifstream *fin, const int &nTotalParams);
	const int AssginKeys(ifstream *fin, const int &nTotalParams);
	bool ActionMapLookUpTable(const int &nStrlength, const char *pInputStr, char *pOutStr);
	void ToLowerCase(const char *pIpStr, char *pOpstr);
	bool LookUpTable(const char *c, DWORD *dwSemantics, const int &nIndex);
	bool CheckExistingKeys(const DWORD &newKey, const int &nIndex);
	bool DiscreteActionKeys(const int &nIndex);
	void SetKeyBuffer(const int &nIndex , const  DWORD &dwData);
	void AssignControlsToPlayers();
};
