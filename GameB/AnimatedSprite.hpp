//
//  AnimatedSprite.hpp
//  GameB
//
//  Created by Ellen Dahlgren on 2019-01-13.
//  Copyright © 2019 Ellen Dahlgren. All rights reserved.
//

#ifndef AnimatedSprite_hpp
#define AnimatedSprite_hpp
#include "Sprite.hpp"
#include <vector>


namespace GameB {
    
    class AnimatedSprite: public Sprite{
        
    public:
         static AnimatedSprite* getInstance(int x, int y, int w, int h,const std::string& filePath);
        ~AnimatedSprite();
        void draw() const;
        void tick(int time);
        virtual void move(int time){}
        
        
    protected:
         AnimatedSprite(int x, int y,int rowsInSpriteSheet, int columnsInSpriteSheet,const std::string& filePath);
         void startAnimation();
    
    private:
        SDL_Texture* texture = nullptr;
        void makeTexture(const std::string& filePath);
        int rows;
        int columns;
        int w, h;
        
        std::vector<int> verticalSpriteSquares;
        std::vector<int> horisontalSpriteSquares;
    };
}

#endif /* AnimatedSprite_hpp */
