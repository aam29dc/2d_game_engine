#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "entity.h"

class GameObject : public Entity {
public:
	static unsigned int _count;

	bool solid;
	bool destroyed;

	GameObject(const unsigned int width = 1, const unsigned int height = 1);
	~GameObject();
};

#endif