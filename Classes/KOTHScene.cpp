#include <chrono>
#include <ctime>
#include <unistd.h>
#include "KOTHScene.h"
#include "PanzerWarsScene.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;
using namespace cocos2d;
using namespace std::chrono;

int x,y,x2,y2;
high_resolution_clock::time_point start1, start2, crono;
bool dentro1, dentro2, stop;
double temp1, temp2, timeElapsed;
auto audio = CocosDenshion::SimpleAudioEngine::getInstance();

////////////////////////////////
//Manejo de fondos y movimientos
Point KOTH::tileCoordForPosition(Point _position)
{
    int x = _position.x / tileMap->getTileSize().width;
    int y = ((tileMap->getMapSize().height*tileMap->getTileSize().height) - _position.y)/tileMap->getTileSize().height;
    return Point(x, y);
}

void KOTH::initPlayerStatus()
{
	//Inicio estado de player1
	p1.setHealth(100);
	p1.setDefence(5);
	p1.setAttack(p1.getDefence());
	p1.setSpeed(2);
	//Inicio estado de player2
	p2.setHealth(100);
	p2.setDefence(5);
	p2.setAttack(p2.getDefence());
	p2.setSpeed(2);

}

void KOTH::gameUpdate(float interval)
{
    ////////////////////////////////////////////////////////////
    // Movimiento Jugadores


    loc1 = _player1->getPosition();
    loc2 = _player2->getPosition();
    if(!pause) {
        timeElapsed = std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now()-crono).count() /1000;
        log("Tiempo = %lf", timeElapsed);
	dentro1 = false;
	dentro2 = false;
	KOTHCounter1(loc1);
	KOTHCounter2(loc2);
	if(up1) {
	    switch(dirAnt1) {
		case 0:
		    break;
		case 1:
		    this->_player1->runAction(RotateBy::create(0.02, 180));
		    break;
		case 2:
		    this->_player1->runAction(RotateBy::create(0.01, 90));
		    break;
		case 3:
		    this->_player1->runAction(RotateBy::create(0.01, -90));
		    break;
	    }
	    dirAnt1 = 0;
	    setPlayer1Position(ccp(loc1.x,++loc1.y+p1.getSpeed())); // player 1 going up
	}
	else if(down1) {
	    switch(dirAnt1) {
		case 0:
		    this->_player1->runAction(RotateBy::create(0.02, 180));
		    break;
		case 1:
		    break;
		case 2:
		    this->_player1->runAction(RotateBy::create(0.01, -90));
		    break;
		case 3:
		    this->_player1->runAction(RotateBy::create(0.01, 90));
		    break;
	    }
	    dirAnt1 = 1;
	    setPlayer1Position(ccp(loc1.x,--loc1.y-p1.getSpeed())); // player 1 going down
	}
	else if(right1) {
	    switch(dirAnt1) {
		case 0:
		    this->_player1->runAction(RotateBy::create(0.01, 90));
		    break;
		case 1:
		    this->_player1->runAction(RotateBy::create(0.01, -90));
		    break;
		case 2:
		    this->_player1->runAction(RotateBy::create(0.02, 180));
		    break;
		case 3:
		    break;
	    }
	    dirAnt1 = 3;
	    setPlayer1Position(ccp(++loc1.x+p1.getSpeed(),loc1.y)); // player 1 going right
	}
	else if(left1) {
	    switch(dirAnt1) {
		case 0:
		    this->_player1->runAction(RotateBy::create(0.01, -90));
		    break;
		case 1:
		    this->_player1->runAction(RotateBy::create(0.01, 90));
		    break;
		case 2:
		    break;
		case 3:
		    this->_player1->runAction(RotateBy::create(0.02, 180));
		    break;
	    }
	    dirAnt1 = 2;
	    setPlayer1Position(ccp(--loc1.x-p1.getSpeed(),loc1.y)); // player 1 going left
	}
	if(up2) {
	    switch(dirAnt2) {
		case 0:
		    break;
		case 1:
		    this->_player2->runAction(RotateBy::create(0.02, 180));
		    break;
		case 2:
		    this->_player2->runAction(RotateBy::create(0.01, 90));
		    break;
		case 3:
		    this->_player2->runAction(RotateBy::create(0.01, -90));
		    break;
	    }
	    dirAnt2 = 0;
	    setPlayer2Position(ccp(loc2.x,++loc2.y+p2.getSpeed())); // player 2 going up
	    KOTHCounter2(_player2->getPosition());
	}
	else if(down2) {
	    switch(dirAnt2) {
		case 0:
		    this->_player2->runAction(RotateBy::create(0.02, 180));
		    break;
		case 1:
		    break;
		case 2:
		    this->_player2->runAction(RotateBy::create(0.01, -90));
		    break;
		case 3:
		    this->_player2->runAction(RotateBy::create(0.01, 90));
		    break;
	    }
	    dirAnt2 = 1;
	    setPlayer2Position(ccp(loc2.x,--loc2.y-p2.getSpeed())); // player 2 going down
	    KOTHCounter2(_player2->getPosition());
	}
	else if(right2) {
	    switch(dirAnt2) {
		case 0:
		    this->_player2->runAction(RotateBy::create(0.01, 90));
		    break;
		case 1:
		    this->_player2->runAction(RotateBy::create(0.01, -90));
		    break;
		case 2:
		    this->_player2->runAction(RotateBy::create(0.02, 180));
		    break;
		case 3:
		    break;
	    }
	    dirAnt2 = 3;
	    setPlayer2Position(ccp(++loc2.x+p2.getSpeed(),loc2.y)); // player 2 going right
	    KOTHCounter2(_player2->getPosition());
	}
	else if(left2) {
	   switch(dirAnt2) {
		case 0:
		    this->_player2->runAction(RotateBy::create(0.01, -90));
		    break;
		case 1:
		    this->_player2->runAction(RotateBy::create(0.01, 90));
		    break;
		case 2:
		    break;
		case 3:
		    this->_player2->runAction(RotateBy::create(0.02, 180));
		    break;
	    }
	    dirAnt2 = 2;
	    setPlayer2Position(ccp(--loc2.x-p2.getSpeed(),loc2.y)); // player 2 going left
	    KOTHCounter2(_player2->getPosition());
	}


	////////////////////////////////////////////////////////
	// pARA TIempo

	if(dentro1) {
		//temp = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
		temp1 = std::chrono::duration<double, std::milli>( high_resolution_clock::now() - start1 ).count();
		duration1 = duration1 + temp1;
		log("DURATION 1 = %f", duration1);
	}
	if(dentro2) {
		temp2 = std::chrono::duration<double, std::milli>( high_resolution_clock::now() - start2 ).count();
		//temp = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
		duration2 = duration2 + temp2;
		log("DURATION 2 = %f", duration2);
	}

    /////////////////////////////////////////////
    // Para colisiones entre sprites
    bbP1 = _player1->getBoundingBox();
    bbP2 = _player2->getBoundingBox();
    for(i=0; i<3; i++) {
	if(bbP1.intersectsRect(bbM2[i]) && (actM2[i]==true)) {
	    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Audio/Bomb.mp3");
	    //-10 a health de p1
	    if(p1.getHealth()>0)
	    p1.setHealth(p1.getHealth()-50);
	    if(p1.getHealth()<0)
	    p1.setHealth(0);
            log("Player 1 actived mine %d", i);
	    log("Player 1 Life = %d", p1.getHealth());
	    this->removeChild(minaP2[i]);
	    actM2[i] = false;
	}
	if(bbP2.intersectsRect(bbM1[i]) && (actM1[i]==true)) {
	    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Audio/Bomb.mp3");
	    //-10 a health de p2
	    if(p2.getHealth()>0)
	    p2.setHealth(p2.getHealth()-50);
	    if(p2.getHealth()<0)
	    p2.setHealth(0);
	    log("Player 2 actived mine %d", i);
	    log("Player 2 Life = %d", p2.getHealth());
	    this->removeChild(minaP1[i]);
	    actM1[i] = false;
	}
    }
    if(actm1)
    {
    	locm1 = misil1->getPosition();
	bbm1 = misil1->getBoundingBox();
	switch (dirm1)
	{
		case 0:
		    setMisil1Position(ccp(locm1.x,++locm1.y+3));
		    break;
		case 1:
		     setMisil1Position(ccp(locm1.x,--locm1.y-3));
		     break;
		case 2:
		    setMisil1Position(ccp(--locm1.x-3,locm1.y));
		    break;
		case 3:
		    setMisil1Position(ccp(++locm1.x+3,locm1.y));
	}
	if(bbm1.intersectsRect(bbP2))
	{
		this->removeChild(misil1);
		actm1 = false;
		p2.setHealth(p2.getHealth()-20);
		if(p2.getHealth()<0)
		p2.setHealth(0);
	}
    }
    if(actm2)
    {
	locm2 = misil2->getPosition();
	bbm2 = misil2->getBoundingBox();
	switch (dirm2)
	{
		case 0:
		    setMisil2Position(ccp(locm2.x,++locm2.y+3));
		    break;
		case 1:
		    setMisil2Position(ccp(locm2.x,--locm2.y-3));
		    break;
		case 2:
		    setMisil2Position(ccp(--locm2.x-3,locm2.y));
		    break;
		case 3:
		    setMisil2Position(ccp(++locm2.x+3,locm2.y));
	}
	if(bbm2.intersectsRect(bbP1))
	{
		this->removeChild(misil2);
		actm2 = false;
		p1.setHealth(p1.getHealth()-20);
		if(p1.getHealth()<0)
		p1.setHealth(0);
	}
    }
    ///////////////////////////////////////
    //Spawneo
	if(!p2.getHealth())
	{
		setPlayer2Position(ccp(x2,y2));
		p2.setHealth(100);

	}
	if(!p1.getHealth())
	{
		setPlayer1Position(ccp(x,y));
		p1.setHealth(100);

	}
  /////////////////////////////////////////
  //Health bar player 1
  switch (p1.getHealth()) {
    case 100:
      removeChild(HB1);
      HB1 = Sprite::create("healthBar.png");
      HB1->setPosition(ccp(x-400,y+525));
      HB1->setScaleX(0.9);
      addChild(HB1);
      break;
    case 80:
      removeChild(HB1);
      HB1 = Sprite::create("healthBar.png");
      HB1->setPosition(ccp(x-400,y+525));
      HB1->setScaleX(0.72);
      addChild(HB1);
      break;
    case 60:
      removeChild(HB1);
      HB1 = Sprite::create("healthBar.png");
      HB1->setPosition(ccp(x-400,y+525));
      HB1->setScaleX(0.54);
      addChild(HB1);
      break;
    case 50:
      removeChild(HB1);
      HB1 = Sprite::create("healthBar.png");
      HB1->setPosition(ccp(x-400,y+525));
      HB1->setScaleX(0.45);
      addChild(HB1);
      break;
    case 40:
      removeChild(HB1);
      HB1 = Sprite::create("healthBar.png");
      HB1->setPosition(ccp(x-400,y+525));
      HB1->setScaleX(0.36);
      addChild(HB1);
      break;
    case 30:
        removeChild(HB1);
        HB1 = Sprite::create("healthBar.png");
        HB1->setPosition(ccp(x-400,y+525));
        HB1->setScaleX(0.27);
        addChild(HB1);
        break;
    case 20:
        removeChild(HB1);
        HB1 = Sprite::create("healthBar.png");
        HB1->setPosition(ccp(x-400,y+525));
        HB1->setScaleX(0.18);
        addChild(HB1);
        break;
    case 10:
        removeChild(HB1);
        HB1 = Sprite::create("healthBar.png");
        HB1->setPosition(ccp(x-400,y+525));
        HB1->setScaleX(0.09);
        addChild(HB1);
        break;
  }
  switch (p2.getHealth()) {
    case 100:
      removeChild(HB2);
      HB2 = Sprite::create("healthBar.png");
      HB2->setPosition(ccp(x+300,y+525));
      HB2->setScaleX(0.9);
      addChild(HB2);
      break;
    case 80:
      removeChild(HB2);
      HB2 = Sprite::create("healthBar.png");
      HB2->setPosition(ccp(x+300,y+525));
      HB2->setScaleX(0.72);
      addChild(HB2);
      break;
    case 60:
      removeChild(HB2);
      HB2 = Sprite::create("healthBar.png");
      HB2->setPosition(ccp(x+300,y+525));
      HB2->setScaleX(0.54);
      addChild(HB2);
      break;
    case 50:
      removeChild(HB2);
      HB2 = Sprite::create("healthBar.png");
      HB2->setPosition(ccp(x+300,y+525));
      HB2->setScaleX(0.45);
      addChild(HB2);
      break;
    case 40:
      removeChild(HB2);
      HB2 = Sprite::create("healthBar.png");
      HB2->setPosition(ccp(x+300,y+525));
      HB2->setScaleX(0.36);
      addChild(HB2);
      break;
    case 30:
      removeChild(HB2);
      HB2 = Sprite::create("healthBar.png");
      HB2->setPosition(ccp(x+300,y+525));
      HB2->setScaleX(0.27);
      addChild(HB2);
      break;
    case 20:
      removeChild(HB2);
      HB2 = Sprite::create("healthBar.png");
      HB2->setPosition(ccp(x+300,y+525));
      HB2->setScaleX(0.18);
      addChild(HB2);
      break;
    case 10:
      removeChild(HB2);
      HB2 = Sprite::create("healthBar.png");
      HB2->setPosition(ccp(x+300,y+525));
      HB2->setScaleX(0.09);
      addChild(HB2);
      break;
  }


    ///////////////////////////////////////
    //Game Over
    if(timeElapsed>90)
    {
	pause = true;
	audio->stopBackgroundMusic();

	if(duration1>duration2) {
	Size vS1 = Director::getInstance()->getVisibleSize();
	Vec2 ori1 = Director::getInstance()->getVisibleOrigin();
	auto gameOver1 = Label::createWithTTF("Game Over\n Player 1 Won", "fonts/Marker Felt.ttf", 26);
    	gameOver1->setPosition(Vec2(ori1.x + vS1.width/2,
                            ori1.y + vS1.height/2));
	gameOver1->enableOutline(Color4B(255,0,0,255),5);
	this->addChild(gameOver1,1);
        }
	if(duration2>duration1) {
	Size vS2 = Director::getInstance()->getVisibleSize();
	Vec2 ori2 = Director::getInstance()->getVisibleOrigin();
	auto gameOver2 = Label::createWithTTF("Game Over\n Player 2 Won", "fonts/Marker Felt.ttf", 26);
    	gameOver2->setPosition(Vec2(ori2.x + vS2.width/2,
                            ori2.y + vS2.height/2));
	gameOver2->enableOutline(Color4B(0,255,0,255),5);
    	this->addChild(gameOver2, 1);

	}
	if(duration2==duration1)
	{
	Size vS3 = Director::getInstance()->getVisibleSize();
	Vec2 ori3 = Director::getInstance()->getVisibleOrigin();
	auto gameOver3 = Label::createWithTTF("Game Over\n It's a tie!", "fonts/Marker Felt.ttf", 26);
    	gameOver3->setPosition(Vec2(ori3.x + vS3.width/2,
                            ori3.y + vS3.height/2));
	gameOver3->enableOutline(Color4B(255,0,255,255),3);
    	this->addChild(gameOver3, 1);
	}

     }
   }

}

void KOTH::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    log("Key with keycode %d pressed", keyCode);
    switch(keyCode){
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case EventKeyboard::KeyCode::KEY_A:
	    left1 = true;
	    break;
 	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	case EventKeyboard::KeyCode::KEY_D:
	    right1 = true;
	    break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
 	case EventKeyboard::KeyCode::KEY_W:
	    up1 = true;
	    break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
 	case EventKeyboard::KeyCode::KEY_S:
	    down1 = true;
	    break;
	case EventKeyboard::KeyCode::KEY_Q:
	    if(cantM1>0 && !pause){
		for(i=0; i<3; i++) {
		    if(actM1[i]==false) {
			cantM1--;
			minaP1[i] = Sprite::create("mina.png");
			minaP1[i]->setPosition(_player1->getPosition());
			minaP1[i]->setScale(0.4);
			this->addChild(minaP1[i]);
			bbM1[i] = minaP1[i]->getBoundingBox();
			actM1[i] = true;
			break;
		    }
		}
	    }
	    break;
	case EventKeyboard::KeyCode::KEY_E:
	    if(actm1==false && !pause) {
   	 	audio->playEffect("Audio/explosion3.mp3");
    		audio->setEffectsVolume(0.3);
		misil1 = Sprite::create("c1.png");
		misil1->setPosition(_player1->getPosition());
		misil1->setScale(0.4);
		this->addChild(misil1);
		actm1 = true;
		dirm1 = dirAnt1;
		switch (dirm1) {
			case 0:
		    		misil1->runAction(RotateBy::create(0.001, -90));
		    		break;
			case 1:
		    		misil1->runAction(RotateBy::create(0.001, 90));
		     		break;
			case 2:
		    		misil1->runAction(RotateBy::create(0.001, 180));
		    		break;
			default:
		    		break;
		}
	    }
	    break;
	case EventKeyboard::KeyCode::KEY_O:
	    if(actm2==false && !pause) {
   	 	audio->playEffect("Audio/explosion3.mp3");
    		audio->setEffectsVolume(0.3);
		misil2 = Sprite::create("c1.png");
		misil2->setPosition(_player2->getPosition());
		misil2->setScale(0.4);
		this->addChild(misil2);
		actm2 = true;
		dirm2 = dirAnt2;
		switch (dirm2) {
			case 0:
		    		misil2->runAction(RotateBy::create(0.001, -90));
		    		break;
			case 1:
		    		misil2->runAction(RotateBy::create(0.001, 90));
		     		break;
			case 2:
		    		misil2->runAction(RotateBy::create(0.001, 180));
		    		break;
			default:
		    		break;
		}
	    }
	    break;
	case EventKeyboard::KeyCode::KEY_J:
	    left2 = true;
	    break;
	case EventKeyboard::KeyCode::KEY_L:
	    right2 = true;
	    break;
 	case EventKeyboard::KeyCode::KEY_I:
	    up2 = true;
	    break;
 	case EventKeyboard::KeyCode::KEY_K:
	    down2 = true;
	    break;
	case EventKeyboard::KeyCode::KEY_U:
	    if(cantM2>0 && !pause){
		for(i=0; i<3; i++) {
		    if(actM2[i]==false) {
			cantM2--;
			minaP2[i] = Sprite::create("mina.png");
			minaP2[i]->setPosition(_player2->getPosition());
			minaP2[i]->setScale(0.4);
			this->addChild(minaP2[i]);
			bbM2[i] = minaP2[i]->getBoundingBox();
			actM2[i] = true;
			break;
		    }
		}
	    }
	    break;
    }
}

void KOTH::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    log("Key with keycode %d released", keyCode);
    switch(keyCode){
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case EventKeyboard::KeyCode::KEY_A:
	    left1 = false;
	    break;
 	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	case EventKeyboard::KeyCode::KEY_D:
	    right1 = false;
	    break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
 	case EventKeyboard::KeyCode::KEY_W:
	    up1 = false;
	    break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
 	case EventKeyboard::KeyCode::KEY_S:
	    down1 = false;
	    break;
	case EventKeyboard::KeyCode::KEY_J:
	    left2 = false;
	    break;
	case EventKeyboard::KeyCode::KEY_L:
	    right2 = false;
	    break;
 	case EventKeyboard::KeyCode::KEY_I:
	    up2 = false;
	    break;
 	case EventKeyboard::KeyCode::KEY_K:
	    down2 = false;
    }
}

void KOTH::setPlayer1Position(Point position)
{
    Point tileCoord = this->tileCoordForPosition(position);
    int tileGid = _blockage->getTileGIDAt(tileCoord);
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
    _player1->setPosition(position);
}

void KOTH::setPlayer2Position(Point position)
{
    Point tileCoord = this->tileCoordForPosition(position);
    int tileGid = _blockage->getTileGIDAt(tileCoord);
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
    _player2->setPosition(position);
}

void KOTH::setMisil1Position(Point position)
{
    Point tileCoord = this->tileCoordForPosition(position);
    int tileGid = _blockage->getTileGIDAt(tileCoord);
    if (tileGid) {
        auto properties = tileMap->getPropertiesForGID(tileGid).asValueMap();
        if (!properties.empty()) {
            auto collision = properties["Collision"].asString();
            if ("True" == collision) {
	    this->removeChild(misil1);
	    actm1 = false;
	    log("COLISION");
            return;
            }
        }else return;
    }
    misil1->setPosition(position);
}

void KOTH::setMisil2Position(Point position)
{
    Point tileCoord = this->tileCoordForPosition(position);
    int tileGid = _blockage->getTileGIDAt(tileCoord);
    if (tileGid) {
        auto properties = tileMap->getPropertiesForGID(tileGid).asValueMap();
        if (!properties.empty()) {
            auto collision = properties["Collision"].asString();
            if ("True" == collision) {
		this->removeChild(misil2);
		actm2 = false;
		log("COLISION");
                return;
            }
        }else return;
    }
    misil2->setPosition(position);
}

void KOTH::KOTHCounter1(Point position)
{
    Point tileCoord = this->tileCoordForPosition(position);
    int tileGid = _blockage->getTileGIDAt(tileCoord);
    log("tileGid = %d", tileGid);
    if (tileGid) {
        auto properties = tileMap->getPropertiesForGID(tileGid).asValueMap();
        if (!properties.empty()) {
            auto koth = properties["KOTH"].asString();
            if("True" == koth) {
		log("KOTH");
		start1 = high_resolution_clock::now();
		dentro1 = true;

            } else {
		dentro1 = false;
		log("FELipao");
	    }
	}

    }

}
void KOTH::KOTHCounter2(Point position)
{
    Point tileCoord = this->tileCoordForPosition(position);
    int tileGid = _blockage->getTileGIDAt(tileCoord);
    log("tileGid = %d", tileGid);
    if (tileGid) {
        auto properties = tileMap->getPropertiesForGID(tileGid).asValueMap();
        if (!properties.empty()) {
            auto koth = properties["KOTH"].asString();
            if("True" == koth) {
		log("KOTH");
		start2 = high_resolution_clock::now();
		dentro2 = true;
            }else
	    {
		dentro2 = false;
		//log("FELIPAO2");
            }

        }
    }

}

Scene* KOTH::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = KOTH::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}


// on "init" you need to initialize your instance
bool KOTH::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    for (i=0; i<3; i++) {
	actM1[i] = false;
	actM2[i] = false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    KOTH::createButtons(visibleSize);

    //Se agrega una etiqueta con el titulo
    auto label = Label::createWithTTF("King of the Hill", "fonts/Marker Felt.ttf", 32);
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    label->enableOutline(Color4B(255,0,0,0),5);
    this->addChild(label, 1);

    /////////////////////////////////
    ///// Manejo de fondos
    //Se carga el mapa y se hacen los collisions tiles con los que el tanque tiene que chocar
    tileMap = new CCTMXTiledMap();
    tileMap->initWithTMXFile("KOTH.tmx");
    _blockage = tileMap->layerNamed("Collision");
    _blockage->setVisible(false);
   // _koth = tileMap->layerNamed("KOTH");
  //  _koth->setVisible(false);

    tileMap->setPosition(origin.x,origin.y);
    this->addChild(tileMap);
    //Se obtiene la layer de objetos 'palpables' por el juego
    TMXObjectGroup *objects = tileMap->getObjectGroup("Objects");
    CCASSERT(NULL!=objects, "'Object Layer 1' object group not found");

    //Se inician los estados de los players
    initPlayerStatus();

    //Se crea el sprite de player 1
    auto Player = objects->getObject("Player1");
    CCASSERT(!Player.empty(),"Player object not found");
     x = Player["x"].asInt();
     y = Player["y"].asInt();
    _player1 = p1.getPlayer();
    _player1 =Sprite::create("tank3.png");
    setPlayer1Position(ccp(x,y));
    _player1->setScale(0.4);
    addChild(_player1);

    //Se crea el sprite de player 2
    auto Player2 = objects->getObject("Player2");
     x2 = Player2["x"].asInt();
     y2 = Player2["y"].asInt();
    _player2 = p2.getPlayer();
    _player2 = Sprite::create("tank3.png");
    _player2->setPosition(ccp(x2,y2));
    _player2->setScale(0.4);
    addChild(_player2);
    //_player2->runAction(RotateBy::create(0.001, 180));

    //Se crea sprite health bar de player 1
    HB1 = Sprite::create("healthBar.png");
    HB1->setPosition(ccp(x-400,y+525));
    HB1->setScale(0.9);
	addChild(HB1);
   //Se crea sprite health bar de player 2
   	HB2 = Sprite::create("healthBar.png");
    HB2->setPosition(ccp(x+300,y+525));
    HB2->setScale(0.9);
	addChild(HB2);

   //seccion de movimiento
   auto eventListener = EventListenerKeyboard::create();
   eventListener->onKeyPressed = CC_CALLBACK_2(KOTH::onKeyPressed, this);
   eventListener->onKeyReleased = CC_CALLBACK_2(KOTH::onKeyReleased, this);

   this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener,_player1);



    ////////////////////////////////////
    // Actualizacion del juego
    this->schedule(schedule_selector(KOTH::gameUpdate));


    // set the background music and continuously play it.
    audio->preloadBackgroundMusic("Audio/mgs3.mp3");
    //audio->preloadBackgroundMusic("Audio/ff7.mp3");
    audio->playBackgroundMusic("Audio/mgs3.mp3", true);
    crono = high_resolution_clock::now();

    // Pausa o continua el juego
    auto pausa = cocos2d::EventListenerKeyboard::create();
    pausa->onKeyPressed = [=](cocos2d::EventKeyboard::KeyCode tecla, cocos2d::Event * event)->void{
	if (tecla == cocos2d::EventKeyboard::KeyCode::KEY_SPACE){
	    if (pause){
		label->setString("King of the Hill");
		Director::sharedDirector()->resume();
	    }
	    else {
		label->setString("Pausa");
		Director::sharedDirector()->pause();
	    }
	    pause = !pause;
	}
    };

    // Game over


    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(pausa,this);



    return true;
}

void KOTH::createButtons(Size visibleSize)
{
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    // set the font for menu with text
    MenuItemFont::setFontSize(14);

    // Boton para volver al menu de inicio
    auto mbVolver = MenuItemFont::create("Menu de Inicio", CC_CALLBACK_1(KOTH::VolverCallBack, this));
    mbVolver->setAnchorPoint(Vec2(0.0,0.0));
    mbVolver->setPosition(0, visibleSize.height/15);
    mbVolver->setColor(Color3B(240, 230, 140));

    // Se crea un boton de salir
    auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png",
                                           CC_CALLBACK_1(KOTH::menuCloseCallback, this));
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2 + visibleSize.height/15));
    auto menu = Menu::create(mbVolver, closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 2);
}

void KOTH::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void KOTH::VolverCallBack(Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Audio/Button.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
    Director::sharedDirector()->replaceScene(PanzerWars::createScene());
}
