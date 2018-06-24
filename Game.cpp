#include "Game.h"
//#include "SoundMixer.h"

//#include "CollisionManager.h"

#include "Environment.h"


Game* Game::s_pInstance = 0;

Game* Game::Instance()
  {
    if(s_pInstance == 0)
    {
      s_pInstance = new Game();
      return s_pInstance;
    }

    return s_pInstance;
  }


bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
  int flags = 0;

  if (fullscreen) {//if method parameter = true then make variable in line below
    flags = SDL_WINDOW_SHOWN;
  }
  
  // initialise SDL
   if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
   {
     std::cout << "Game: SDL init success\n";
     // if succeeded create our window
     m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
 
 // if the window creation succeeded create our renderer
     if(m_pWindow != 0)
     {
       std::cout << "Game: Window creation success\n";
       m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

       if (m_pRenderer != 0) {
         std::cout << "Game: Renderer creation success\n";
         SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 0, 255);
       }
       else {
         std::cout << "Game: Renderer init failed\n";
         return false;
       }
     }
     else
     {
       std::cout << "Game: Window init failed\n";
       return false;
     }
   }
   else
   {
     std::cout << "Game: SDL init failed\n";
     return false; // sdl could not initialise
   }

   std::cout << "Game: Init success\n";
   m_bRunning = true;//start the main loop

   windowWidth = 600;
   windowHeight = 600;
   borderWidth = 10;
   UIHeight = 70;

   srand (time(NULL));
   // env = new Environment(10,10);

   env = TheEnvironment::Instance();
   env->setup(2,20,0, getWindowHeight(), getWindowWidth(), 20);
   std::cout << "Game.init() - env->setup() complete\n";
   /*
   initText();
   loadSounds();
   */
   
   //  m_pGameStateManager = new GameStateManager();
   
   //start on MenuState
   //m_pGameStateManager->changeState(new MenuState());
   
   
   return true;
}
/*
void Game::initText()
{

  if(TTF_Init()==-1) {
    printf("TTF_Init: %s\n", TTF_GetError());
    exit(2);
  }
  
  fontTTF = TTF_OpenFont("Assets/ka1.ttf", 24);
  if (fontTTF == NULL) {
        fprintf(stderr, "error: font not found\n");
    }

  scoreMessage = TTF_RenderText_Solid(fontTTF, "SCORE: 00 . 00", textColour); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
  scoreText = SDL_CreateTextureFromSurface(m_pRenderer, scoreMessage); 
  scoreRect.x = 0 + 30 + 55;  //controls the rect's x coordinate 
  scoreRect.y = 20+54; // controls the rect's y coordinte
  scoreRect.w = 150; // controls the width of the rect
  scoreRect.h = 30; // controls the height of the rect

  highScoreMessage = TTF_RenderText_Solid(fontTTF, "HIGH: 00 . 00", textColour); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
  highScoreText = SDL_CreateTextureFromSurface(m_pRenderer, highScoreMessage); 
  highScoreRect.x = windowWidth-150-30+55;  //controls the rect's x coordinate 
  highScoreRect.y = 20+54; // controls the rect's y coordinte
  highScoreRect.w = 150; // controls the width of the rect
  highScoreRect.h = 30; // controls the height of the rect
}

//pass in 0 to update score, 1 to update highScore
void Game::updateScore(std::string text)
{  
  text.insert(0, "SCORE: ");
  scoreMessage = TTF_RenderText_Solid(fontTTF, text.c_str(), textColour);
  scoreText = SDL_CreateTextureFromSurface(m_pRenderer, scoreMessage); 
}
*/


void Game::loadSounds()
{
  //TheSoundMixer::Instance()->load("assets/changeDirection.wav", "spaceBar", SOUND_SFX); 
}


void Game::render()
{
  SDL_SetRenderDrawColor(m_pRenderer, 210, 81, 88, 0xFF);

  SDL_RenderClear(m_pRenderer); // clear the renderer to the draw colour

  env->draw();

  SDL_RenderPresent(m_pRenderer);  //draw to the screen
}

void Game::update() {
  /*
   //loop through and update our objects
   for(size_t i = 0; i < m_gameObjects.size(); i++)
   {
     m_gameObjects[i]->update();
   }
  */

    env->update();

}

void Game::clean() {
  std::cout << "Game: cleaning game\n";
  /*
  for (size_t i = 0; i < m_gameObjects.size(); i++) {
    m_gameObjects[i]->clean();
  }
  
  m_gameObjects.clear();
  */
  //destroy fonts
  /*
  SDL_DestroyTexture(scoreText);
  SDL_DestroyTexture(highScoreText);
  TTF_Quit();
  */
  env->clean();
  delete TheEnvironment::Instance();
  
  SDL_DestroyWindow (m_pWindow);
  SDL_DestroyRenderer (m_pRenderer);
  SDL_Quit();
}

void Game::handleEvents()
{
  TheInputHandler::Instance()->update();
}

void Game::quit() {
  m_bRunning = false;
}
