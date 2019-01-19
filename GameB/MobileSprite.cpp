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
    
    MobileSprite::MobileSprite(int x, int y,const string& filePath):Sprite(x,y,0,0,filePath),xSpeed(0.0), ySpeed(0.0),hitFloor(false){
        makeTexture(filePath);
        
        turnedUpper = false;
        turnedLower = false;
       
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
        
        if(getY()>(gameSys.getHeight()-Sprite::getDrect().h)&&hitFloor ==false){
            hitFloor =true;
        }
        move(time,xSpeed,ySpeed);
    }
    
    void MobileSprite::move(int time, double xSpeed, double ySpeed){
        
        if(affectedByGravity&&hitFloor){
            bounceMove(time, xSpeed, ySpeed);
        }
        else if(affectedByGravity&&hitFloor==false){
            gravityMove(time, xSpeed, ySpeed);
        }else{
            if(xSpeed==0.0){
                setX(getX());
            }else{
                setX(getX()+1*time*xSpeed);
                
            }if(ySpeed==0.0){
                setY(getY());
            }else{
                setY(getY()+1*time*ySpeed);
            }
        }
        
    
    }
    
    void MobileSprite::gravityMove(int time, double xSpeed, double ySpeed){
        power--;

        if( power<0&&ySpeed<=0.00){
            ySpeed*=-1;
            xSpeed*=1.3;
            ySpeed*=1.3;
        }
    
        setX(getX()+1*time*(xSpeed));
        setY(getY()+1*time*(ySpeed));
    
    }
    
      void MobileSprite::bounceMove(int time, double xSpeed, double ySpeed){
    
          if(getYspeed()<0&&getY()>(getStartingYposition()-startingPower)){
              startingPower--;
          }
          else if(getYspeed()<0&&getY()<(getStartingYposition()-startingPower)&&turnedUpper==false){
              
              setYspeed(ySpeed*-1);
              turnedUpper =true;
              turnedLower = false;
          }
          
          if((getYspeed()>0)&&getY()<(gameSys.getHeight()-Sprite::getDrect().h)){
          }
          else if((getYspeed()>0)&&getY()>(gameSys.getHeight()-Sprite::getDrect().h)){
              setYspeed(ySpeed*-1);
              turnedUpper =false;
              turnedLower = true;
          }
          
          setX(getX()+1*time*(xSpeed));
          setY(getY()+1*time*(ySpeed));
     }
    
    
    void MobileSprite::setPower(int p){
        power=p;
        startingPower =p;
        }
 
}

    
