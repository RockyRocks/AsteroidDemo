#ifndef __GFXMANAGER_H
#define __GFXMANAGER_H


#include "IRenderer.h"

#ifdef _WIN32
#include "RenderWindow.h"
#endif

#include "..\..\common\utils\Singleton.h"

// GraphicsManager Description
//
// The graphics manager manages the renderer pointers. It also stores some
// global variables (e.g. width/height) that can be accessed by other systems/objects
// if necessary
class GraphicsManager : public Singleton<GraphicsManager>
{
	friend Singleton<GraphicsManager>;

public:
	void start();
	void stop();

	const float getWidth() const;
	const float getHeight() const;

	void setWidth(const float width);
	void setHeight(const float height);

	IRenderer * getRenderer() const;

	void createExplosion(float nx, float ny);

private:
	GraphicsManager();
	~GraphicsManager();
	GraphicsManager(const GraphicsManager&);
	GraphicsManager& operator=(const GraphicsManager);

	IRenderer * m_pRenderer;
	float m_Height;
	float m_Width;
};

inline const float GraphicsManager::getWidth() const
{
	return m_Width;
}
inline const float GraphicsManager::getHeight() const
{
	return m_Height;
}
inline void GraphicsManager::setWidth(const float width)
{
	m_Width = width;
}
inline void GraphicsManager::setHeight(const float height)
{
	m_Height = height;
}

#endif
