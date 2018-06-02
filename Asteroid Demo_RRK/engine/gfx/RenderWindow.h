#pragma once

#include <vector>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>

#include "IRenderer.h"
#include "GraphicsManager.h"
#include "..\..\common\utils\Utils.h"
#include "..\..\common\utils\MathLib.h"
#include <glut.h>

using namespace MathLib;
using namespace std;

class RenderWindow: public IRenderer
{
private:
	float m_EntityTransMtx[16];
	int m_width;
	int m_height;
	int m_bpp;
	int m_refresh;
	int m_fullscreen;
	bool m_CreateExplosion;

	float m_ExplosionX;
	float m_ExplosionY;
	vector<Vector2f> m_ExplosionVertices;
	vector<Vector2f> m_TranslationPos;

	void SetviewProjection();
	bool renderExplosion(float nx, float ny);
	void CheckForResolution();
	void LoadCfgInfo();
	void ResizeWindow(int w, int h);
	
public:
	RenderWindow();
	virtual ~RenderWindow();

	void createExplosion(const bool b, const float nx, const float ny);
	void AddExplosionVertices(const float &fOriginX, const float &fOriginY, const float &fLen, 
		const float &fHalfLen);
	bool DrawExplosionPieces();
	void start();
	void stop();

	virtual void preRender();
	virtual void postRender();

	virtual void bindTexture(unsigned int texid);
	virtual void unbindTexture();

	virtual int getViewWidth() { return m_width; }
	virtual int getViewHeight() { return m_height; }
	
};