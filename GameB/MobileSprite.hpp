//
//  MobileSprite.hpp
//  GameB
//
//  Created by Ellen Dahlgren on 2019-01-13.
//  Copyright © 2019 Ellen Dahlgren. All rights reserved.
//

#ifndef MobileSprite_hpp
#define MobileSprite_hpp

#include "Sprite.hpp"
#include <string>


namespace GameB {
    
    
    class MobileSprite: public Sprite{
        
    public:
        static MobileSprite* getInstance(int x, int y, int w, int h,const std::string& filePath);
        void draw() const;
        void tick(int time);
      
        ~MobileSprite();
        
        void setXspeed(double speed){xSpeed = speed;}
        void setYspeed(double speed){ySpeed = speed;}
        
        double getXspeed() const{return xSpeed;};
        double getYspeed() const{return ySpeed;};
        
        void setPower(int p);
        int getPower() const {return power;}
        
        bool isAffactedByGravity()const {return affectedByGravity;}
        void setAffectedByGravity(bool status){affectedByGravity = status;}

        
    protected:
         MobileSprite(int x, int y,const std::string& filePath);
        
    private:
        SDL_Texture* texture= nullptr;
        bool affectedByGravity;
        bool hitFloor;
        bool turnedUpper;
        bool turnedLower;
        int power;
        int startingPower;
        double xSpeed;
        double ySpeed;
        
        
        void makeTexture(const std::string& filePath);
        void move(int time, double xSpeed, double ySpeed);
        void gravityMove(int time, double xSpeed, double ySpeed);
        void bounceMove(int time, double xSpeed, double ySpeed);
    };
    
}

#endif /* MobileSprite_hpp */
