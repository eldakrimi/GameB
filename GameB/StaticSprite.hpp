//
//  StaticSprite.hpp
//  GameB
//
//  Created by Ellen Dahlgren on 2019-01-13.
//  Copyright © 2019 Ellen Dahlgren. All rights reserved.
//

#ifndef StaticSprite_hpp
#define StaticSprite_hpp

#include "Sprite.hpp"
#include <string>

namespace GameB {
    class StaticSprite : public Sprite{
        
        
    public:
         static StaticSprite* getInstance(int x, int y, int w, int h,const std::string& filePath);
         void draw() const;
         void tick(int time){};
         ~StaticSprite();

        
    protected:
        StaticSprite(int x, int y, int w, int h,const std::string& filePath);
    private:
        SDL_Texture* texture= nullptr;
        void makeTexture(const std::string& filePath);

     
        
        
        
    };
    
}

#endif /* StaticSprite_hpp */
