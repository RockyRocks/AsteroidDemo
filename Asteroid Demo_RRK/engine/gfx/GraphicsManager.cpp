#include "GraphicsManager.h"

GraphicsManager::GraphicsManager(void)
{
	m_pRenderer = NULL;
}

GraphicsManager::~GraphicsManager(void)
{
}

void GraphicsManager::start()
{
#ifdef _WIN32
	m_pRenderer = new RenderWindow();
#endif

}
void GraphicsManager::stop()
{
	m_pRenderer->stop();

	delete m_pRenderer;
}

IRenderer * GraphicsManager::getRenderer() const
{
	return m_pRenderer;
}

void GraphicsManager::createExplosion(float nx, float ny)
{
	m_pRenderer->createExplosion(true, nx, ny);
}
