//
//  MobileSprite.cpp
//  GameB
//
//  Created by Ellen Dahlgren on 2019-01-13.
//  Copyright © 2019 Ellen Dahlgren. All rights reserved.
//

#include "MobileSprite.hpp"
#include <SDL2_image/SDL_image.h>
#include <iostream>
#include <string>
#include "GameSystem.hpp"

using namespace std;

namespace GameB{
    
    MobileSprite* MobileSprite::getInstance(int x, int y, int w, int h,const std::string& filePath){
        return new MobileSprite(x,y,filePath);
    }
    
    MobileSprite::MobileSprite(int x, int y,const string& filePath):Sprite(x,y,0,0,filePath){
        makeTexture(filePath);
       
    }
    
    
   void  MobileSprite::makeTexture(const std::string& filePath){
        if(texture != nullptr){
            SDL_DestroyTexture(texture);
        }
       
         SDL_Surface* surf =  IMG_Load(filePath.c_str());
         Sprite::setSurface(surf);
      
        texture = SDL_CreateTextureFromSurface(gameSys.get_ren(), surf);
        
        Sprite::setWH(surf->w, surf->h);
      
    }

    MobileSprite::~MobileSprite(){
        cout << "Destructor in MobileSprite object has been called!" << endl;
        SDL_FreeSurface(Sprite::getSurface());
        SDL_DestroyTexture(texture);
    }
    
    void MobileSprite::draw() const{
        SDL_RenderCopy(gameSys.get_ren(),texture,NULL,&getDrect());
        
    }
    


    void MobileSprite::tick(int time){
        move(time);
    }
 
    
    
    
    
}

    
