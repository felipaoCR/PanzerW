#include "Arcade3Scene.h"
#include "PanzerWarsScene.h"
#include "SimpleAudioEngine.h"
#include <time.h>


USING_NS_CC;
using namespace cocos2d;
using namespace std;

auto audioA3 = CocosDenshion::SimpleAudioEngine::getInstance();
auto audioA3_BM = CocosDenshion::SimpleAudioEngine::getInstance();
////////////////////////////////
//Manejo de fondos y movimientos
Point Arcade3::tileCoordForPosition(Point _position)
{
    int x = _position.x / tileMap->getTileSize().width;
    int y = ((tileMap->getMapSize().height*tileMap->getTileSize().height) - _position.y)/tileMap->getTileSize().height;
    return Point(x, y);
}

void Arcade3::initPlayerStatus()
{
	//Inicio estado de player1
	p1.setHealth(100);
	p1.setDefence(5);
	p1.setAttack(120);
	p1.setSpeed(1);
	//Inicio estado de player2
	p2.setHealth(100);
	p2.setDefence(10);
	p2.setAttack(120);
	p2.setSpeed(2);
  //Inico de estado de enemy1
  e1.setHealth(200);
  e1.setDefence(5);
  e1.setAttack(e1.getDefence());
  e1.setSpeed(1);
  //Inico de estado de enemy2
  e2.setHealth(200);
  e2.setDefence(5);
  e2.setAttack(e2.getDefence());
  e2.setSpeed(1);

  e3.setHealth(200);
  e3.setDefence(5);
  e3.setAttack(e1.getDefence());
  e3.setSpeed(1);

}

void Arcade3::gameUpdate(float interval)
{

    if(!pause) {
    //Se chequea si se toman los upgrades
        loc1 = _player1->getPosition();
        loc2 = _player2->getPosition();
        loc3 = _enemy1->getPosition();
        loc4 = _enemy2->getPosition();
        loc5= _enemy3->getPosition();
        HB1->setPosition(ccp(loc1.x,loc1.y+40));
        HB2->setPosition(ccp(loc2.x,loc2.y+40));
    //Se inician/refrescan los porcentajes de salud por hit al tanque
        HPpercentage1 = p2.getAttack()/p1.getDefence();
        HPpercentage2 = p1.getAttack()/p2.getDefence();
	if(!firstSpeed)
	getUpgrade(speedUp);
	if(!firstAttack)
	getUpgrade(attackUp);
	if(!firstDefence)
	getUpgrade(defenceUp);
	if(!firstHP)
	getUpgrade(HpUp);

	//////////////////////////////////////////////
	// Bounding Box
    bbP1 = _player1->getBoundingBox();
    bbP2 = _player2->getBoundingBox();
    bbE1= _enemy1->getBoundingBox();
    bbE2= _enemy2->getBoundingBox();
    bbE3=_enemy3->getBoundingBox();

	///////////////////////////////////////////
	//Bloqueos
	if ((bbP1.intersectsRect(bbE1) && e1.getHealth())  || (bbP1.intersectsRect(bbE2) && e2.getHealth()) || (bbP1.intersectsRect(bbE3) && e3.getHealth())) {
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
	if (bbP1.intersectsRect(bbE1)) {
	    e1Collision = true;
	} else {
	    e1Collision = false;
	}
	if (bbP1.intersectsRect(bbE2)) {
	    e2Collision = true;
	} else {
	    e2Collision = false;
	}
	if (bbP1.intersectsRect(bbE3)) {
	    e3Collision = true;
	} else {
	    e3Collision = false;
	}
    ////////////////////////////////////////////////////////////
    // Movimiento Jugadores y se establece la posicion de health bars
    if(p1.getHealth()) {
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
    }
    if(p2.getHealth()) {
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
    }
//MOVIMIENTO DE ENEMIGOS
if (e1.getHealth()) {
  if((abs(loc1.x-loc3.x)<20) &&((loc1.y-loc3.y)>20 ) && !e1Collision){//0
    switch (dirAntE1) {
      case 0:
        break;
      case 1:
        this->_enemy1->runAction(RotateBy::create(0.00002, 180));
        break;
      case 2:
        this->_enemy1->runAction(RotateBy::create(0.0000001, 90));
        break;
      case 3:
        this->_enemy1->runAction(RotateBy::create(0.0000001, -90));
        break;
      case 4:
        this->_enemy1->runAction(RotateBy::create(0.0000005, -45));
        break;
      case 5:
        this->_enemy1->runAction(RotateBy::create(0.000000015, -135));
        break;
      case 6:
        this->_enemy1->runAction(RotateBy::create(0.0000000015, 135));
        break;
      case 7:
        this->_enemy1->runAction(RotateBy::create(0.00000000005, 45));
        break;
      }
    dirAntE1 = 0;
    setEnemy1Position(ccp(loc3.x,++loc3.y+e1.getSpeed())); // enemy1 going up
    log("0");
    //KOTHCounter3(_enemy1->getPosition());
    //  dispararMisilENemigo();
  }
  if((abs(loc1.x-loc3.x)<20) &&((loc3.y-loc1.y)>20 ) && !e1Collision){//1
    switch (dirAntE1) {
      case 0:
        this->_enemy1->runAction(RotateBy::create(0.02, 180));
        break;
      case 1:
        break;
      case 2:
        this->_enemy1->runAction(RotateBy::create(0.01, -90));
        break;
      case 3:
        this->_enemy1->runAction(RotateBy::create(0.01, 90));
        break;
      case 4:
        this->_enemy1->runAction(RotateBy::create(0.015, 135));
        break;
      case 5:
        this->_enemy1->runAction(RotateBy::create(0.005, 45));
        break;
      case 6:
        this->_enemy1->runAction(RotateBy::create(0.005, -45));
        break;
      case 7:
        this->_enemy1->runAction(RotateBy::create(0.015, -135));
        break;
      }
    log("1");
    dirAntE1 = 1;
  //  dispararMisilENemigo();
    setEnemy1Position(ccp(loc3.x,--loc3.y)); // enemy1 going down
    //KOTHCounter3(_enemy1->getPosition());
  }
  //
  if(((loc3.x-loc1.x)>20) &&(abs(loc1.y-loc3.y)<20) && !e1Collision){//2
    switch (dirAntE1) {
      case 0:
        this->_enemy1->runAction(RotateBy::create(0.01, -90));
        break;
      case 1:
        this->_enemy1->runAction(RotateBy::create(0.01, 90));
        break;
      case 2:
        break;
      case 3:
        this->_enemy1->runAction(RotateBy::create(0.02, 180));
        break;
      case 4:
        this->_enemy1->runAction(RotateBy::create(0.015, -135));
        break;
      case 5:
        this->_enemy1->runAction(RotateBy::create(0.015, 135));
        break;
      case 6:
        this->_enemy1->runAction(RotateBy::create(0.005, 45));
        break;
      case 7:
        this->_enemy1->runAction(RotateBy::create(0.005, -45));
        break;
      }
    log("2");
    dirAntE1 = 2;
    //dispararMisilENemigo();
    setEnemy1Position(ccp(--loc3.x,loc3.y)); // enemy1 going left
    //KOTHCounter3(_enemy1->getPosition());
    //  dispararMisilENemigo();
  }
  //
  if(((loc1.x-loc3.x)>20) &&(abs(loc1.y-loc3.y)<20) && !e1Collision){//3
    switch (dirAntE1) {
      case 0:
        this->_enemy1->runAction(RotateBy::create(0.01, 90));
        break;
      case 1:
        this->_enemy1->runAction(RotateBy::create(0.01, -90));
        break;
      case 2:
        this->_enemy1->runAction(RotateBy::create(0.02, 180));
        break;
      case 3:
        break;
      case 4:
        this->_enemy1->runAction(RotateBy::create(0.005, 45));
        break;
      case 5:
        this->_enemy1->runAction(RotateBy::create(0.005, -45));
        break;
      case 6:
        this->_enemy1->runAction(RotateBy::create(0.015, -135));
        break;
      case 7:
        this->_enemy1->runAction(RotateBy::create(0.015, 135));
        break;
      }
    dirAntE1 = 3;
    log("3");
    //dispararMisilENemigo();
    setEnemy1Position(ccp(++loc3.x,loc3.y)); // enemy1 going right
    //KOTHCounter3(_enemy1->getPosition());
  }
  //
  if(((loc1.x-loc3.x)>20) && ((loc1.y-loc3.y)>20) && !e1Collision){ //4
    switch (dirAntE1) {
      case 0:
        this->_enemy1->runAction(RotateBy::create(0.005, 45));
        break;
      case 1:
        this->_enemy1->runAction(RotateBy::create(0.015, -135));
        break;
      case 2:
        this->_enemy1->runAction(RotateBy::create(0.015, 135));
        break;
      case 3:
        this->_enemy1->runAction(RotateBy::create(0.005, -45));
        break;
      case 4:
        break;
      case 5:
        this->_enemy1->runAction(RotateBy::create(0.01, -90));
        break;
      case 6:
        this->_enemy1->runAction(RotateBy::create(0.02, 180));
        break;
      case 7:
        this->_enemy1->runAction(RotateBy::create(0.01, 90));
        break;
      }
    log("4");
    dirAntE1 = 4;
    //dispararMisilENemigo();
    setEnemy1Position(ccp((++loc3.x),(++loc3.y)));// enemy 1 going up and right
  }
  //
  if(((loc1.x-loc3.x)>20) && ((loc3.y-loc1.y)>20) && !e1Collision){ //5
    switch (dirAntE1) {
      case 0:
        this->_enemy1->runAction(RotateBy::create(0.015, 135));
        break;
      case 1:
        this->_enemy1->runAction(RotateBy::create(0.005, -45));
        break;
      case 2:
        this->_enemy1->runAction(RotateBy::create(0.015, -135));
        break;
      case 3:
        this->_enemy1->runAction(RotateBy::create(0.005, 45));
        break;
      case 4:
        this->_enemy1->runAction(RotateBy::create(0.01, 90));
        break;
      case 5:
        break;
      case 6:
        this->_enemy1->runAction(RotateBy::create(0.01, -90));
        break;
      case 7:
        this->_enemy1->runAction(RotateBy::create(0.02, 180));
        break;
      }
    log("5");
    dirAntE1 = 5;
    setEnemy1Position(ccp((++loc3.x),(--loc3.y))); //enemy1 going down and right
    //dispararMisilENemigo();

  }
  //
  if(((loc3.x-loc1.x)>20) && ((loc3.y-loc1.y)>20) && !e1Collision){//6
    switch (dirAntE1) {
      case 0:
        this->_enemy1->runAction(RotateBy::create(0.015, -135));
        break;
      case 1:
        this->_enemy1->runAction(RotateBy::create(0.005, 45));
        break;
      case 2:
        this->_enemy1->runAction(RotateBy::create(0.005, -45));
        break;
      case 3:
        this->_enemy1->runAction(RotateBy::create(0.015, 135));
        break;
      case 4:
        this->_enemy1->runAction(RotateBy::create(0.02, 180));
        break;
      case 5:
        this->_enemy1->runAction(RotateBy::create(0.01, 90));
        break;
      case 6:
        break;
      case 7:
        this->_enemy1->runAction(RotateBy::create(0.01, -90));
        break;
      }
    log("6");
    dirAntE1 = 6;
    //  dispararMisilENemigo();
    setEnemy1Position(ccp((--loc3.x),(--loc3.y))); //enemy1 going down and left
    //dispararMisilENemigo();
  }
  if(((loc3.x-loc1.x)>20) && ((loc1.y-loc3.y)>20) && !e1Collision){//7
    switch (dirAntE1) {
      case 0:
        this->_enemy1->runAction(RotateBy::create(0.005, -45));
        break;
      case 1:
        this->_enemy1->runAction(RotateBy::create(0.015, 135));
        break;
      case 2:
        this->_enemy1->runAction(RotateBy::create(0.005, 45));
        break;
      case 3:
        this->_enemy1->runAction(RotateBy::create(0.015, -135));
        break;
      case 4:
        this->_enemy1->runAction(RotateBy::create(0.01, -90));
        break;
      case 5:
        this->_enemy1->runAction(RotateBy::create(0.02, 180));
        break;
      case 6:
        this->_enemy1->runAction(RotateBy::create(0.01, 90));
        break;
      case 7:
        break;
      }
    log("7");
    dirAntE1 = 7;
    setEnemy1Position(ccp((--loc3.x),(++loc3.y)));//enemy1 going left and up
    //dispararMisilENemigo();
  }
  srand (time(NULL));
  int ramdom;
  ramdom= rand() % 10;

  if (ramdom<3){
  //  dispararMisilENemigo1();
  }

  log("ramdom=%d",ramdom);

  log("Loc3.x =%f",loc3.x);
  log("Loc1.x =%f",loc1.x);
  log("Loc3.y =%f",loc3.y);
  log("Loc1.y =%f",loc1.y);
}

//---------------------------------------------------------
//MOVIMIENTO ENEMIGO  2
//this->_enemy2->runAction(RotateBy::create(0.01, 180));
if(e2.getHealth()) {
if(!e2Collision) {
switch (tramo) {
  case 1:
    //this->_enemy2->runAction(RotateBy::create(0.01, 180));
    if( loc4.x<445){
      setEnemy2Position(ccp(++loc4.x+e2.getSpeed(),loc4.y));
      dirAntE2=3;
    }else{
      this->_enemy2->runAction(RotateBy::create(0.01, 90));
      tramo=2;
      }
    break;
  case 2:
    if(loc4.y>463){
      setEnemy2Position(ccp(loc4.x,--loc4.y-e2.getSpeed()));
      dirAntE2=1;
    }else{
      this->_enemy2->runAction(RotateBy::create(0.01, -90));
      tramo=3;
    }
    break;
  case 3:
    if(loc4.x<697){
      setEnemy2Position(ccp(++loc4.x+e2.getSpeed(),loc4.y));
      dirAntE2=3;
    }else{
      this->_enemy2->runAction(RotateBy::create(0.01, 90));
      tramo=4;
    }
    break;
  case 4:
    if(loc4.y>260){
      setEnemy2Position(ccp(loc4.x,--loc4.y-e2.getSpeed()));
      dirAntE2=1;
    }else{
      this->_enemy2->runAction(RotateBy::create(0.01, 90));
      tramo=5;
    }
    break;
  case 5:
    if(loc4.x>370){
      setEnemy2Position(ccp(--loc4.x-e2.getSpeed(),loc4.y));
      dirAntE2=2;
    }else{
      this->_enemy2->runAction(RotateBy::create(0.01, 90));
      tramo=6;
    }
    break;
  case 6:
    if(loc4.y<380){
      dirAntE2=0;
      setEnemy2Position(ccp(loc4.x,++loc4.y+e2.getSpeed()));
    }else{

      this->_enemy2->runAction(RotateBy::create(0.01, 45));
      tramo=7;
    }
    break;
  case 7:
    if(loc4.y<494 && loc4.x<504){
      dirAntE2=4;
      setEnemy2Position(ccp(++loc4.x+e2.getSpeed(),++loc4.y+e2.getSpeed()));
    }else{
      this->_enemy2->runAction(RotateBy::create(0.01, 45));
      tramo=16;
    }
    break;
  case 8:
    if( loc4.x<904){
      dirAntE2=3;
      setEnemy2Position(ccp(++loc4.x+e2.getSpeed(),loc4.y));
    }else{
      this->_enemy2->runAction(RotateBy::create(0.01, 90));
      tramo=9;
    }
    break;
  case 9:
    if(loc4.y>437){
      dirAntE2=1;
      setEnemy2Position(ccp(loc4.x,--loc4.y-e2.getSpeed()));
    }else{
      this->_enemy2->runAction(RotateBy::create(0.01, 90));
      tramo=10;
    }
    break;
 case 10:
    if(loc4.x>697){
      setEnemy2Position(ccp(--loc4.x-e2.getSpeed(),loc4.y));
      dirAntE2=2;
    }else{
      this->_enemy2->runAction(RotateBy::create(0.01, -90));
      tramo=11;
    }
    break;
  case 11:
    if(loc4.y>70){
      setEnemy2Position(ccp(loc4.x,--loc4.y-e2.getSpeed()));
      dirAntE2=1;
    }else{
      this->_enemy2->runAction(RotateBy::create(0.01, 90));
      tramo=12;
    }
    break;
    case 12:
      if(loc4.x>380){
        setEnemy2Position(ccp(--loc4.x-e2.getSpeed(),loc4.y));
        dirAntE2=2;
      }else{
        this->_enemy2->runAction(RotateBy::create(0.01, 90));
        tramo=13;
      }
      break;
    case 13:
      if(loc4.y<430){
        setEnemy2Position(ccp(loc4.x,++loc4.y+e2.getSpeed()));
        dirAntE2=0;
      }else{
        this->_enemy2->runAction(RotateBy::create(0.01, -90));
        tramo=14;
      }
      break;
    case 14:
      if(loc4.x>130){
        setEnemy2Position(ccp(--loc4.x-e2.getSpeed(),loc4.y));
        dirAntE2=2;
      }else{
        this->_enemy2->runAction(RotateBy::create(0.01, 90));
        tramo=15;
      }
      break;
    case 15:
      if( loc4.y<595){
        setEnemy2Position(ccp(loc4.x,++loc4.y+e2.getSpeed()));
        dirAntE2=0;
      }else{
        this->_enemy2->runAction(RotateBy::create(0.01, 90));

        tramo=1;
      }
      break;
    case 16:

      if( loc4.x<575){
        setEnemy2Position(ccp(++loc4.x+e2.getSpeed(),loc4.y));
        dirAntE2=3;
      }else{
        this->_enemy2->runAction(RotateBy::create(0.01, -90));

        tramo=17;
      }

      break;
    case 17:
      if(loc4.y<608){
        setEnemy2Position(ccp(loc4.x,++loc4.y+e2.getSpeed()));
        dirAntE2=0;
      }else{
        this->_enemy2->runAction(RotateBy::create(0.01, 90));
        tramo=8;
      }
      break;
}
}

log("loc4.x=%f",loc4.x);
log("loc4.y=%f",loc4.y);
log("tramo=%d",tramo);
}

//ENEMIGO3
if(e3.getHealth()) {
srand (time(NULL));
int r1= rand()%10;
if (!e3Collision) {
if(loc1.y<280&& loc1.x>315&&loc1.x<420){

if (r1<5){
  switch(dirAntE3) {
case 0:
    this->_enemy3->runAction(RotateBy::create(0.02, 180));
    break;
case 1:
  break;
case 2:
    this->_enemy3->runAction(RotateBy::create(0.01, -90));
    break;
case 3:
    this->_enemy3->runAction(RotateBy::create(0.01, 90));
    break;
  }
  dirAntE3 = 1;
  setEnemy3Position(ccp(loc1.x,609));
}else{
  switch(dirAntE3) {
case 0:
    this->_enemy3->runAction(RotateBy::create(0.02, -90));
    break;
case 1:
  this->_enemy3->runAction(RotateBy::create(0.01, 90));
  break;
case 2:
    break;
case 3:
    this->_enemy3->runAction(RotateBy::create(0.01, 180));
    break;
  }
  dirAntE3 = 2;
  setEnemy3Position(ccp(732,loc1.y));
}
}

//---------------------------------------------------------------------------------------------------------
if(loc1.y<280&& loc1.x>630&&loc1.x<745){

if (r1<5){
  switch(dirAntE3) {
case 0:
    this->_enemy3->runAction(RotateBy::create(0.02, 180));
    break;
case 1:
  break;
case 2:
    this->_enemy3->runAction(RotateBy::create(0.01, -90));
    break;
case 3:
    this->_enemy3->runAction(RotateBy::create(0.01, 90));
    break;
  }
  dirAntE3 = 1;
  setEnemy3Position(ccp(loc1.x,609));
}else{
  switch(dirAntE3) {
case 0:
    this->_enemy3->runAction(RotateBy::create(0.02, 90));
    break;
case 1:
  this->_enemy3->runAction(RotateBy::create(0.01, -90));
  break;
case 2:
    this->_enemy3->runAction(RotateBy::create(0.01, 180));
    break;
case 3:
    break;
  }
  dirAntE3 = 3;
  setEnemy3Position(ccp(303,loc1.y));
}
}
//----------------------------------------------------
if(loc1.y<550&&loc1.y>450&& loc1.x>435&&loc1.x<580){

if (r1<5){
  switch(dirAntE3) {
case 0:
    this->_enemy3->runAction(RotateBy::create(0.02, 90));
    break;
case 1:
  this->_enemy3->runAction(RotateBy::create(0.01, -90));
  break;
case 2:
    this->_enemy3->runAction(RotateBy::create(0.01,180));
    break;
case 3:
   break;
  }
  dirAntE3 = 3;
  setEnemy3Position(ccp(135,loc1.y));
}else{
  switch(dirAntE3) {
case 0:
    this->_enemy3->runAction(RotateBy::create(0.02, -90));
    break;
case 1:
  this->_enemy3->runAction(RotateBy::create(0.01, 90));
  break;
case 2:
    break;
case 3:
    this->_enemy3->runAction(RotateBy::create(0.01, 180));
    break;
  }
  dirAntE3 = 2;
  setEnemy3Position(ccp(891,loc1.y));
}
}
if(loc1.y>575&&loc1.x>630&&loc1.x<770){
switch(dirAntE3) {
  case 0:
      break;
  case 1:
    this->_enemy3->runAction(RotateBy::create(0.01, 180));
    break;
  case 2:
      this->_enemy3->runAction(RotateBy::create(0.01, 90));
      break;
  case 3:
      this->_enemy3->runAction(RotateBy::create(0.01, -90));
      break;
    }
dirAntE3 = 0;
setEnemy3Position(ccp(loc1.x,90));

}

if(loc1.y>575&&loc1.x>297&&loc1.x<423){
switch(dirAntE3) {
  case 0:
      break;
  case 1:
    this->_enemy3->runAction(RotateBy::create(0.01, 180));
    break;
  case 2:
      this->_enemy3->runAction(RotateBy::create(0.01, 90));
      break;
  case 3:
      this->_enemy3->runAction(RotateBy::create(0.01, -90));
      break;
    }
dirAntE3 = 0;
setEnemy3Position(ccp(loc1.x,90));

}
}

if((r1!=0&&6)&&loc5.x!=500&&loc5.y!=500){

  dispararMisilENemigo3();
}
//------------------------------------------------------------------------------
log("r1=%d",r1);
}

if(e2.getHealth()){
r2=rand() % 10;
if (r2<3&& r2!=r2ant){
  activarMinaE2(ccp(loc4.x,loc4.y));
  r2ant=r2;
}
if(r2!=1&&3&&5&&7){

  dispararMisilENemigo2();
}
}


/////////////////////////////////////////////
    // Para colisiones entre sprites
    for(i=0; i<3; i++) {
    if(bbP1.intersectsRect(bbM2[i]) && (actM2[i]==true)) {
      CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Audio/Bomb.mp3");
      //-10 a health de p1
      if(p1.getHealth()>0)
      p1.setHealth(p1.getHealth()-50);
      if(p1.getHealth()<0)
      p1.setHealth(0);
      hitP2 = true;
      explosion(minaP2[i]);
      delta = std::chrono::duration<double, std::milli>(high_resolution_clock::now()-start).count();
      end += delta;
      if (end > 5) {
    tileMap->removeChild(minaP2[i]);
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
      hitP1 = true;
      explosion(minaP1[i]);
      delta = std::chrono::duration<double, std::milli>(high_resolution_clock::now()-start).count();
      end += delta;
      if (end > 5) {
    tileMap->removeChild(minaP1[i]);
    end = 0;
      }
      actM1[i] = false;
    }

    if(bbP1.intersectsRect(bbM4[i]) && (actM4[i]==true)) {
      CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Audio/Bomb.mp3");
      //-10 a health de p1
      if(p1.getHealth()>0)
      p1.setHealth(p1.getHealth()-50);
      if(p1.getHealth()<0)
      p1.setHealth(0);
      hitP2 = true;
      explosion(minaE2[i]);
      delta = std::chrono::duration<double, std::milli>(high_resolution_clock::now()-start).count();
      end += delta;
      if (end > 5) {
    tileMap->removeChild(minaE2[i]);
    end = 0;
      }
      actM4[i] = false;
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
    case 1:
         setMisil1Position(ccp(locm1.x,--locm1.y-3));
         break;
    case 2:
        setMisil1Position(ccp(--locm1.x-3,locm1.y));
        break;
    case 3:
        setMisil1Position(ccp(++locm1.x+3,locm1.y));
    }
    if(bbm1.intersectsRect(bbE1))
    {
    explosion(misil1);
    delta = std::chrono::duration<double, std::milli>(high_resolution_clock::now()-start).count();
    end += delta;
    if (end > 5) {
        tileMap->removeChild(misil1);
        end = 0;
    }
    actm1 = false;
    e1.setHealth(e1.getHealth()-50);
    hitP1 = true;
    if(e1.getHealth()<0)
    e1.setHealth(0);
    }
    if(bbm1.intersectsRect(bbE2))
    {
    explosion(misil1);
    delta = std::chrono::duration<double, std::milli>(high_resolution_clock::now()-start).count();
    end += delta;
    if (end > 5) {
        tileMap->removeChild(misil1);
        end = 0;
    }
    actm1 = false;
    e2.setHealth(e1.getHealth()-50);
    hitP1 = true;
    if(e2.getHealth()<0)
    e2.setHealth(0);
    }
    //---------------
    if(bbm1.intersectsRect(bbE3))
    {
    explosion(misil1);
    delta = std::chrono::duration<double, std::milli>(high_resolution_clock::now()-start).count();
    end += delta;
    if (end > 5) {
        tileMap->removeChild(misil1);
        end = 0;
    }
    actm1 = false;
    e3.setHealth(e1.getHealth()-50);
    hitP1 = true;
    if(e3.getHealth()<0)
    e3.setHealth(0);
    }
    for(i=0; i<3; i++) {
      if((actM2[i]) && bbm1.intersectsRect(bbM2[i])) {
    explosion(misil1);
    explosion(minaP2[i]);
    delta = std::chrono::duration<double, std::milli>(high_resolution_clock::now()-start).count();
    end += delta;
    if (end > 5) {
        tileMap->removeChild(misil1);
        tileMap->removeChild(minaP2[i]);
        end = 0;
    }
    actm1 = false;
    actM2[i] = false;
      }
    }
    for(i=0; i<3; i++) {
      if((actM4[i]) && bbm1.intersectsRect(bbM4[i])) {
    explosion(misil1);
    explosion(minaE2[i]);
    delta = std::chrono::duration<double, std::milli>(high_resolution_clock::now()-start).count();
    end += delta;
    if (end > 5) {
        tileMap->removeChild(misil1);
        tileMap->removeChild(minaE2[i]);
        end = 0;
    }
    actm1 = false;
    actM4[i] = false;
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
        tileMap->removeChild(misil2);
        end = 0;
    }
    actm2 = false;
    p1.setHealth(p1.getHealth()-HPpercentage1);
    hitP2 = true;
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
        tileMap->removeChild(misil2);
        tileMap->removeChild(minaP1[i]);
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
        tileMap->removeChild(misil2);
        tileMap->removeChild(misil1);
        end = 0;
    }
    actm2 = false;
    actm1 = false;
      }
    }
}
    if(actm1 && actmE1) {
      if(bbm1.intersectsRect(bbmE1)) {
    explosion(misil3);
    explosion2(misil1);
    delta = std::chrono::duration<double, std::milli>(high_resolution_clock::now()-start).count();
    end += delta;
    if (end > 5) {
        tileMap->removeChild(misil3);
        tileMap->removeChild(misil1);
        end = 0;
    }
    actmE1 = false;
    actm1 = false;
      }
    }
    if(actm1 && actmE2) {
      if(bbm1.intersectsRect(bbmE2)) {
    	explosion(misil4);
    	explosion2(misil1);
    delta = std::chrono::duration<double, std::milli>(high_resolution_clock::now()-start).count();
    end += delta;
    if (end > 5) {
        tileMap->removeChild(misil4);
        tileMap->removeChild(misil1);
        end = 0;
    }
    actmE2 = false;
    actm1 = false;
      }
    }
    if(actm1 && actmE3) {
      if(bbm1.intersectsRect(bbmE3)) {
    explosion(misil5);
    explosion2(misil1);
    delta = std::chrono::duration<double, std::milli>(high_resolution_clock::now()-start).count();
    end += delta;
    if (end > 5) {
        tileMap->removeChild(misil5);
        tileMap->removeChild(misil1);
        end = 0;
    }
    actmE3 = false;
    actm1 = false;
      }
    }


    ///-----------------------------------------------------
    if(actmE1)  {
    locmE1 = misil3->getPosition();
    bbmE1 = misil3->getBoundingBox();
    switch (dirmE1)
    {
      case 0:
          setMisil3Position(ccp(locmE1.x,++locmE1.y+3));
          break;
      case 1:
          setMisil3Position(ccp(locmE1.x,--locmE1.y-3));
          break;
      case 2:
          setMisil3Position(ccp(--locmE1.x-3,locmE1.y));
          break;
      case 3:
          setMisil3Position(ccp(++locmE1.x+3,locmE1.y));
          break;
      case 4:
          setMisil3Position(ccp(++locmE1.x+3,++locmE1.y+3));
          break;
      case 5:
          setMisil3Position(ccp(++locmE1.x+3,--locmE1.y-3));
          break;
      case 6:
          setMisil3Position(ccp(--locmE1.x-3,--locmE1.y-3));
          break;
      case 7:
          setMisil3Position(ccp(--locmE1.x-3,++locmE1.y+3));
      }
    if(bbmE1.intersectsRect(bbP1))
    {
    tileMap->removeChild(misil3);
    actmE1 = false;
    hitP2 = true;
    p1.setHealth(p1.getHealth()-20);
    if(p1.getHealth()<0)
    p1.setHealth(0);
    }
    }




    if(actmE2)  {
      locmE2 = misil4->getPosition();
      bbmE2 = misil4->getBoundingBox();
      switch (dirmE2)
      {
        case 0:
            setMisil4Position(ccp(locmE2.x,++locmE2.y+3));
            break;
        case 1:
            setMisil4Position(ccp(locmE2.x,--locmE2.y-3));
            break;
        case 2:
            setMisil4Position(ccp(--locmE2.x-3,locmE2.y));
            break;
        case 3:
            setMisil4Position(ccp(++locmE2.x+3,locmE2.y));
            break;
        case 4:
            setMisil4Position(ccp(++locmE2.x+3,++locmE2.y+3));
            break;
        case 5:
            setMisil4Position(ccp(++locmE2.x+3,--locmE2.y-3));
            break;
        case 6:
            setMisil4Position(ccp(--locmE2.x-3,--locmE2.y-3));
            break;
        case 7:
            setMisil4Position(ccp(--locmE2.x-3,++locmE2.y+3));
        }
    if(bbmE2.intersectsRect(bbP1))
    {
      tileMap->removeChild(misil4);
      actmE2 = false;
      hitP2 = true;
      p1.setHealth(p1.getHealth()-20);
      if(p1.getHealth()<0)
      p1.setHealth(0);
    }
      }
    if(actmE3)  {
      locmE3 = misil5->getPosition();
      bbmE3 = misil5->getBoundingBox();
      switch (dirmE3)
      {
        case 0:
            setMisil5Position(ccp(locmE3.x,++locmE3.y+3));
            break;
        case 1:
            setMisil5Position(ccp(locmE3.x,--locmE3.y-3));
            break;
        case 2:
            setMisil5Position(ccp(--locmE3.x-3,locmE3.y));
            break;
        case 3:
            setMisil5Position(ccp(++locmE3.x+3,locmE3.y));
            break;
        case 4:
            setMisil5Position(ccp(++locmE3.x+3,++locmE3.y+3));
            break;
        case 5:
            setMisil5Position(ccp(++locmE3.x+3,--locmE3.y-3));
            break;
          case 6:
              setMisil5Position(ccp(--locmE3.x-3,--locmE3.y-3));
              break;
          case 7:
              setMisil5Position(ccp(--locmE3.x-3,++locmE3.y+3));
          }
      if(bbmE3.intersectsRect(bbP1))
      {
        tileMap->removeChild(misil5);
        actmE3 = false;
        hitP2 = true;
        p1.setHealth(p1.getHealth()-20);
        if(p1.getHealth()<0)
        p1.setHealth(0);
      }
        }

//------------------------------------------------------------
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
    if(false)
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

    ////////////////////////////////////////////////
    // Enemy is dead
    if(!e1.getHealth())
	explosion2(_enemy1);

    if(!e2.getHealth())
	explosion2(_enemy2);

    if(!e3.getHealth())
	explosion2(_enemy3);

    ///////////////////////////////////////
    //Game Over
    if(!p1.getHealth()) {
	explosion2(_player1);
	auto gameOver = Label::createWithTTF("Game Over", "fonts/Marker Felt.ttf", 26);
    	gameOver->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    	this->addChild(gameOver, 1);
	deltaGO = std::chrono::duration<double, std::milli>(high_resolution_clock::now()-startGO).count();
	endGO += deltaGO;
	if (endGO > 5) {
	    pause = true;
            removeChild(HB1);
	    audioA3->stopAllEffects();
	    audioA3_BM->stopBackgroundMusic();
	    Director::sharedDirector()->pause();
	}
    }
    if(!e1.getHealth() && !e2.getHealth() && !e3.getHealth()) {
	explosion2(_player2);
	auto gameOver = Label::createWithTTF("You are the funcking BOSS", "fonts/Marker Felt.ttf", 26);
    	gameOver->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    	this->addChild(gameOver, 1);
	deltaGO = std::chrono::duration<double, std::milli>(high_resolution_clock::now()-startGO).count();
	endGO += deltaGO;
	if (endGO > 5) {
	    pause = true;
	    audioA3->stopAllEffects();
	    audioA3_BM->stopBackgroundMusic();
	    Director::sharedDirector()->pause();
	}
    }
}
}

void Arcade3::explosion(Sprite *player)
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

void Arcade3::explosion2(Sprite *player)
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

void Arcade3::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
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
			tileMap->addChild(minaP1[i], _player1->getZOrder());
			bbM1[i] = minaP1[i]->getBoundingBox();
			actM1[i] = true;
			break;
		    }
		}
	    }
	    break;
	case EventKeyboard::KeyCode::KEY_E:
	    if(actm1==false && !pause && p1.getHealth()) {
   	 	audioA3->playEffect("Audio/explosion3.mp3");
    		audioA3->setEffectsVolume(0.3);
		misil1 = Sprite::create("c1.png");
		misil1->setPosition(_player1->getPosition());
		misil1->setScale(0.4);
		tileMap->addChild(misil1, _player1->getZOrder());
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
	    if(cantM2>0 && !pause && p2.getHealth()){
		for(i=0; i<3; i++) {
		    if(actM2[i]==false) {
			cantM2--;
			minaP2[i] = Sprite::create("mina.png");
			minaP2[i]->setPosition(_player2->getPosition());
			minaP2[i]->setScale(0.4);
			tileMap->addChild(minaP2[i],_player2->getZOrder());
			bbM2[i] = minaP2[i]->getBoundingBox();
			actM2[i] = true;
			break;
		    }
		}
	    }
	    break;
	case EventKeyboard::KeyCode::KEY_O:
	    if(actm2==false && !pause && p2.getHealth()) {
   	 	audioA3->playEffect("Audio/explosion3.mp3");
    		audioA3->setEffectsVolume(0.3);
		misil2 = Sprite::create("c1.png");
		misil2->setPosition(_player2->getPosition());
		misil2->setScale(0.4);
		tileMap->addChild(misil2,_player2->getZOrder());
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

void Arcade3::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
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

void Arcade3::setPlayer1Position(Point position)
{
    Point tileCoord = this->tileCoordForPosition(position);
    int tileGid = _blockage->getTileGIDAt(tileCoord);
    if (tileGid) {
        auto properties = tileMap->getPropertiesForGID(tileGid).asValueMap();
        if (!properties.empty()) {
            auto collision = properties["Collision"].asString();
	    auto magma = properties["Magma"].asString();
            if(magma=="True")
	    {
		p1.setHealth(0);
            }
            if ("True" == collision && magma!="True") {
		log("COLISION");
                return;
            }
        }else return;
    }
    _player1->setPosition(position);
}

void Arcade3::setPlayer2Position(Point position)
{
    Point tileCoord = this->tileCoordForPosition(position);
    int tileGid = _blockage->getTileGIDAt(tileCoord);
    log("tileGid = %d", tileGid);
    if (tileGid) {
	//log("DEBUG");
        auto properties = tileMap->getPropertiesForGID(tileGid).asValueMap();
        if (!properties.empty()) {
            auto collision = properties["Collision"].asString();
            auto magma = properties["Magma"].asString();
            if(magma=="True")
	    {
		p2.setHealth(0);
            }
            if ("True" == collision && magma!="True") {
		log("COLISION");
                return;
            }
        }else return;
    }
    _player2->setPosition(position);
}
void Arcade3::setEnemy1Position(Point position)
{
    Point tileCoord = this->tileCoordForPosition(position);
    int tileGid = _blockage->getTileGIDAt(tileCoord);
    if (tileGid) {
        auto properties = tileMap->getPropertiesForGID(tileGid).asValueMap();
        if (!properties.empty()) {
            auto collision = properties["Collision"].asString();
            auto magma = properties["Magma"].asString();
            if ("True" == collision || magma == "True") {
		log("COLISION");
                return;
            }
        }else return;
    }
    _enemy1->setPosition(position);
}
void Arcade3::setEnemy2Position(Point position)
{
    Point tileCoord = this->tileCoordForPosition(position);
    int tileGid = _blockage->getTileGIDAt(tileCoord);
    if (tileGid) {
        auto properties = tileMap->getPropertiesForGID(tileGid).asValueMap();
        if (!properties.empty()) {
            auto collision = properties["Collision"].asString();
            auto magma = properties["Magma"].asString();
            if ("True" == collision || magma == "True") {
		log("COLISION");
                return;
            }
        }else return;
    }
    _enemy2->setPosition(position);
}

void Arcade3::setEnemy3Position(Point position)
{
    Point tileCoord = this->tileCoordForPosition(position);
    int tileGid = _blockage->getTileGIDAt(tileCoord);
    if (tileGid) {
        auto properties = tileMap->getPropertiesForGID(tileGid).asValueMap();
        if (!properties.empty()) {
            auto collision = properties["Collision"].asString();
	    auto magma = properties["Magma"].asString();
            if ("True" == collision || magma == "True") {
		log("COLISION");
                return;
            }
        }else return;
    }
    _enemy3->setPosition(position);
}

void Arcade3::setMisil1Position(Point position)
{
    Point tileCoord = this->tileCoordForPosition(position);
    int tileGid = _blockage->getTileGIDAt(tileCoord);
    if (tileGid) {
        auto properties = tileMap->getPropertiesForGID(tileGid).asValueMap();
        if (!properties.empty()) {
            auto collision = properties["Collision"].asString();
              auto magma = properties["Magma"].asString();
            if ("True" == collision && magma != "True") {
	    	tileMap->removeChild(misil1, misil1->getZOrder());
	    	actm1 = false;
	    	log("COLISION");
            	return;
            }
        }else return;
    }
    misil1->setPosition(position);
}

void Arcade3::setMisil2Position(Point position)
{
    Point tileCoord = this->tileCoordForPosition(position);
    int tileGid = _blockage->getTileGIDAt(tileCoord);
    if (tileGid) {
        auto properties = tileMap->getPropertiesForGID(tileGid).asValueMap();
        if (!properties.empty()) {
            auto collision = properties["Collision"].asString();
            auto magma = properties["Magma"].asString();
            if ("True" == collision && magma != "True") {
		tileMap->removeChild(misil2, misil2->getZOrder());
		actm2 = false;
		log("COLISION");
                return;
            }
        }else return;
    }
    misil2->setPosition(position);
}
//------------------------------------------
///MISIL enemigo
void Arcade3::dispararMisilENemigo1(){
  if(actmE1==false && !pause) {
    audioA3->playEffect("Audio/explosion3.mp3");
    audioA3->setEffectsVolume(0.3);
    misil3 = Sprite::create("c1.png");
misil3->setPosition(_enemy1->getPosition());
misil3->setScale(0.4);
tileMap->addChild(misil3, _enemy1->getZOrder());
actmE1 = true;
dirmE1 = dirAntE1;
switch (dirmE1) {
  case 0:
    misil3->runAction(RotateBy::create(0.001, -90));
    break;
  case 1:
    misil3->runAction(RotateBy::create(0.001, 90));
    break;
  case 2:
    misil3->runAction(RotateBy::create(0.001, 180));
    break;
  case 3:
    misil3->runAction(RotateBy::create(0.001, -0));
    break;
  case 4:
    misil3->runAction(RotateBy::create(0.001, -45));
    break;
  case 5:
    misil3->runAction(RotateBy::create(0.001, 45));
    break;
  case 6:
    misil3->runAction(RotateBy::create(0.001, 135));
    break;
  case 7:
    misil3->runAction(RotateBy::create(0.001, -135));
    break;
default:
        break;
      }
  }
}

void Arcade3::setMisil3Position(Point position)
{
    Point tileCoord = this->tileCoordForPosition(position);
    int tileGid = _blockage->getTileGIDAt(tileCoord);
    if (tileGid) {
        auto properties = tileMap->getPropertiesForGID(tileGid).asValueMap();
        if (!properties.empty()) {
            auto collision = properties["Collision"].asString();
            auto magma = properties["Magma"].asString();
            if ("True" == collision && magma != "True") {
		tileMap->removeChild(misil3, _enemy1->getZOrder());
		actmE1 = false;
		log("COLISION");
                return;
            }
        }else return;
    }
    misil3->setPosition(position);
}
void Arcade3::dispararMisilENemigo2(){
  if(actmE2==false && !pause) {
    audioA3->playEffect("Audio/explosion3.mp3");
    audioA3->setEffectsVolume(0.3);
    misil4 = Sprite::create("c1.png");
misil4->setPosition(_enemy2->getPosition());
misil4->setScale(0.4);
tileMap->addChild(misil4, _enemy2->getZOrder());
actmE2 = true;
dirmE2 = dirAntE2;
switch (dirmE2) {
  case 0:
    misil4->runAction(RotateBy::create(0.001, -90));
    break;
  case 1:
    misil4->runAction(RotateBy::create(0.001, 90));
    break;
  case 2:
    misil4->runAction(RotateBy::create(0.001, 180));
    break;
  case 3:
    misil4->runAction(RotateBy::create(0.001, -0));
    break;
  case 4:
    misil4->runAction(RotateBy::create(0.001, -45));
    break;
  case 5:
    misil4->runAction(RotateBy::create(0.001, 45));
    break;
  case 6:
    misil4->runAction(RotateBy::create(0.001, 135));
    break;
  case 7:
    misil4->runAction(RotateBy::create(0.001, -135));
    break;
default:
        break;
      }
  }
}

void Arcade3::setMisil4Position(Point position)
{
    Point tileCoord = this->tileCoordForPosition(position);
    int tileGid = _blockage->getTileGIDAt(tileCoord);
    if (tileGid) {
        auto properties = tileMap->getPropertiesForGID(tileGid).asValueMap();
        if (!properties.empty()) {
            auto collision = properties["Collision"].asString();
            auto magma = properties["Magma"].asString();
            if ("True" == collision && magma != "True") {
		tileMap->removeChild(misil4, _enemy2->getZOrder());
		actmE2 = false;
		log("COLISION");
                return;
            }
        }else return;
    }
    misil4->setPosition(position);
}
//---------------
void Arcade3::dispararMisilENemigo3(){
  if(actmE3==false && !pause) {
    audioA3->playEffect("Audio/explosion3.mp3");
    audioA3->setEffectsVolume(0.3);
    misil5 = Sprite::create("c1.png");
misil5->setPosition(_enemy3->getPosition());
misil5->setScale(0.4);
tileMap->addChild(misil5, _enemy3->getZOrder());
actmE3 = true;
dirmE3 = dirAntE3;
switch (dirmE3) {
  case 0:
    misil5->runAction(RotateBy::create(0.001, -90));
    break;
  case 1:
    misil5->runAction(RotateBy::create(0.001, 90));
    break;
  case 2:
    misil5->runAction(RotateBy::create(0.001, 180));
    break;
  case 3:
    misil5->runAction(RotateBy::create(0.001, -0));
    break;
  case 4:
    misil5->runAction(RotateBy::create(0.001, -45));
    break;
  case 5:
    misil5->runAction(RotateBy::create(0.001, 45));
    break;
  case 6:
    misil5->runAction(RotateBy::create(0.001, 135));
    break;
  case 7:
    misil5->runAction(RotateBy::create(0.001, -135));
    break;
default:
        break;
      }
  }
}

void Arcade3::setMisil5Position(Point position)
{
    Point tileCoord = this->tileCoordForPosition(position);
    int tileGid = _blockage->getTileGIDAt(tileCoord);
    if (tileGid) {
        auto properties = tileMap->getPropertiesForGID(tileGid).asValueMap();
        if (!properties.empty()) {
            auto collision = properties["Collision"].asString();
            auto magma = properties["Magma"].asString();
            if ("True" == collision && magma != "True") {
		              tileMap->removeChild(misil5);
              		actmE3 = false;
              		log("COLISION");
                  return;
            }
        }else return;
    }
    misil5->setPosition(position);
}

void Arcade3::activarMinaE2(Point position){
  if(cantM4>0 && !pause){
    for(i=0; i<3; i++) {
      if(actM4[i]==false) {
        cantM4--;
        minaE2[i] = Sprite::create("mina.png");
        minaE2[i]->setPosition(_enemy2->getPosition());
        minaE2[i]->setScale(0.4);
        tileMap->addChild(minaE2[i],_enemy2->getZOrder());
        bbM4[i] = minaE2[i]->getBoundingBox();
        actM4[i] = true;
        log("Mina %d puesta",i);
        break;
      }
    }
  }
}

//-----------------------------------------
void Arcade3::getUpgrade(Sprite *upgrade)
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

Scene* Arcade3::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = Arcade3::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Arcade3::init()
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

    Director::sharedDirector()->resume();
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    Arcade3::createButtons(visibleSize);

    //Se agrega una etiqueta con el titulo
    auto label = Label::createWithTTF("Arcade3", "fonts/Marker Felt.ttf", 26);
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label, 1);

    /////////////////////////////////
    ///// Manejo de fondos
    //Se carga el mapa y se hacen los collisions tiles con los que el tanque tiene que chocar
    tileMap = new CCTMXTiledMap();
    tileMap->initWithTMXFile("Arcade3.tmx");
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
    tileMap->addChild(_player1, 1);

    //Se crea el sprite de player 2
  auto Player2 = objects->getObject("Player2");
    int x2 = Player2["x"].asInt();
    int y2 = Player2["y"].asInt();
    _player2 = p2.getPlayer();
    _player2 = Sprite::create("tank3.png");
    _player2->setPosition(ccp(x2,y2));
    _player2->setScale(0.3);
    tileMap->addChild(_player2, 1);
    _player2->runAction(RotateBy::create(0.01, 180));
    _player2->runAction(FadeOut::create(0.001));
    //Se crea el sprite de enemigo 1
    auto Enemy1 = objects->getObject("Enemy1");
    int   x3 = Enemy1["x"].asInt();
    int y3 = Enemy1["y"].asInt();
    _enemy1 = e1.getPlayer();
    _enemy1 = Sprite::create("tank1.png");
    setEnemy1Position(ccp(350,450));
    //    _enemy1->setPosition(ccp(x-400,y+150));
    _enemy1->setScale(0.3);
    tileMap->addChild(_enemy1,1);

    //Se crea el sprite de enemigo 2
    auto Enemy2 = objects->getObject("Enemy2");
    int   x4 = Enemy2["x"].asInt();
    int y4 = Enemy2["y"].asInt();
    _enemy2 = e2.getPlayer();
    _enemy2 = Sprite::create("tank2.png");
    setEnemy2Position(ccp(108,600));
    this->_enemy2->runAction(RotateBy::create(0.0000001,-90));
    //    _enemy1->setPosition(ccp(x-400,y+150));
    _enemy2->setScale(0.3);
    tileMap->addChild(_enemy2,1);

    //Se crea el sprite de enemigo 3
    auto Enemy3 = objects->getObject("Enemy3");
    int   x5 = Enemy3["x"].asInt();
    int y5 = Enemy3["y"].asInt();
    _enemy3 = e3.getPlayer();
    _enemy3 = Sprite::create("tank6.png");
    setEnemy3Position(ccp(500,500));
    this->_enemy3->runAction(RotateBy::create(0.0000001, 0));
    //  -enemy2->set(ccp(x-400,y+150));
    _enemy3->setScale(0.3);
    tileMap->addChild(_enemy3,1);

    //Se crea sprite health bar de player 1
    HB1 = Sprite::create("healthBar.png");
    HB1->setPosition(ccp(x,y+40));
    HB1->setScaleX(0.225);
    HB1->setScaleY(0.1);
	addChild(HB1);
   //Se crea sprite health bar de player 2
    HB2 = Sprite::create("healthBar.png");
    HB2->setPosition(ccp(x2,y2+40));
    HB2->setScaleX(0.225);
    HB2->setScaleY(0.1);
	addChild(HB2);
    HB2->runAction(FadeOut::create(0.001));
   //Se crean los sprites de upgrade
    //Tag = 1
    HpUp = Sprite::create("HpUp.png");
    HpUp->setPosition(ccp(x2,y2-300));
    HpUp->setScale(0.3);
    HpUp->setTag(1);
    addChild(HpUp);

    //Tag = 2
    speedUp = Sprite::create("speedUp.png");
    speedUp->setPosition(ccp(x,y+300));
    speedUp->setScale(0.3);
    speedUp->setTag(2);
    addChild(speedUp);

    //Tag = 3
    defenceUp = Sprite::create("defenceUp.png");
    defenceUp->setPosition(ccp(x,y+200));
    defenceUp->setScale(0.3);
    defenceUp->setTag(3);
    addChild(defenceUp);

    //Tag = 4
    attackUp = Sprite::create("attackUp.png");
    attackUp->setPosition(ccp(x,y+100));
    attackUp->setScale(0.3);
    attackUp->setTag(4);
    addChild(attackUp);


   //seccion de movimiento
   auto eventListener = EventListenerKeyboard::create();
   eventListener->onKeyPressed = CC_CALLBACK_2(Arcade3::onKeyPressed, this);
   eventListener->onKeyReleased = CC_CALLBACK_2(Arcade3::onKeyReleased, this);

   this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener,_player1);



    ////////////////////////////////////
    // Actualizacion del juego
    this->schedule(schedule_selector(Arcade3::gameUpdate));


    // set the background music and continuously play it.
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->playBackgroundMusic("Audio/track01.mp3", true);

    // Pausa o continua el juego
    auto pausa = cocos2d::EventListenerKeyboard::create();
    pausa->onKeyPressed = [=](cocos2d::EventKeyboard::KeyCode tecla, cocos2d::Event * event)->void{
	if (tecla == cocos2d::EventKeyboard::KeyCode::KEY_SPACE){
	    if (pause){
		label->setString("Arcade3");
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

void Arcade3::createButtons(Size visibleSize)
{
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    // set the font for menu with text
    MenuItemFont::setFontSize(14);

    // Boton para volver al menu de inicio
    auto mbVolver = MenuItemFont::create("Menu de Inicio", CC_CALLBACK_1(Arcade3::VolverCallBack, this));
    mbVolver->setAnchorPoint(Vec2(0.0,0.0));
    mbVolver->setPosition(Vec2(1*visibleSize.width/16, 1*visibleSize.height/10));
    mbVolver->setColor(Color3B(140, 40, 140));

    // Se crea un boton de salir
    auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png",
                                           CC_CALLBACK_1(Arcade3::menuCloseCallback, this));
    closeItem->setPosition(Vec2(15*visibleSize.width/16, 1*visibleSize.height/10));
    auto menu = Menu::create(mbVolver, closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 2);
}


void Arcade3::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void Arcade3::VolverCallBack(Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Audio/Button.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
    Director::sharedDirector()->replaceScene(PanzerWars::createScene());
}
