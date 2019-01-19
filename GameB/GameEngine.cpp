//
//  GameEngine.cpp
//  GameB
//
//  Created by Ellen Dahlgren on 2019-01-11.
//  Copyright © 2019 Ellen Dahlgren. All rights reserved.
//

#include "GameEngine.hpp"
#include <iostream>
#include "SDL2/SDL.h"

using namespace std;

namespace GameB {
    
    GameEngine* GameEngine::instance;
    
    //Konstruktorer och destruktorer
    GameEngine::GameEngine(int chosenFps){
        
        fps = (chosenFps < 0) ? 60 : chosenFps;
        instance = this;
    }
    
    GameEngine::GameEngine(){
        GameEngine(60);
    }
    
    GameEngine::~GameEngine() {
        cout << "Destructor in GameEngine object has been called!" << endl;
        for(Sprite* s:sprites){
            delete s;
        }
        for(Level* l:levels){
            delete l;
        }
    }
    
    //Statiska metoder som spelprogrammeraren når
    void GameEngine::startGameLoop(){
        instance->gameLost=false;
        instance->loadNewLevel(0);
        instance->runGameLoop();
    }
    void GameEngine::addSprite(Sprite* s){
        instance->added.push_back(s);
    }
    void GameEngine::removeSprite(Sprite* s){
        instance->removed.push_back(s);
    }
    
    void GameEngine::installFreeFunction(SDL_Keycode keycode, void(*function_ptr)()) {
        instance-> freeFunctionsMap.insert(make_pair(keycode, function_ptr));
    }
    void GameEngine::installMemberFunction(SDL_Keycode keycode, function<void()> func) {
        instance->memberFunctionAndObjectBindningMap.insert(make_pair(keycode, func));
    }
    
    void GameEngine::addLevel(Level *l){
        instance->levels.push_back(l);
    }
    void GameEngine::setLoseGame(){
        instance->gameLost=true;
    }
    
    bool GameEngine::getFinaltextStatus(){
        return instance->finalTextNotSet;
    }
    
    
    //Privata metoder:
    void GameEngine::runGameLoop(){
        quit = false;
        finalTextNotSet =true;
        bool isInputText =false;
        textBoxExist = false;
                
        Uint32 lastTick = SDL_GetTicks();
        Uint32 nextTick;
        
        while(!quit){
        nextTick = lastTick + 1000 / fps;
            
        SDL_Event event;
            while (SDL_PollEvent(&event)) {
                for(Sprite* s :sprites)
                    s->handleCommand(event);
                handleEvent(event);
            }//inre while-loop
            
            callTickInAllSprites(nextTick - lastTick);
            evaluateCollisions();
            checkSpritesOutsideScreen();
            
            for(Sprite* s : added){
                sprites.push_back(s); }
            added.clear();
            
            removeFromRemovedVector();
            
            
            for (int i =0;i<sprites.size(); i++){
                
                if(finalTextNotSet){
                    if (EnterTextSprite *e=dynamic_cast<EnterTextSprite *>(sprites[i])){
                        textBox=e;
                        if(isInputText){
                            memberFunctionAndObjectBindningMap.clear();
                            textInputStart();
                            finalTextNotSet =false;
                            
                        }else{
                            isInputText =true;
                        }
                    }
                }
            }
            
            for (Sprite* s : sprites){
                if(!s->isAlive()){
                    removed.push_back(s);
                }
            }

            
            show();
            checkForLevelChange();
            calculateDelayToNextTick(nextTick);
            lastTick = nextTick;
            
            
        }//yttre while-loop
    }
    
    void GameEngine::removeFromRemovedVector(){
        for (Sprite* s : removed) {

            for (std::vector<Sprite*>::iterator i = sprites.begin(); i != sprites.end(); ){
                if (*i == s) {
                    currentLevel->removeSpriteFromChangeLevelVector(s);
                    i = sprites.erase(i);
                    
                    delete s;
                }
                else  i++;}
        }
        
        removed.clear();
        
    }
    
    void GameEngine::checkForLevelChange(){
      
        if(currentLevel->isChangeLevelVectorEmpty()){
            currentLevel->setLevelFinished(true);
           
        }
        if(currentLevel->checkLevelStatus()){
            for(Sprite* s: sprites){
                removed.push_back(s);
            }
            removeFromRemovedVector();
            
            if(gameLost){
                currentLevel = levels[levels.size()-1];
            }else{
                long pos = find(levels.begin(), levels.end(), currentLevel) - levels.begin();
                currentLevel = levels[pos+1];
            }
            
            currentLevel->loadLevel();
        }
        
    }
    
    void GameEngine::loadNewLevel(int pos){
        currentLevel = levels[pos];
        currentLevel->loadLevel();
    }
    
    
    //Hjälpmetoder till gameloop
    void GameEngine::checkSpritesOutsideScreen(){
        for(Sprite*s : sprites){
            if ((s->getX()<0)||(s->getX()>600)||s->getY()<0||s->getY()>400){
                s->handleOutsideScreen();
            }
        }
    }
    
    void GameEngine::callTickInAllSprites(int millisecPassed){
        for(Sprite* s :sprites){
            s->tick(millisecPassed);
        }
    }
    
    void GameEngine::calculateDelayToNextTick(Uint32 nextTick){
        int delay = nextTick - SDL_GetTicks();
        if (delay > 0) {
            SDL_Delay(delay);
        }
    }
    
    void GameEngine::show(){
        SDL_RenderClear(gameSys.get_ren());
        for(Sprite* s : sprites)
            s->draw();
        SDL_RenderPresent(gameSys.get_ren());
    }
    
    void GameEngine::evaluateCollisions(){
        for(Sprite* s1 :sprites){
            for(Sprite* s2: sprites){
                if(s1->hasCollided(s2)){
                    s1->collisionAction();
                }
            }
        }
    }
    

    bool GameEngine::checkIfKeyIsMapped(SDL_Keycode keycode) {
        bool isKeyMapped = false;
        if (freeFunctionsMap.count(keycode) > 0) {
            freeFunctionsMap[keycode]();
            isKeyMapped = true;
            }
            
            if(memberFunctionAndObjectBindningMap.count(keycode) > 0){
            memberFunctionAndObjectBindningMap[keycode]();
            isKeyMapped = true;
            }
            
            return isKeyMapped;
        }

    
    
    void GameEngine::handleEvent(SDL_Event event){
        switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN:
                SDL_Keycode SDLkeycode = event.key.keysym.sym;
                if (SDLkeycode == SDLK_ESCAPE) { quit = true; }
                checkIfKeyIsMapped(SDLkeycode);
                break;
        }
    }
    
    void GameEngine::textInputStart(){
        bool textInputDone = false;
        SDL_Event eve;
        string textToRender = "";
        
        SDL_StartTextInput();
        while (!textInputDone){
            while (SDL_PollEvent(&eve)) {
                switch (eve.type) {
                    case SDL_KEYDOWN:
                        if (eve.key.keysym.sym == SDLK_RETURN) {
                            textBox->setFinalText(textToRender);
                            textInputDone = true;
                        }
                        break;
                  
                    case SDL_TEXTINPUT:
                        textToRender.append(eve.text.text);
                        textBox->setText(textToRender);
                        show();
                        break;
                    case SDL_QUIT:
                        textInputDone = true;
                        SDL_Quit();
                        break;
                }
            }
        }
        SDL_StopTextInput();
        
    }
    
    
}//namespace GameB


