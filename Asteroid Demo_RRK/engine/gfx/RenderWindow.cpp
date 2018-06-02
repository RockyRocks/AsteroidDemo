#include "RenderWindow.h"
#include "..\..\common\logger\Logger.h"
#include "..\..\common\timer\WinTimer.h"

RenderWindow::RenderWindow()
{
	// Default value for Initializing the window
	 m_width= 800;
	 m_height=600;
	 m_bpp= 24;
	 m_refresh= 60;
	 m_fullscreen=0;
	 m_ExplosionX = 0.0f;
	 m_ExplosionY = 0.0f;
	 m_CreateExplosion = false;

	 for(int i=0; i < 16; ++i)
	 {
		 m_EntityTransMtx[i] = 0.0f;
	 }

	 float fTempPoints =1.0f;
	 Vector2f vTempVert;

	 vTempVert = Vector2f(fTempPoints, fTempPoints);
	 m_TranslationPos.push_back(vTempVert);
	 vTempVert = Vector2f(fTempPoints, -fTempPoints);
	 m_TranslationPos.push_back(vTempVert);
	 vTempVert = Vector2f(-fTempPoints, -fTempPoints);
	 m_TranslationPos.push_back(vTempVert);
	 vTempVert = Vector2f(-fTempPoints, -fTempPoints);
	 m_TranslationPos.push_back(vTempVert);
}

RenderWindow::~RenderWindow()
{

}

/*
 Check for Standard values entered by user, to enter into full Screen Mode
*/
void RenderWindow::CheckForResolution()
{
	if(m_width>=1600) 
	{
		m_width=1600;
		m_height=1200;
	}
	else if(m_width>=1280) 
	{
		m_width=1280;
		m_height=1024;
	}
	else if(m_width>=1024)
	{
		m_width=1024;
		m_height=768;
	}
	else if(m_width>=800) 
	{
		m_width=800;
		m_height=600;
		m_bpp = 24; /// 32 bit Per pixel is not supported by 800 X 600
	}
	else
	{
		m_width=640;
		m_height=480;
		m_bpp = 24; /// 32 bit Per pixel is not supported by 640 X 480
	}
}

void RenderWindow::LoadCfgInfo()
{
	ifstream ifs("Config.cfg");
	if(!ifs)
	{
		cout<<"unable to load Config file, loading Defaults"<<endl;
	}
	else
	{
		while(!ifs.eof()) 
		{
			char buffer[128];
			ifs >> buffer;
			if(string("Width") == buffer )
			{
				ifs >> m_width;
			}
			else if(string("Height") == buffer )
			{
				ifs >> m_height;
			}
			else if(std::string("Bpp") == buffer )
			{
				ifs >> m_bpp;
			}
			else if( std::string("Refresh") == buffer )
			{
				ifs >> m_refresh;
			}
			else if( std::string("Fullscreen") == buffer )
			{
				ifs >> m_fullscreen;
			}
		}
			// close the config file
		ifs.close();
	}
}

void RenderWindow::start()
{
	char gameModeStr[128];

	LoadCfgInfo();
	// set 32 bit or 24 bit in display mode (Bits Per Pixel)
	if(m_bpp == 32)
	{
		glutInitDisplayMode(GLUT_DEPTH|GLUT_RGBA|GLUT_DOUBLE);
	}
	else
	{
		m_bpp = 24;
		glutInitDisplayMode(GLUT_DEPTH|GLUT_RGB|GLUT_DOUBLE);
	}

	if(m_fullscreen)
	{
		CheckForResolution();
		sprintf_s(gameModeStr,"%dx%d:%d@%d",m_width,m_height,m_bpp,m_refresh);
		glutGameModeString(gameModeStr);
		glutEnterGameMode();
	}
	else
	{
		glutInitWindowSize(m_width,m_height);
		glutCreateWindow("Asteroid-Demo");
	}

	GraphicsManager::GetInstance()->setWidth(m_width);
	GraphicsManager::GetInstance()->setHeight(m_height);

	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
	glLineWidth(2.0f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	SetviewProjection();
}

void RenderWindow::stop()
{
	if(m_fullscreen)
	{
		glutLeaveGameMode();
	}
}

void RenderWindow::ResizeWindow(int w, int h)
{
	
}

void RenderWindow::SetviewProjection()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, m_width, 0, m_height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void RenderWindow::preRender()
{
#ifdef _DEBUG
	std::string s = "Asteroid [DEBUG] Dt = ";
	s.append(Utils::numberToString(WinTimer::GetInstance()->getDeltaTime()));
	s.append(" - Fps: ");
	s.append(Utils::numberToString((1/WinTimer::GetInstance()->getDeltaTime())));
	glutSetWindowTitle(s.c_str());
#endif

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );
	glClearColor(0.0, 0.0, 0.0, 1.0);
}
void RenderWindow::postRender()
{
	// Reset colour back to the original clear colour
	glColor3f(1.0f,1.0f,1.0f);
	glFlush();
	glutSwapBuffers();
}



void RenderWindow::createExplosion(const bool b, const float nx, const float ny)
{
	m_CreateExplosion = b;
	m_ExplosionX = nx;
	m_ExplosionY = ny;
}

bool RenderWindow::renderExplosion(float nx, float ny)
{
	static float ftotalDivisions = 20; // no of divisions in the collision
	static float fEachInterval = 0;
	static float inc = 1;
	static bool isInc = true;
	static bool bAddExplosionVertices = false;
	static bool isExplosionDrawn = false;

	float ntotalLen = 30;  // length of the vector or collision line 
	float len = ntotalLen;
	float x = nx; // center coordinate of tank where collision has to be drawn
	float y = ny; //
	float halfLen = 0.0f;
	
	if (!isExplosionDrawn)
	{
		fEachInterval = ntotalLen/ftotalDivisions;

		float Temp = ftotalDivisions;
		if(isInc)
		{
			Temp -= (Temp - inc);
			len = Temp * fEachInterval;
			halfLen = (Temp/2) * fEachInterval;
			inc++;
		}
		else if(!isInc)
		{
			len = inc * fEachInterval;
			halfLen = (len/2);
			inc--;
		}
		glPushMatrix();
			glBegin(GL_LINES);
			glVertex2f(x,y);
			glVertex2f(x + len,y);

			glVertex2f(x,y);
			glVertex2f(x - len,y);

			glVertex2f(x,y);
			glVertex2f(x,y + len);

			glVertex2f(x,y);
			glVertex2f(x,y - len);

			glVertex2f(x,y);
			glVertex2f(x +halfLen, y + len);

			glVertex2f(x,y);
			glVertex2f(x +len, y + halfLen);

			glVertex2f(x,y);
			glVertex2f(x +len, y - halfLen);

			glVertex2f(x,y);
			glVertex2f(x +halfLen, y -len);

			glVertex2f(x,y);
			glVertex2f(x - halfLen, y - len);

			glVertex2f(x,y);
			glVertex2f(x - len, y - halfLen);

			glVertex2f(x,y);
			glVertex2f(x - len, y + halfLen);

			glVertex2f(x,y);
			glVertex2f(x - halfLen, y + len);

			glEnd();
		glPopMatrix();
		if(!bAddExplosionVertices)
		{
			AddExplosionVertices(x,y, len, halfLen);
			bAddExplosionVertices = true;
		}
		if(inc > ftotalDivisions)
		{
			isInc = false;
		}
		else if(inc <= 0)
		{
			
			isExplosionDrawn = true;
		}
	}
	else
	{
		if(DrawExplosionPieces())
		{
			// Reset all Values;
			inc = 1;
			isExplosionDrawn = false;
			bAddExplosionVertices = false;
			isInc = true;
			m_ExplosionVertices.clear();
			return true;
		}
		else
		{
			return false;
		}

	}
	return false;
}


void RenderWindow::AddExplosionVertices(const float &fOriginX, const float &fOriginY, const float &fLen, 
										const float &fHalfLen)
{
	int nEdgelength = 10;
	float fLength = fLen * nEdgelength;
	float fHalfLength = fHalfLen * nEdgelength;

	Vector2f vTempVert;
	vTempVert = Vector2f(fOriginX, fOriginY);
	m_ExplosionVertices.push_back(vTempVert);

	//Triangle one
	vTempVert = Vector2f(fOriginX + fHalfLength, fOriginY + fLength);
	m_ExplosionVertices.push_back(vTempVert);

	vTempVert = Vector2f(fOriginX + fLength, fOriginY + fHalfLength);
	m_ExplosionVertices.push_back(vTempVert);

	//Triangle two
	vTempVert = Vector2f(fOriginX + fLength, fOriginY - fHalfLength);
	m_ExplosionVertices.push_back(vTempVert);

	vTempVert = Vector2f(fOriginX + fHalfLength, fOriginY - fLength);
	m_ExplosionVertices.push_back(vTempVert);


	//Triangle three
	vTempVert = Vector2f(fOriginX -fHalfLength, fOriginY - fLength);
	m_ExplosionVertices.push_back(vTempVert);

	vTempVert = Vector2f(fOriginX - fLength, fOriginY - fHalfLength);
	m_ExplosionVertices.push_back(vTempVert);

	//Triangle four
	vTempVert = Vector2f(fOriginX - fLength, fOriginY + fHalfLength);
	m_ExplosionVertices.push_back(vTempVert);

	vTempVert = Vector2f(fOriginX - fHalfLength, fOriginY + fLength);
	m_ExplosionVertices.push_back(vTempVert);
}

bool RenderWindow::DrawExplosionPieces()
{
	static float inc = 0.0f;
	float fTotalInterval = 10;
	int nTriangles = 4;
	Vector2f Corodinates;
	int nCount = 0;
	if(m_ExplosionVertices.size() != ((nTriangles *2) +1))
	{
		inc =0.0f;
		return true;
	}
	glPushMatrix();
	for (int j=0, i=0; j<nTriangles;j++)
	{

		Corodinates = m_TranslationPos[j];
		Corodinates *=inc;
		glTranslatef(Corodinates.x, Corodinates.y, 0);
		glBegin(GL_LINE_STRIP);

		Corodinates = m_ExplosionVertices[0];
		glVertex2f(Corodinates.x, Corodinates.y);

		Corodinates = m_ExplosionVertices[ i+ 1];
		glVertex2f(Corodinates.x, Corodinates.y);

		Corodinates = m_ExplosionVertices[i + 2];
		glVertex2f(Corodinates.x, Corodinates.y);
		
		Corodinates = m_ExplosionVertices[0];
		glVertex2f(Corodinates.x, Corodinates.y);

		i += 2;
		glEnd();
	}
	glPopMatrix();
	inc += 0.2 ;
	if(inc > fTotalInterval)
	{
		inc =0.0f;
		return true;
	}
	else
	{
		return false;
	}
}

void RenderWindow::bindTexture(unsigned int texid)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texid);
}
void RenderWindow::unbindTexture()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}
