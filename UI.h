#ifndef _UI_
#define _UI_
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "SDL2/SDL2_gfxPrimitives.h" 

#include "GameObject.h"
#include "Game.h"
/*#include "Microbe.h"
  #include "FoodSource.h"*/
//#include "Environment.h"


#include <iostream>
#include <vector>

class Environment;

class UI
{
public:

int microbeIndex;
int foodEatenPercentage;

 //text
  TTF_Font* fontTTF; //this opens a font style and sets a size
  SDL_Color textColour = {0,0,0};  // this is the color in rgb format

  
  SDL_Surface* microbeNumberMessage;
  SDL_Texture* microbeNumberText; 
  SDL_Rect microbeNumberRect;

  SDL_Surface* widthLabelMessage;
  SDL_Texture* widthLabelText;
  SDL_Rect widthLabelRect;

  SDL_Surface* widthMessage;
  SDL_Texture* widthText;
  SDL_Rect widthRect;

  SDL_Surface* speedLabelMessage;
  SDL_Texture* speedLabelText;
  SDL_Rect speedLabelRect;

  SDL_Surface* speedMessage;
  SDL_Texture* speedText;
  SDL_Rect speedRect;

  SDL_Surface* childLabelMessage;
  SDL_Texture* childLabelText;
  SDL_Rect childLabelRect;

  SDL_Surface* childMessage;
  SDL_Texture* childText;
  SDL_Rect childRect;

  SDL_Surface* lifetimeMessage;
  SDL_Texture* lifetimeText;
  SDL_Rect lifetimeRect;

  SDL_Surface* lifetimeLabelMessage;
  SDL_Texture* lifetimeLabelText;
  SDL_Rect lifetimeLabelRect;

  SDL_Surface* statusLabelMessage;
  SDL_Texture* statusLabelText;
  SDL_Rect statusLabelRect;

  SDL_Surface* statusMessage;
  SDL_Texture* statusText;
  SDL_Rect statusRect;

  SDL_Surface* foodLabelMessage;
  SDL_Texture* foodLabelText;
  SDL_Rect foodLabelRect;

  SDL_Surface* foodMessage;
  SDL_Texture* foodText;
  SDL_Rect foodRect;

  SDL_Surface* fitnessLabelMessage;
  SDL_Texture* fitnessLabelText;
  SDL_Rect fitnessLabelRect;

  SDL_Surface* fitnessMessage;
  SDL_Texture* fitnessText;
  SDL_Rect fitnessRect;

  SDL_Surface* gene0Message;
  SDL_Texture* gene0Text;
  SDL_Rect gene0Rect;

  SDL_Surface* gene1Message;
  SDL_Texture* gene1Text;
  SDL_Rect gene1Rect;

  SDL_Surface* gene2Message;
  SDL_Texture* gene2Text;
  SDL_Rect gene2Rect;

  SDL_Surface* gene3Message;
  SDL_Texture* gene3Text;
  SDL_Rect gene3Rect;


public:
  UI();
  
  void draw();

  void update();

void initText();

void clean();
};

#endif
