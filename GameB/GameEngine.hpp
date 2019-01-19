//
//  GameEngine.hpp
//  GameB
//
//  Created by Ellen Dahlgren on 2019-01-11.
//  Copyright © 2019 Ellen Dahlgren. All rights reserved.
//

#ifndef GameEngine_hpp
#define GameEngine_hpp

#include "GameSystem.hpp"
#include "Sprite.hpp"
#include "EnterTextSprite.hpp"
#include "Level.hpp"
#include <vector>
#include <unordered_map>
#include "SDL2/SDL.h"

namespace GameB {
    
    class GameEngine{
        
        
    public:
        
        GameEngine(int chosenFps);
        GameEngine();
        ~GameEngine();
        
        static void startGameLoop();
        static void addSprite(Sprite* s);
        static void removeSprite(Sprite* s);
        static void installFreeFunction(SDL_Keycode keycode, void(*function_ptr)());
        static void installMemberFunction(SDL_Keycode keycode, std::function<void()> func);
        static void addLevel(Level* l);
        static void setLoseGame();
        
        static bool getFinaltextStatus();
        
    private:
        static GameEngine* instance;
        bool quit;
        bool finalTextNotSet;
        bool gameLost;
        bool textBoxExist;
        int fps;
        Level* currentLevel;
        EnterTextSprite* textBox;
        
        std::vector<Sprite*> sprites;
        std::vector<Sprite*> added;
        std::vector<Sprite*> removed;
        std::vector<Level*> levels;
        
        std::unordered_map<SDL_Keycode, std::function<void()>> freeFunctionsMap;
        std::unordered_map<SDL_Keycode, std::function<void()>> memberFunctionAndObjectBindningMap;
        

        
        //hjälpmetoder
        void runGameLoop();
        void calculateDelayToNextTick(Uint32 nextTick);
        void callTickInAllSprites(int millisecPassed);
        void show();
        void handleEvent(SDL_Event event);
        void checkSpritesOutsideScreen();
        void evaluateCollisions();
        bool checkIfKeyIsMapped(SDL_Keycode keycode);
        void loadNewLevel(int position);
        void checkForLevelChange();
        void textInputStart();
        void removeFromRemovedVector();
    };
    
    
    
    
}

#endif /* GameEngine_hpp */
