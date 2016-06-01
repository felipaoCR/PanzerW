#ifndef __ModoVs_Scene_H__
#define __ModoVs_Scene_H__

#include "cocos2d.h"

class ModoVs : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void VolverCallBack(cocos2d::Ref* pSender);
    void createButtons(cocos2d::Size size);
    void KOTHCallBack(cocos2d::Ref* pSender);
    void BatallaCallBack(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(ModoVs);
};

#endif // __ModoVs_Scene_H__
