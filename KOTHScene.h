#ifndef __KOTH_Scene_H__
#define __KOTH_Scene_H__

#include "cocos2d.h"
#include "Player.h"
#include <CCTMXLayer.h>
#include <CCTMXTiledMap.h>
#include <CCTMXObjectGroup.h>
#include <CCScene.h>


using namespace std;
using namespace cocos2d;

class KOTH : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CCTMXLayer *_blockage;

    //Cosas para los fondos
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    void setPlayer1Position(Point position);
    void setPlayer2Position(Point position);
    Point tileCoordForPosition(Point _position);
    bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);
    double keyPressedDuration(cocos2d::EventKeyboard::KeyCode);	
    void ModoArcadePlayerPosition(Point position);
    void initPlayerStatus();
    //Para movimiento continuo
    void gameUpdate(float interval);
    void onKeyHold(float interval);
    void KOTHCounter1(Point position);
    void KOTHCounter2(Point position);
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void VolverCallBack(cocos2d::Ref* pSender);
    void createButtons(cocos2d::Size size);
    
    // implement the "static create()" method manually
    CREATE_FUNC(KOTH);
private:
        Player p1, p2;
    double duration1=0, duration2=0;
    bool pause = false;
    bool game_Over = false;
    Sprite *_player1, *_player2, *sprite, *minaP1[3], *minaP2[3], *misil;
    CCTMXTiledMap *tileMap;
    CCTMXLayer *background;
    bool up1 = false, down1 = false, right1 = false, left1 = false; //Para control del player 1
    bool up2 = false, down2 = false, right2 = false, left2 = false; //Para control del player 2
    Rect bbP1, bbP2, bbM1[3], bbM2[3], bbm1, bbm2; //Para las colisiones con las minas
    int cantM1 = 5, cantM2 = 5; //Cantidad inicial de minas
    bool actM1[3], actM2[3], actm1[3], actm2[3]; //Maximo de minas y misiles a la vez
    int i; //Para recorrer arreglos
    int dirAnt1 = 1, dirAnt2 = 0; //Direccion anterior: 0 up, 1 down, 2 left, 3 right
};

#endif // __KOTH_Scene_H__
