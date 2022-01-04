/**
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 **/

#include "Niveau3.h"
#include "LastPagee.h"
#include "Definitions.h"
#include <iostream>
#include <string>
using namespace std;
USING_NS_CC;


cocos2d::Scene* Niveau3::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();

    // 'layer' is an autorelease object
    auto layer = Niveau3::create();


    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}


// on initialise l'instance dans "init()"
bool Niveau3::init()
{
    
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);

    auto edgeNode = Node::create();
    edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    edgeNode->setPhysicsBody(edgeBody);

    this->addChild(edgeNode);

    //-----------------------------Background Color-------------------------------------//

    auto bg = cocos2d::LayerColor::create(Color4B(255, 255, 255, 255));
    this->addChild(bg);

    //-------------------------Section du niveau----------------------------------------------//
    auto labelLevel = Sprite::create("level_2.png");
    labelLevel->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, 870));
    this->addChild(labelLevel);

    // -----------------Cadre du mûr-----------------// 

    Build_Wall(4, 110, 770, 0); // up
    Build_Wall(4, 110, 110, 0); // down
    Build_Wall(7, 90, 110, 1); // Left
    Build_Wall(7, 530, 110, 1); // Right
    Build_Wall(1, 220, 660, 2); // middle 1
    Build_Wall(1, 440, 550, 2); // middle 2
    Build_Wall(1, 330, 440, 2); // middle 3
    Build_Wall(1, 330, 330, 2); // middle 4
    Build_Wall(1, 440, 660, 2); // middle 5

     //-----------------La trajectoire du ballon-----------------------------//
     
    //Bottom
    for (int i = 0; i < 3; i++) {
        Block_B[i] = Sprite::create("Red_Path.png");
        Block_B[i]->setPosition(110* (i + 2)-20, 220);
        Block_B[i]->setVisible(false);
        this->addChild(Block_B[i]);
    }

  
    //Left
    for (int i = 0; i < 4; i++) {
        Block_L[i] = Sprite::create("Red_Path.png");
        Block_L[i]->setPosition(200, 110 * (i + 2));
        Block_L[i]->setVisible(false);
        this->addChild(Block_L[i]);
    }

    //Right
    for (int i = 0; i < 3; i++) {
        Block_R[i] = Sprite::create("Red_Path.png");
        Block_R[i]->setPosition(420, 110 * (i + 2));
        Block_R[i]->setVisible(false);
        this->addChild(Block_R[i]);
    }

    //Middle
    for (int i = 0; i < 2; i++) {
        Block_M[i] = Sprite::create("Red_Path.png");
        Block_M[i]->setPosition(310, 110 * (i + 5));
        Block_M[i]->setVisible(false);
        this->addChild(Block_M[i]);
    }
    
    // ------------------Création du ballon

    ball = Sprite::create("ball_color.png");
    ball->setPosition(420, 440);

    //ajouter les caracteristiques physique du ballon
    auto spriteBody = PhysicsBody::createCircle(ball->getContentSize().width / 2, PhysicsMaterial(0, 1, 0));
    spriteBody->setGravityEnable(false);
    ball->setPhysicsBody(spriteBody);


    this->addChild(ball, 0);



 //--------------------------configuration des touches du clavier-------------------------------//

    auto keyBoardListener = cocos2d::EventListenerKeyboard::create();
    keyBoardListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)->void {
        Vec2 location = event->getCurrentTarget()->getPosition();

        location = event->getCurrentTarget()->getPosition();
        float x = location.x;
        float y = location.y;
        auto action = cocos2d::MoveTo::create(10, cocos2d::Vec2(x, y));

        ball->runAction(action);

        char key ='_';

        switch (keyCode)
        {

        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            
            if (location.x == 420 && location.y == 660 || location.x == 310 && location.y == 550) {
                event->getCurrentTarget()->setPosition(location.x - 110, location.y);
                
            }
            else if (location.x == 420 && location.y == 220) {
                event->getCurrentTarget()->setPosition(location.x - 2 * 110, location.y);
                
            }
            key = 'L';
            break;

        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            if ( location.x == 200 && location.y == 550) {
                event->getCurrentTarget()->setPosition(location.x + 110, location.y);
                
            }
            else if (location.x == 200 && location.y == 220) {
                event->getCurrentTarget()->setPosition(location.x + 2 * 110, location.y);
                
            }
            key = 'R';
            break;

        case EventKeyboard::KeyCode::KEY_UP_ARROW:
           
            if (location.x == 420 && location.y == 220) {
                event->getCurrentTarget()->setPosition(location.x, location.y + 2 * 110.0f);
                
            }
            else if (location.x == 200 && location.y == 220){
                event->getCurrentTarget()->setPosition(location.x, location.y + 3 * 110.0f);
            
            }
            else if (location.x == 310 && location.y == 550){ 
                event->getCurrentTarget()->setPosition(location.x, location.y + 110.0f); 
            }
            key = 'U';
            break;

        case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            if (location.x == 420 && location.y == 440) {
                event->getCurrentTarget()->setPosition(location.x, location.y - 2 * 110.0f);
                
            }
            else if (location.x == 200 && location.y == 550) {
                event->getCurrentTarget()->setPosition(location.x, location.y - 3 * 110.0f);
                
            }
            else if (location.x == 310 && location.y == 660) {
                event->getCurrentTarget()->setPosition(location.x, location.y - 110.0f);
                
            }
            key = 'D';
            break;

        }

        this->detectCollision(key);

    };

    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(keyBoardListener, ball);


    return true;
}
//------------------------- fonction pour passer le niveau-----------------------//

void Niveau3::detectCollision(char key) {

    //------------------------- fonction pour passer le niveau-----------------------//
    if (key == 'R' || key == 'L') {
        for (int i = 0; i < 3; i++) {
            if ((ball->getPosition().y == 220 && ball->getPosition().x >= Block_B[i]->getPosition().x)
                || (ball->getPosition().y == 220 && ball->getPosition().x <= Block_B[i]->getPosition().x))
            {
                Block_B[i]->setVisible(true);
                B = true;
            }
        }
    }
    else if (key == 'D' || key == 'U') {
        for (int i = 0; i < 3; i++) {
            if ((ball->getPosition().x == 420 && ball->getPosition().y >= Block_R[i]->getPosition().y)
                || (ball->getPosition().x == 420 && ball->getPosition().y <= Block_R[i]->getPosition().y))
            {
                Block_R[i]->setVisible(true);
                R = true;
            }
        }
        for (int i = 0; i < 4; i++) {
            if ((ball->getPosition().x == 200 && ball->getPosition().y <= Block_L[i]->getPosition().y)
                || (ball->getPosition().x == 200 && ball->getPosition().y >= Block_L[i]->getPosition().y))
            {
                Block_L[i]->setVisible(true);
                L = true;
            }
            
        }
        for (int i = 0; i < 2; i++) {
            if ((ball->getPosition().x == 310 && ball->getPosition().y <= Block_M[i]->getPosition().y)
                || (ball->getPosition().x == 310 && ball->getPosition().y >= Block_M[i]->getPosition().y))
            {
                Block_M[i]->setVisible(true);
                M = true;
            }
        }
    }
    //---------------creation effets du victoire et pour passer au niveau suivant ----------------//

    if (B && R && L && M) {
        auto emitter = ParticleFireworks::create();
        emitter->setPosition(310, 330);
        addChild(emitter, 10);
        this->scheduleOnce(CC_SCHEDULE_SELECTOR(Niveau3::GoToLastPagee), DISPLAY_TIME_SPLASH_SCENE);
    }
}

//-----------------------------------fonction pour créer le mûr---------------------------//
void Niveau3::Build_Wall(int nb_block, float x, float y, int id_block) {

    for (int i = 0; i < nb_block; i++) {

        Block[i] = Sprite::create("block_.png");

        if (id_block == 1) { 
            Block[i]->setPosition(x, y * (i + 1));

        }
        else if (id_block == 0) { 
            Block[i]->setPosition(x * (i + 2) - 20, y);
        }
        else if (id_block == 2) {
            Block[i]->setPosition(x * (i + 1)-20, y);
        }
        this->addChild(Block[i]);
    }
    
}

void Niveau3::GoToLastPagee(float dt)
{
    auto scene = LastPagee::createScene();

    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}