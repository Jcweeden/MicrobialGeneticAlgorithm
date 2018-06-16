#ifndef _Game_
#define _Game_
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "InputHandler.h"
//#include "Environment.h"
//#include "GameObject.h"


#include <iostream>
#include <vector>

//class GameObject;
class Environment;

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
  //void loadTextures();
  void loadObjects();
  //void initText();
  //bool loadFromRenderedText( std::string textureText, SDL_Color textColor );

  
  //std::vector<GameObject*> m_gameObjects;

  SDL_Renderer* getRenderer() const { return m_pRenderer; }

  bool running() {return m_bRunning;}

  int getUIHeight(){return UIHeight;}
  int getWindowHeight(){return windowHeight;}
  int getWindowWidth(){return windowWidth;}
  int getBorderWidth(){return borderWidth;}

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
  int borderWidth;
  int UIHeight;


  //GameStateManager* m_pGameStateManager;

  //start the game loop
  bool m_bRunning;


  //text
  /*
  TTF_Font* fontTTF; //this opens a font style and sets a size
  SDL_Color textColour = {40,104,19};  // this is the color in rgb format

  
  SDL_Surface* scoreMessage;
  SDL_Texture* scoreText; 
  SDL_Rect scoreRect;

  SDL_Surface* highScoreMessage;
  SDL_Texture* highScoreText;
  SDL_Rect highScoreRect;
  */

};

typedef Game TheGame;

#endif
