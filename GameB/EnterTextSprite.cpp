//
//  EnterTextSprite.cpp
//  GameB
//
//  Created by Ellen Dahlgren on 2019-01-14.
//  Copyright © 2019 Ellen Dahlgren. All rights reserved.
//

#include "EnterTextSprite.hpp"
#include "GameEngine.hpp"
#include <iostream>

using namespace std;
namespace GameB {
    
    EnterTextSprite::EnterTextSprite(int x, int y):Sprite(x,y,0,0,""){
        textToRender="";
        makeTexture(textToRender);
        
    }
    
    EnterTextSprite* EnterTextSprite::createEnterTextSprite(int x, int y){
        return new EnterTextSprite(x,y);
        
    }
    
    EnterTextSprite::~EnterTextSprite(){
        SDL_FreeSurface(Sprite::getSurface());
        SDL_DestroyTexture(texture);
         cout << "Destructor in EnterText has been called!" << endl;
    }
    
    void EnterTextSprite::makeTexture(const string& textToRender){
        if(texture != nullptr){
            SDL_DestroyTexture(texture);
        }
        if(surf !=nullptr){
            SDL_FreeSurface(surf);

        }
        SDL_Color yellow ={255,255,0};
        
        surf = TTF_RenderText_Solid(gameSys.get_font(), textToRender.c_str(),yellow);
        Sprite::setSurface(surf);
        
        texture = SDL_CreateTextureFromSurface(gameSys.get_ren(), surf);
        
        if(surf==nullptr){
            Sprite::setWH(10, 10);
            
        }else{
            Sprite::setWH(surf->w, surf->h);
        }        
        
    }
    
    void EnterTextSprite::setText(const string& txt) {
        makeTexture(txt);
        
    }
    void EnterTextSprite::setFinalText(const string finalText){
        
        makeTexture(finalText);
    }
    
    void EnterTextSprite::draw() const{
        
        SDL_RenderCopy(gameSys.get_ren(),texture,NULL, &getDrect());
    }
    void EnterTextSprite::tick(int time){
        
    }
    
}

