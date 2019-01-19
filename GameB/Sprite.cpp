//
//  Sprite.cpp
//  GameB
//
//  Created by Ellen Dahlgren on 2019-01-12.
//  Copyright © 2019 Ellen Dahlgren. All rights reserved.
//

#include "Sprite.hpp"

namespace GameB {
    
    Sprite::Sprite(int x, int y, int w, int h,const std::string& filePath):dRect{x,y,w,h},startingXposition(x),startingYposition(y)
    {
        
    }
    
    void Sprite::setWH(int w, int h){
        dRect.w = w;
        dRect.h = h;
    }
    void Sprite::setSrcRect(int x, int y, int w, int h){
        srcRect.x= x;
        srcRect.y= y;
        srcRect.w= w;
        srcRect.h= h;
    }
 
    
    bool Sprite::hasCollided(Sprite *other){
        
        if(this!=other && this->isCollideble() && other->isCollideble()){
            
            SDL_Rect intersection;
            if (SDL_IntersectRect(&getDrect(), &other->getDrect(), &intersection)) {
                for (int i = 0; i < intersection.w; i++) {
                    for (int a = 0; a < intersection.h; a++) {
                        if (other->isPixelColored(intersection.x + i, intersection.y + a) && isPixelColored(intersection.x + i, intersection.y + a)) {
                            return true;
                        }
                    }
                }
            }
        }
            return false;
    }
    
    bool Sprite::isPixelColored(int x, int y) {
        
        SDL_Surface* surf = getSurface();
        int surfX = x - getX();
        int surfY = y - getY();
        SDL_LockSurface(surf);
        Uint32* pixels = static_cast<Uint32*>(surf->pixels);
        Uint32 pixel = pixels[surfY*surf->w + surfX];
        SDL_UnlockSurface(surf);
        
        SDL_PixelFormat* pfm = surf->format;
        Uint8 r, g, b, alpha = 0;
        SDL_GetRGBA(pixel, pfm, &r, &g, &b, &alpha);
        
        return alpha > 0x0F;
        
        
        
    }
    
        

    
   
    
    
}
