//
//  Level.cpp
//  GameB
//
//  Created by Ellen Dahlgren on 2019-01-13.
//  Copyright © 2019 Ellen Dahlgren. All rights reserved.
//

#include "Level.hpp"
#include "GameEngine.hpp"
#include <iostream>


using namespace std;

namespace GameB{
    
    Level::Level(string name):name(name),levelFinished(false){
         GameEngine::addLevel(this);
        
    }
    
    Level* Level:: createLevel(string name){
        return new Level(name);
    }
    Level::~Level(){
        cout << "Destructor level object has been called!" << endl;
        
    }
    
    void Level::addSpriteToLevel(Sprite* s){
        spritesInLevel.push_back(s);
    }
    
    void Level:: addSpriteToChangeLevelVector(Sprite *s){
        changeLevelVector.push_back(s);
    }
    
    void Level:: removeSpriteFromChangeLevelVector(Sprite* s){
        for (std::vector<Sprite*>::iterator i =  changeLevelVector.begin(); i !=  changeLevelVector.end(); ){
            if (*i == s) {
                i =  changeLevelVector.erase(i);
                cout << "removed from ChangeLevelVector" << endl;
            }
            else  i++;}
    }
    
    
    void Level::loadLevel(){
        for(Sprite* s: spritesInLevel){
            GameEngine::addSprite(s);
        }
    }
    
    //förbjud kopiering/tilldelning?
    
    
    
}
