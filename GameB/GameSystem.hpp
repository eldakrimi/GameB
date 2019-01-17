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
        int getHeight() const { return HEIGHT; };// är detta värdesemantik? ska den vara final?
        int getWidth() const { return WIDTH; };// är detta värdesemantik? ska den vara final?
        
    
        
    private:
        SDL_Window* win; //flera ska använda detta fönster
        SDL_Renderer* ren;//flera ska använda denna renderare.
        TTF_Font* font;
        const int HEIGHT = 400;
        const int WIDTH = 600;
    };
    
    extern GameSystem gameSys;
}

#endif /* GameSystem_hpp */
