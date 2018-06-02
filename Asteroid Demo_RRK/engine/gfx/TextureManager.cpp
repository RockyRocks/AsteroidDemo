#include "TextureManager.h"
#include <algorithm>

#include "GxBase.h"
using namespace gxbase;

TextureManager::TextureManager(void)
{
}

TextureManager::~TextureManager(void)
{
	destroy();
}

void TextureManager::destroy()
{
	TextureHandleMap::iterator it;
	it = m_TextureHandles.begin();
	while(it != m_TextureHandles.end())
	{
		glDeleteTextures(1, &(it->second));
		it++;
	}

	m_TextureHandles.clear();
}

void TextureManager::start()
{
	//std::string imgdir = Utils::getResourcesDir("\\images\\");
	//imgdir.append("*.bmp");

	//WIN32_FIND_DATA ffd;
	//HANDLE hFind = INVALID_HANDLE_VALUE;
	//hFind = FindFirstFile(imgdir.c_str(), &ffd);
	//do
	//{
	//	char *filename = ffd.cFileName;

	//	std::string texdir = Utils::getResourcesDir("\\images\\");
	//	texdir.append(filename);
	//	//std::string out;
	//	//Utils::trimString(texdir, out);
	//	GLuint texhandle;
	//	if(strstr(filename, "alpha") != NULL)
	//	{
	//		// has alpha in the name, load as alpha texture
	//		texhandle = loadAlphaTexture(texdir.c_str(), GL_LINEAR);
	//	}
	//	else
	//	{
	//		texhandle = loadTexture(texdir.c_str(), GL_LINEAR);
	//	}

	//	std::string fname;
	//	fname.assign(filename);
	//	
	//	//std::transform(fname.begin(), fname.end(), fname.begin(), tolower);
	//	Utils::toLowerCase(fname);

	//	m_TextureHandles[fname] = texhandle;
	//}
	//while(FindNextFile(hFind, &ffd) != 0);

	//std::cout << "[TextureManager::start]" << std::endl;
}

GLuint TextureManager::getTexture(std::string &fname)
{
	Utils::toLowerCase(fname);

	std::string imgdir = Utils::getResourcesDir("\\images\\");
	imgdir.append(fname);

	GLuint h;// = loadTexture(imgdir.c_str(), GL_LINEAR);

	if(strstr(fname.c_str(), "alpha") != NULL)
	{
		// has alpha in the name, load as alpha texture
		h = loadAlphaTexture(imgdir.c_str(), GL_LINEAR);
	}
	else
	{
		h = loadTexture(imgdir.c_str(), GL_LINEAR);
	}

	// add it to the map
	m_TextureHandles[fname] = h;

	return h;
}

GLuint TextureManager::getTexture(const char *texturename)
{
	std::string fname;
	fname.append(texturename);
	Utils::toLowerCase(fname);

	std::string imgdir = Utils::getResourcesDir("\\images\\");
	imgdir.append(fname);

	GLuint h;// = loadTexture(imgdir.c_str(), GL_LINEAR);


	if(strstr(fname.c_str(), "alpha") != NULL)
	{
		// has alpha in the name, load as alpha texture
		h = loadAlphaTexture(imgdir.c_str(), GL_LINEAR);
	}
	else
	{
		h = loadTexture(imgdir.c_str(), GL_LINEAR);
	}

	// add it to the map
	m_TextureHandles[fname] = h;

	return h;
	
}

GLuint TextureManager::findHandle(const std::string &fname)
{
	GLuint h;
	TextureHandleMap::iterator it = m_TextureHandles.find(fname);

	if(it == m_TextureHandles.end())
	{
		h = m_TextureHandles["default.bmp"];
	}
	else
		h = m_TextureHandles[fname];

	return h;
}

GLuint TextureManager::loadTexture(const char *texturename, GLint filterparam)
{
	GLuint h;

	Image image;

	image.Load(texturename);
	glGenTextures(1, &h);
	glBindTexture(GL_TEXTURE_2D, h);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterparam);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterparam);
	image.gluBuild2DMipmaps();
	image.Free();

	return h;
}

GLuint TextureManager::loadAlphaTexture(const char *texturename, GLint filterparam)
{
	GLuint h;

	Image image;

	image.Load(texturename);
	image.SetFormat(image.ALPHA);
	glGenTextures(1, &h);
	glBindTexture(GL_TEXTURE_2D, h);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterparam);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterparam);
	image.glTexImage2D(0);
	image.Free();

	return h;
}