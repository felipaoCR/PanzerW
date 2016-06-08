#ifndef __Level_Scene_H__
#define __Level_Scene_H__

#include "cocos2d.h"

class Level : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void VolverCallBack(cocos2d::Ref* pSender);
    void createButtons(cocos2d::Size size);
    void ModoArcadeCallBack(cocos2d::Ref* pSender);
    void Arcade2CallBack(cocos2d::Ref* pSender);
    void Arcade3CallBack(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Level);
};

#endif // __Level_Scene_H__
