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

#include "Niveau1.h"
#include "Niveau2Scene.h"
#include "Definitions.h"
#include <iostream>
#include <string>

using namespace std;
USING_NS_CC;

cocos2d::Scene* Niveau1::createScene()
{
    // 'scene' est l'initialisation de l'objet
    auto scene = Scene::createWithPhysics();

    // 'layer' est l'initialisation de l'objet
    auto layer = Niveau1::create();

    // Création du layer comme un fils de scene
    scene->addChild(layer);

    // faire retourner la scène
    return scene;
}

// on initialise l'instance dans "init()"
bool Niveau1::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //-----------------------------Couleur d'arrière plan-------------------------------------//

    auto bg = cocos2d::LayerColor::create(Color4B(255, 255, 255, 255));
    this->addChild(bg);

    //--------------------------Section du niveau-----------------------------------//

    auto labelLevel = Sprite::create("level_1.png");
    labelLevel->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, 870));
    this->addChild(labelLevel);

    // -----------------------Cadre du mûr--------------------------------// 
   
    Build_Wall(1, 90, 770, 0); // up
    Build_Wall(1, 90, 110, 0); // down
    Build_Wall(7, 90, 110, 1); // Left
    Build_Wall(7, 530, 110, 1); // Right
    Build_Wall(7, 200, 110, 2); // Mid1
    Build_Wall(7, 420, 110, 2); // Mid2

    //-----------------------------La trajectoire du ballon----------------------------------//

    for (int i = 0; i < 5; i++) {
        Block_M[i] = Sprite::create("Green_Path.png");
        Block_M[i]->setPosition(310, 110 * (i + 2));
        Block_M[i]->setVisible(false);
        this->addChild(Block_M[i]);
    }

    // --------------------------Création du ballon ------------------------------------------//
    
    ball = Sprite::create("ball_color.png");
    ball->setPosition(310, 220);

    //--------------------ajouter les caracteristiques physique du ballon-------------------- //

    auto spriteBody = PhysicsBody::createCircle(ball->getContentSize().width / 2, PhysicsMaterial(0, 1, 0));
    spriteBody->setGravityEnable(false);
    ball->setPhysicsBody(spriteBody);
    this->addChild(ball, 0);

 //--------------------------configuration des touches du clavier-------------------------------//

    auto keyBoardListener = cocos2d::EventListenerKeyboard::create();
    keyBoardListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)->void {
        Vec2 location = event->getCurrentTarget()->getPosition();

        char key = '_';
        if (location.y == 220) {
            if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW) {
                event->getCurrentTarget()->setPosition(location.x, location.y + 4 * 110.0f);
                key = 'U';
            }
        }

        location = event->getCurrentTarget()->getPosition();
        float x = location.x;
        float y = location.y;
        auto action = cocos2d::MoveTo::create(10, cocos2d::Vec2(x, y));
        ball->runAction(action);


        this->detectCollision(key = 'U');
    };

    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(keyBoardListener, ball);

    return true;
}

//------------------------- fonction pour passer le niveau-----------------------//

void Niveau1::detectCollision(char key) {

    //------------------------- fonction pour passer le niveau-----------------------//

    if (key == 'U') {
        for (int i = 0; i < 5; i++) {
            if ((ball->getPosition().x == 310 && ball->getPosition().y >= Block_M[i]->getPosition().y)) {
                Block_M[i]->setVisible(true);
            }
        }
    }

    //---------------creation effets du victoire et pour passer au niveau suivant ----------------//
    if (ball->getPosition().x == 310 && ball->getPosition().y == 660) {

        auto emitter = ParticleFireworks::create();
        emitter->setPosition(310, 330);
        addChild(emitter, 10);
        this->scheduleOnce(CC_SCHEDULE_SELECTOR(Niveau1::GoToNiveau2Scene), DISPLAY_TIME_SPLASH_SCENE);
    }
}

//-----------------------------------fonction pour créer le mûr---------------------------//

void Niveau1::Build_Wall(int nb_block, float x, float y, int id_block) {

    for (int i = 0; i < nb_block; i++) {

        Block[i] = Sprite::create("block_.png");

        if (id_block == 1) { 
            Block[i]->setPosition(x, y * (i + 1));

        }
        else if (id_block == 0) { 
            Block[i]->setPosition(310, y);
        }
        else {
            Block[i]->setPosition(x, y * (i + 1));
        }
        this->addChild(Block[i]);
    }
}


void Niveau1::GoToNiveau2Scene(float dt) {

    auto scene = Niveau2Scene::createScene();

    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));

}