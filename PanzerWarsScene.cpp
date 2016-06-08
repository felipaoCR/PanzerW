#include "PanzerWarsScene.h"
#include "ModoVsScene.h"
#include "LevelScene.h"
#include "CreditosScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* PanzerWars::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = PanzerWars::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool PanzerWars::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    
    //////////////////////////
    //// Musica de fondo

    CocosDenshion::SimpleAudioEngine *audio = CocosDenshion::SimpleAudioEngine::sharedEngine();
    audio->preloadBackgroundMusic("Audio/ozzy.mp3");
    audio->playBackgroundMusic("Audio/ozzy.mp3", true);


    ///////////////////////////////////
    ////Se crea el menú de inicio

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    PanzerWars::createMenu(visibleSize);

    ///////////////////////////////////////
    ////// Sonido de Botones
    CocosDenshion::SimpleAudioEngine *button = CocosDenshion::SimpleAudioEngine::sharedEngine();
    button->preloadEffect("Audio/Button.mp3");

    //Se agrega una etiqueta con el titulo    
    auto label = Label::createWithTTF("Panzer Wars", "fonts/Marker Felt.ttf", 26);
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label, 1);

    //Se configura el background
    LayerGradient *bgLayer = LayerGradient::create(ccc4(0, 0, 128, 255), ccc4(0, 0, 0, 255));
    bgLayer->setZOrder(0);
    this->addChild(bgLayer);
    
    return true;
}


/////////////////////////////////////////////////////////
/////// Se crean los botones del menu de inicio  ////////
/////////////////////////////////////////////////////////

void PanzerWars::createMenu(Size visibleSize)
{
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    // set the font for menu with text
    MenuItemFont::setFontSize(20);

    // create first menu item
    auto mbVs = MenuItemFont::create("Modo vs.", CC_CALLBACK_1(PanzerWars::ModoVsCallBack, this));
    // CC_CALLBACK_1 is a macro which helps to indicate function pointer.

    // create second menu item
    auto mbArcade = MenuItemFont::create("Arcade", CC_CALLBACK_1(PanzerWars::ModoArcadeCallBack, this));

    // create third menu item
    auto mbCreditos = MenuItemFont::create("Créditos", CC_CALLBACK_1(PanzerWars::CreditosCallBack,this));

    // now create a menu with menu items.
    auto menuCenter = Menu::create(mbVs,mbArcade,mbCreditos, NULL);

    // set the position of menu
    menuCenter->setPosition(Vec2(visibleSize.width/2.0, visibleSize.height/2.0));

    // set the text color for the menu
    menuCenter->setColor(Color3B(240, 230, 140));

    // set the alignment & padding for the menu.
    menuCenter->alignItemsVertically();

    // add it to scene-layer
    this->addChild(menuCenter, 3);


    // Se crea un boton de salir y se agrega al menu
    auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png",
                                           CC_CALLBACK_1(PanzerWars::menuCloseCallback, this));
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
}


void PanzerWars::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

// Se presiona modo vs
void PanzerWars::ModoVsCallBack(Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Audio/Button.mp3");
    Director::sharedDirector()->replaceScene(ModoVs::createScene());
}

// Se presiona modo arcade
void PanzerWars::ModoArcadeCallBack(Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Audio/Button.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
    Director::sharedDirector()->replaceScene(Level::createScene());
}

// Se presiona creditos
void PanzerWars::CreditosCallBack(Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Audio/Button.mp3");
    Director::sharedDirector()->replaceScene(Creditos::createScene());
}
