#include "Game.h"
//#include "SoundMixer.h"

#include "UI.h"

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

  if (fullscreen) {
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
   UIHeight = 200;
   frameTime = 0;

   
   srand (time(NULL));

   //setup environment
   env = TheEnvironment::Instance();
   env->setup(10,40,15, getWindowHeight(), getWindowWidth(), 25);
   std::cout << "Game.init() - env->setup() complete\n";

   //setup UI
   ui = new UI();
   std::cout << "Game.init() - ui->setup() complete\n";

   //load sounds into the soundMixer
   loadSounds();
   
   return true;
}

void Game::loadSounds()
{
  TheSoundMixer::Instance()->load("Assets/Audio/synthc.wav", "0", SOUND_SFX); // c
  TheSoundMixer::Instance()->load("Assets/Audio/synthd.wav", "1", SOUND_SFX); // d
  TheSoundMixer::Instance()->load("Assets/Audio/synthe.wav", "2", SOUND_SFX); // ey
}


void Game::render()
{
  SDL_SetRenderDrawColor(m_pRenderer, 210, 81, 88, 0xFF);

  SDL_RenderClear(m_pRenderer); // clear the renderer to the draw colour

  env->draw();

  ui->draw();

  SDL_RenderPresent(m_pRenderer);  //draw to the screen
}

void Game::update() {
  
  env->update();
  ui->update();
  TheSoundMixer::Instance()->playQueuedGenotypes();
}

void Game::clean() {
  std::cout << "Game: cleaning game\n";

  env->clean();
  delete TheEnvironment::Instance();

  ui->clean();
  delete ui;
  
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
