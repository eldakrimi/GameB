//
//  MobileSprite.hpp
//  GameB
//
//  Created by Ellen Dahlgren on 2019-01-13.
//  Copyright © 2019 Ellen Dahlgren. All rights reserved.
//

#ifndef MobileSprite_hpp
#define MobileSprite_hpp

#include "Sprite.hpp"
#include <string>


namespace GameB {
    
    
    class MobileSprite: public Sprite{
        
    public:
        static MobileSprite* getInstance(int x, int y, int w, int h,const std::string& filePath);
        void draw() const;
        void tick(int time);
        void virtual move(int time){}
        ~MobileSprite();
        
    protected:
         MobileSprite(int x, int y,const std::string& filePath);
        
        
        
    private:
        SDL_Texture* texture= nullptr;
        void makeTexture(const std::string& filePath);
        void gravityMove();
    };
    
}

#endif /* MobileSprite_hpp */
