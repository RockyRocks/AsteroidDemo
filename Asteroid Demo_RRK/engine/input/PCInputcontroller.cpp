#include "PCInputcontroller.h"


// you can Assign your Own GUID by GUID generator provided by microsoft
const GUID	PCInputcontroller::m_GuidApp = { 0xbd0e8406, 0xfb56, 0x4322, {0x8b, 0xc6, 0xbd, 0x6e, 0x48, 0x1f, 0x55, 0x64 } };

DIACTION PCInputcontroller::g_RegActions[] =
{

	{ ACTIONS_PLAYER1_MOVEFWD,		 DIKEYBOARD_UP,			 0, "Up"},
	{ ACTIONS_PLAYER1_MOVEDOWN,		 DIKEYBOARD_DOWN,		 0, "Down"},
	{ ACTIONS_PLAYER1_TURNLEFT,		 DIKEYBOARD_LEFT,		 0, "Left"},
	{ ACTIONS_PLAYER1_TURNRIGHT,	 DIKEYBOARD_RIGHT,		 0, "Right"},
	{ ACTIONS_PLAYER1_FIRE,			 DIKEYBOARD_RCONTROL,	 0, "Fire"},

	{ ACTIONS_PLAYER2_MOVEFWD,		 DIKEYBOARD_W,			 0, "Up"},
	{ ACTIONS_PLAYER2_MOVEDOWN,		 DIKEYBOARD_S,		     0, "Down"},
	{ ACTIONS_PLAYER2_TURNLEFT,		 DIKEYBOARD_A,		     0, "Left"},
	{ ACTIONS_PLAYER2_TURNRIGHT,	 DIKEYBOARD_D,		     0, "Right"},
	{ ACTIONS_PLAYER2_FIRE,		     DIKEYBOARD_LCONTROL,	 0, "Fire"},

	{ ACTIONS_PLAYER2LEFTRIGHT, DIAXIS_ARCADES_LATERAL,     0, "Left/Right"},
	{ ACTIONS_PLAYER2UPDOWN,    DIAXIS_ARCADES_MOVE ,	    0, "Up/Down"},

	{ ACTIONS_QUIT,				DIKEYBOARD_ESCAPE,	     0, "Quit"},

	{ ACTIONS_F1,				DIKEYBOARD_F1,	     0, "F1_Key"},
	{ ACTIONS_F2,				DIKEYBOARD_F2,	     0, "F2_Key"},
	{ ACTIONS_F3,				DIKEYBOARD_F3,	     0, "F3_Key"},
	{ ACTIONS_F4,				DIKEYBOARD_F4,	     0, "F4_Key"},
	{ ACTIONS_F5,				DIKEYBOARD_F5,	     0, "F5_Key"},
	{ ACTIONS_F6,				DIKEYBOARD_F6,	     0, "F6_Key"},
	{ ACTIONS_F7,				DIKEYBOARD_F7,	     0, "F7_Key"},
	{ ACTIONS_F8,				DIKEYBOARD_F8,	     0, "F8_Key"},
	{ ACTIONS_F9,				DIKEYBOARD_F9,	     0, "F9_Key"},
	{ ACTIONS_F10,				DIKEYBOARD_F10,	     0, "F10_Key"},
	{ ACTIONS_F11,				DIKEYBOARD_F11,	     0, "F11_Key"},
	{ ACTIONS_F12,				DIKEYBOARD_F12,	     0, "F12_Key"},
	
	{ ACTIONS_ENTER,			DIKEYBOARD_RETURN,	 0, "ENTER_Key"},
	{ ACTIONS_TAB,				DIKEYBOARD_TAB,	     0, "TAB_Key"},
	{ ACTIONS_YES,				DIKEYBOARD_Y,	     0, "YES_Key"},
	{ ACTIONS_N0,				DIKEYBOARD_N,	     0, "NO_Key"},
	{ ACTIONS_RSHIFT,		    DIKEYBOARD_RSHIFT, 0, "RightControl_Key"},
	{ ACTIONS_SPACE,		    DIKEYBOARD_SPACE,    0, "Space_Key"},

	{ ACTIONS_PLAYER2ATTACK,    DIBUTTON_ARCADES_ATTACK,0, "KEYBOARDATTACK"},
};

PCInputcontroller::PCInputcontroller():isPlayer1GamePad(false), isPlayer2GamePad(false)
{
	m_pDI = NULL;
	m_nDevices = 0;
	m__pDeviceArray = NULL;
	m_DwGenre = DIVIRTUAL_ARCADE_SIDE2SIDE;
	sprintf_s(m_ActionMapName, sizeof(m_ActionMapName)/ sizeof(char), "%s","Asteroid");
	for (int i=0; i<(sizeof(bKeyBuffer)/sizeof(bKeyBuffer[0]));i++)
	{
		bKeyBuffer[i] = 0;
	}

	for (int i=0; i<(sizeof(bDiscreteKeyBuffer)/sizeof(bDiscreteKeyBuffer[0]));i++)
	{
		bDiscreteKeyBuffer[i] = 0;
	}

	for (int i=0; i<(sizeof(bKeyPress)/sizeof(bKeyPress[0]));i++)
	{
		bKeyPress[i] = 0;
	}
	for (int i=0; i<(sizeof(nP1Keys)/sizeof(nP1Keys[0]));i++)
	{
		nP1Keys[i] = 0;
	}
	for (int i=0; i<(sizeof(nP2Keys)/sizeof(nP2Keys[0]));i++)
	{
		nP2Keys[i] = 0;
	}
}


PCInputcontroller::~PCInputcontroller()
{
	
}


void PCInputcontroller::Start()
{
	Logger::GetInstance()->printMsg(INFO, "Starting input controller");
	m_pDI = NULL;
	LoadCustomkeys();
	LoadConfig();
	AssignControlsToPlayers();
	m_TotalActions = sizeof(g_RegActions) / sizeof(DIACTION);
	if(!InitDirectInput())
	{
		cout<<"InitDirectInput is not Initialized"<<endl;
	}
	AcquireDevices();
}

void PCInputcontroller::LoadConfig()
{
	ifstream	fin;
	fin.open("Input.cfg", ifstream::in);
	if(!fin.is_open())
	{		
		Logger::GetInstance()->printMsg(INFO, "Cannot find Input.cfg");
		return;
	}
	while(!fin.eof())
	{
		char cReadChar[256];
		int nLengthOfLine = Readtheline(&fin,cReadChar, sizeof(cReadChar));
		if(nLengthOfLine == 0)continue;
		istrstream streamin (cReadChar, nLengthOfLine );
		string temp="";
		streamin>>temp;
		if(!_stricmp(temp.c_str(), "Player1"))
		{
			AssginPlayer1contols(&fin, 4);  // no.of parameters
		}
		if(!_stricmp(temp.c_str(), "Player2"))
		{
			AssginPlayer2contols(&fin, 4);
		}
		if(!_stricmp(temp.c_str(), "Keys"))
		{
			Logger::GetInstance()->printMsg(INFO, "Assigning keys");
			AssginKeys(&fin, 2);
		}
	}
	fin.close();
}

/*
The function is to read the line from the script
*/
const int PCInputcontroller::Readtheline(ifstream *fin, char *pOutputStr, const int &nStrSize)
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
const int PCInputcontroller::TrimString(const int &nStrlength, const char *pInputStr, char *pOutStr)
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
const int PCInputcontroller::RemoveSpaces(const int &nStrlength, const char *pInputStr, char *pOutStr)
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
const int PCInputcontroller::GetValue(const int &nStrlength, const char *pInputStr, char *pOutStr)
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

const int PCInputcontroller::AssginPlayer1contols(ifstream *fin, const int &nTotalParams)
{
	
	Logger::GetInstance()->printMsg(INFO, "Assigning P1 keys");

	float width = 0.0f;
	float Height =0.0f;

	int nCount = 0;
	while (!fin->eof())
	{
		if(nCount == nTotalParams)
		{
			return 1;
		}
		else
		{
			char cReadChar[256], cForMattedOutput[256], cMappingString[256];
			int nLengthOfLine = Readtheline(fin, cReadChar, sizeof(cReadChar));
			if(nLengthOfLine == 0)continue;
			nLengthOfLine = GetValue(nLengthOfLine, cReadChar, cForMattedOutput);
			istrstream streamin (cForMattedOutput, nLengthOfLine );
			string tempStr;
			streamin>>tempStr;
			DWORD dwSemantics = 0;
			ActionMapLookUpTable(nLengthOfLine,tempStr.c_str(), cMappingString );
			if(nCount ==0)
			{
				if(LookUpTable(cMappingString, &dwSemantics, 0))
				{
					g_RegActions[0].dwSemantic = dwSemantics;
				}
			}
			else if(nCount ==1)
			{
				if(LookUpTable(cMappingString, &dwSemantics, 2))
				{
					g_RegActions[2].dwSemantic = dwSemantics;
				}
			}
			else if(nCount ==2)
			{
				if(LookUpTable(cMappingString, &dwSemantics, 3))
				{
					g_RegActions[3].dwSemantic = dwSemantics;
				}
			}
			else if(nCount ==3)
			{
				if(LookUpTable(cMappingString, &dwSemantics, 4))
				{
					g_RegActions[4].dwSemantic = dwSemantics;
				}
			}
			nCount++;
		}
	}
	return 0;
}

const int PCInputcontroller::AssginKeys(ifstream *fin, const int &nTotalParams)
{
	float width = 0.0f;
	float Height =0.0f;

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
			string tempStr;
			streamin>>tempStr;
			char lowercase[256];
			ToLowerCase(tempStr.c_str(), lowercase);
			if(nCount ==0)
			{
				if(!strcmp(lowercase, "keyboard"))
				{
					Logger::GetInstance()->printMsg(INFO, "Setting P1 Keyboard");
					isPlayer1GamePad = false;
				}
				else 
				{
					Logger::GetInstance()->printMsg(INFO, "Setting P1 Gamepad");

					isPlayer1GamePad = true;
				}
				
			}
			else if(nCount ==1)
			{
				if(!strcmp(lowercase, "keyboard"))
				{
					isPlayer2GamePad = false;
				}
				else 
				{
					isPlayer2GamePad = true;
				}
			}
			nCount++;
		}
	}
	return 0;
}

bool PCInputcontroller::ActionMapLookUpTable(const int &nStrlength, const char *pInputStr, char *pOutStr)
{
	if(nStrlength <=0)
	{
		return 0;
	}
	else
	{
		ToLowerCase(pInputStr, pOutStr);
		return 1;
	}
	return 0;
}

/*
This function is to convert the string to lower case
*/
void PCInputcontroller::ToLowerCase(const char *pIpStr, char *pOpstr)
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
const int PCInputcontroller::AssginPlayer2contols(ifstream *fin, const int &nTotalParams)
{
	float width = 0.0f;
	float Height =0.0f;

	int nCount = 0;
	while (!fin->eof())
	{
		if(nCount == nTotalParams)
		{
			return 1;
		}
		else
		{
			char cReadChar[256], cForMattedOutput[256], cMappingString[256];
			int nLengthOfLine = Readtheline(fin, cReadChar, sizeof(cReadChar));
			if(nLengthOfLine == 0)continue;
			nLengthOfLine = GetValue(nLengthOfLine, cReadChar, cForMattedOutput);
			istrstream streamin (cForMattedOutput, nLengthOfLine );
			string tempStr;
			streamin>>tempStr;
			DWORD dwSemantics = 0;
			ActionMapLookUpTable(nLengthOfLine,tempStr.c_str(), cMappingString );
			if(nCount ==0)
			{
				if(LookUpTable(cMappingString, &dwSemantics, 5))
				{
					g_RegActions[5].dwSemantic = dwSemantics;
				}
			}
			else if(nCount ==1)
			{
				if(LookUpTable(cMappingString, &dwSemantics, 7))
				{
					g_RegActions[7].dwSemantic = dwSemantics;
				}
			}
			else if(nCount ==2)
			{
				if(LookUpTable(cMappingString, &dwSemantics, 8))
				{
					g_RegActions[8].dwSemantic = dwSemantics;
				}
			}
			else if(nCount ==3)
			{
				if(LookUpTable(cMappingString, &dwSemantics, 9))
				{
					g_RegActions[9].dwSemantic = dwSemantics;
				}
			}
			nCount++;
		}
	}
	return 0;
}
void PCInputcontroller::Stop()
{
	UnacquireDevices();
	if(m__pDeviceArray!= NULL)
	{
		delete [] m__pDeviceArray;
		m__pDeviceArray = NULL;
		m_nDevices = 0;
	}

	if(m_pDI != NULL)
	{
		m_pDI->Release();
		m_pDI = NULL;
	}

}

bool PCInputcontroller::KeyDown(Key key)
{

	return true;
}

bool PCInputcontroller::KeyPressed(int Key)
{

	return false;
}

bool PCInputcontroller::KeyUP(Key key)
{
	return true;
}

/*
	Update state of keyboard device	
*/
void PCInputcontroller::Update()
{
	CheckInput();
}

BOOL  PCInputcontroller::DIEnumDevicesBySemanticsCallback(LPCDIDEVICEINSTANCE lpddi,  
														IDirectInputDevice8	*lpdid, DWORD dwFlags, 
														DWORD dwRemaining, LPVOID pvRef)
{
	HRESULT		hr;

	// Devices of type DI8DEVTYPE_DEVICECTRL are specialized devices not generally
	// considered appropriate to control game actions. We just ignore these.
	if (GET_DIDEVICE_TYPE(lpddi->dwDevType) == DI8DEVTYPE_DEVICECTRL)
		return DIENUM_CONTINUE;

	// Assign exclusive control of this device to us.
	hr = lpdid->SetCooperativeLevel(NULL, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
	//if(FAILED(m_pDIKeyboardDevice->SetCooperativeLevel(NULL, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))

	if (FAILED(hr))
		return DIENUM_CONTINUE;

	// Build the action map for the device. This will map each action to
	//  the most appropriate function on the device.
	hr = lpdid->BuildActionMap(&m_diaf, NULL, DIDBAM_DEFAULT);
	if (FAILED(hr))
		return DIENUM_CONTINUE;
	DWORD i =0;
	for (i = 0; i < m_diaf.dwNumActions; i++)
	{
		if (m_diaf.rgoAction[i].dwHow != DIAH_UNMAPPED)
			break;
	}
	if (i < m_diaf.dwNumActions)
	{
		// If any controls were mapped, we will be using this device,
		//  so set the action map on this device.
		hr = lpdid->SetActionMap(&m_diaf, NULL, DIDSAM_DEFAULT);
		if (FAILED(hr))
			return DIENUM_CONTINUE;

		if (m__pDeviceArray == NULL)
			m__pDeviceArray = new LPDIRECTINPUTDEVICE8[dwRemaining + 1];

		m__pDeviceArray[m_nDevices] = lpdid;
		m_nDevices++;

		// Add a reference to this device, since DirectInput will 
		//  release the device when we return.
		lpdid->AddRef();
	}
	return DIENUM_CONTINUE;
}



BOOL CALLBACK PCInputcontroller::statDIEnumDevicesBySemanticsCallback(LPCDIDEVICEINSTANCE lpddi,  
									  LPDIRECTINPUTDEVICE8	lpdid, DWORD dwFlags, DWORD dwRemaining, LPVOID pvRef)
{
	PCInputcontroller *pthis = reinterpret_cast<PCInputcontroller*>(pvRef);

	//PCInputcontroller *pthis = (PCInputcontroller*)statDIEnumDevicesBySemanticsCallback;
	return (pthis->DIEnumDevicesBySemanticsCallback(lpddi,  
		lpdid, dwFlags, 
		 dwRemaining,pvRef));
}
// Acquire (obtain control of) the devices
void PCInputcontroller::AcquireDevices()
{
	for (int iDevice = 0; iDevice < m_nDevices; iDevice++)
		m__pDeviceArray[iDevice]->Acquire();
}

// Unacquire (release control of) the devices
void PCInputcontroller::UnacquireDevices()
{
	if (m__pDeviceArray == NULL)
		return;

	for (int iDevice = 0; iDevice < m_nDevices; iDevice++)
	{
		m__pDeviceArray[iDevice]->Unacquire();
		m__pDeviceArray[iDevice]->Release();
	}
}

/*
	Init keyboard device
*/	
bool PCInputcontroller::InitDirectInput(void)
{

	if(FAILED(DirectInput8Create(GetModuleHandle(NULL),DIRECTINPUT_VERSION, IID_IDirectInput8,(void**)&m_pDI,NULL)))
	{
		//Logger::GetInstance()->printMsg(ERROR, "DirectInput8Create() failed! - InitDirectInput()");
		return false;
	}

	ZeroMemory(&m_diaf, sizeof(DIACTIONFORMAT));
	m_diaf.dwSize = sizeof(DIACTIONFORMAT);
	m_diaf.dwActionSize = sizeof(DIACTION);
	m_diaf.dwNumActions = m_TotalActions;
	m_diaf.dwDataSize = m_TotalActions * sizeof(DWORD);
	m_diaf.rgoAction = g_RegActions;
	m_diaf.guidActionMap = m_GuidApp;
	m_diaf.dwGenre = m_DwGenre;
	m_diaf.dwBufferSize = 16;
	m_diaf.lAxisMin = -100;
	m_diaf.lAxisMax = 100;
	sprintf_s(m_diaf.tszActionMap, MAX_PATH, m_ActionMapName);

	if (FAILED(m_pDI->EnumDevicesBySemantics(NULL, &m_diaf, &PCInputcontroller::statDIEnumDevicesBySemanticsCallback,
		this, DIEDBSFL_ATTACHEDONLY)))
	{
		return FALSE;
	}

	return true;
}



void PCInputcontroller::CheckInput()
{
	DIDEVICEOBJECTDATA	pdidod[INPUT_DATA_LIMIT];
	DWORD				dwObjCount;

	if (m__pDeviceArray == NULL)
		return;

	for (int iDevice = 0; iDevice < m_nDevices; iDevice++)
	{
		// Poll the device for data. 
		m__pDeviceArray[iDevice]->Poll(); 

		// Retrieve the data.
		dwObjCount = INPUT_DATA_LIMIT;
		m__pDeviceArray[iDevice]->GetDeviceData(sizeof(DIDEVICEOBJECTDATA),
			pdidod,
			&dwObjCount, 0);

		for (DWORD i = 0; i < dwObjCount; i++)
		{
			// Handle the actions regardless of what device returned them.
			ActionKeys(pdidod[i].uAppData, pdidod[i].dwData);
			//cout<<"dwObjCount"<<dwObjCount<<endl;
		}
		//current = 0;
	}
}

void PCInputcontroller::AssignControlsToPlayers()
{
	if((isPlayer1GamePad)&&(isPlayer2GamePad)) // default P1 -> keyboard and P2 -> Keyboard
	{
		nP1Keys[0] = 0; // 		return;
		nP1Keys[1] = 2;
		nP1Keys[2] = 3;
		nP1Keys[3] = 4;

		nP2Keys[0] = 5;
		nP2Keys[1] = 7;
		nP2Keys[2] = 8;
		nP2Keys[3] = 9;
		return;
	}
	else if((!isPlayer1GamePad)&&(isPlayer2GamePad)) // P1 -> keyboard and P2 -> joystick
	{
		nP1Keys[0] = 0; // 		return;
		nP1Keys[1] = 2;
		nP1Keys[2] = 3;
		nP1Keys[3] = 4;

		nP2Keys[0] = 10;
		nP2Keys[1] = 11;
		nP2Keys[2] = 12;
		nP2Keys[3] = 33;
		return;

	}
	else if((isPlayer1GamePad)&&(!isPlayer2GamePad)) // P1 -> joystick and P2 -> GamePad
	{
		nP1Keys[0] = 10; // 		return;
		nP1Keys[1] = 11;
		nP1Keys[2] = 12;
		nP1Keys[3] = 33;

		nP2Keys[0] = 5;
		nP2Keys[1] = 7;
		nP2Keys[2] = 8;
		nP2Keys[3] = 9;
		return;
	}
	else
	{
		nP1Keys[0] = 0; // 		return;
		nP1Keys[1] = 2;
		nP1Keys[2] = 3;
		nP1Keys[3] = 4;

		nP2Keys[0] = 5;
		nP2Keys[1] = 7;
		nP2Keys[2] = 8;
		nP2Keys[3] = 9;
		return;
	}

}

void PCInputcontroller::ActionKeys(UINT nAction, DWORD dwData)
{
	int	nAxisPos = (int)dwData;
	switch (nAction)
	{
		case ACTIONS_PLAYER1_MOVEFWD:
			SetKeyBuffer(0, dwData);
			break;

		case ACTIONS_PLAYER1_MOVEDOWN:
			SetKeyBuffer(1, dwData);
			break;

		case ACTIONS_PLAYER1_TURNLEFT:
			SetKeyBuffer(2, dwData);
			break;

		case ACTIONS_PLAYER1_TURNRIGHT:
			SetKeyBuffer(3, dwData);
			break;

		case ACTIONS_PLAYER1_FIRE:
			SetKeyBuffer(4, dwData);
			break;

		case ACTIONS_PLAYER2_MOVEFWD:
			SetKeyBuffer(5, dwData);
			break;

		case ACTIONS_PLAYER2_MOVEDOWN:
			SetKeyBuffer(6, dwData);
			break;

		case ACTIONS_PLAYER2_TURNLEFT:
			SetKeyBuffer(7, dwData);
			break;

		case ACTIONS_PLAYER2_TURNRIGHT:
			SetKeyBuffer(8, dwData);
			break;

		case ACTIONS_PLAYER2_FIRE:
			SetKeyBuffer(9, dwData);
			break;
		
		case ACTIONS_PLAYER2LEFTRIGHT:
			if (nAxisPos < -AXIS_THRESHOLD)
			{
				bKeyBuffer[10] = true;
				bKeyBuffer[11] = false;
			}
			else if (nAxisPos > AXIS_THRESHOLD)
			{
				bKeyBuffer[11] = true;
				bKeyBuffer[10] = false;
			}
			else
			{
				bKeyBuffer[10] = false;
				bKeyBuffer[11] = false;
			}
			break;

		case ACTIONS_PLAYER2UPDOWN:
			if (nAxisPos < -AXIS_THRESHOLD)
			{
				bKeyBuffer[12] = true;
				bKeyBuffer[13] = false;
			}
			else if (nAxisPos > AXIS_THRESHOLD)
			{
				bKeyBuffer[13] = true;
				bKeyBuffer[12] = false;
			}
			else
			{
				bKeyBuffer[12] = false;
				bKeyBuffer[13] = false;
			}
			break;

		case ACTIONS_QUIT:
			SetKeyBuffer(14, dwData);
			break;

		case ACTIONS_F1:
			SetKeyBuffer(15, dwData);
			break;

		case ACTIONS_F2:
			SetKeyBuffer(16, dwData);
			break;

		case ACTIONS_F3:
			SetKeyBuffer(17, dwData);
			break;

		case ACTIONS_F4:
			SetKeyBuffer(18, dwData);
			break;

		case ACTIONS_F5:
			SetKeyBuffer(19, dwData);
			break;

		case ACTIONS_F6:
			SetKeyBuffer(20, dwData);
			break;

		case ACTIONS_F7:
			SetKeyBuffer(21, dwData);
			break;

		case ACTIONS_F8:
			SetKeyBuffer(22, dwData);
			break;

		case ACTIONS_F9:
			SetKeyBuffer(23, dwData);
			break;

		case ACTIONS_F10:
			SetKeyBuffer(24, dwData);
			break;

		case ACTIONS_F11:
			SetKeyBuffer(25, dwData);
			break;

		case ACTIONS_F12:
			SetKeyBuffer(26, dwData);
			break;

		case ACTIONS_ENTER:
			SetKeyBuffer(27, dwData);
			break;

		case ACTIONS_TAB:
			SetKeyBuffer(28, dwData);
			break;


		case ACTIONS_YES:
			SetKeyBuffer(29, dwData);
			break;

		case ACTIONS_N0:
			SetKeyBuffer(30, dwData);
			break;

		case ACTIONS_RSHIFT:
			SetKeyBuffer(31, dwData);
			break;

		case ACTIONS_SPACE:
			SetKeyBuffer(32, dwData);
			break;

		case ACTIONS_PLAYER2ATTACK:
			SetKeyBuffer(33, dwData);
			break;

		default:
			break;
	}
}


void PCInputcontroller::SetKeyBuffer(const int &nIndex , const  DWORD &dwData)
{
	if(bKeyPress[nIndex] ==0)
	{
		bKeyPress[nIndex] =1;
	}
	else if(bKeyPress[nIndex] ==1)
	{
		bKeyPress[nIndex] = 0;
		bDiscreteKeyBuffer[nIndex] = 1;
	}
	bKeyBuffer[nIndex] = (dwData != 0);
}

bool PCInputcontroller::ActionKeysActive(UINT nAction, bool IsContinousKeyPress)
{
	switch (nAction)
	{
	case ACTIONS_PLAYER1_MOVEFWD:
		if(IsContinousKeyPress)
		{
			return(bKeyBuffer[nP1Keys[0]]);
		}
		else
		{	
			return(DiscreteActionKeys(nP1Keys[0]));
		}

	case ACTIONS_PLAYER1_MOVEDOWN:
		if(IsContinousKeyPress)
		{
			return(bKeyBuffer[1]);
		}
		else
		{	
			return(DiscreteActionKeys(1));
		}

	case ACTIONS_PLAYER1_TURNLEFT:
		if(IsContinousKeyPress)
		{
			return(bKeyBuffer[nP1Keys[1]]);
		}
		else
		{	
			return(DiscreteActionKeys(nP1Keys[1]));
		}

	case ACTIONS_PLAYER1_TURNRIGHT:
		if(IsContinousKeyPress)
		{
			return(bKeyBuffer[nP1Keys[2]]);
		}
		else
		{	
			return(DiscreteActionKeys(nP1Keys[2]));
		}

	case ACTIONS_PLAYER1_FIRE:
		if(IsContinousKeyPress)
		{
			return(bKeyBuffer[nP1Keys[3]]);
		}
		else
		{	
			return(DiscreteActionKeys(nP1Keys[3]));
		}


	case ACTIONS_PLAYER2_MOVEFWD:
		if(IsContinousKeyPress)
		{
			return(bKeyBuffer[nP2Keys[0]]);
		}
		else
		{	
			return(DiscreteActionKeys(nP2Keys[0]));
		}


	case ACTIONS_PLAYER2_MOVEDOWN:
		if(IsContinousKeyPress)
		{
			return(bKeyBuffer[6]);
		}
		else
		{	
			return(DiscreteActionKeys(6));
		}


	case ACTIONS_PLAYER2_TURNLEFT:
		if(IsContinousKeyPress)
		{
			return(bKeyBuffer[nP2Keys[1]]);
		}
		else
		{	
			return(DiscreteActionKeys(nP2Keys[1]));
		}


	case ACTIONS_PLAYER2_TURNRIGHT:
		if(IsContinousKeyPress)
		{
			return(bKeyBuffer[nP2Keys[2]]);
		}
		else
		{	
			return(DiscreteActionKeys(nP2Keys[2]));
		}


	case ACTIONS_PLAYER2_FIRE:
		if(IsContinousKeyPress)
		{
			return(bKeyBuffer[nP2Keys[3]]);
		}
		else
		{	
			return(DiscreteActionKeys(nP2Keys[3]));
		}
/*
	case ACTIONS_PLAYER2_JOYLEFT:

		if(IsContinousKeyPress)
		{
			return(bKeyBuffer[10]);
		}
		else
		{	
			return(DiscreteActionKeys(10));
		}

		
	case ACTIONS_PLAYER2_JOYRIGHT:
		if(bKeyBuffer[11])
		{
			return bKeyBuffer[11];
		}
		
		else
		{
			return false;
		}
		
	case ACTIONS_PLAYER2UPDOWN:
		if(bKeyBuffer[12])
		{
			return bKeyBuffer[12];
		}
		else if(bKeyBuffer[13])
		{
			return bKeyBuffer[13];
		}
		else
		{
			return false;
		}
		break;
*/
	case ACTIONS_QUIT:
		if(IsContinousKeyPress)
		{
			return(bKeyBuffer[14]);
		}
		else
		{	
			return(DiscreteActionKeys(14));
		}


	case ACTIONS_F1:
		if(IsContinousKeyPress)
		{
			return(bKeyBuffer[15]);
		}
		else
		{	
			return(DiscreteActionKeys(15));
		}

	case ACTIONS_F2:
		if(IsContinousKeyPress)
		{
			return(bKeyBuffer[16]);
		}
		else
		{	
			return(DiscreteActionKeys(16));
		}

	case ACTIONS_F3:
		if(IsContinousKeyPress)
		{
			return(bKeyBuffer[17]);
		}
		else
		{	
			return(DiscreteActionKeys(17));
		}

	case ACTIONS_F4:
		if(IsContinousKeyPress)
		{
			return(bKeyBuffer[18]);
		}
		else
		{	
			return(DiscreteActionKeys(18));
		}

	case ACTIONS_F5:
		if(IsContinousKeyPress)
		{
			return(bKeyBuffer[19]);
		}
		else
		{	
			return(DiscreteActionKeys(19));
		}

	case ACTIONS_F6:
		if(IsContinousKeyPress)
		{
			return(bKeyBuffer[20]);
		}
		else
		{	
			return(DiscreteActionKeys(20));
		}

	case ACTIONS_F7:
		if(IsContinousKeyPress)
		{
			return(bKeyBuffer[21]);
		}
		else
		{	
			return(DiscreteActionKeys(21));
		}

	case ACTIONS_F8:
		if(IsContinousKeyPress)
		{
			return(bKeyBuffer[22]);
		}
		else
		{	
			return(DiscreteActionKeys(22));
		}

	case ACTIONS_F9:
		if(IsContinousKeyPress)
		{
			return(bKeyBuffer[23]);
		}
		else
		{	
			return(DiscreteActionKeys(23));
		}
		break;

	case ACTIONS_F10:
		if(IsContinousKeyPress)
		{
			return(bKeyBuffer[24]);
		}
		else
		{	
			return(DiscreteActionKeys(24));
		}

	case ACTIONS_F11:
		if(IsContinousKeyPress)
		{
			return(bKeyBuffer[25]);
		}
		else
		{	
			return(DiscreteActionKeys(25));
		}

	case ACTIONS_F12:
		if(IsContinousKeyPress)
		{
			return(bKeyBuffer[26]);
		}
		else
		{	
			return(DiscreteActionKeys(26));
		}
		break;

	case ACTIONS_ENTER:
		if(IsContinousKeyPress)
		{
			return(bKeyBuffer[27]);
		}
		else
		{	
			return(DiscreteActionKeys(27));
		}
		break;

	case ACTIONS_TAB:
		if(IsContinousKeyPress)
		{
			return(bKeyBuffer[28]);
		}
		else
		{	
			return(DiscreteActionKeys(28));
		}
		break;

	case ACTIONS_YES:
		if(IsContinousKeyPress)
		{
			return(bKeyBuffer[29]);
		}
		else
		{	
			return(DiscreteActionKeys(29));
		}
		break;

	case ACTIONS_N0:
		if(IsContinousKeyPress)
		{
			return(bKeyBuffer[30]);
		}
		else
		{	
			return(DiscreteActionKeys(30));
		}
		break;

	case ACTIONS_RSHIFT:
		if(IsContinousKeyPress)
		{
			return(bKeyBuffer[31]);
		}
		else
		{	
			return(DiscreteActionKeys(31));
		}
		break;

	case ACTIONS_SPACE:
		if(IsContinousKeyPress)
		{
			return(bKeyBuffer[32]);
		}
		else
		{	
			return(DiscreteActionKeys(32));
		}
		break;

	//case ACTIONS_PLAYER2ATTACK:
	//	if(IsContinousKeyPress)
	//	{
	//		return(bKeyBuffer[33]);
	//	}
	//	else
	//	{	
	//		return(DiscreteActionKeys(33));
	//	}
	//	break;

	default:
		return 0;
	}
}
bool PCInputcontroller::DiscreteActionKeys(const int &nIndex)
{
	int nSize = sizeof(bDiscreteKeyBuffer)/sizeof(bDiscreteKeyBuffer[0]);
	if(nIndex >= nSize)
	{
		return 0;
	}
	else
	{
		if(bDiscreteKeyBuffer[nIndex] ==1)
		{
			bDiscreteKeyBuffer[nIndex] = 0;
			return true;
		}
		else
		{
			return(bDiscreteKeyBuffer[nIndex]);
		}
	}
}

bool PCInputcontroller::LookUpTable(const char *c, DWORD *dwSemantics, const int &nIndex)
{
	vector<CustomKeys>::iterator it;
	CustomKeys tempCustomKeys;
	for (it = m_customKeys.begin(); it!= m_customKeys.end(); ++it)
	{
		tempCustomKeys = *it;
		if(tempCustomKeys.keys == c)
		{
			if(CheckExistingKeys(tempCustomKeys.dwSemantics, nIndex))
			{
				*dwSemantics = tempCustomKeys.dwSemantics;
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}
	return 0;
}

bool PCInputcontroller::CheckExistingKeys(const DWORD &newKey, const int &nIndex)
{
	for (int i = 0; i<sizeof(g_RegActions) / sizeof(DIACTION); i++)
	{
		if((g_RegActions[i].dwSemantic == newKey) && (i != nIndex))
		{
			return 0;
		}
	}
	return 1;
}

void PCInputcontroller::LoadCustomkeys()
{

	m_customKeys.push_back(CustomKeys("a",DIKEYBOARD_A));
	m_customKeys.push_back(CustomKeys("b",DIKEYBOARD_B));
	m_customKeys.push_back(CustomKeys("c",DIKEYBOARD_C));
	m_customKeys.push_back(CustomKeys("d",DIKEYBOARD_D));
	m_customKeys.push_back(CustomKeys("e",DIKEYBOARD_E));
	m_customKeys.push_back(CustomKeys("f",DIKEYBOARD_F));
	m_customKeys.push_back(CustomKeys("g",DIKEYBOARD_G));
	m_customKeys.push_back(CustomKeys("h",DIKEYBOARD_H));
	m_customKeys.push_back(CustomKeys("i",DIKEYBOARD_I));
	m_customKeys.push_back(CustomKeys("j",DIKEYBOARD_J));
	m_customKeys.push_back(CustomKeys("k",DIKEYBOARD_K));
	m_customKeys.push_back(CustomKeys("l",DIKEYBOARD_L));
	m_customKeys.push_back(CustomKeys("m",DIKEYBOARD_M));
	m_customKeys.push_back(CustomKeys("n",DIKEYBOARD_N));

	m_customKeys.push_back(CustomKeys("o",DIKEYBOARD_O));
	m_customKeys.push_back(CustomKeys("p",DIKEYBOARD_P));
	m_customKeys.push_back(CustomKeys("q",DIKEYBOARD_Q));
	m_customKeys.push_back(CustomKeys("r",DIKEYBOARD_R));
	m_customKeys.push_back(CustomKeys("s",DIKEYBOARD_S));
	m_customKeys.push_back(CustomKeys("t",DIKEYBOARD_T));
	m_customKeys.push_back(CustomKeys("u",DIKEYBOARD_U));
	m_customKeys.push_back(CustomKeys("v",DIKEYBOARD_V));
	m_customKeys.push_back(CustomKeys("w",DIKEYBOARD_W));
	m_customKeys.push_back(CustomKeys("x",DIKEYBOARD_X));
	m_customKeys.push_back(CustomKeys("y",DIKEYBOARD_Y));
	m_customKeys.push_back(CustomKeys("z",DIKEYBOARD_Z));

	m_customKeys.push_back(CustomKeys("0",DIKEYBOARD_0));
	m_customKeys.push_back(CustomKeys("1",DIKEYBOARD_1));
	m_customKeys.push_back(CustomKeys("2",DIKEYBOARD_2));
	m_customKeys.push_back(CustomKeys("3",DIKEYBOARD_3));
	m_customKeys.push_back(CustomKeys("4",DIKEYBOARD_4));
	m_customKeys.push_back(CustomKeys("5",DIKEYBOARD_5));
	m_customKeys.push_back(CustomKeys("6",DIKEYBOARD_6));
	m_customKeys.push_back(CustomKeys("7",DIKEYBOARD_7));
	m_customKeys.push_back(CustomKeys("8",DIKEYBOARD_8));
	m_customKeys.push_back(CustomKeys("9",DIKEYBOARD_9));

	m_customKeys.push_back(CustomKeys("lctrl",DIKEYBOARD_LCONTROL));
	m_customKeys.push_back(CustomKeys("rctrl",DIKEYBOARD_RCONTROL));
	m_customKeys.push_back(CustomKeys("rshift",DIKEYBOARD_LCONTROL));
	m_customKeys.push_back(CustomKeys("lshift",DIKEYBOARD_RCONTROL));
	m_customKeys.push_back(CustomKeys("enter",DIKEYBOARD_RETURN));
	m_customKeys.push_back(CustomKeys("up",DIKEYBOARD_UP));
	m_customKeys.push_back(CustomKeys("down",DIKEYBOARD_DOWN));
	m_customKeys.push_back(CustomKeys("left",DIKEYBOARD_LEFT));
	m_customKeys.push_back(CustomKeys("right",DIKEYBOARD_RIGHT));
	m_customKeys.push_back(CustomKeys("space",DIKEYBOARD_SPACE));

	m_customKeys.push_back(CustomKeys("numpad0",DIKEYBOARD_NUMPAD0));
	m_customKeys.push_back(CustomKeys("numpad1",DIKEYBOARD_NUMPAD1));
	m_customKeys.push_back(CustomKeys("numpad2",DIKEYBOARD_NUMPAD2));
	m_customKeys.push_back(CustomKeys("numpad3",DIKEYBOARD_NUMPAD3));
	m_customKeys.push_back(CustomKeys("numpad4",DIKEYBOARD_NUMPAD4));
	m_customKeys.push_back(CustomKeys("numpad5",DIKEYBOARD_NUMPAD5));
	m_customKeys.push_back(CustomKeys("numpad6",DIKEYBOARD_NUMPAD6));
	m_customKeys.push_back(CustomKeys("numpad7",DIKEYBOARD_NUMPAD7));
	m_customKeys.push_back(CustomKeys("numpad8",DIKEYBOARD_NUMPAD8));
	m_customKeys.push_back(CustomKeys("numpad9",DIKEYBOARD_NUMPAD9));
}

