/****
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
 ****/

#ifndef GAME_SCENE_LEVEL_1_H
#define GAME_SCENE_LEVEL_1_H

#pragma once

#include "cocos2d.h"
#include<vector>


USING_NS_CC;

class Niveau1 : public cocos2d::Scene {

public:
    static cocos2d::Scene* createScene();

    virtual bool init();

private:
    cocos2d::Sprite* ball;
    cocos2d::Sprite* Block[8];
    cocos2d::Sprite* Block_M[8];

    cocos2d::ParticleMeteor* emitter;


    cocos2d::Color4B* m_TextureData;
    cocos2d::Texture2D* m_Texture;
    cocos2d::Sprite* m_Sprite;

    int* V_B;
    char key;
    bool R, L = false;

    cocos2d::PhysicsWorld* sceneWorld;


    CREATE_FUNC(Niveau1);

    void GoToNiveau2Scene(float dt);

    void SetPhysicsWorld(cocos2d::PhysicsWorld* world) { sceneWorld = world; };

    void Build_Wall(int nb_block, float x, float y, int id_block); 

    void detectCollision(char key);

};


#endif GAME_SCENE_LEVEL_1_H