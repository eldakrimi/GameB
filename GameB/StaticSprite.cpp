//
//  StaticSprite.cpp
//  GameB
//
//  Created by Ellen Dahlgren on 2019-01-13.
//  Copyright © 2019 Ellen Dahlgren. All rights reserved.
//

#include "StaticSprite.hpp"
#include "GameSystem.hpp"
#include <string>
#include <iostream>

using namespace std;

namespace GameB {
    
    StaticSprite*  StaticSprite::getInstance(int x, int y, int w, int h,const std::string& filePath){
        return new StaticSprite(x,y,w,h,filePath);
    }
    
    StaticSprite::StaticSprite(int x, int y, int w, int h, const string& filePath):Sprite(x,y,w,h,filePath){

        Sprite::setWH(w, h);
        makeTexture(filePath);
        
    }
    
    void StaticSprite::makeTexture(const string& filePath){
        if(texture != nullptr){
            SDL_DestroyTexture(texture);
        }
        SDL_Surface* surf = SDL_LoadBMP(filePath.c_str());
        texture = SDL_CreateTextureFromSurface(gameSys.get_ren(), surf);
        SDL_FreeSurface(surf);
        
    }
    
    void StaticSprite::draw() const{
    
        SDL_RenderCopy(gameSys.get_ren(),texture,NULL,&getDrect());
    }
    
    StaticSprite::~StaticSprite(){
        cout << "Destructor in StaticdSprite object has been called!" << endl;
        SDL_DestroyTexture(texture);
    }
    
}
