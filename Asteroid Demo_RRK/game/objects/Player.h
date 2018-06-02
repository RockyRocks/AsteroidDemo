#ifndef __PLAYER_H
#define __PLAYER_H

#include "..\..\engine\gfx\GraphicsManager.h"
#include "BaseEntity.h"
#include "..\physics\CollisionPrimitives.h"

class Player : public BaseEntity
{
public:
	Player(const std::string &name, const Vector2f &centre);
	virtual void fire();
	virtual void update();
	virtual void reset();
	virtual ~Player(void);

	virtual void render(IRenderer *renderer);
};

#endif