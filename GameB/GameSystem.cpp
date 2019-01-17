//
//  GameSystem.cpp
//  GameB
//
//  Created by Ellen Dahlgren on 2019-01-11.
//  Copyright © 2019 Ellen Dahlgren. All rights reserved.
//

#include "GameSystem.hpp"
#include <SDL2/SDL.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <iostream>


using namespace std;

namespace GameB {
    GameSystem::GameSystem(){
        
        //Initierar SDL
        SDL_Init(SDL_INIT_EVERYTHING);
        if( SDL_Init(SDL_INIT_EVERYTHING) < 0 )
        {
            printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
            
        }
        
        //Skapar ett fönster
        win = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
        if (win == NULL)
        {
          
            printf("Could not create window: %s\n", SDL_GetError());
        }
        
        
        //Skapar en renderare
        ren = SDL_CreateRenderer(win, -1, 0);//skapar en renderare kopplat till detta fönster.
        if (ren == NULL) {
            // Om det inte blir ngn renderare.
            printf("Could not create renderer: %s\n", SDL_GetError());
        }
        
        //Initierar font
        TTF_Init();
        font = TTF_OpenFont("krungthep.ttf", 36);
        if(font== NULL)
        {
            printf("Could not create font %s\n", SDL_GetError());
        }
        
        
        //startar musik
        Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096);
        Mix_Chunk* m = Mix_LoadWAV("music.wav");
        Mix_PlayChannel(-1, m, -1);
        
    }
    GameSystem::~GameSystem(){
        cout << "Destructor in GameSystem has been called" << endl;
        SDL_DestroyWindow(win);
        SDL_DestroyRenderer(ren);
        TTF_CloseFont(font);
        Mix_CloseAudio();
        TTF_Quit();
        SDL_Quit();
    }
    
    SDL_Renderer* GameSystem::get_ren() const{
        return ren;
    }
    TTF_Font* GameSystem::get_font() const{
        return font;
    }
    
    
    GameSystem gameSys;
}


