#include "CTFScene.h"
#include "PanzerWarsScene.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;
using namespace cocos2d;
using namespace std;

auto audioC = CocosDenshion::SimpleAudioEngine::getInstance();
auto audioCTF = CocosDenshion::SimpleAudioEngine::getInstance();
////////////////////////////////
//Manejo de fondos y movimientos
Point CTF::tileCoordForPosition(Point _position)
{
    int x = _position.x / tileMap->getTileSize().width;
    int y = ((tileMap->getMapSize().height*tileMap->getTileSize().height) - _position.y)/tileMap->getTileSize().height;
    return Point(x, y);
}

void CTF::initPlayer1Status()
{
	//Inicio estado de player1
	p1.setHealth(100);
	p1.setDefence(5);
	p1.setAttack(120);
	p1.setSpeed(1);
}

void CTF::initPlayer2Status()
{
	//Inicio estado de player2
	p2.setHealth(100);
	p2.setDefence(10);
	p2.setAttack(120);
	p2.setSpeed(2);
}

void CTF::gameUpdate(float interval)
{
    if(!pause) {
	loc1 = _player1->getPosition();
	loc2 = _player2->getPosition();
	bbP1 = _player1->getBoundingBox();
	bbP2 = _player2->getBoundingBox();
	bbB1 = ban1->getBoundingBox();
	bbB2 = ban2->getBoundingBox();
	HB1->setPosition(ccp(loc1.x,loc1.y+40));
	HB2->setPosition(ccp(loc2.x,loc2.y+40));
	//Se inician/refrescan los porcentajes de salud por hit al tanque
	HPpercentage1 = p2.getAttack()/p1.getDefence();
	HPpercentage2 = p1.getAttack()/p2.getDefence();
        //Verifica si player esta en layer 3
        onTop(ccp(loc1.x,loc1.y), _player1);
        onTop(ccp(loc2.x,loc2.y), _player2);

	timePlaying = std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now()-inicio).count() /1000;
    //Se chequea si se toman los upgrades
	if(!firstSpeed)
	getUpgrade(speedUp);
	if(!firstAttack)
	getUpgrade(attackUp);
	if(!firstDefence)
	getUpgrade(defenceUp);
	if(!firstHP)
	getUpgrade(HpUp);

	////////////////////////////////////////////////////////
	//Bloqueos
	for (j=0; j<6; j++) {
	    if(((actnPnt1[j]) && bbP1.intersectsRect(bbnPnt1[j])) || ((actnPnt2[j]) && bbP1.intersectsRect(bbnPnt2[j]))) {
		switch(dirAnt1) {
		    case 0:
			up1 = false;
			_player1->setPosition(loc1.x-1,loc1.y);
			break;
		    case 1:
			down1 = false;
			_player1->setPosition(loc1.x+1,loc1.y);
			break;
		    case 2:
			left1 = false;
			_player1->setPosition(loc1.x+1,loc1.y);
			break;
		    case 3:
			right1 = false;
			_player1->setPosition(loc1.x-1,loc1.y);
			break;
		}
	    }
	    if(((actnPnt1[j]) && bbP2.intersectsRect(bbnPnt1[j])) || ((actnPnt2[j]) && bbP2.intersectsRect(bbnPnt2[j]))) {
		switch(dirAnt2) {
		    case 0:
			up2 = false;
			_player2->setPosition(loc2.x-1,loc2.y);
			break;
		    case 1:
			down2 = false;
			_player2->setPosition(loc2.x+1,loc2.y);
			break;
		    case 2:
			left2 = false;
			_player2->setPosition(loc2.x+1,loc2.y);
			break;
		    case 3:
			right2 = false;
			_player2->setPosition(loc2.x-1,loc2.y);
			break;
		}
	    }
	}
	if (bbP1.intersectsRect(bbP2)) {
	    switch(dirAnt2) {
		case 0:
		    up2 = false;
		    break;
		case 1:
		    down2 = false;
		    break;
		case 2:
		    left2 = false;
		    break;
		case 3:
		    right2 = false;
		    break;
	    }
	    switch(dirAnt1) {
		case 0:
		    up1 = false;
		    break;
		case 1:
		    down1 = false;
		    break;
		case 2:
		    left1 = false;
		    break;
		case 3:
		    right1 = false;
		    break;
	    }
	}
	if (bbP1.intersectsRect(bbB1)) {
	    switch(dirAnt1) {
		case 0:
		    up1 = false;
		    break;
		case 1:
		    down1 = false;
		    break;
		case 2:
		    left1 = false;
		    break;
		case 3:
		    right1 = false;
		    break;
	    }
	}
	if (bbP2.intersectsRect(bbB2)) {
	    switch(dirAnt2) {
		case 0:
		    up2 = false;
		    break;
		case 1:
		    down2 = false;
		    break;
		case 2:
		    left2 = false;
		    break;
		case 3:
		    right2 = false;
		    break;
	    }
	}

	////////////////////////////////////////////////////////////
	// Movimiento Jugadores y se establece la posicion de health bars
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
	}

    /////////////////////////////////////////////
    // Para colisiones entre sprites
    for(i=0; i<3; i++) {
	if(bbP1.intersectsRect(bbM2[i]) && (actM2[i])) {
	    //if (!end) {
	    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Audio/Bomb.mp3");
	    //-10 a health de p1
	    if(p1.getHealth()>0)
	    p1.setHealth(p1.getHealth()-50);
	    if(p1.getHealth()<0)
	    p1.setHealth(0);
	    hitP2 = true;
	    explosion(minaP2[i]);
	    //}
	    delta = std::chrono::duration<double, std::milli>(high_resolution_clock::now()-start).count()/1000;
	    end = delta;
	    if (end > 2) {
		removeChild(minaP2[i]);
		end = 0;
	    }
  	        actM2[i] = false;
	}
	if(bbP2.intersectsRect(bbM1[i]) && (actM1[i])) {
	    //if(!end){
	    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Audio/Bomb.mp3");
	    //-10 a health de p2
	    if(p2.getHealth()>0)
	    p2.setHealth(p2.getHealth()-50);
	    if(p2.getHealth()<0)
	    p2.setHealth(0);
	    hitP1 = true;
	    explosion(minaP1[i]);
	    //}
	    delta = std::chrono::duration<double, std::milli>(high_resolution_clock::now()-start).count()/1000;
	    end = delta;
	    if (end > 2) {
		removeChild(minaP1[i]);
		end = 0;
	    }
  		actM1[i] = false;
	}
	//Destruccion de puente
	for (j=1; j<7; j++) {
	    if (bbPnt1[j-1].intersectsRect(bbM1[i]) && (actM1[i]) && (actPnt1[j-1])) {
		if (!end) {
		    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Audio/Bomb.mp3");
		    explosion(pnt1[j-1]);
		    explosion(minaP1[i]);
		}
		delta = std::chrono::duration<double, std::milli>(high_resolution_clock::now()-start).count()/1000;
		end = delta;
		if (end > 1) {
		    removeChild(pnt1[j-1]);
		    removeChild(minaP1[i]);
		    npnt1[j-1]->runAction(FadeIn::create(0.01f));
		    actPnt1[j-1] = false;
		    actnPnt1[j-1] = true;
		    actM1[i] = false;
		    end = 0;
		}
	    }
	    if (bbPnt1[j-1].intersectsRect(bbM2[i]) && (actM2[i]) && (actPnt1[j-1])) {
		if (!end) {
		    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Audio/Bomb.mp3");
		    explosion(pnt1[j-1]);
		    explosion(minaP2[i]);
		}
		delta = std::chrono::duration<double, std::milli>(high_resolution_clock::now()-start).count()/1000;
		end = delta;
		if (end > 1) {
		    removeChild(pnt1[j-1]);
		    removeChild(minaP2[i]);
		    npnt1[j-1]->runAction(FadeIn::create(0.01f));
		    actPnt1[j-1] = false;
		    actnPnt1[j-1] = true;
		    actM2[i] = false;
		    end = 0;
		}
	    }
	    if (bbPnt2[j-1].intersectsRect(bbM1[i]) && (actM1[i]) && (actPnt2[j-1])) {
		if (!end) {
		    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Audio/Bomb.mp3");
		    explosion(pnt2[j-1]);
		    explosion(minaP1[i]);
		}
		delta = std::chrono::duration<double, std::milli>(high_resolution_clock::now()-start).count()/1000;
		end = delta;
		if (end > 1) {
		    removeChild(pnt2[j-1]);
		    removeChild(minaP1[i]);
		    npnt2[j-1]->runAction(FadeIn::create(0.01f));
		    actPnt2[j-1] = false;
		    actnPnt2[j-1] = true;
		    actM1[i] = false;
		    end = 0;
		}
	    }
	    if (bbPnt2[j-1].intersectsRect(bbM2[i]) && (actM2[i]) && (actPnt2[j-1])) {
		if (!end) {
		    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Audio/Bomb.mp3");
		    explosion(pnt2[j-1]);
		    explosion(minaP2[i]);
		}
		delta = std::chrono::duration<double, std::milli>(high_resolution_clock::now()-start).count()/1000;
		end = delta;
		if (end > 1) {
		    removeChild(pnt2[j-1]);
		    removeChild(minaP2[i]);
		    npnt2[j-1]->runAction(FadeIn::create(0.01f));
		    actPnt2[j-1] = false;
		    actnPnt2[j-1] = true;
		    actM2[i] = false;
		    end = 0;
		}
	    }
	}
    }

    /////////////////////////////////////////
    //Misiles
        if(actm1)
    {
    	locm1 = misil1->getPosition();
	bbm1 = misil1->getBoundingBox();
	// if(_player1->getZOrder()==2)
	// {
	//     misil1->setZOrder(2);
	// }
        //onTop(ccp(locm1.x,locm1.y), misil1);
	//if(movm1) {
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
//	}
	}
	if(bbm1.intersectsRect(bbP2))
	{
		//if(!end) {
		explosion(misil1);
		movm1 = false;
		p2.setHealth(p2.getHealth()-HPpercentage2);
		hitP1 = true;
		if(p2.getHealth()<0)
		p2.setHealth(0);
		//}
		delta = std::chrono::duration<double, std::milli>(high_resolution_clock::now()-start).count()/1000;
		end = delta;
		if (end > 2) {
		    tileMap->removeChild(misil1);
		    end = 0;
		}
    actm1 = false;
	}
	for(i=0; i<3; i++) {
	    if((actM2[i]) && bbm1.intersectsRect(bbM2[i])) {
		//if(!end) {
		explosion(misil1);
		explosion(minaP2[i]);
		movm1=false;
		//}
		delta = std::chrono::duration<double, std::milli>(high_resolution_clock::now()-start).count()/1000;
		end = delta;
		if (end > 2) {
		    tileMap->removeChild(misil1);
		    removeChild(minaP2[i]);
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
	// if(_player2->getZOrder()==2)
	// {
	//     misil2->setZOrder(2);
	// }
        //onTop(ccp(locm2.x,locm2.y), misil2);
	//if(movm2){
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
//	}
	if(bbm2.intersectsRect(bbP1))
	{
		//if(!end){
		explosion(misil2);
		p1.setHealth(p1.getHealth()-HPpercentage1);
		hitP2 = true;
		if(p1.getHealth()<0)
		p1.setHealth(0);
		movm2 = false;
		//}
		delta = std::chrono::duration<double, std::milli>(high_resolution_clock::now()-start).count()/1000;
		end = delta;
		if (end > 2) {
		    tileMap->removeChild(misil2);
		    end = 0;
		}
    actm2 = false;
	}
	for(i=0; i<3; i++) {
	    if((actM1[i]) && bbm2.intersectsRect(bbM1[i])) {
		//if(!end) {
		explosion(misil2);
		explosion(minaP1[i]);
		movm2=false;
		//}
		delta = std::chrono::duration<double, std::milli>(high_resolution_clock::now()-start).count()/1000;
		end = delta;
		if (end > 2) {
		    tileMap->removeChild(misil2);
		    removeChild(minaP1[i]);
		    end = 0;
		}
    actm2 = false;
    actM1[i] = false;
	    }
	}
	if(actm1) {
	    if(bbm1.intersectsRect(bbm2)) {
		//if(!end) {
		explosion(misil2);
		explosion2(misil1);
		movm1=false;
		movm2=false;
		//}
		delta = std::chrono::duration<double, std::milli>(high_resolution_clock::now()-start).count()/1000;
		end = delta;
		if (end > 2) {
		    tileMap->removeChild(misil2);
		    tileMap->removeChild(misil1);
		    end = 0;
		    endGO = 0;
		}
    actm2 = false;
    actm1 = false;
	    }
	}
    }
    ////////////////////////////////////
    /// Barras de vida
    if(hitP2)
    {
	if(p1.getHealth()==100)
	{
      	  removeChild(HB1);
      	  HB1 = Sprite::create("healthBar.png");
      	  HB1->setPosition(ccp(loc1.x,loc1.y+40));
      	  HB1->setScaleX(0.225);
      	  HB1->setScaleY(0.1);
      	  addChild(HB1);
	}else if(p1.getHealth()!=100 && p1.getHealth()>0)
	{
	  HB1->setScaleX(0.225*((float)p1.getHealth()/100));
	}
	hitP2 = false;
    }
    if(hitP1)
    {
	if(p2.getHealth()==100)
	 {
      	  removeChild(HB2);
      	  HB2 = Sprite::create("healthBar.png");
   	  HB2->setPosition(ccp(loc2.x,loc2.y+40));
          HB2->setScaleX(0.225);
      	  HB2->setScaleY(0.1);
      	  addChild(HB2);
	}else if(p2.getHealth()!=100 && p2.getHealth()>0)
	{
	  HB2->setScaleX(0.225*((float)p2.getHealth()/100));
	}
	hitP1 = false;
    }
    if(hpup1)
    {
	HB1->setScaleX(1.2*0.225);
	hpup1 = false;
    }
    if(hpup2)
    {
	HB2->setScaleX(1.2*0.225);
	hpup2 = false;
    }

    ///////////////////////////////////////////////////
    //Bandera capturada
    if (bbP1.intersectsRect(bbB2)) {
	ban2->setPosition(loc1);
	ban2->setScale(0.75f);
	b2WasTaken = true;
	if (b2WasTaken){
		log("Ban 2 tomada");
		ban2->setZOrder(3);
		noBan2->setZOrder(2);
	}
    }
    if (bbP2.intersectsRect(bbB1)) {
	ban1->setPosition(loc2);
	ban1->setScale(0.75f);
	b1WasTaken = true;
	if (b1WasTaken){
		log("Ban 1 tomada");
		ban1->setZOrder(3);
		noBan1->setZOrder(2);
	}
    }
    if (bbP2.intersectsRect(bbnB2) && b1WasTaken && !b2WasTaken) {
	scoreP2++;
	log("Score P1: %d",scoreP1);
	log("Score P2: %d",scoreP2);
	b1WasTaken = false;
	ban1->setPosition(ccp(xC1+175,yC1+227));
	ban1->setScale(1.235);
	noBan1->setZOrder(1);
	ban1->setZOrder(1);
    }
    if (bbP1.intersectsRect(bbnB1) && b2WasTaken && !b1WasTaken) {
	scoreP1++;
	log("Score P1: %d",scoreP1);
	log("Score P2: %d",scoreP2);
	b2WasTaken = false;
	ban2->setPosition(ccp(xC2+75,yC2+233));
	ban2->setScale(1.235);
	noBan2->setZOrder(1);
	ban2->setZOrder(1);
    }

    ///////////////////////////////////////
    //Game Over
    if(timePlaying>180) {
	if (scoreP1 == scoreP2) { //Tie
	    Size vS3 = Director::getInstance()->getVisibleSize();
	    Vec2 ori3 = Director::getInstance()->getVisibleOrigin();
	    auto gameOver3 = Label::createWithTTF("Game Over\nIt's a tie!", "fonts/Marker Felt.ttf", 26);
    	    gameOver3->setPosition(Vec2(ori3.x + vS3.width/2, ori3.y + vS3.height/2));
	    gameOver3->enableOutline(Color4B(255,0,255,255),3);
    	    this->addChild(gameOver3, 1);
	} else if (scoreP1 > scoreP2) { //Player 1 won
	    Size vS3 = Director::getInstance()->getVisibleSize();
	    Vec2 ori3 = Director::getInstance()->getVisibleOrigin();
	    auto gameOver3 = Label::createWithTTF("Game Over\nPlayer 1 Won!", "fonts/Marker Felt.ttf", 26);
    	    gameOver3->setPosition(Vec2(ori3.x + vS3.width/2, ori3.y + vS3.height/2));
	    gameOver3->enableOutline(Color4B(255,0,255,255),3);
    	    this->addChild(gameOver3, 1);
	} else {//Player 2 won
	    Size vS3 = Director::getInstance()->getVisibleSize();
	    Vec2 ori3 = Director::getInstance()->getVisibleOrigin();
	    auto gameOver3 = Label::createWithTTF("Game Over\nPlayer 2 Won!", "fonts/Marker Felt.ttf", 26);
    	    gameOver3->setPosition(Vec2(ori3.x + vS3.width/2, ori3.y + vS3.height/2));
	    gameOver3->enableOutline(Color4B(255,0,255,255),3);
    	    this->addChild(gameOver3, 1);
	}
	pause = true;
	audioC->stopAllEffects();
	audioCTF->stopBackgroundMusic();
	Director::sharedDirector()->pause();
    }

    //Spawneo
    if(!p2.getHealth()) {
	if(!endGO) {
	    explosion2(_player2);
	    if (b1WasTaken) {
		b1WasTaken = false;
		ban1->setPosition(ccp(xC1+175,yC1+227));
		ban1->setScale(1.235);
		noBan1->setZOrder(1);
		ban1->setZOrder(1);
	    }
	}
	deltaGO = std::chrono::duration<double, std::milli>(high_resolution_clock::now()-startGO).count()/1000;
	endGO = deltaGO;
	if(endGO>2.5) {
	    removeChild(_player2);
	    _player2 = Sprite::create("tank3.png");
	    _player2->setPosition(ccp(xC2,yC2));
	    _player2->setScale(0.3);
	    addChild(_player2);
	    _player2->runAction(RotateBy::create(0.01, 180));
	    dirAnt2 = 0;
	    _player2->runAction(FadeIn::create(0.01f));
	    initPlayer2Status();
	    hitP1 = true;
	    endGO=0;
	}
    }
    if(!p1.getHealth()) {
	if(!endGO) {
	    explosion2(_player1);
	    if (b2WasTaken) {
		b2WasTaken = false;
		ban2->setPosition(ccp(xC2+75,yC2+233));
		ban2->setScale(1.235);
		noBan2->setZOrder(1);
		ban2->setZOrder(1);
	    }
	}
	deltaGO = std::chrono::duration<double, std::milli>(high_resolution_clock::now()-startGO).count()/1000;
	endGO = deltaGO;
	if(endGO>2.5) {
	    removeChild(_player1);
	    _player1 =Sprite::create("tank3.png");
	    setPlayer1Position(ccp(xC1,yC1));
	    _player1->setScale(0.3);
	    addChild(_player1);
	    dirAnt1 = 1;
	    _player1->runAction(FadeIn::create(0.01f));
	    initPlayer1Status();
	    hitP2 = true;
	    endGO=0;
	}
    }

}
}

void CTF::explosion(Sprite *player)
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

void CTF::explosion2(Sprite *player)
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

void CTF::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
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
	    if(cantM1>0 && !pause && p1.getHealth()){
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
	    if(actm1==false && !pause && p1.getHealth()) {
   	 	audioC->playEffect("Audio/explosion3.mp3");
    		audioC->setEffectsVolume(0.3);
		misil1 = Sprite::create("c1.png");
		misil1->setPosition(_player1->getPosition());
		misil1->setScale(0.4);
		tileMap->addChild(misil1,1);
		actm1 = true;
		movm1 = true;
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
	    if(cantM2>0 && !pause && p2.getHealth()){
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
	    if(actm2==false && !pause && p2.getHealth()) {
   	 	audioC->playEffect("Audio/explosion3.mp3");
    		audioC->setEffectsVolume(0.3);
		misil2 = Sprite::create("c1.png");
		misil2->setPosition(_player2->getPosition());
		misil2->setScale(0.4);
		tileMap->addChild(misil2,1);
		actm2 = true;
		movm2 = true;
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

void CTF::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
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

void CTF::setPlayer1Position(Point position)
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

void CTF::setPlayer2Position(Point position)
{
    Point tileCoord = this->tileCoordForPosition(position);
    int tileGid = _blockage->getTileGIDAt(tileCoord);
    log("tileGid = %d", tileGid);
    if (tileGid) {
	//log("DEBUG");
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

void CTF::setMisil1Position(Point position)
{
    Point tileCoord = this->tileCoordForPosition(position);
    int tileGid = _blockage->getTileGIDAt(tileCoord);
    if (tileGid) {
        auto properties = tileMap->getPropertiesForGID(tileGid).asValueMap();
        if (!properties.empty()) {
            auto collision = properties["Collision"].asString();
            if ("True" == collision) {
	    	tileMap->removeChild(misil1);
	    	actm1 = false;
	    	log("COLISION");
            	return;
            }
        }else return;
    }
    misil1->setPosition(position);
}

void CTF::setMisil2Position(Point position)
{
    Point tileCoord = this->tileCoordForPosition(position);
    int tileGid = _blockage->getTileGIDAt(tileCoord);
    if (tileGid) {
        auto properties = tileMap->getPropertiesForGID(tileGid).asValueMap();
        if (!properties.empty()) {
            auto collision = properties["Collision"].asString();
            if ("True" == collision) {
		tileMap->removeChild(misil2);
		actm2 = false;
		log("COLISION");
                return;
            }
        }else return;
    }
    misil2->setPosition(position);
}

void CTF::getUpgrade(Sprite *upgrade)
{
	//log("Tag = %d",upgrade->getTag());
   bbspeedUp = upgrade->getBoundingBox();
   if((bbP1).intersectsRect(bbspeedUp) && (!firstHP || !firstSpeed || !firstDefence || !firstAttack))
   {
	switch(upgrade->getTag())
	{
	  case 1:
	     p1.setHealth(120);
	     hpup1 = true;
	     firstHP = true;
	  break;
	  case 2:
	     p1.setSpeed(2*p1.getSpeed());
	     firstSpeed = true;
	  break;
	  case 3:
             p1.setDefence(2*p1.getDefence());
	     firstDefence = true;
	  break;
	  case 4:
	     p1.setAttack(2*p1.getAttack());
	     firstAttack = true;
	  break;
	}
         removeChild(upgrade);
   }

   if((bbP2).intersectsRect(bbspeedUp) && (!firstHP || !firstSpeed || !firstDefence || !firstAttack))
   {
	switch(upgrade->getTag())
	{
	  case 1:
	     p2.setHealth(120);
	     firstHP = true;
	     hpup2 = true;
	  break;
	  case 2:
	     p2.setSpeed(2*p2.getSpeed());
	     firstSpeed = true;
	  break;
	  case 3:
             p2.setDefence(2*p2.getDefence());
	     firstDefence = true;
	  break;
	  case 4:
	     p2.setAttack(2*p2.getAttack());
	     firstAttack = true;
	  break;
	}
        removeChild(upgrade);
   }

}

void CTF::onTop(Point position,Sprite *player)
{
    Point tileCoord = this->tileCoordForPosition(position);
    int tileGid = _blockage->getTileGIDAt(tileCoord);
    if (tileGid) {
        auto properties = tileMap->getPropertiesForGID(tileGid).asValueMap();
        if (!properties.empty()) {
	    auto onTop = properties["onTop"].asString();
	    auto notTop = properties["notTop"].asString();
            if (onTop == "True")
	    {
		player->setZOrder(2);
		return;
            }
            if (notTop == "True")
	    {
         	player->setZOrder(1);
		return;
            }

        }
    }
}

Scene* CTF::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = CTF::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool CTF::init()
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

    for (j=0; j<6; j++) {
	actPnt1[j] = true;
	actPnt2[j] = true;
	actnPnt1[j] = false;
	actnPnt2[j] = false;
    }

    Director::sharedDirector()->resume();

    inicio = high_resolution_clock::now();

    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    CTF::createButtons(visibleSize);

    //Se agrega una etiqueta con el titulo
    auto label = Label::createWithTTF("Capture the Flag", "fonts/Marker Felt.ttf", 26);
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label, 1);

    /////////////////////////////////
    ///// Manejo de fondos
    //Se carga el mapa y se hacen los collisions tiles con los que el tanque tiene que chocar
    tileMap = new CCTMXTiledMap();
    tileMap->initWithTMXFile("CTF.tmx");
    _blockage = tileMap->layerNamed("Collision");
    water = tileMap->layerNamed("water");
    water->setVisible(false);
    _blockage->setVisible(false);

    tileMap->setPosition(origin.x,origin.y);
    this->addChild(tileMap);
    //Se obtiene la layer de objetos 'palpables' por el juego
    TMXObjectGroup *objects = tileMap->getObjectGroup("Objects");
    CCASSERT(NULL!=objects, "'Object Layer 1' object group not found");

    //Se inician los estados de los players
    initPlayer1Status();
    initPlayer2Status();

    //Coordenadas de los jugadores
    auto Player = objects->getObject("Player1");
    CCASSERT(!Player.empty(),"Player object not found");
    xC1 = Player["x"].asInt();
    yC1 = Player["y"].asInt();
    auto Player2 = objects->getObject("Player2");
    xC2 = Player2["x"].asInt();
    yC2 = Player2["y"].asInt();

    //Objetos Destruibles
    //Puentes
    dy = 108;
    dx = 238.085;
    //Puente1
    pnt1[0] = Sprite::create("puente1.png");
    pnt1[0]->setPosition(ccp(xC1-dx-135.85,yC1+dy));
    pnt1[0]->setScale(1.235);
    tileMap->addChild(pnt1[0],1);
    bbPnt1[0] = pnt1[0]->getBoundingBox();
    pnt1[1] = Sprite::create("puente2.png");
    pnt1[1]->setPosition(ccp(xC1-dx-108.68,yC1+dy));
    pnt1[1]->setScale(1.235);
    tileMap->addChild(pnt1[1],1);
    bbPnt1[1] = pnt1[1]->getBoundingBox();
    pnt1[2] = Sprite::create("puente3.png");
    pnt1[2]->setPosition(ccp(xC1-dx-81.51,yC1+dy));
    pnt1[2]->setScale(1.235);
    tileMap->addChild(pnt1[2],1);
    bbPnt1[2] = pnt1[2]->getBoundingBox();
    pnt1[3] = Sprite::create("puente4.png");
    pnt1[3]->setPosition(ccp(xC1-dx-54.34,yC1+dy));
    pnt1[3]->setScale(1.235);
    tileMap->addChild(pnt1[3],1);
    bbPnt1[3] = pnt1[3]->getBoundingBox();
    pnt1[4] = Sprite::create("puente5.png");
    pnt1[4]->setPosition(ccp(xC1-dx-27.17,yC1+dy));
    pnt1[4]->setScale(1.235);
    tileMap->addChild(pnt1[4],1);
    bbPnt1[4] = pnt1[4]->getBoundingBox();
    pnt1[5] = Sprite::create("puente6.png");
    pnt1[5]->setPosition(ccp(xC1-dx,yC1+dy));
    pnt1[5]->setScale(1.235);
    tileMap->addChild(pnt1[5],1);
    bbPnt1[5] = pnt1[5]->getBoundingBox();
    //Puente2
    pnt2[0] = Sprite::create("puente1.png");
    pnt2[0]->setPosition(ccp(xC1-dx-135.85,yC1+dy-35.345));
    pnt2[0]->setScale(1.235);
    tileMap->addChild(pnt2[0],1);
    bbPnt2[0] = pnt2[0]->getBoundingBox();
    pnt2[1] = Sprite::create("puente2.png");
    pnt2[1]->setPosition(ccp(xC1-dx-108.68,yC1+dy-35.345));
    pnt2[1]->setScale(1.235);
    tileMap->addChild(pnt2[1],1);
    bbPnt2[1] = pnt2[1]->getBoundingBox();
    pnt2[2] = Sprite::create("puente3.png");
    pnt2[2]->setPosition(ccp(xC1-dx-81.51,yC1+dy-35.345));
    pnt2[2]->setScale(1.235);
    tileMap->addChild(pnt2[2],1);
    bbPnt2[0] = pnt2[2]->getBoundingBox();
    pnt2[3] = Sprite::create("puente4.png");
    pnt2[3]->setPosition(ccp(xC1-dx-54.34,yC1+dy-35.345));
    pnt2[3]->setScale(1.235);
    tileMap->addChild(pnt2[3],1);
    bbPnt2[3] = pnt2[3]->getBoundingBox();
    pnt2[4] = Sprite::create("puente5.png");
    pnt2[4]->setPosition(ccp(xC1-dx-27.17,yC1+dy-35.345));
    pnt2[4]->setScale(1.235);
    tileMap->addChild(pnt2[4],1);
    bbPnt2[4] = pnt2[4]->getBoundingBox();
    pnt2[5] = Sprite::create("puente6.png");
    pnt2[5]->setPosition(ccp(xC1-dx,yC1+dy-35.345));
    pnt2[5]->setScale(1.235);
    tileMap->addChild(pnt2[5],1);
    bbPnt2[5] = pnt2[5]->getBoundingBox();
    //NoPuente1
    npnt1[0] = Sprite::create("nopuente1.png");
    npnt1[0]->setPosition(ccp(xC1-dx-135.85,yC1+dy));
    npnt1[0]->setScale(1.235);
    tileMap->addChild(npnt1[0],1);
    bbnPnt1[0] = npnt1[0]->getBoundingBox();
    npnt1[0]->runAction(FadeOut::create(0.01f));
    npnt1[1] = Sprite::create("nopuente2.png");
    npnt1[1]->setPosition(ccp(xC1-dx-108.68,yC1+dy));
    npnt1[1]->setScale(1.235);
    tileMap->addChild(npnt1[1],1);
    bbnPnt1[1] = npnt1[1]->getBoundingBox();
    npnt1[1]->runAction(FadeOut::create(0.01f));
    npnt1[2] = Sprite::create("nopuente3.png");
    npnt1[2]->setPosition(ccp(xC1-dx-81.51,yC1+dy));
    npnt1[2]->setScale(1.235);
    tileMap->addChild(npnt1[2],1);
    bbnPnt1[2] = npnt1[2]->getBoundingBox();
    npnt1[2]->runAction(FadeOut::create(0.01f));
    npnt1[3] = Sprite::create("nopuente4.png");
    npnt1[3]->setPosition(ccp(xC1-dx-54.34,yC1+dy));
    npnt1[3]->setScale(1.235);
    tileMap->addChild(npnt1[3],1);
    bbnPnt1[3] = npnt1[3]->getBoundingBox();
    npnt1[3]->runAction(FadeOut::create(0.01f));
    npnt1[4] = Sprite::create("nopuente5.png");
    npnt1[4]->setPosition(ccp(xC1-dx-27.17,yC1+dy));
    npnt1[4]->setScale(1.235);
    tileMap->addChild(npnt1[4],1);
    bbnPnt1[4] = npnt1[4]->getBoundingBox();
    npnt1[4]->runAction(FadeOut::create(0.01f));
    npnt1[5] = Sprite::create("nopuente6.png");
    npnt1[5]->setPosition(ccp(xC1-dx,yC1+dy));
    npnt1[5]->setScale(1.235);
    tileMap->addChild(npnt1[5],1);
    bbnPnt1[5] = npnt1[5]->getBoundingBox();
    npnt1[5]->runAction(FadeOut::create(0.01f));;
    //NoPuente2
    npnt2[0] = Sprite::create("nopuente1.png");
    npnt2[0]->setPosition(ccp(xC1-dx-135.85,yC1+dy-35.345));
    npnt2[0]->setScale(1.235);
    tileMap->addChild(npnt2[0],1);
    bbnPnt2[0] = npnt2[0]->getBoundingBox();
    npnt2[0]->runAction(FadeOut::create(0.01f));;
    npnt2[1] = Sprite::create("nopuente2.png");
    npnt2[1]->setPosition(ccp(xC1-dx-108.68,yC1+dy-35.345));
    npnt2[1]->setScale(1.235);
    tileMap->addChild(npnt2[1],1);
    bbnPnt2[1] = npnt2[1]->getBoundingBox();
    npnt2[1]->runAction(FadeOut::create(0.01f));;
    npnt2[2] = Sprite::create("nopuente3.png");
    npnt2[2]->setPosition(ccp(xC1-dx-81.51,yC1+dy-35.345));
    npnt2[2]->setScale(1.235);
    tileMap->addChild(npnt2[2],1);
    bbnPnt2[2] = npnt2[2]->getBoundingBox();
    npnt2[2]->runAction(FadeOut::create(0.01f));;
    npnt2[3] = Sprite::create("nopuente4.png");
    npnt2[3]->setPosition(ccp(xC1-dx-54.34,yC1+dy-35.345));
    npnt2[3]->setScale(1.235);
    tileMap->addChild(npnt2[3],1);
    bbnPnt2[3] = npnt2[3]->getBoundingBox();
    npnt2[3]->runAction(FadeOut::create(0.01f));;
    npnt2[4] = Sprite::create("nopuente5.png");
    npnt2[4]->setPosition(ccp(xC1-dx-27.17,yC1+dy-35.345));
    npnt2[4]->setScale(1.235);
    tileMap->addChild(npnt2[4],1);
    bbnPnt2[4] = npnt2[4]->getBoundingBox();
    npnt2[4]->runAction(FadeOut::create(0.01f));;
    npnt2[5] = Sprite::create("nopuente6.png");
    npnt2[5]->setPosition(ccp(xC1-dx,yC1+dy-35.345));
    npnt2[5]->setScale(1.235);
    tileMap->addChild(npnt2[5],1);
    bbnPnt2[5] = npnt2[5]->getBoundingBox();
    npnt2[5]->runAction(FadeOut::create(0.01f));

    //Banderas
    noBan1 = Sprite::create("nobandera.png");
    noBan1->setPosition(ccp(xC1+175,yC1+227));
    noBan1->setScale(1.235);
    tileMap->addChild(noBan1,1);
    bbnB1 = noBan1->getBoundingBox();
    //noBan1->runAction(FadeOut::create(0.01f));
    noBan2 = Sprite::create("nobandera.png");
    noBan2->setPosition(ccp(xC2+75,yC2+233));
    noBan2->setScale(1.235);
    tileMap->addChild(noBan2,1);
    bbnB2 = noBan2->getBoundingBox();
    //noBan2->runAction(FadeOut::create(0.01f));

    //Se crea el sprite de player 1
    _player1 = p1.getPlayer();
    _player1 =Sprite::create("tank3.png");
    setPlayer1Position(ccp(xC1,yC1));
    _player1->setScale(0.3);
    tileMap->addChild(_player1,1);

    //Se crea el sprite de player 2
    _player2 = p2.getPlayer();
    _player2 = Sprite::create("tank3.png");
    _player2->setPosition(ccp(xC2,yC2));
    _player2->setScale(0.3);
    tileMap->addChild(_player2,1);
    _player2->runAction(RotateBy::create(0.01, 180));

    //Banderas
    ban1 = Sprite::create("bandera.png");
    ban1->setPosition(ccp(xC1+175,yC1+227));
    ban1->setScale(1.235);
    tileMap->addChild(ban1,2);
    ban2 = Sprite::create("bandera.png");
    ban2->setPosition(ccp(xC2+75,yC2+233));
    ban2->setScale(1.235);
    tileMap->addChild(ban2,2);

    //Se crea sprite health bar de player 1
    HB1 = Sprite::create("healthBar.png");
    HB1->setPosition(ccp(xC1,yC1+40));
    HB1->setScaleX(0.225);
    HB1->setScaleY(0.1);
	addChild(HB1,1);
   //Se crea sprite health bar de player 2
    HB2 = Sprite::create("healthBar.png");
    HB2->setPosition(ccp(xC2,yC2+40));
    HB2->setScaleX(0.225);
    HB2->setScaleY(0.1);
	addChild(HB2,1);
   //Se crean los sprites de upgrade
    //Tag = 1
    HpUp = Sprite::create("HpUp.png");
    HpUp->setPosition(ccp(xC2,yC2-300));
    HpUp->setScale(0.3);
    HpUp->setTag(1);
    addChild(HpUp);

    //Tag = 2
    speedUp = Sprite::create("speedUp.png");
    speedUp->setPosition(ccp(xC1,yC1+300));
    speedUp->setScale(0.3);
    speedUp->setTag(2);
    addChild(speedUp);

    //Tag = 3
    defenceUp = Sprite::create("defenceUp.png");
    defenceUp->setPosition(ccp(xC1,yC1+200));
    defenceUp->setScale(0.3);
    defenceUp->setTag(3);
    addChild(defenceUp);

    //Tag = 4
    attackUp = Sprite::create("attackUp.png");
    attackUp->setPosition(ccp(xC1,yC1+100));
    attackUp->setScale(0.3);
    attackUp->setTag(4);
    addChild(attackUp);


   //seccion de movimiento
   auto eventListener = EventListenerKeyboard::create();
   eventListener->onKeyPressed = CC_CALLBACK_2(CTF::onKeyPressed, this);
   eventListener->onKeyReleased = CC_CALLBACK_2(CTF::onKeyReleased, this);

   this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener,_player1);



    ////////////////////////////////////
    // Actualizacion del juego
    this->schedule(schedule_selector(CTF::gameUpdate));


    // set the background music and continuously play it.
    audioCTF = CocosDenshion::SimpleAudioEngine::getInstance();
    audioCTF->playBackgroundMusic("Audio/track01.mp3", true);

    // Pausa o continua el juego
    auto pausa = cocos2d::EventListenerKeyboard::create();
    pausa->onKeyPressed = [=](cocos2d::EventKeyboard::KeyCode tecla, cocos2d::Event * event)->void{
	if (tecla == cocos2d::EventKeyboard::KeyCode::KEY_SPACE){
	    if (pause){
		label->setString("Capture the Flag");
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

void CTF::createButtons(Size visibleSize)
{
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    // set the font for menu with text
    MenuItemFont::setFontSize(14);

    // Boton para volver al menu de inicio
    auto mbVolver = MenuItemFont::create("Menu de Inicio", CC_CALLBACK_1(CTF::VolverCallBack, this));
    mbVolver->setAnchorPoint(Vec2(0.0,0.0));
    mbVolver->setPosition(Vec2(1*visibleSize.width/16, 1*visibleSize.height/10));
    mbVolver->setColor(Color3B(140, 40, 140));

    // Se crea un boton de salir
    auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png",
                                           CC_CALLBACK_1(CTF::menuCloseCallback, this));
    closeItem->setPosition(Vec2(15*visibleSize.width/16, 1*visibleSize.height/10));
    auto menu = Menu::create(mbVolver, closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 2);
}


void CTF::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void CTF::VolverCallBack(Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Audio/Button.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
    Director::sharedDirector()->replaceScene(PanzerWars::createScene());
}
