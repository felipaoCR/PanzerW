#ifndef __ModoArcade_Scene_H__
#define __ModoArcade_Scene_H__

#include "cocos2d.h"
#include <CCTMXLayer.h>
#include <CCTMXTiledMap.h>
#include <CCTMXObjectGroup.h>
#include <CCScene.h>

using namespace std;
using namespace cocos2d;

class ModoArcade : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init() override;

    CCTMXLayer *_blockage;

    //Cosas para los fondos
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    void setPlayerPosition(Point position);
    Point tileCoordForPosition(Point _position);
    bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);
    double keyPressedDuration(cocos2d::EventKeyboard::KeyCode);	
    void ModoArcadePlayerPosition(Point position);

    //Para movimiento continuo
    void onKeyHold(float interval);
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void VolverCallBack(cocos2d::Ref* pSender);
    void createButtons(cocos2d::Size size);
    
    // implement the "static create()" method manually
    CREATE_FUNC(ModoArcade);

private:
    bool pause = false;  //Controla si el juego se pausa
    Sprite *_player, *sprite, *bala;
    CCTMXTiledMap *tileMap;
    CCTMXLayer *background;
    bool up = false, down = false, right = false, left = false;  //Para el movimiento del jugador
    bool fire; //Para los disparos
};

#endif // __ModoArcade_Scene_H__
