#ifndef __IRENDERER_H
#define __IRENDERER_H

/* Interface for renderers. */
class IRenderer
{
public:
	// start the graphics system
	virtual void start() = 0;

	// stop the graphics system, clear up pointers, etc.
	virtual void stop() = 0;
	virtual void preRender() = 0;
	virtual void postRender() = 0;

	virtual void bindTexture(unsigned int texid) = 0;
	virtual void unbindTexture() = 0;

	virtual int getViewWidth() = 0;
	virtual int getViewHeight() = 0;

	// This should really be "renderParticleSystem" or "createParticleSystem"
	virtual bool renderExplosion(float nx, float ny) = 0;

	virtual void createExplosion(const bool b, const float nx, const float ny) = 0;

	virtual ~IRenderer() {};
};

#endif