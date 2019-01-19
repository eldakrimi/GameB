//
//  GameSystem.hpp
//  GameB
//
//  Created by Ellen Dahlgren on 2019-01-11.
//  Copyright © 2019 Ellen Dahlgren. All rights reserved.
//

#ifndef GameSystem_hpp
#define GameSystem_hpp

#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>


namespace GameB{
    class GameSystem
    {
    public:
        GameSystem();
        ~GameSystem();
        SDL_Renderer* get_ren() const;
        TTF_Font* get_font() const;
        int getHeight() const { return HEIGHT; };
        int getWidth() const { return WIDTH; };
        
    
        
    private:
        SDL_Window* win;
        SDL_Renderer* ren;
        TTF_Font* font;
        const int HEIGHT = 400;
        const int WIDTH = 600;
    };
    
    extern GameSystem gameSys;
}

#endif /* GameSystem_hpp */
