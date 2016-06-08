#include "LevelScene.h"
#include "PanzerWarsScene.h"
#include "SimpleAudioEngine.h"
#include "ModoArcadeScene.h"
#include "Arcade2Scene.h"
#include "Arcade3Scene.h"

USING_NS_CC;

Scene* Level::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Level::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Level::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Level::createButtons(visibleSize);

    //Se agrega una etiqueta con el titulo    
    auto label = Label::createWithTTF("Select Level", "fonts/Marker Felt.ttf", 26);
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
////////// Se crean los botones del modo VS /////////////
/////////////////////////////////////////////////////////

void Level::createButtons(Size visibleSize)
{
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    // set the font for menu with text
    MenuItemFont::setFontSize(20);

    // Boton para volver al menu de inicio
    auto mbVolver = MenuItemFont::create("Volver", CC_CALLBACK_1(Level::VolverCallBack, this));
    mbVolver->setAnchorPoint(Vec2(0.0,0.0));
    mbVolver->setPosition(0, 0);
    mbVolver->setColor(Color3B(240, 230, 140));

    // Se crea un boton de salir
    auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png",
                                           CC_CALLBACK_1(Level::menuCloseCallback, this));
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    auto menu = Menu::create(mbVolver, closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 3);

    // create first menu item
    auto mbL1 = MenuItemFont::create("Level 1", CC_CALLBACK_1(Level::ModoArcadeCallBack, this));

    // create second menu item
    auto mbL2 = MenuItemFont::create("Level 2", CC_CALLBACK_1(Level::Arcade2CallBack, this));

    // create third menu item
    auto mbL3 = MenuItemFont::create("Level 3", CC_CALLBACK_1(Level::Arcade3CallBack, this));

    // now create a menu with menu items.
    auto menuCenter = Menu::create(mbL1, mbL2, mbL3, NULL);

    // set the position of menu
    menuCenter->setPosition(Vec2(visibleSize.width/2.0, visibleSize.height/2.0));

    // set the text color for the menu
    menuCenter->setColor(Color3B(240, 230, 140));

    // set the alignment & padding for the menu.
    menuCenter->alignItemsVertically();

    // add it to scene-layer
    this->addChild(menuCenter, 3);
}

void Level::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void Level::VolverCallBack(Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Audio/Button.mp3");
    Director::sharedDirector()->replaceScene(PanzerWars::createScene());
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

void Level::ModoArcadeCallBack(Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Audio/Button.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
    Director::sharedDirector()->replaceScene(ModoArcade::createScene());
}

void Level::Arcade2CallBack(Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Audio/Button.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
    Director::sharedDirector()->replaceScene(Arcade2::createScene());
}

void Level::Arcade3CallBack(Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Audio/Button.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
    Director::sharedDirector()->replaceScene(Arcade3::createScene());
}
