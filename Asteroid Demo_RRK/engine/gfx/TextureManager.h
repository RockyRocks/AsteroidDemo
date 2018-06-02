#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <map>
#include <iostream>
#include <string>
#include <direct.h>
#include <glut.h>
#include "..\..\common\utils\Utils.h"
#include "..\..\common\utils\Singleton.h"

// TextureManager Description
//
// Using the Image class in gxbase, the texture manager will handle the creation/deletion of textures.
// It will look in the "resources\images\" folder for bmp's and automatically load them into memory.
// bmp's with "alpha" in the name will automatically be loaded as an alpha texture;
// To get a OpenGL texture handle use the full name of the bmp (including extension)
//
// GLuint tex = TextureManager::GetInstance()->getTexture("mytexture.bmp");
// glBindTexture(tex);
class TextureManager : public Singleton<TextureManager>
{
	friend Singleton<TextureManager>;

public:
	void start();
	void destroy();

	GLuint getTexture(const char *texturename);
	GLuint getTexture(std::string &fname);
private:
	typedef std::map<std::string, GLuint> TextureHandleMap;
	TextureHandleMap m_TextureHandles;

	GLuint loadTexture(const char *texturename, GLint filterparam);
	GLuint loadAlphaTexture(const char *texturename, GLint filterparam);
	GLuint findHandle(const std::string &fname);

	TextureManager(void);
	~TextureManager(void);
	TextureManager(const TextureManager&);
	TextureManager& operator=(const TextureManager);
};
