#include "ModoArcadeScene.h"
#include "PanzerWarsScene.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;
using namespace cocos2d;

////////////////////////////////
//Manejo de fondos y movimientos
Point ModoArcade::tileCoordForPosition(Point _position)
{
    int x = _position.x / tileMap->getTileSize().width;
    int y = ((tileMap->getMapSize().height*tileMap->getTileSize().height) - _position.y)/tileMap->getTileSize().height;
    return Point(x, y);
}

void ModoArcade::onKeyHold(float interval)
{
    Vec2 loc = _player->getPosition();
    if(!pause) {
	if(up) {
	    setPlayerPosition(ccp(loc.x,++loc.y+0.001)); // going up
	}
	if(down) {
	    setPlayerPosition(ccp(loc.x,--loc.y-0.001)); // going down
	}
	if(right) {
	    setPlayerPosition(ccp(++loc.x+0.001,loc.y)); // going right
	}
	if(left) {
	    setPlayerPosition(ccp(--loc.x-0.001,loc.y)); // going left
	}
    }
}

void ModoArcade::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    log("Key with keycode %d pressed", keyCode);
    switch(keyCode){
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case EventKeyboard::KeyCode::KEY_A:
	    left = true;
	    break;
 	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	case EventKeyboard::KeyCode::KEY_D:
	    right = true;
	    break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
 	case EventKeyboard::KeyCode::KEY_W:
	    up = true;
	    break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
 	case EventKeyboard::KeyCode::KEY_S:
	    down = true;
	    break;
	case EventKeyboard::KeyCode::KEY_SPACE:
	    bala = Sprite::create("saprissa.png");
	    bala->setPosition(_player->getPosition());
	    bala->setScale(0.05);
	    this->addChild(bala, 0);	    
    }
}

void ModoArcade::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    log("Key with keycode %d released", keyCode);
    switch(keyCode){
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case EventKeyboard::KeyCode::KEY_A:
	    left = false;
	    break;
 	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	case EventKeyboard::KeyCode::KEY_D:
	    right = false;
	    break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
 	case EventKeyboard::KeyCode::KEY_W:
	    up = false;
	    break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
 	case EventKeyboard::KeyCode::KEY_S:
	    down = false;
    }
}

void ModoArcade::setPlayerPosition(Point position)
{
    Point tileCoord = this->tileCoordForPosition(position);
    int tileGid = _blockage->getTileGIDAt(tileCoord);
    log("tileGid = %d", tileGid);
    if (tileGid) {
        auto properties = tileMap->getPropertiesForGID(tileGid).asValueMap();
        if (!properties.empty()) {
            auto collision = properties["Collision"].asString();
            if ("True" == collision) {
		log("COLISION");
                return;
            }
        }else return;
    }
    _player->setPosition(position);
}


Scene* ModoArcade::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ModoArcade::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ModoArcade::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    ModoArcade::createButtons(visibleSize);

    //Se agrega una etiqueta con el titulo    
    auto label = Label::createWithTTF("Modo Arcade", "fonts/Marker Felt.ttf", 26);
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label, 1);

    //Se configura el background
    /*LayerGradient *bgLayer = LayerGradient::create(ccc4(51, 0, 128, 255), ccc4(0, 0, 0, 255));
    bgLayer->setZOrder(0);
    this->addChild(bgLayer);*/

    /////////////////////////////////
    ///// Manejo de fondos
    //Se carga el mapa y se hacen los collisions tiles con los que el tanque tiene que chocar
    tileMap = new CCTMXTiledMap();    
    tileMap->initWithTMXFile("test2.tmx");
    _blockage = tileMap->layerNamed("Blockage01");
    _blockage->setVisible(false);

    tileMap->setPosition(origin.x,origin.y);
    this->addChild(tileMap);
    //Se obtiene la layer de objetos 'palpables' por el juego
    TMXObjectGroup *objects = tileMap->getObjectGroup("Object Layer 1");	
    CCASSERT(NULL!=objects, "'Object Layer 1' object group not found");
    //Se crea el sprite de objeto
    auto Player = objects->getObject("Player");
    CCASSERT(!Player.empty(),"Player object not found");

    int x = Player["x"].asInt();
    int y = Player["y"].asInt();

    _player = Sprite::create("tank3.png");
    setPlayerPosition(ccp(x,y));
    _player->setScale(0.3);
    addChild(_player);


    ///////////////////////////////////
    /// Tanque que gira (demostracion)
    sprite = cocos2d::Sprite::create("tank3.png");
    sprite->setPosition(250, this->getBoundingBox().getMidY());
    sprite->setScale(0.5);
    auto rotate = cocos2d::RotateBy::create(1, 45);
    auto repeat1 = cocos2d::RepeatForever::create(rotate);
    this->addChild(sprite, 0);
    sprite->runAction(repeat1);

   //seccion de movimiento   
   auto eventListener = EventListenerKeyboard::create();
   eventListener->onKeyPressed = CC_CALLBACK_2(ModoArcade::onKeyPressed, this);
   eventListener->onKeyReleased = CC_CALLBACK_2(ModoArcade::onKeyReleased, this);

   this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener,_player);


    ////////////////////////////////////
    // Para movimiento continuo
    this->schedule(schedule_selector(ModoArcade::onKeyHold));
	
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();

    // set the background music and continuously play it.
    audio->playBackgroundMusic("Audio/track01.mp3", true);


    // Pausa o continua el juego
    auto pausa = cocos2d::EventListenerKeyboard::create();
    pausa->onKeyPressed = [=](cocos2d::EventKeyboard::KeyCode tecla, cocos2d::Event * event)->void{
	if (tecla == cocos2d::EventKeyboard::KeyCode::KEY_P){
	    if (pause){
		label->setString("Modo Arcade");
		Director::sharedDirector()->resume();
		CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		CocosDenshion::SimpleAudioEngine::getInstance()->resumeAllEffects();
	    }
	    else {
		label->setString("Pausa");
		Director::sharedDirector()->pause();
		CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		CocosDenshion::SimpleAudioEngine::getInstance()->pauseAllEffects();
	    }
	    pause = !pause;
	}
    };

    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(pausa,this);
    return true;
}

/////////////////////////////////////////////////////////
////////// Se crean los botones del arcade //////////////
/////////////////////////////////////////////////////////

void ModoArcade::createButtons(Size visibleSize)
{
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    // set the font for menu with text
    MenuItemFont::setFontSize(14);

    // Boton para volver al menu de inicio
    auto mbVolver = MenuItemFont::create("Atras", CC_CALLBACK_1(ModoArcade::VolverCallBack, this));
    mbVolver->setAnchorPoint(Vec2(0.0,0.0));
    mbVolver->setPosition(0, 0);
    mbVolver->setColor(Color3B(240, 230, 140));

    // Se crea un boton de salir
    auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png",
                                           CC_CALLBACK_1(ModoArcade::menuCloseCallback, this));
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    auto menu = Menu::create(mbVolver, closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 2);
}


void ModoArcade::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void ModoArcade::VolverCallBack(Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Audio/Button.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
    Director::sharedDirector()->replaceScene(PanzerWars::createScene());
}
