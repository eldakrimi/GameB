//
//  EnterTextSprite.hpp
//  GameB
//
//  Created by Ellen Dahlgren on 2019-01-14.
//  Copyright © 2019 Ellen Dahlgren. All rights reserved.
//

#ifndef EnterTextSprite_hpp
#define EnterTextSprite_hpp

#include "Sprite.hpp"
#include <string>

namespace GameB {
    class EnterTextSprite:public Sprite{
        
    public:
        static EnterTextSprite* createEnterTextSprite(int x, int y, int w, int h);
        
        void draw() const;
        void tick(int time);
        std::string getText() { return textToRender; }
        void setText(const std::string& textToRender );
        virtual void setFinalText(const std::string lastText);
        
        ~EnterTextSprite();
    protected:
        EnterTextSprite(int x, int y, int w, int h);
        SDL_Texture* getTexture() const {return texture;}
        void makeTexture(const std::string& filePath);
        
    private:
        SDL_Texture* texture = nullptr;
        SDL_Surface* surf = nullptr;
        SDL_Rect  inputRect;
    
        std::string textToRender = "";
        std::string lastText="";
        
    };
}

#endif /* EnterTextSprite_hpp */
