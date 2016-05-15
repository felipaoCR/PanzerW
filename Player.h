#ifndef __Player_H__
#define __Player_H__


#include "cocos2d.h"
#include <CCTMXLayer.h>
#include <CCTMXTiledMap.h>
#include <CCTMXObjectGroup.h>
#include <CCScene.h>

using namespace std;
using namespace cocos2d;

class Player
{
private:
	Sprite *_player;
	int Health;
	int Defence;
	int Attack;	
	float Speed;

public:

Player()
{
	;
}
~Player()
{
	;
}
Sprite *getPlayer()
{
	return _player;
}

void setHealth(int health)
{
	Health = health;	
}
void setDefence(int defence)
{
	Defence = defence;
}
void setAttack()
{
	Attack = -3*Defence+45; //Formula para el ataque
}
void setSpeed(float speed)
{
	Speed = speed;
}

int getHealth()
{
	return Health;
}
int getDefence()
{
	return Defence;
}
int getAttack()
{
	return Attack;
}
float getSpeed()
{	
	return Speed;
}	
};

#endif

