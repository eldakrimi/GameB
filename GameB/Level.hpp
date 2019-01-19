//
//  Level.hpp
//  GameB
//
//  Created by Ellen Dahlgren on 2019-01-13.
//  Copyright © 2019 Ellen Dahlgren. All rights reserved.
//


#ifndef Level_hpp
#define Level_hpp

#include <string>
#include <vector>
#include "Sprite.hpp"

namespace GameB{
    
    class Level{
        
    public:
        static Level* createLevel(std::string name);
        
        ~Level();
        
        void addSpriteToLevel(Sprite* s);
        void addSpriteToChangeLevelVector(Sprite* s);
        void removeSpriteFromChangeLevelVector(Sprite* s);
        void loadLevel();
        
        bool isChangeLevelVectorEmpty(){  return changeLevelVector.empty();}
        std:: string getLevelName()const {return name;}
        bool checkLevelStatus() const {return levelFinished;}
        void setLevelFinished(bool status){levelFinished = status;}
      
        
    protected:
        Level(std:: string name);
        
    private:
       std::vector<Sprite*> spritesInLevel;
       std::vector<Sprite*>changeLevelVector;
        
        std:: string name;
        bool levelFinished;
        
    };
}

#endif /* Level_hpp */
