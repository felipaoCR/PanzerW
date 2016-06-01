#include "BatallaScene.h"
#include "PanzerWarsScene.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;
using namespace cocos2d;
using namespace std;

////////////////////////////////
//Manejo de fondos y movimientos
Point Batalla::tileCoordForPosition(Point _position)
{
    int x = _position.x / tileMap->getTileSize().width;
    int y = ((tileMap->getMapSize().height*tileMap->getTileSize().height) - _position.y)/tileMap->getTileSize().height;
    return Point(x, y);
}

void Batalla::initPlayerStatus()
{
	//Inicio estado de player1
	p1.setHealth(100);
	p1.setDefence(5);
	p1.setAttack(p1.getDefence());
	p1.setSpeed(1);
	//Inicio estado de player2
	p2.setHealth(100);
	p2.setDefence(10);
	p2.setAttack(p2.getDefence());
	p2.setSpeed(2);
	
}

void Batalla::gameUpdate(float interval)
{
    ////////////////////////////////////////////////////////////
    // Movimiento Jugadores
    loc1 = _player1->getPosition();
    loc2 = _player2->getPosition();
    if(!pause) {
	if(up1) {
	    switch(dirAnt1) {
		case 0:
		    break;
		case 1:
		    this->_player1->runAction(RotateBy::create(0.1, 180));
		    break;
		case 2:
		    this->_player1->runAction(RotateBy::create(0.1, 90));
		    break;
		case 3:
		    this->_player1->runAction(RotateBy::create(0.1, -90));
		    break;
	    }
	    dirAnt1 = 0;
	    setPlayer1Position(ccp(loc1.x,++loc1.y+p1.getSpeed())); // player 1 going up
	}
	else if(down1) {
	    switch(dirAnt1) {
		case 0:
		    this->_player1->runAction(RotateBy::create(0.2, 180));
		    break;
		case 1:
		    break;
		case 2:
		    this->_player1->runAction(RotateBy::create(0.1, -90));
		    break;
		case 3:
		    this->_player1->runAction(RotateBy::create(0.1, 90));
		    break;
	    }
	    dirAnt1 = 1;
	    setPlayer1Position(ccp(loc1.x,--loc1.y-p1.getSpeed())); // player 1 going down
	}
	else if(right1) {
	    switch(dirAnt1) {
		case 0:
		    this->_player1->runAction(RotateBy::create(0.1, 90));
		    break;
		case 1:
		    this->_player1->runAction(RotateBy::create(0.1, -90));
		    break;
		case 2:
		    this->_player1->runAction(RotateBy::create(0.2, 180));
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
		    this->_player1->runAction(RotateBy::create(0.1, -90));
		    break;
		case 1:
		    this->_player1->runAction(RotateBy::create(0.1, 90));
		    break;
		case 2:
		    break;
		case 3:
		    this->_player1->runAction(RotateBy::create(0.2, 180));
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
		    this->_player2->runAction(RotateBy::create(0.2, 180));
		    break;
		case 2:
		    this->_player2->runAction(RotateBy::create(0.1, 90));
		    break;
		case 3:
		    this->_player2->runAction(RotateBy::create(0.1, -90));
		    break;
	    }
	    dirAnt2 = 0;
	    setPlayer2Position(ccp(loc2.x,++loc2.y+p2.getSpeed())); // player 2 going up
	}
	else if(down2) {
	    switch(dirAnt2) {
		case 0:
		    this->_player2->runAction(RotateBy::create(0.2, 180));
		    break;
		case 1:
		    break;
		case 2:
		    this->_player2->runAction(RotateBy::create(0.1, -90));
		    break;
		case 3:
		    this->_player2->runAction(RotateBy::create(0.1, 90));
		    break;
	    }
	    dirAnt2 = 1;
	    setPlayer2Position(ccp(loc2.x,--loc2.y-p2.getSpeed())); // player 2 going down
	}
	else if(right2) {
	    switch(dirAnt2) {
		case 0:
		    this->_player2->runAction(RotateBy::create(0.1, 90));
		    break;
		case 1:
		    this->_player2->runAction(RotateBy::create(0.1, -90));
		    break;
		case 2:
		    this->_player2->runAction(RotateBy::create(0.2, 180));
		    break;
		case 3:
		    break;
	    }
	    dirAnt2 = 3;
	    setPlayer2Position(ccp(++loc2.x+p2.getSpeed(),loc2.y)); // player 2 going right
	}
	else if(left2) {
	   switch(dirAnt2) {
		case 0:
		    this->_player2->runAction(RotateBy::create(0.1, -90));
		    break;
		case 1:
		    this->_player2->runAction(RotateBy::create(0.1, 90));
		    break;
		case 2:
		    break;
		case 3:
		    this->_player2->runAction(RotateBy::create(0.2, 180));
		    break;
	    }
	    dirAnt2 = 2;
	    setPlayer2Position(ccp(--loc2.x-p2.getSpeed(),loc2.y)); // player 2 going left
	}
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
	    explosion(minaP2[i]);
	    delta = std::chrono::duration<double, std::milli>(high_resolution_clock::now()-start).count();
	    end += delta;
	    if (end > 5) {
		this->removeChild(minaP2[i]);
		end = 0;
	    }
	    actM2[i] = false;
	}
	if(bbP2.intersectsRect(bbM1[i]) && (actM1[i]==true)) {
	    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Audio/Bomb.mp3");
	    //-10 a health de p2
	    if(p2.getHealth()>0)
	    p2.setHealth(p2.getHealth()-50);
	    if(p2.getHealth()<0)
	    p2.setHealth(0);
	    explosion(minaP1[i]);
	    delta = std::chrono::duration<double, std::milli>(high_resolution_clock::now()-start).count();
	    end += delta;
	    if (end > 5) {
		this->removeChild(minaP1[i]);
		end = 0;
	    }
	    actM1[i] = false;
	}
    }
    /////////////////////////////////////////
        if(actm1)
    {
    	locm1 = misil1->getPosition();
	bbm1 = misil1->getBoundingBox();
	switch (dirm1)
	{
		case 0:
		    setMisil1Position(ccp(locm1.x,++locm1.y+3));
		    break;
		//this->misil1->runAction(RotateTo::create(0.1, 90));
		case 1:
		     setMisil1Position(ccp(locm1.x,--locm1.y-3));
		     break;
		//this->misil1->runAction(RotateTo::create(0.1, -90));
		case 2:
		    setMisil1Position(ccp(--locm1.x-3,locm1.y));
		    break;
		//this->misil1->runAction(RotateTo::create(0.1, 0));
		case 3:
		    setMisil1Position(ccp(++locm1.x+3,locm1.y));
		//this->misil1->runAction(RotateTo::create(0.1, 180));
	}
	if(bbm1.intersectsRect(bbP2))
	{
		explosion(misil1);
		delta = std::chrono::duration<double, std::milli>(high_resolution_clock::now()-start).count();
		end += delta;
		if (end > 5) {
		    this->removeChild(misil1);
		    end = 0;
		}
		actm1 = false;
		p2.setHealth(p2.getHealth()-20);
		if(p2.getHealth()<0)
		p2.setHealth(0);
	}
	for(i=0; i<3; i++) {
	    if((actM2[i]) && bbm1.intersectsRect(bbM2[i])) {
		explosion(misil1);
		explosion(minaP2[i]);
		delta = std::chrono::duration<double, std::milli>(high_resolution_clock::now()-start).count();
		end += delta;
		if (end > 5) {
		    this->removeChild(misil1);
		    this->removeChild(minaP2[i]);
		    end = 0;
		}
		actm1 = false;
		actM2[i] = false;
	    }
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
		explosion(misil2);
		delta = std::chrono::duration<double, std::milli>(high_resolution_clock::now()-start).count();
		end += delta;
		if (end > 5) {
		    this->removeChild(misil2);
		    end = 0;
		}
		actm2 = false;
		p1.setHealth(p1.getHealth()-20);
		if(p1.getHealth()<0)
		p1.setHealth(0);
	}
	for(i=0; i<3; i++) {
	    if((actM1[i]) && bbm2.intersectsRect(bbM1[i])) {
		explosion(misil2);
		explosion(minaP1[i]);
		delta = std::chrono::duration<double, std::milli>(high_resolution_clock::now()-start).count();
		end += delta;
		if (end > 5) {
		    this->removeChild(misil2);
		    this->removeChild(minaP1[i]);
		    end = 0;
		}
		actm2 = false;
		actM1[i] = false;
	    }
	}
	if(actm1) {
	    if(bbm1.intersectsRect(bbm2)) {
		explosion(misil2);
		explosion2(misil1);
		delta = std::chrono::duration<double, std::milli>(high_resolution_clock::now()-start).count();
		end += delta;
		if (end > 5) {
		    this->removeChild(misil2);
		    this->removeChild(misil1);
		    end = 0;
		}
		actm2 = false;
		actm1 = false;
	    }
	}
    }
    ////////////////////////////////////
    /// Barras de vida
  switch (p1.getHealth()) {
    case 100:
      removeChild(HB1);
      HB1 = Sprite::create("healthBar.png");
      HB1->setPosition(Vec2(3*visibleSize.width/16, 15*visibleSize.height/16));
      HB1->setScaleX(0.9);
      addChild(HB1);
      break;
    case 80:
      removeChild(HB1);
      HB1 = Sprite::create("healthBar.png");
      HB1->setPosition(Vec2(3*visibleSize.width/16, 15*visibleSize.height/16));
      HB1->setScaleX(0.72);
      addChild(HB1);
      break;
    case 60:
      removeChild(HB1);
      HB1 = Sprite::create("healthBar.png");
      HB1->setPosition(Vec2(3*visibleSize.width/16, 15*visibleSize.height/16));
      HB1->setScaleX(0.54);
      addChild(HB1);
      break;
    case 50:
      removeChild(HB1);
      HB1 = Sprite::create("healthBar.png");
      HB1->setPosition(Vec2(3*visibleSize.width/16, 15*visibleSize.height/16));
      HB1->setScaleX(0.45);
      addChild(HB1);
      break;
    case 40:
      removeChild(HB1);
      HB1 = Sprite::create("healthBar.png");
      HB1->setPosition(Vec2(3*visibleSize.width/16, 15*visibleSize.height/16));
      HB1->setScaleX(0.36);
      addChild(HB1);
      break;
    case 30:
        removeChild(HB1);
        HB1 = Sprite::create("healthBar.png");
        HB1->setPosition(Vec2(3*visibleSize.width/16, 15*visibleSize.height/16));
        HB1->setScaleX(0.27);
        addChild(HB1);
        break;
    case 20:
        removeChild(HB1);
        HB1 = Sprite::create("healthBar.png");
        HB1->setPosition(Vec2(3*visibleSize.width/16, 15*visibleSize.height/16));
        HB1->setScaleX(0.18);
        addChild(HB1);
        break;
    case 10:
        removeChild(HB1);
        HB1 = Sprite::create("healthBar.png");
        HB1->setPosition(Vec2(3*visibleSize.width/16, 15*visibleSize.height/16));
        HB1->setScaleX(0.09);
        addChild(HB1);
        break;
  }
  switch (p2.getHealth()) {
    case 100:
      removeChild(HB2);
      HB2 = Sprite::create("healthBar.png");
      HB2->setPosition(Vec2(13*visibleSize.width/16, 15*visibleSize.height/16));
      HB2->setScaleX(0.9);
      addChild(HB2);
      break;
    case 80:
      removeChild(HB2);
      HB2 = Sprite::create("healthBar.png");
      HB2->setPosition(Vec2(13*visibleSize.width/16, 15*visibleSize.height/16));
      HB2->setScaleX(0.72);
      addChild(HB2);
      break;
    case 60:
      removeChild(HB2);
      HB2 = Sprite::create("healthBar.png");
      HB2->setPosition(Vec2(13*visibleSize.width/16, 15*visibleSize.height/16));
      HB2->setScaleX(0.54);
      addChild(HB2);
      break;
    case 50:
      removeChild(HB2);
      HB2 = Sprite::create("healthBar.png");
      HB2->setPosition(Vec2(13*visibleSize.width/16, 15*visibleSize.height/16));
      HB2->setScaleX(0.45);
      addChild(HB2);
      break;
    case 40:
      removeChild(HB2);
      HB2 = Sprite::create("healthBar.png");
      HB2->setPosition(Vec2(13*visibleSize.width/16, 15*visibleSize.height/16));
      HB2->setScaleX(0.36);
      addChild(HB2);
      break;
    case 30:
      removeChild(HB2);
      HB2 = Sprite::create("healthBar.png");
      HB2->setPosition(Vec2(13*visibleSize.width/16, 15*visibleSize.height/16));
      HB2->setScaleX(0.27);
      addChild(HB2);
      break;
    case 20:
      removeChild(HB2);
      HB2 = Sprite::create("healthBar.png");
      HB2->setPosition(Vec2(13*visibleSize.width/16, 15*visibleSize.height/16));
      HB2->setScaleX(0.18);
      addChild(HB2);
      break;
    case 10:
      removeChild(HB2);
      HB2 = Sprite::create("healthBar.png");
      HB2->setPosition(Vec2(13*visibleSize.width/16, 15*visibleSize.height/16));
      HB2->setScaleX(0.09);
      addChild(HB2);
      break;
  }
    ///////////////////////////////////////
    //Game Over
    if(!p1.getHealth()) {
	explosion2(_player1);
        removeChild(HB1);
        HB1 = Sprite::create("healthBar.png");
        HB1->setPosition(Vec2(3*visibleSize.width/16, 15*visibleSize.height/16));
        HB1->setScaleX(0.005);
        addChild(HB1);
	auto gameOver = Label::createWithTTF("  Game Over\nPlayer 2 Won", "fonts/Marker Felt.ttf", 26);
    	gameOver->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    	this->addChild(gameOver, 1);
	deltaGO = std::chrono::duration<double, std::milli>(high_resolution_clock::now()-startGO).count();
	endGO += deltaGO;
	if (endGO > 5) {
	    pause = true;
	}
    }
    if(!p2.getHealth()) {
	explosion2(_player2);
	removeChild(HB2);
        HB2 = Sprite::create("healthBar.png");
        HB2->setPosition(Vec2(3*visibleSize.width/16, 15*visibleSize.height/16));
        HB2->setScaleX(0.005);
        addChild(HB2);
	auto gameOver = Label::createWithTTF("  Game Over\nPlayer 1 Won", "fonts/Marker Felt.ttf", 26);
    	gameOver->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    	this->addChild(gameOver, 1);
	deltaGO = std::chrono::duration<double, std::milli>(high_resolution_clock::now()-startGO).count();
	endGO += deltaGO;
	if (endGO > 5) {
	    pause = true;
	}
    }

}

void Batalla::explosion(Sprite *player)
{
    Vector<SpriteFrame*> animFrames(4);
    char str[100] = {0};
    for(int i = 1; i < 5; i++) {
	sprintf(str, "exp%d.png",i);
	auto frame = SpriteFrame::create(str,Rect(0,0,50,63));
	animFrames.pushBack(frame);
    }
    auto animation = Animation::createWithSpriteFrames(animFrames, 0.25f);
    auto animate = Animate::create(animation);
    player->runAction(animate);
    player->runAction(FadeOut::create(2.0f));
    start = high_resolution_clock::now();
}

void Batalla::explosion2(Sprite *player)
{
    Vector<SpriteFrame*> animFrames(4);
    char str[100] = {0};
    for(int i = 1; i < 5; i++) {
	sprintf(str, "exp%d.png",i);
	auto frame = SpriteFrame::create(str,Rect(0,0,50,63));
	animFrames.pushBack(frame);
    }
    auto animation = Animation::createWithSpriteFrames(animFrames, 0.25f);
    auto animate = Animate::create(animation);
    player->runAction(animate);
    player->runAction(FadeOut::create(2.0f));
    startGO = high_resolution_clock::now();
}

void Batalla::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
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
	case EventKeyboard::KeyCode::KEY_O:
	    if(actm2==false && !pause) {
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
    }
}

void Batalla::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
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

void Batalla::setPlayer1Position(Point position)
{
    /*Point tileCoord = this->tileCoordForPosition(position);
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
    }*/
    _player1->setPosition(position);
}

void Batalla::setPlayer2Position(Point position)
{
    /*Point tileCoord = this->tileCoordForPosition(position);
    int tileGid = _blockage->getTileGIDAt(tileCoord);
    log("tileGid = %d", tileGid);
    if (tileGid) {
	log("DEBUG");
        auto properties = tileMap->getPropertiesForGID(tileGid).asValueMap();
        if (!properties.empty()) {
            auto collision = properties["Collision"].asString();
            if ("True" == collision) {
		log("COLISION");
                return;
            }
        }else return;
    }*/
    _player2->setPosition(position);
}

void Batalla::setMisil1Position(Point position)
{
    /*Point tileCoord = this->tileCoordForPosition(position);
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
    }*/
    misil1->setPosition(position);
}

void Batalla::setMisil2Position(Point position)
{
    /*Point tileCoord = this->tileCoordForPosition(position);
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
    }*/
    misil2->setPosition(position);
}

Scene* Batalla::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Batalla::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Batalla::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    for (int i=0; i<3; i++) {
	actM1[i] = false;
	actM2[i] = false;
    }

    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    Batalla::createButtons(visibleSize);

    //Se agrega una etiqueta con el titulo    
    auto label = Label::createWithTTF("Batalla", "fonts/Marker Felt.ttf", 26);
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label, 1);

    /////////////////////////////////
    ///// Manejo de fondos
    //Se carga el mapa y se hacen los collisions tiles con los que el tanque tiene que chocar
    tileMap = new CCTMXTiledMap();    
    tileMap->initWithTMXFile("CTF.tmx");
    _blockage = tileMap->layerNamed("Collision");
    _blockage->setVisible(false);

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
    int x = Player["x"].asInt();
    int y = Player["y"].asInt();
    _player1 = p1.getPlayer();
    _player1 =Sprite::create("tank3.png");
    setPlayer1Position(ccp(x-50,y-50));
    _player1->setScale(0.3);
    addChild(_player1);

    //Se crea el sprite de player 2
    auto Player2 = objects->getObject("Player2");
    int x2 = Player2["x"].asInt();
    int y2 = Player2["y"].asInt();
    _player2 = p2.getPlayer();
    _player2 = Sprite::create("tank3.png");
    _player2->setPosition(ccp(x2,y2));
    _player2->setScale(0.3);
    addChild(_player2);
    _player2->runAction(RotateBy::create(0.01, 180));
    
    //Se crea sprite health bar de player 1
    HB1 = Sprite::create("healthBar.png");
    HB1->setPosition(Vec2(3*visibleSize.width/16, 15*visibleSize.height/16));
    HB1->setScale(0.9);
	addChild(HB1);
   //Se crea sprite health bar de player 2
   	HB2 = Sprite::create("healthBar.png");
    HB2->setPosition(Vec2(13*visibleSize.width/16, 15*visibleSize.height/16));
    HB2->setScale(0.9);
	addChild(HB2);
	
   //seccion de movimiento
   auto eventListener = EventListenerKeyboard::create();
   eventListener->onKeyPressed = CC_CALLBACK_2(Batalla::onKeyPressed, this);
   eventListener->onKeyReleased = CC_CALLBACK_2(Batalla::onKeyReleased, this);

   this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener,_player1);



    ////////////////////////////////////
    // Actualizacion del juego
    this->schedule(schedule_selector(Batalla::gameUpdate));


    // set the background music and continuously play it.
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->playBackgroundMusic("Audio/track01.mp3", true);

    // Pausa o continua el juego
    auto pausa = cocos2d::EventListenerKeyboard::create();
    pausa->onKeyPressed = [=](cocos2d::EventKeyboard::KeyCode tecla, cocos2d::Event * event)->void{
	if (tecla == cocos2d::EventKeyboard::KeyCode::KEY_SPACE){
	    if (pause){
		label->setString("Batalla");
		Director::sharedDirector()->resume();
	    }
	    else {
		label->setString("Pausa");
		Director::sharedDirector()->pause();
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

void Batalla::createButtons(Size visibleSize)
{
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    // set the font for menu with text
    MenuItemFont::setFontSize(14);

    // Boton para volver al menu de inicio
    auto mbVolver = MenuItemFont::create("Menu de Inicio", CC_CALLBACK_1(Batalla::VolverCallBack, this));
    mbVolver->setAnchorPoint(Vec2(0.0,0.0));
    mbVolver->setPosition(Vec2(1*visibleSize.width/16, 1*visibleSize.height/10));
    mbVolver->setColor(Color3B(140, 40, 140));

    // Se crea un boton de salir
    auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png",
                                           CC_CALLBACK_1(Batalla::menuCloseCallback, this));
    closeItem->setPosition(Vec2(15*visibleSize.width/16, 1*visibleSize.height/10));
    auto menu = Menu::create(mbVolver, closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 2);
}


void Batalla::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void Batalla::VolverCallBack(Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Audio/Button.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
    Director::sharedDirector()->replaceScene(PanzerWars::createScene());
}


