#ifndef _Game_
#define _Game_
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "SDL2/SDL2_gfxPrimitives.h" 

#include "InputHandler.h"

#include <iostream>
#include <vector>

class Environment;
class UI;

class Game
{
public:

  static Game* Instance();
        
  
  bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
  void render();
  void update();
  void handleEvents();
  void clean();

  void quit();

  void loadSounds();
  //void loadObjects();

  
  SDL_Renderer* getRenderer() const { return m_pRenderer; }

  bool running() {return m_bRunning;}

  int getUIHeight(){return UIHeight;}
  int getWindowHeight(){return windowHeight;}
  int getWindowWidth(){return windowWidth;}

  Uint32 getFrameTime() { return frameTime; }
  void setFrameTime(Uint32 val) { frameTime = val; }
  
private:

  Game(){}

  //static instance variable
  static Game* s_pInstance;

  Environment* env;
  
  //the time it took to render the last frame
  Uint32 frameTime;
  
  SDL_Window* m_pWindow;
  SDL_Renderer* m_pRenderer;

  int windowWidth;
  int windowHeight;
  int UIHeight;

  UI* ui;

  //start the game loop
  bool m_bRunning;

};

typedef Game TheGame;

#endif
