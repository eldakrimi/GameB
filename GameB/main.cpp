//
//  main.cpp
//  GameB
//
//  Created by Ellen Dahlgren on 2019-01-11.
//  Copyright © 2019 Ellen Dahlgren. All rights reserved.
//


#include "GameEngine.hpp"
#include "StaticSprite.hpp"
#include "MobileSprite.hpp"
#include "AnimatedSprite.hpp"
#include "Level.hpp"
#include <SDL2_mixer/SDL_mixer.h>

using namespace std;
using namespace GameB;

//vill jag skapa från getInstance eller som subklass?
class Background : public StaticSprite {
public: Background(int x, int y,int w, int h, string image):StaticSprite(x,y,w,h,image){
    
}
};

class Player: public MobileSprite {
public: Player(int x, int y,string image):MobileSprite(x,y,image){
    makeCollideble();
}

    void moveDown(){
        if(getY()<(gameSys.getHeight()-Sprite::getDrect().h))
        setY(getY()+5);
    }
    
    void moveUp(){
        if(getY()>0)
            setY(getY()-5);
    }
    void collisionAction(){
        Sprite::setAliveStatus(false);
    }
    
    void handleCommand(SDL_Event& event){
        switch (event.key.keysym.sym) {
            case SDLK_DOWN:
                moveDown();
                break;
            case SDLK_UP:
                moveUp();
                break;
            case SDLK_SPACE:
                Bullet* bullet = new Bullet(getX()+30, getY(),"shot.png");
                GameEngine::addSprite(bullet);
                break;
        }
    }
    
    
    //inre klass bullet
    class Bullet : public MobileSprite{
    public: Bullet(int x, int y,string image):MobileSprite(x,y,image){
        makeCollideble();
    }
    void move(int time){
        setX(getX()+1*time*0.3);
    }
        
        
    void handleOutsideScreen(){
        GameEngine::removeSprite(this);
        }
    };
};



class AnimatedEnemy: public  AnimatedSprite{
public: AnimatedEnemy(int x, int y,int rowsInSpriteSheet, int columnsInSpriteSheet, string image):AnimatedSprite(x,y,rowsInSpriteSheet,columnsInSpriteSheet, image){
}
    

    void move(int time){
        startAnimation();
        setX(getX()+1*time*0.2);
    }
    
    void handleOutsideScreen(){
        setX(10);
        setY(10);
    }
    
    void restartBee(){
        handleOutsideScreen();
    }
};

class Enemy: public MobileSprite {
    public: Enemy(int x, int y,string image):MobileSprite(x,y,image){
        makeCollideble();
    }
    
    void collisionAction(){
        GameEngine::removeSprite(this);
      //Sprite::setAliveStatus(false);
   }
    
    void handleOutsideScreen(){
        setX(500);
    }
    
    void move(int time){
        setX(getX()-1*time*0.1);
    }
    
};

class EndText: public EnterTextSprite{
public: EndText(int x, int y,const std::string& l,const std::string& p):EnterTextSprite(x,y),lastTextToshow(l),prompt(p){
     setText(lastTextToshow);
    
}
    
    void setFinalText(std:: string finalText){
        finalText.append(prompt);
        setText(finalText);
    }

private:
    std::string prompt;
    std::string lastTextToshow;

    
};

//Free functions
void pause(){
    Mix_Pause(-1);
}
void resume(){
    Mix_Resume(-1);
}
    
    
    

int main(int argc, const char * argv[]) {
    GameEngine ses = GameEngine(60);
    const int WIDTH = gameSys.getWidth();
    const int HEIGHT = gameSys.getHeight();
    
    
    
    //Level 1
    
    Level* levelOne = Level::createLevel("First");
    Background* startBackground = new Background(0,0,WIDTH,HEIGHT,"farsta1.bmp");
    levelOne->addSpriteToLevel(startBackground);
    
    Player* player= new Player(50,150,"ada.png");
    levelOne->addSpriteToLevel(player);
    
    Enemy* enemyOne= new Enemy(500,150,"gloo.png");
    levelOne->addSpriteToLevel(enemyOne);
    levelOne->addSpriteToChangeLevelVector(enemyOne);
    
    AnimatedEnemy* aniEmy = new AnimatedEnemy(10,10,1,2, "twobeez.png");
    levelOne->addSpriteToLevel(aniEmy);
    
    //Level 2
    Level* levelTwo = Level::createLevel("Second");
    Background* secBackground = new Background(0,0,WIDTH,HEIGHT,"stockholmBW.bmp");
    levelTwo->addSpriteToLevel(secBackground);
    
    Player* secPlayer= new Player(50,150,"ada.png");
    levelTwo->addSpriteToLevel(secPlayer);

    Enemy* enemyTwo= new Enemy(500,150,"gloo.png");
    levelTwo->addSpriteToLevel(enemyTwo);
    levelTwo->addSpriteToChangeLevelVector(enemyTwo);

    Enemy* enemyThree= new Enemy(500,300,"gloo.png");
    levelTwo->addSpriteToLevel(enemyThree);
    levelTwo->addSpriteToChangeLevelVector(enemyThree);
    
    //Level 3
    Level* levelThree = Level::createLevel("Third");
    
    Background* endBackground = new Background(0,0,WIDTH,HEIGHT,"farsta1.bmp");
    levelThree->addSpriteToLevel(endBackground);
    
    EndText* box= new EndText(100,150,"Type your name", "! You are great");
    levelThree ->addSpriteToLevel(box);
    levelThree ->addSpriteToChangeLevelVector(box);
    
    
    GameEngine::installFreeFunction(SDLK_p, pause);
    GameEngine::installFreeFunction(SDLK_r, resume);
    
    auto binding = bind(&AnimatedEnemy::restartBee, aniEmy);
    GameEngine::installMemberFunction(SDLK_f, binding);
    

    
    
 


    GameEngine::startGameLoop();
    
    return 0;
}
