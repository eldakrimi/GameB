//
//  Sprite.hpp
//  GameB
//
//  Created by Ellen Dahlgren on 2019-01-12.
//  Copyright © 2019 Ellen Dahlgren. All rights reserved.
//

#ifndef Sprite_hpp
#define Sprite_hpp

#include <SDL2/SDL.h>
#include <string>

namespace GameB {
    class Sprite{
    public:
        virtual ~Sprite(){};
        virtual void tick(int millisPassed) = 0;
        virtual void draw() const=0;
        virtual void collisionAction(){};
        virtual void handleOutsideScreen(){};
        virtual void handleCommand(SDL_Event& event){};
        
        
        
        //Getters och setters
        void setX(int x) { dRect.x = x; }
        void setY(int y) { dRect.y = y; }
        int& getX() {return  dRect.x;}
        int& getY() {return  dRect.y;}
        
        const SDL_Rect& getDrect() const{return dRect;}
        const SDL_Rect& getSrect() const{return srcRect;}
        
        bool hasCollided(Sprite* other);
        
        bool isCollideble()const { return collideble;}
        bool isAlive()const {return alive;}
        void setAliveStatus (bool status){alive=status;}
        bool isHit() const {return hit;}
        void setHitStatus (bool status){hit=true;}
        
    protected:
        Sprite(int x, int y, int w, int h,const std::string& filePath);
        void makeCollideble() { collideble = true; }
        //osäker om den behövs
        void setWH(int w, int h);
        void setSrcRect(int x, int y, int w, int h);

        
        SDL_Surface* getSurface() const { return surface; };
        void setSurface(SDL_Surface* s){
            surface = s;
        }
       
        
    private:
        SDL_Rect dRect;
        SDL_Rect srcRect;
        SDL_Surface* surface;
        
        //får man initiera saker här?
        bool alive =true;
        bool collideble= false;
        bool hit=false;
        
        //kanske inte kan vara här/publik?
        bool isPixelColored(int x, int y);
        
        //förbjud kopiering och tilldelning
        const Sprite& operator=(const Sprite&)=delete;
        Sprite(const Sprite&)= delete;
        
    };
}
#endif /* Sprite_hpp */
