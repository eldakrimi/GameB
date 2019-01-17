//
//  AnimatedSprite.cpp
//  GameB
//
//  Created by Ellen Dahlgren on 2019-01-13.
//  Copyright © 2019 Ellen Dahlgren. All rights reserved.
//

#include "AnimatedSprite.hpp"
#include <SDL2_image/SDL_image.h>
#include "GameSystem.hpp"
#include <iostream>

using namespace std;

namespace GameB {
    
    
    AnimatedSprite* AnimatedSprite::getInstance(int x, int y, int rows, int columns,const string& filePath){
        return new AnimatedSprite(x,y,rows,columns,filePath);
    }
    
    AnimatedSprite::AnimatedSprite(int x, int y,int rowsInSpriteSheet, int columnsInSpriteSheet,const string& filePath):Sprite(x,y,0,0,filePath){
        
        rows = rowsInSpriteSheet;
        columns = columnsInSpriteSheet;
        makeTexture(filePath);
        
    }
    
    void AnimatedSprite::makeTexture(const std::string& filePath){
        if(texture != nullptr){
            SDL_DestroyTexture(texture);
        }
        
        SDL_Surface* surf =  IMG_Load(filePath.c_str());
        Sprite::setSurface(surf);
       
        texture = SDL_CreateTextureFromSurface(gameSys.get_ren(), surf);
        SDL_QueryTexture(texture, NULL, NULL, &w, &h);
        
        if (rows!=0 && columns!=0){
            w= w/columns;
            h=h/rows;
            setWH(w, h);
        }
        
        for(int i=0; i<rows;i++){
            verticalSpriteSquares.push_back(h*i);
        }
        
        for(int i=0; i<columns;i++){
            horisontalSpriteSquares.push_back(w*i);
        }

        Sprite::setSrcRect(0,0 , w, h);
    }
    void AnimatedSprite::draw() const{
        
        SDL_RenderCopy(gameSys.get_ren(),texture,&getSrect(),&getDrect());
        
    }
 
    
    
    void AnimatedSprite::startAnimation(){
        if(getSrect().x==0){
            Sprite::setSrcRect(horisontalSpriteSquares[1],verticalSpriteSquares[0] , w, h);
            
        }else{
            Sprite::setSrcRect(horisontalSpriteSquares[0],verticalSpriteSquares[0] , w, h);
        }
        
    }
    
    AnimatedSprite::~AnimatedSprite(){
        cout << "Destructor in MobileSprite object has been called!" << endl;
        SDL_FreeSurface(Sprite::getSurface());
        SDL_DestroyTexture(texture);
    }
    
    void AnimatedSprite::tick(int time){
        move(time);
    }

    
}
