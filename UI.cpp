#include "UI.h"

#include "Environment.h"

UI::UI() :
    microbeIndex(0), foodEatenPercentage(0), displayStats(false), displayHelp(true), simulationStartTime(SDL_GetTicks()), lastStatsUpdateTime(0)
{
  initText();
}

void UI::initText()
{
  if(TTF_Init()==-1) {
    printf("TTF_Init: %s\n", TTF_GetError());
    exit(2);
  }
  
  fontTTF = TTF_OpenFont("Assets/brandon_reg.otf", 96);
  if (fontTTF == NULL) {
    fprintf(stderr, "error: font not found\n");
  }
  
  microbeNumberMessage = TTF_RenderText_Blended(fontTTF, "1", textColour); // as TTF_RenderText_Blended could only be used on SDL_Surface then you have to create the surface first
  microbeNumberText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), microbeNumberMessage); 
  microbeNumberRect.x = 10;  //controls the rect's x coordinate 
  microbeNumberRect.y = TheGame::Instance()->getWindowHeight(); // controls the rect's y coordinte
  microbeNumberRect.w = TheGame::Instance()->getWindowWidth()/12 - 20; // controls the width of the rect
  microbeNumberRect.h = TheGame::Instance()->getWindowWidth()/12; // controls the height of the rect


  widthLabelMessage = TTF_RenderText_Blended(fontTTF, "Diameter: ", textColour); // as TTF_RenderText_Blended could only be used on SDL_Surface then you have to create the surface first
  widthLabelText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), widthLabelMessage); 
  widthLabelRect.x = 10;  //controls the rect's x coordinate 
  widthLabelRect.y = TheGame::Instance()->getWindowHeight() + (TheGame::Instance()->getUIHeight()/10)*2 + 6; // controls the rect's y coordinte
  widthLabelRect.w = TheGame::Instance()->getWindowWidth()/6;  // controls the width of the rect
  widthLabelRect.h = (TheGame::Instance()->getUIHeight()/10)*2; // controls the height of the rect
  
  widthMessage = TTF_RenderText_Blended(fontTTF, " - ", textColour); // as TTF_RenderText_Blended could only be used on SDL_Surface then you have to create the surface first
  widthText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), widthMessage); 
  widthRect.x = TheGame::Instance()->getWindowWidth()/6 + 10;  //controls the rect's x coordinate 
  widthRect.y = TheGame::Instance()->getWindowHeight() + (TheGame::Instance()->getUIHeight()/10)*2 + 6; // controls the rect's y coordinte
  widthRect.w = TheGame::Instance()->getWindowWidth()/9;  // controls the width of the rect
  widthRect.h = (TheGame::Instance()->getUIHeight()/10)*2; // controls the height of the rect

  speedLabelMessage = TTF_RenderText_Blended(fontTTF, "Speed:    ", textColour); // as TTF_RenderText_Blended could only be used on SDL_Surface then you have to create the surface first
  speedLabelText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), speedLabelMessage); 
  speedLabelRect.x = 10;  //controls the rect's x coordinate 
  speedLabelRect.y = TheGame::Instance()->getWindowHeight() + (TheGame::Instance()->getUIHeight()/10)*4  + 4; // controls the rect's y coordinte
  speedLabelRect.w = TheGame::Instance()->getWindowWidth()/6;  // controls the width of the rect
  speedLabelRect.h = (TheGame::Instance()->getUIHeight()/10)*2; // controls the height of the rect
  
  speedMessage = TTF_RenderText_Blended(fontTTF, "text: -", textColour); // as TTF_RenderText_Blended could only be used on SDL_Surface then you have to create the surface first
  speedText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), speedMessage); 
  speedRect.x = TheGame::Instance()->getWindowWidth()/6 + 10;  //controls the rect's x coordinate 
  speedRect.y = TheGame::Instance()->getWindowHeight() + (TheGame::Instance()->getUIHeight()/10)*4 + 4; // controls the rect's y coordinte
  speedRect.w = TheGame::Instance()->getWindowWidth()/9;  // controls the width of the rect
  speedRect.h = (TheGame::Instance()->getUIHeight()/10)*2; // controls the height of the rect

  childLabelMessage = TTF_RenderText_Blended(fontTTF, "Children: ", textColour); // as TTF_RenderText_Blended could only be used on SDL_Surface then you have to create the surface first
  childLabelText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), childLabelMessage); 
  childLabelRect.x = 10;  //controls the rect's x coordinate 
  childLabelRect.y = TheGame::Instance()->getWindowHeight() + (TheGame::Instance()->getUIHeight()/10)*6 + 4; // controls the rect's y coordinte
  childLabelRect.w = TheGame::Instance()->getWindowWidth()/6; // controls the width of the rect
  childLabelRect.h = (TheGame::Instance()->getUIHeight()/10)*2; // controls the height of the rect
  
  childMessage = TTF_RenderText_Blended(fontTTF, "text: -", textColour); // as TTF_RenderText_Blended could only be used on SDL_Surface then you have to create the surface first
  childText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), childMessage); 
  childRect.x = TheGame::Instance()->getWindowWidth()/6 + 10;  //controls the rect's x coordinate 
  childRect.y = TheGame::Instance()->getWindowHeight() + (TheGame::Instance()->getUIHeight()/10)*6  + 4; // controls the rect's y coordinte
  childRect.w = TheGame::Instance()->getWindowWidth()/9; // controls the width of the rect
  childRect.h = (TheGame::Instance()->getUIHeight()/10)*2; // controls the height of the rect

  lifetimeLabelMessage = TTF_RenderText_Blended(fontTTF, "Lifetime: ", textColour); // as TTF_RenderText_Blended could only be used on SDL_Surface then you have to create the surface first
  lifetimeLabelText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), lifetimeLabelMessage); 
  lifetimeLabelRect.x = 10;  //controls the rect's x coordinate 
  lifetimeLabelRect.y = TheGame::Instance()->getWindowHeight() + (TheGame::Instance()->getUIHeight()/10)*8; // controls the rect's y coordinte
  lifetimeLabelRect.w = TheGame::Instance()->getWindowWidth()/6; // controls the width of the rect
  lifetimeLabelRect.h = (TheGame::Instance()->getUIHeight()/10)*2; // controls the height of the rect

  lifetimeMessage = TTF_RenderText_Blended(fontTTF, "text: -", textColour); // as TTF_RenderText_Blended could only be used on SDL_Surface then you have to create the surface first
  lifetimeText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), lifetimeMessage); 
  lifetimeRect.x = TheGame::Instance()->getWindowWidth()/6 + 10;  //controls the rect's x coordinate 
  lifetimeRect.y = TheGame::Instance()->getWindowHeight() + (TheGame::Instance()->getUIHeight()/10)*8; // controls the rect's y coordinte
  lifetimeRect.w = TheGame::Instance()->getWindowWidth()/9; // controls the width of the rect
  lifetimeRect.h = (TheGame::Instance()->getUIHeight()/10)*2; // controls the height of the rect

  statusLabelMessage = TTF_RenderText_Blended(fontTTF, "Status: ", textColour); // as TTF_RenderText_Blended could only be used on SDL_Surface then you have to create the surface first
  statusLabelText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), statusLabelMessage); 
  statusLabelRect.x = TheGame::Instance()->getWindowWidth()/3;  //controls the rect's x coordinate 
  statusLabelRect.y = TheGame::Instance()->getWindowHeight(); // controls the rect's y coordinte
  statusLabelRect.w = TheGame::Instance()->getWindowWidth()/6; // controls the width of the rect
  statusLabelRect.h = (TheGame::Instance()->getUIHeight()/10)*2; // controls the height of the rect

  statusMessage = TTF_RenderText_Blended(fontTTF, "Seeking food", textColour); // as TTF_RenderText_Blended could only be used on SDL_Surface then you have to create the surface first
  statusText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), statusMessage); 
  statusRect.x = TheGame::Instance()->getWindowWidth()/2;  //controls the rect's x coordinate 
  statusRect.y = TheGame::Instance()->getWindowHeight(); // controls the rect's y coordinte
  statusRect.w = TheGame::Instance()->getWindowWidth()/2; // controls the width of the rect
  statusRect.h = (TheGame::Instance()->getUIHeight()/10)*2; // controls the height of the rect

  foodLabelMessage = TTF_RenderText_Blended(fontTTF, "Food collected for reproduction: ", textColour); // as TTF_RenderText_Blended could only be used on SDL_Surface then you have to create the surface first
  foodLabelText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), foodLabelMessage); 
  foodLabelRect.x = 250;  //controls the rect's x coordinate 
  foodLabelRect.y = TheGame::Instance()->getWindowHeight() + (TheGame::Instance()->getUIHeight()/10)*2 + 6; // controls the rect's y coordinte
  foodLabelRect.w = TheGame::Instance()->getWindowWidth()/3 + 50; // controls the width of the rect
  foodLabelRect.h = (TheGame::Instance()->getUIHeight()/10)*2; // controls the height of the rect

  foodMessage = TTF_RenderText_Blended(fontTTF, "89%", textColour); // as TTF_RenderText_Blended could only be used on SDL_Surface then you have to create the surface first
  foodText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), foodMessage); 
  foodRect.x = 250  + (TheGame::Instance()->getUIHeight()/10)*2 + TheGame::Instance()->getWindowWidth()/3 + 10;  //controls the rect's x coordinate 
  foodRect.y = TheGame::Instance()->getWindowHeight() + (TheGame::Instance()->getUIHeight()/10)*2 + 6; // controls the rect's y coordinte
  foodRect.w = TheGame::Instance()->getWindowWidth()/17; // controls the width of the rect
  foodRect.h = (TheGame::Instance()->getUIHeight()/10)*2; // controls the height of the rect

  fitnessLabelMessage = TTF_RenderText_Blended(fontTTF, "Genes (music notes) fitness rating: ", textColour); // as TTF_RenderText_Blended could only be used on SDL_Surface then you have to create the surface first
  fitnessLabelText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), fitnessLabelMessage); 
  fitnessLabelRect.x = 250;  //controls the rect's x coordinate 
  fitnessLabelRect.y = TheGame::Instance()->getWindowHeight() + (TheGame::Instance()->getUIHeight()/10)*2 + 70; // controls the rect's y coordinte
  fitnessLabelRect.w = TheGame::Instance()->getWindowWidth()/3 + 50; // controls the width of the rect
  fitnessLabelRect.h = (TheGame::Instance()->getUIHeight()/10)*2; // controls the height of the rect
  
  fitnessMessage = TTF_RenderText_Blended(fontTTF, "3/4", textColour); // as TTF_RenderText_Blended could only be used on SDL_Surface then you have to create the surface first
  fitnessText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), fitnessMessage); 
  fitnessRect.x = 250  + (TheGame::Instance()->getUIHeight()/10)*2 + TheGame::Instance()->getWindowWidth()/3 + 10;  //controls the rect's x coordinate 
  fitnessRect.y = TheGame::Instance()->getWindowHeight() + (TheGame::Instance()->getUIHeight()/10)*2 + 70; // controls the rect's y coordinte
  fitnessRect.w = TheGame::Instance()->getWindowWidth()/17; // controls the width of the rect
  fitnessRect.h = (TheGame::Instance()->getUIHeight()/10)*2; // controls the height of the rect

  gene0Message = TTF_RenderText_Blended(fontTTF, "A", textColour); // as TTF_RenderText_Blended could only be used on SDL_Surface then you have to create the surface first
  gene0Text = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), gene0Message); 
  gene0Rect.x = 298;  //controls the rect's x coordinate 
  gene0Rect.y = 755; // controls the rect's y coordinte
  gene0Rect.w = 23; // controls the width of the rect
  gene0Rect.h = 29; // controls the height of the rect

  gene1Message = TTF_RenderText_Blended(fontTTF, "B", textColour); // as TTF_RenderText_Blended could only be used on SDL_Surface then you have to create the surface first
  gene1Text = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), gene1Message); 
  gene1Rect.x = 355;  //controls the rect's x coordinate 
  gene1Rect.y = 755; // controls the rect's y coordinte
  gene1Rect.w = 23; // controls the width of the rect
  gene1Rect.h = 29; // controls the height of the rect

  gene2Message = TTF_RenderText_Blended(fontTTF, "C", textColour); // as TTF_RenderText_Blended could only be used on SDL_Surface then you have to create the surface first
  gene2Text = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), gene2Message); 
  gene2Rect.x = 412;  //controls the rect's x coordinate 
  gene2Rect.y = 755; // controls the rect's y coordinte
  gene2Rect.w = 23; // controls the width of the rect
  gene2Rect.h = 29; // controls the height of the rect

  gene3Message = TTF_RenderText_Blended(fontTTF, "D", textColour); // as TTF_RenderText_Blended could only be used on SDL_Surface then you have to create the surface first
  gene3Text = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), gene3Message); 
  gene3Rect.x = 469;  //controls the rect's x coordinate 
  gene3Rect.y = 755; // controls the rect's y coordinte
  gene3Rect.w = 23; // controls the width of the rect
  gene3Rect.h = 29; // controls the height of the rect

  
  //stats
  statsLabelMessage = TTF_RenderText_Blended(fontTTF, "Stats", textColour); // as TTF_RenderText_Blended could only be used on SDL_Surface then you have to create the surface first
  statsLabelText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), statsLabelMessage); 
  statsLabelRect.x = 15;  //controls the rect's x coordinate 
  statsLabelRect.y = 0; // controls the rect's y coordinte
  statsLabelRect.w = 65; // controls the width of the rect
  statsLabelRect.h = (TheGame::Instance()->getUIHeight()/10)*2; // controls the height of the rect

  maxFitnessAchievedMessage = TTF_RenderText_Blended(fontTTF, "Max fitness achieved:", textColour); // as TTF_RenderText_Blended could only be used on SDL_Surface then you have to create the surface first
  maxFitnessAchievedText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), maxFitnessAchievedMessage); 
  maxFitnessAchievedRect.x = 10;  //controls the rect's x coordinate 
  maxFitnessAchievedRect.y = 40; // controls the rect's y coordinte
  maxFitnessAchievedRect.w = 195; // controls the width of the rect
  maxFitnessAchievedRect.h = (TheGame::Instance()->getUIHeight()/10)*2; // controls the height of the rect

  maxFitnessAchievedLabelMessage = TTF_RenderText_Blended(fontTTF, "false", textColour); // as TTF_RenderText_Blended could only be used on SDL_Surface then you have to create the surface first
  maxFitnessAchievedLabelText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), maxFitnessAchievedLabelMessage); 
  maxFitnessAchievedLabelRect.x = 10 + 195 + 10;  //controls the rect's x coordinate 
  maxFitnessAchievedLabelRect.y = 40; // controls the rect's y coordinte
  maxFitnessAchievedLabelRect.w = TheGame::Instance()->getWindowWidth()/15; // controls the width of the rect
  maxFitnessAchievedLabelRect.h = (TheGame::Instance()->getUIHeight()/10)*2; // controls the height of the rect

  //ACHIEVED AFTER
  //Y: 70
  numMicrobesLabelMessage = TTF_RenderText_Blended(fontTTF, "After:", textColour); // as TTF_RenderText_Blended could only be used on SDL_Surface then you have to create the surface first
  numMicrobesLabelText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), numMicrobesLabelMessage); 
  numMicrobesLabelRect.x = 10;  //controls the rect's x coordinate 
  numMicrobesLabelRect.y = 70; // controls the rect's y coordinte
  numMicrobesLabelRect.w = 60; // controls the width of the rect
  numMicrobesLabelRect.h = (TheGame::Instance()->getUIHeight()/10)*2; // controls the height of the rect

  numMicrobesMessage = TTF_RenderText_Blended(fontTTF, "17 microbes", textColour); // as TTF_RenderText_Blended could only be used on SDL_Surface then you have to create the surface first
  numMicrobesText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), numMicrobesMessage); 
  numMicrobesRect.x = 10 + 60 + 10;  //controls the rect's x coordinate 
  numMicrobesRect.y = 70; // controls the rect's y coordinte
  numMicrobesRect.w = 100; // controls the width of the rect
  numMicrobesRect.h = (TheGame::Instance()->getUIHeight()/10)*2; // controls the height of the rect

  //AVG FITNESS
  avgFitnessLabelMessage = TTF_RenderText_Blended(fontTTF, "Average fitness:", textColour); // as TTF_RenderText_Blended could only be used on SDL_Surface then you have to create the surface first
  avgFitnessLabelText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), avgFitnessLabelMessage); 
  avgFitnessLabelRect.x = 10;  //controls the rect's x coordinate 
  avgFitnessLabelRect.y = 110; // controls the rect's y coordinte
  avgFitnessLabelRect.w = 150; // controls the width of the rect
  avgFitnessLabelRect.h = (TheGame::Instance()->getUIHeight()/10)*2; // controls the height of the rect

  avgFitnessMessage = TTF_RenderText_Blended(fontTTF, "1.0", textColour); // as TTF_RenderText_Blended could only be used on SDL_Surface then you have to create the surface first
  avgFitnessText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), avgFitnessMessage); 
  avgFitnessRect.x = 150 + 20;  //controls the rect's x coordinate 
  avgFitnessRect.y = 110; // controls the rect's y coordinte
  avgFitnessRect.w = TheGame::Instance()->getWindowWidth()/15-10; // controls the width of the rect
  avgFitnessRect.h = (TheGame::Instance()->getUIHeight()/10)*2; // controls the height of the rect

  //MiN
  //Y: 140
  minFitnessLabelMessage = TTF_RenderText_Blended(fontTTF, "Lowest fitness: ", textColour); // as TTF_RenderText_Blended could only be used on SDL_Surface then you have to create the surface first
  minFitnessLabelText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), minFitnessLabelMessage);
  minFitnessLabelRect.x = 10;  //controls the rect's x coordinate 
  minFitnessLabelRect.y = 140; // controls the rect's y coordinte
  minFitnessLabelRect.w = 150; // controls the width of the rect
  minFitnessLabelRect.h = (TheGame::Instance()->getUIHeight()/10)*2; // controls the height of the rect

  minFitnessMessage = TTF_RenderText_Blended(fontTTF, "1.0", textColour); // as TTF_RenderText_Blended could only be used on SDL_Surface then you have to create the surface first
  minFitnessText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), minFitnessMessage); 
  minFitnessRect.x = 150 + 20;  //controls the rect's x coordinate 
  minFitnessRect.y = 140; // controls the rect's y coordinte
  minFitnessRect.w = TheGame::Instance()->getWindowWidth()/15-10; // controls the width of the rect
  minFitnessRect.h = (TheGame::Instance()->getUIHeight()/10)*2; // controls the height of the rect
  
  //Max
  //Y: 170
  maxFitnessLabelMessage = TTF_RenderText_Blended(fontTTF, "Highest fitness:", textColour); // as TTF_RenderText_Blended could only be used on SDL_Surface then you have to create the surface first
  maxFitnessLabelText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), maxFitnessLabelMessage);
  maxFitnessLabelRect.x = 10;  //controls the rect's x coordinate 
  maxFitnessLabelRect.y = 170; // controls the rect's y coordinte
  maxFitnessLabelRect.w = 150; // controls the width of the rect
  maxFitnessLabelRect.h = (TheGame::Instance()->getUIHeight()/10)*2; // controls the height of the rect

  maxFitnessMessage = TTF_RenderText_Blended(fontTTF, "1.0", textColour); // as TTF_RenderText_Blended could only be used on SDL_Surface then you have to create the surface first
  maxFitnessText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), maxFitnessMessage); 
  maxFitnessRect.x = 150 + 20;  //controls the rect's x coordinate 
  maxFitnessRect.y = 170; // controls the rect's y coordinte
  maxFitnessRect.w = TheGame::Instance()->getWindowWidth()/15-10; // controls the width of the rect
  maxFitnessRect.h = (TheGame::Instance()->getUIHeight()/10)*2; // controls the height of the rect



  //av lifespan
  avgLifespanLabelMessage = TTF_RenderText_Blended(fontTTF, "Average lifetime:", textColour); // as TTF_RenderText_Blended could only be used on SDL_Surface then you have to create the surface first
  avgLifespanLabelText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), avgLifespanLabelMessage); 
  avgLifespanLabelRect.x = 10;  //controls the rect's x coordinate 
  avgLifespanLabelRect.y = 210; // controls the rect's y coordinte
  avgLifespanLabelRect.w = 160; // controls the width of the rect
  avgLifespanLabelRect.h = (TheGame::Instance()->getUIHeight()/10)*2; // controls the height of the rect

  avgLifespanMessage = TTF_RenderText_Blended(fontTTF, "00:00", textColour); // as TTF_RenderText_Blended could only be used on SDL_Surface then you have to create the surface first
  avgLifespanText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), avgLifespanMessage); 
  avgLifespanRect.x = 160 + 20;  //controls the rect's x coordinate 
  avgLifespanRect.y = 210; // controls the rect's y coordinte
  avgLifespanRect.w = 60; // controls the width of the rect
  avgLifespanRect.h = (TheGame::Instance()->getUIHeight()/10)*2; // controls the height of the rect

  //Time elapsed
  //250
  timeElapsedLabelMessage = TTF_RenderText_Blended(fontTTF, "Time elapsed:      ", textColour); // as TTF_RenderText_Blended could only be used on SDL_Surface then you have to create the surface first
  timeElapsedLabelText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), timeElapsedLabelMessage); 
  timeElapsedLabelRect.x = 10;  //controls the rect's x coordinate 
  timeElapsedLabelRect.y = 250; // controls the rect's y coordinte
  timeElapsedLabelRect.w = 160; // controls the width of the rect
  timeElapsedLabelRect.h = (TheGame::Instance()->getUIHeight()/10)*2; // controls the height of the rect

  timeElapsedMessage = TTF_RenderText_Blended(fontTTF, "00:00", textColour); // as TTF_RenderText_Blended could only be used on SDL_Surface then you have to create the surface first
  timeElapsedText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), timeElapsedMessage); 
  timeElapsedRect.x = 160 + 20;  //controls the rect's x coordinate 
  timeElapsedRect.y = 250; // controls the rect's y coordinte
  timeElapsedRect.w = 60; // controls the width of the rect
  timeElapsedRect.h = (TheGame::Instance()->getUIHeight()/10)*2; // controls the height of the rect
  
  //help
  helpLabelMessage = TTF_RenderText_Blended(fontTTF, "Help", textColour); // as TTF_RenderText_Blended could only be used on SDL_Surface then you have to create the surface first
  helpLabelText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), helpLabelMessage); 
  helpLabelRect.x = 15;  //controls the rect's x coordinate 
  helpLabelRect.y = 0; // controls the rect's y coordinte
  helpLabelRect.w = 60; // controls the width of the rect
  helpLabelRect.h = (TheGame::Instance()->getUIHeight()/10)*2; // controls the height of the rect

  statsMessage = TTF_RenderText_Blended(fontTTF, "Stats", textColour); // as TTF_RenderText_Blended could only be used on SDL_Surface then you have to create the surface first
  statsText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), statsMessage); 
  statsRect.x = 10;  //controls the rect's x coordinate 
  statsRect.y = 40; // controls the rect's y coordinte
  statsRect.w = 50; // controls the width of the rect
  statsRect.h = (TheGame::Instance()->getUIHeight()/10)*2; // controls the height of the rect

  /*
  helpMessage = TTF_RenderText_Blended(fontTTF, "Help", textColour); // as TTF_RenderText_Blended could only be used on SDL_Surface then you have to create the surface first
  helpText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), helpMessage); 
  helpRect.x = 10;  //controls the rect's x coordinate 
  helpRect.y = 70; // controls the rect's y coordinte
  helpRect.w = 45; // controls the width of the rect
  helpRect.h = (TheGame::Instance()->getUIHeight()/10)*2; // controls the height of the rect
  */

  gridMessage = TTF_RenderText_Blended(fontTTF, "Grid", textColour); // as TTF_RenderText_Blended could only be used on SDL_Surface then you have to create the surface first
  gridText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), gridMessage); 
  gridRect.x = 10;  //controls the rect's x coordinate 
  gridRect.y = 80; // controls the rect's y coordinte
  gridRect.w = 45; // controls the width of the rect
  gridRect.h = (TheGame::Instance()->getUIHeight()/10)*2; // controls the height of the rect

  terrainMessage = TTF_RenderText_Blended(fontTTF, "Terrain", textColour); // as TTF_RenderText_Blended could only be used on SDL_Surface then you have to create the surface first
  terrainText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), terrainMessage); 
  terrainRect.x = 10;  //controls the rect's x coordinate 
  terrainRect.y = 110; // controls the rect's y coordinte
  terrainRect.w = 68; // controls the width of the rect
  terrainRect.h = (TheGame::Instance()->getUIHeight()/10)*2; // controls the height of the rect

  pathMessage = TTF_RenderText_Blended(fontTTF, "Path", textColour); // as TTF_RenderText_Blended could only be used on SDL_Surface then you have to create the surface first
  pathText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), pathMessage); 
  pathRect.x = 10;  //controls the rect's x coordinate 
  pathRect.y = 140; // controls the rect's y coordinte
  pathRect.w = 45; // controls the width of the rect
  pathRect.h = (TheGame::Instance()->getUIHeight()/10)*2; // controls the height of the rect

  READMEMessage = TTF_RenderText_Blended(fontTTF, "README", textColour); // as TTF_RenderText_Blended could only be used on SDL_Surface then you have to create the surface first
  READMEText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), READMEMessage); 
  READMERect.x = 10;  //controls the rect's x coordinate 
  READMERect.y = 180; // controls the rect's y coordinte
  READMERect.w = 80; // controls the width of the rect
  READMERect.h = (TheGame::Instance()->getUIHeight()/10)*2; // controls the height of the rect
}

void UI::draw()
{
  //UI box background
  boxRGBA(TheGame::Instance()->getRenderer(),
          0, TheGame::Instance()->getWindowHeight(),
          TheGame::Instance()->getWindowWidth(), TheGame::Instance()->getUIHeight() + TheGame::Instance()->getWindowHeight(),
          229, 154, 157, 255);

  
  //selected microbe number box

  //deallocate previous frame's texture
  if( microbeNumberText != NULL ) SDL_DestroyTexture( microbeNumberText );
  
  //if no microbe is selected draw in gray
  if (microbeIndex == -1) {
    boxRGBA(TheGame::Instance()->getRenderer(),
            0, TheGame::Instance()->getWindowHeight(),
            TheGame::Instance()->getWindowWidth()/12-1,
            TheGame::Instance()->getWindowHeight() + TheGame::Instance()->getWindowWidth()/12-1,
            102, 102, 102, 255);

    //set microbe number to -, as none have been selected
    microbeNumberMessage = TTF_RenderText_Blended(fontTTF, "-", textColour);
    microbeNumberText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), microbeNumberMessage);
    SDL_RenderCopy(TheGame::Instance()->getRenderer(), microbeNumberText, NULL, &microbeNumberRect);
    SDL_FreeSurface( microbeNumberMessage );

  }
  else //draw same colour as selected microbe
  {
    boxRGBA(TheGame::Instance()->getRenderer(),
            0, TheGame::Instance()->getWindowHeight(),
            TheGame::Instance()->getWindowWidth()/12-1,
            TheGame::Instance()->getWindowHeight() + TheGame::Instance()->getWindowWidth()/12-1,
            TheEnvironment::Instance()->microbes[microbeIndex]->colourR,
            TheEnvironment::Instance()->microbes[microbeIndex]->colourG,
            TheEnvironment::Instance()->microbes[microbeIndex]->colourB,
            TheEnvironment::Instance()->microbes[microbeIndex]->colourA);

    //set microbe number
    microbeNumberMessage = TTF_RenderText_Blended(fontTTF, std::to_string(TheEnvironment::Instance()->microbes[microbeIndex]->microbeID).c_str(), textColour);
    microbeNumberText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), microbeNumberMessage);
    SDL_RenderCopy(TheGame::Instance()->getRenderer(), microbeNumberText, NULL, &microbeNumberRect); 
    SDL_FreeSurface( microbeNumberMessage );
  }

  //draw outline box for microbe number
  rectangleRGBA(TheGame::Instance()->getRenderer(),
                0, TheGame::Instance()->getWindowHeight(),
                TheGame::Instance()->getWindowWidth()/12,
                TheGame::Instance()->getWindowHeight() + TheGame::Instance()->getWindowWidth()/12,
                0, 0, 0, 255);
  
  //line dividing simulation and UI
  lineRGBA(TheGame::Instance()->getRenderer(),
           0, TheGame::Instance()->getWindowHeight(),
           TheGame::Instance()->getWindowWidth(), TheGame::Instance()->getWindowHeight(),
           0, 0, 0, 255);

  //GENES
  //if no microbe is selected draw boxes in grey
  if (microbeIndex == -1) {
    boxRGBA(TheGame::Instance()->getRenderer(), 290, 750, 328, 788, 102, 102, 102, 255);

    boxRGBA(TheGame::Instance()->getRenderer(), 347, 750, 385, 788, 102, 102, 102, 255);

    boxRGBA(TheGame::Instance()->getRenderer(), 404, 750, 442, 788, 102, 102, 102, 255);

    boxRGBA(TheGame::Instance()->getRenderer(), 461, 750, 499, 788, 102, 102, 102, 255);
  }
  else //a microbe is selected, so draw boxes in either green or red depending on whether the gene is correct
  {
    if (TheEnvironment::Instance()->microbes[microbeIndex]->mga.isGenotypeCorrect(0))
      boxRGBA(TheGame::Instance()->getRenderer(), 290, 750, 328, 788, 0, 255, 0, 255);
    else
      boxRGBA(TheGame::Instance()->getRenderer(), 290, 750, 328, 788, 255, 0, 0, 255);

    if (TheEnvironment::Instance()->microbes[microbeIndex]->mga.isGenotypeCorrect(1))
      boxRGBA(TheGame::Instance()->getRenderer(), 347, 750, 385, 788, 0, 255, 0, 255);
    else
      boxRGBA(TheGame::Instance()->getRenderer(), 347, 750, 385, 788, 255, 0, 0, 255);

    if (TheEnvironment::Instance()->microbes[microbeIndex]->mga.isGenotypeCorrect(2))
      boxRGBA(TheGame::Instance()->getRenderer(), 404, 750, 442, 788, 0, 255, 0, 255);
    else
      boxRGBA(TheGame::Instance()->getRenderer(), 404, 750, 442, 788, 255, 0, 0, 255);
                
    if (TheEnvironment::Instance()->microbes[microbeIndex]->mga.isGenotypeCorrect(3))
      boxRGBA(TheGame::Instance()->getRenderer(), 461, 750, 499, 788, 0, 255, 0, 255);
    else
      boxRGBA(TheGame::Instance()->getRenderer(), 461, 750, 499, 788, 255, 0, 0, 255);
  }

  //gene box black outlines
  rectangleRGBA(TheGame::Instance()->getRenderer(), 290, 750, 329, 789, 0, 0, 0, 255);
  rectangleRGBA(TheGame::Instance()->getRenderer(), 347, 750, 386, 789, 0, 0, 0, 255);
  rectangleRGBA(TheGame::Instance()->getRenderer(), 404, 750, 443, 789, 0, 0, 0, 255);
  rectangleRGBA(TheGame::Instance()->getRenderer(), 461, 750, 500, 789, 0, 0, 0, 255);
  
  ///FOOD EATEN
  if (microbeIndex == -1) {
    boxRGBA(TheGame::Instance()->getRenderer(),
            240, TheGame::Instance()->getWindowHeight() + (TheGame::Instance()->getUIHeight()/10)*2 + 44,
            549, TheGame::Instance()->getWindowHeight() + (TheGame::Instance()->getUIHeight()/10)*2 + 63,
            102, 102, 102, 255);
  }
  else
  {
    float barFull = 0.0f;

    barFull = 310 - (310 * foodEatenPercentage/100);
  
    //red bar for food eaten
    boxRGBA(TheGame::Instance()->getRenderer(),
            549-barFull, TheGame::Instance()->getWindowHeight() + (TheGame::Instance()->getUIHeight()/10)*2 + 44,
            549, TheGame::Instance()->getWindowHeight() + (TheGame::Instance()->getUIHeight()/10)*2 + 63,
            255, 0, 0, 255);

    if (barFull == 310) barFull = 309;
  
    //green bar for food eaten
    boxRGBA(TheGame::Instance()->getRenderer(),
            240, TheGame::Instance()->getWindowHeight() + (TheGame::Instance()->getUIHeight()/10)*2 + 44,
            549 - barFull, TheGame::Instance()->getWindowHeight() + (TheGame::Instance()->getUIHeight()/10)*2 + 63,
            0, 255, 0, 255);
  }
  //draw outline box for food eaten
  rectangleRGBA(TheGame::Instance()->getRenderer(),
                240, TheGame::Instance()->getWindowHeight() + (TheGame::Instance()->getUIHeight()/10)*2 + 44,
                550, TheGame::Instance()->getWindowHeight() + (TheGame::Instance()->getUIHeight()/10)*2 + 64,
                0, 0, 0, 255);
  
  //TEXT
  //draw width text
  SDL_RenderCopy(TheGame::Instance()->getRenderer(), widthLabelText, NULL, &widthLabelRect); 
  SDL_RenderCopy(TheGame::Instance()->getRenderer(), widthText, NULL, &widthRect); 

  //draw speed text
  SDL_RenderCopy(TheGame::Instance()->getRenderer(), speedLabelText, NULL, &speedLabelRect); 
  SDL_RenderCopy(TheGame::Instance()->getRenderer(), speedText, NULL, &speedRect); 
  
  //draw children text
  SDL_RenderCopy(TheGame::Instance()->getRenderer(), childLabelText, NULL, &childLabelRect);
  SDL_RenderCopy(TheGame::Instance()->getRenderer(), childText, NULL, &childRect);

  //draw lifetime text
  SDL_RenderCopy(TheGame::Instance()->getRenderer(), lifetimeLabelText, NULL, &lifetimeLabelRect);
  SDL_RenderCopy(TheGame::Instance()->getRenderer(), lifetimeText, NULL, &lifetimeRect);
  
  //draw microbe status text
  SDL_RenderCopy(TheGame::Instance()->getRenderer(), statusLabelText, NULL, &statusLabelRect);
  SDL_RenderCopy(TheGame::Instance()->getRenderer(), statusText, NULL, &statusRect);

  //draw food text
  SDL_RenderCopy(TheGame::Instance()->getRenderer(), foodLabelText, NULL, &foodLabelRect);
  SDL_RenderCopy(TheGame::Instance()->getRenderer(), foodText, NULL, &foodRect);

  //draw fitness text
  SDL_RenderCopy(TheGame::Instance()->getRenderer(), fitnessLabelText, NULL, &fitnessLabelRect);
  SDL_RenderCopy(TheGame::Instance()->getRenderer(), fitnessText, NULL, &fitnessRect);

  //draw gene text
  SDL_RenderCopy(TheGame::Instance()->getRenderer(), gene0Text, NULL, &gene0Rect);
  SDL_RenderCopy(TheGame::Instance()->getRenderer(), gene1Text, NULL, &gene1Rect);
  SDL_RenderCopy(TheGame::Instance()->getRenderer(), gene2Text, NULL, &gene2Rect);
  SDL_RenderCopy(TheGame::Instance()->getRenderer(), gene3Text, NULL, &gene3Rect);

  if (displayStats)
  {
    //stats box background
    boxRGBA(TheGame::Instance()->getRenderer(),
            0, 0,
            270, 289,
            229, 154, 157, 215);

    //stats box background
    rectangleRGBA(TheGame::Instance()->getRenderer(),
            -1, -1,
            271, 290,
            0, 0, 0, 255);

    //draw stats label text
    SDL_RenderCopy(TheGame::Instance()->getRenderer(), statsLabelText, NULL, &statsLabelRect);

    //underline S in stats
    lineRGBA(TheGame::Instance()->getRenderer(),
             14, 33,
             32, 33,
             0, 0, 0, 255);

        
    //draw max fitness achieved text
    SDL_RenderCopy(TheGame::Instance()->getRenderer(), maxFitnessAchievedText, NULL, &maxFitnessAchievedRect);
    SDL_RenderCopy(TheGame::Instance()->getRenderer(), maxFitnessAchievedLabelText, NULL, &maxFitnessAchievedLabelRect);

    //draw num microbes text
    SDL_RenderCopy(TheGame::Instance()->getRenderer(), numMicrobesText, NULL, &numMicrobesRect);
    SDL_RenderCopy(TheGame::Instance()->getRenderer(), numMicrobesLabelText, NULL, &numMicrobesLabelRect);
    
    //draw average population fitness text
    SDL_RenderCopy(TheGame::Instance()->getRenderer(), avgFitnessText, NULL, &avgFitnessRect);
    SDL_RenderCopy(TheGame::Instance()->getRenderer(), avgFitnessLabelText, NULL, &avgFitnessLabelRect);

    //draw min population fitness text
    SDL_RenderCopy(TheGame::Instance()->getRenderer(), minFitnessText, NULL, &minFitnessRect);
    SDL_RenderCopy(TheGame::Instance()->getRenderer(), minFitnessLabelText, NULL, &minFitnessLabelRect);
    //draw max population fitness text
    SDL_RenderCopy(TheGame::Instance()->getRenderer(), maxFitnessText, NULL, &maxFitnessRect);
    SDL_RenderCopy(TheGame::Instance()->getRenderer(), maxFitnessLabelText, NULL, &maxFitnessLabelRect);
    
    //draw average population lifespan text
    SDL_RenderCopy(TheGame::Instance()->getRenderer(), avgLifespanText, NULL, &avgLifespanRect);
    SDL_RenderCopy(TheGame::Instance()->getRenderer(), avgLifespanLabelText, NULL, &avgLifespanLabelRect);

    //draw time elapsed text
    SDL_RenderCopy(TheGame::Instance()->getRenderer(), timeElapsedText, NULL, &timeElapsedRect);
    SDL_RenderCopy(TheGame::Instance()->getRenderer(), timeElapsedLabelText, NULL, &timeElapsedLabelRect);

  }
  else if (displayHelp)
  {
    //help box background
    boxRGBA(TheGame::Instance()->getRenderer(),
            0, 0,
            100, 220,
            229, 154, 157, 215);

    //help box background
    rectangleRGBA(TheGame::Instance()->getRenderer(),
                  -1, -1,
                  101, 221,
                  0, 0, 0, 255);

    //draw help label text
    SDL_RenderCopy(TheGame::Instance()->getRenderer(), helpLabelText, NULL, &helpLabelRect);

    //underline H in help
    lineRGBA(TheGame::Instance()->getRenderer(),
             15, 33,
             37, 33,
             0, 0, 0, 255);

    //draw text
    SDL_RenderCopy(TheGame::Instance()->getRenderer(), statsText, NULL, &statsRect);
    //underline s in stats
    lineRGBA(TheGame::Instance()->getRenderer(),
             10, 73,
             22, 73,
             0, 0, 0, 255);
    
    SDL_RenderCopy(TheGame::Instance()->getRenderer(), gridText, NULL, &gridRect);
    //underline G in grid
    lineRGBA(TheGame::Instance()->getRenderer(),
             10, 113,
             28, 113,
             0, 0, 0, 255);
    
    SDL_RenderCopy(TheGame::Instance()->getRenderer(), terrainText, NULL, &terrainRect);
    //underline T in terrain
    lineRGBA(TheGame::Instance()->getRenderer(),
             10, 143,
             21, 143,
             0, 0, 0, 255);
    
    SDL_RenderCopy(TheGame::Instance()->getRenderer(), pathText, NULL, &pathRect);
    //underline P in path
    lineRGBA(TheGame::Instance()->getRenderer(),
             10, 173,
             23, 173,
             0, 0, 0, 255);
    
    SDL_RenderCopy(TheGame::Instance()->getRenderer(), READMEText, NULL, &READMERect);
    //underline R in README
    lineRGBA(TheGame::Instance()->getRenderer(),
             10, 213,
             22, 213,
             0, 0, 0, 255);
  }
}

void UI::update()
{
  //check to see if stats have been enabled/disabled
  handleInput();
  
  //reset the selected microbe index
  microbeIndex = TheEnvironment::Instance()->selectedMicrobeIndex;

  //if a microbe has been selected
  if (microbeIndex != -1)
  {
    if( widthText != NULL ) SDL_DestroyTexture( widthText );
    std::string width = std::to_string(TheEnvironment::Instance()->microbes[microbeIndex]->width/15);
    width = width.substr(0,4);
    width.insert(0," ");
    width.append(" ");
    widthMessage = TTF_RenderText_Blended(fontTTF,
                                          width.c_str(),
                                          textColour);
    widthText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), widthMessage);
    SDL_FreeSurface( widthMessage );

    if( speedText != NULL ) SDL_DestroyTexture( speedText );
    std::string speed = std::to_string(TheEnvironment::Instance()->microbes[microbeIndex]->speedMultiplier/10);
    speed = speed.substr(0,4);
    speed.insert(0," ");
    speed.append(" ");
    speedMessage = TTF_RenderText_Blended(fontTTF,
                                          speed.c_str(),
                                          textColour);
    speedText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), speedMessage);
    SDL_FreeSurface( speedMessage );


    if( childText != NULL ) SDL_DestroyTexture( childText );
    std::string children = std::to_string(TheEnvironment::Instance()->microbes[microbeIndex]->childrenProduced);
    if (children.length() == 1) children.insert(0, "0");
    children.insert(2, "  ");
    children.insert(0, "  ");
    childMessage = TTF_RenderText_Blended(fontTTF,
                                          children.c_str(),
                                          textColour);
    childText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), childMessage);
    SDL_FreeSurface( childMessage );


    if( lifetimeText != NULL ) SDL_DestroyTexture( lifetimeText );
    int lifetimeSecs = (SDL_GetTicks() - TheEnvironment::Instance()->microbes[microbeIndex]->microbeSpawnTime)/1000;
    int mins = lifetimeSecs / 60;
    int seconds = lifetimeSecs - (mins * 60);
  
    std::string lifetime = std::to_string(mins);

    if (mins < 10)
    {
      lifetime.insert(0, "0");
    }
    lifetime.append(":");
    if (seconds < 10)
    {
      lifetime.append("0");
    }

    lifetime.append(std::to_string(seconds));   

    lifetimeMessage = TTF_RenderText_Blended(fontTTF,
                                             lifetime.c_str(),
                                             textColour);
    lifetimeText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), lifetimeMessage);
    SDL_FreeSurface( lifetimeMessage );


    if( statusText != NULL ) SDL_DestroyTexture( statusText );
    int status = TheEnvironment::Instance()->microbes[microbeIndex]->currentStatus;
    std::string statusStr;
    switch (status)
    {
      case 0:
        statusStr = "seeking food                     ";
        break;
      case 1:
        statusStr = "waiting for accessible food      ";
        break;
      case 2:
        statusStr = "seeking partner                  ";
        break;
      case 3:
        statusStr = "waiting for available partner    ";
        break;
      case 4:
        statusStr = "dying                            ";
        break;
    }
    if( statusText != NULL ) SDL_DestroyTexture( statusText );
    statusMessage = TTF_RenderText_Blended(fontTTF,
                                           statusStr.c_str(),
                                           textColour);
    statusText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), statusMessage);
    SDL_FreeSurface( statusMessage );


    if( foodText != NULL ) SDL_DestroyTexture( foodText );
    foodEatenPercentage = (float)TheEnvironment::Instance()->microbes[microbeIndex]->foodEaten /
        TheEnvironment::Instance()->microbes[microbeIndex]->foodRequiredToMate * 100;
    std::string foodStr = std::to_string(foodEatenPercentage);
    foodStr.append("%");
    foodMessage = TTF_RenderText_Blended(fontTTF,
                                         foodStr.c_str(),
                                         textColour);
    foodText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), foodMessage);
    SDL_FreeSurface( foodMessage );

    //GENES
    if( gene0Text != NULL ) SDL_DestroyTexture( gene0Text );
    gene0Message = TTF_RenderText_Blended(fontTTF,
                                          std::string(1, TheEnvironment::Instance()->microbes[microbeIndex]->
                                                      mga.getGenotypeLetter(0)).c_str(),
                                          textColour);
    gene0Text = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), gene0Message);
    SDL_FreeSurface( gene0Message );

    if( gene1Text != NULL ) SDL_DestroyTexture( gene1Text );
    gene1Message = TTF_RenderText_Blended(fontTTF,
                                          std::string(1, TheEnvironment::Instance()->microbes[microbeIndex]->
                                                      mga.getGenotypeLetter(1)).c_str(),
                                          textColour);
    gene1Text = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), gene1Message);
    SDL_FreeSurface( gene1Message );
    
    if( gene2Text != NULL ) SDL_DestroyTexture( gene2Text );
    gene2Message = TTF_RenderText_Blended(fontTTF,
                                          std::string(1, TheEnvironment::Instance()->microbes[microbeIndex]->
                                                      mga.getGenotypeLetter(2)).c_str(),
                                          textColour);
    gene2Text = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), gene2Message);
    SDL_FreeSurface( gene2Message );

    if( gene3Text != NULL ) SDL_DestroyTexture( gene3Text );
    gene3Message = TTF_RenderText_Blended(fontTTF,
                                          std::string(1, TheEnvironment::Instance()->microbes[microbeIndex]->
                                                      mga.getGenotypeLetter(3)).c_str(),
                                          textColour);
    gene3Text = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), gene3Message);
    SDL_FreeSurface( gene3Message );

    if( fitnessText != NULL ) SDL_DestroyTexture( fitnessText );
    std::string fitnessStr = std::to_string(TheEnvironment::Instance()->microbes[microbeIndex]->
                                                mga.getFitness());
    fitnessStr.append(" / 4");
    fitnessMessage = TTF_RenderText_Blended(fontTTF,
                                           fitnessStr.c_str(),
                                           textColour);
    fitnessText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), fitnessMessage);
    SDL_FreeSurface( fitnessMessage );
  }
  else //no microbe selected
  {
    //if this variable has not already been set to -1 (no microbe selected)
    if (foodEatenPercentage != -1)
    {
      //then it is necessary to refresh the UI to show no microbe has been selected

      //diameter
      if( widthText != NULL ) SDL_DestroyTexture( widthText );
      widthMessage = TTF_RenderText_Blended(fontTTF,
                                            ((std::string)"").c_str(),
                                            textColour);
      widthText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), widthMessage);
      SDL_FreeSurface( widthMessage );

      //speed
      if( speedText != NULL ) SDL_DestroyTexture( speedText );
      speedMessage = TTF_RenderText_Blended(fontTTF,
                                            ((std::string)"").c_str(),
                                            textColour);
      speedText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), speedMessage);
      SDL_FreeSurface( speedMessage );

      //children
      
      if( childText != NULL ) SDL_DestroyTexture( childText );
      childMessage = TTF_RenderText_Blended(fontTTF,
                                            ((std::string)"").c_str(),
                                            textColour);
      childText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), childMessage);
      SDL_FreeSurface( childMessage );

      //lifetime
      if( lifetimeText != NULL ) SDL_DestroyTexture( lifetimeText );
      lifetimeMessage = TTF_RenderText_Blended(fontTTF,
                                               ((std::string)"").c_str(),
                                               textColour);
      lifetimeText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), lifetimeMessage);
      SDL_FreeSurface( lifetimeMessage );


      //status
      if( statusText != NULL ) SDL_DestroyTexture( statusText );
      std::string statusStr = "no microbe selected              ";
         
      if( statusText != NULL ) SDL_DestroyTexture( statusText );
      statusMessage = TTF_RenderText_Blended(fontTTF,
                                             statusStr.c_str(),
                                             textColour);
      statusText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), statusMessage);
      SDL_FreeSurface( statusMessage );


      //food %
      if( foodText != NULL ) SDL_DestroyTexture( foodText );
      foodMessage = TTF_RenderText_Blended(fontTTF,
                                           ((std::string)" - %").c_str(),
                                           textColour);
      foodText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), foodMessage);
      SDL_FreeSurface( foodMessage );


      //fitness rating
      if( fitnessText != NULL ) SDL_DestroyTexture( fitnessText );
      fitnessMessage = TTF_RenderText_Blended(fontTTF,
                                              ((std::string)" - ").c_str(),
                                              textColour);
      fitnessText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), fitnessMessage);
      SDL_FreeSurface( fitnessMessage );
      
      //genes
      if( gene0Text != NULL ) SDL_DestroyTexture( gene0Text );
      gene0Message = TTF_RenderText_Blended(fontTTF,
                                            ((std::string)"-").c_str(),
                                            textColour);
      gene0Text = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), gene0Message);
      SDL_FreeSurface( gene0Message );
      
      if( gene1Text != NULL ) SDL_DestroyTexture( gene1Text );
      gene1Message = TTF_RenderText_Blended(fontTTF,
                                            ((std::string)"-").c_str(),
                                            textColour);
      gene1Text = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), gene1Message);
      SDL_FreeSurface( gene1Message );
      
      if( gene2Text != NULL ) SDL_DestroyTexture( gene2Text );
      gene2Message = TTF_RenderText_Blended(fontTTF,
                                            ((std::string)"-").c_str(),
                                            textColour);
      gene2Text = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), gene2Message);
      SDL_FreeSurface( gene2Message );
      
      if( gene3Text != NULL ) SDL_DestroyTexture( gene3Text );
      gene3Message = TTF_RenderText_Blended(fontTTF,
                                            ((std::string)"-").c_str(),
                                            textColour);
      gene3Text = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), gene3Message);
      SDL_FreeSurface( gene3Message );


      //final reset
      foodEatenPercentage = -1;
    }
  }

  //if stats are enabled and has surpassed refresh time then update values
  if (displayStats && ((SDL_GetTicks()) - lastStatsUpdateTime) > 1000)
  {
    lastStatsUpdateTime = SDL_GetTicks();
    
    std::string numMicrobesStr;
    
    float achievedTime;
    std::string achievedTimeStr;

    //if max fitness has been reached get num microbes & time
    if (TheEnvironment::Instance()->timeMaxFitnessAchieved != 0)
    {
      //calc time
      achievedTime = TheEnvironment::Instance()->timeMaxFitnessAchieved;
      achievedTimeStr = "false";

      achievedTime /= 1000; //convert from ms to s

      int achievedTimeMins = achievedTime / 60;
      int achievedTimeSeconds = achievedTime - (achievedTimeMins * 60);
  
      achievedTimeStr = std::to_string(achievedTimeMins);

      if (achievedTimeMins < 10)
      {
        achievedTimeStr.insert(0, "0");
      }
      achievedTimeStr.append(":");
      if (achievedTimeSeconds < 10)
      {
        achievedTimeStr.append("0");
      }

      achievedTimeStr.append(std::to_string(achievedTimeSeconds)); 
    
      
      //get number of microbes
      numMicrobesStr = std::to_string(TheEnvironment::Instance()->maxFitnessAchievedReproductions);
      numMicrobesStr.append(" microbes");
    }
    else //else set to default
    {
      numMicrobesStr = "     -     ";
      achievedTimeStr = "false";

    }
    
    //time
    if( maxFitnessAchievedLabelText != NULL ) SDL_DestroyTexture( maxFitnessAchievedLabelText );
    maxFitnessAchievedLabelMessage = TTF_RenderText_Blended(fontTTF,
                                               achievedTimeStr.c_str(),
                                               textColour);
    maxFitnessAchievedLabelText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), maxFitnessAchievedLabelMessage);
    SDL_FreeSurface( maxFitnessAchievedLabelMessage );

    //num
    if( numMicrobesText != NULL ) SDL_DestroyTexture( numMicrobesText );
    numMicrobesMessage = TTF_RenderText_Blended(fontTTF,
                                               numMicrobesStr.c_str(),
                                               textColour);
    numMicrobesText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), numMicrobesMessage);
    SDL_FreeSurface( numMicrobesMessage );

    
    //avg, min/max fitness
    unsigned fitnessTotal = 0;
    unsigned lowestFitnessScore = 4;
    unsigned highestFitnessScore = 0;
    
    for (size_t i = 0; i < TheEnvironment::Instance()->microbes.size(); i++)
    {
      unsigned microbeFitness = TheEnvironment::Instance()->microbes[i]->mga.getFitness();
      
      fitnessTotal += microbeFitness;
      if (microbeFitness < lowestFitnessScore) lowestFitnessScore = microbeFitness;
      if (microbeFitness > highestFitnessScore) highestFitnessScore = microbeFitness;
    }

    //avg fitness
    std::string fitnessAvg = std::to_string((float)fitnessTotal / TheEnvironment::Instance()->microbes.size());

    if (fitnessAvg.length() > 3) 
      fitnessAvg.resize(3);
    else if (fitnessAvg.length() == 1)
      fitnessAvg.append(".0");
    
    if( avgFitnessText != NULL ) SDL_DestroyTexture( avgFitnessText );
    avgFitnessMessage = TTF_RenderText_Blended(fontTTF,
                                               fitnessAvg.c_str(),
                                               textColour);
    avgFitnessText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), avgFitnessMessage);
    SDL_FreeSurface( avgFitnessMessage );

    //min
    std::string minFitness = std::to_string(lowestFitnessScore);
    minFitness.append(".0");
        
    if( minFitnessText != NULL ) SDL_DestroyTexture( minFitnessText );
    minFitnessMessage = TTF_RenderText_Blended(fontTTF,
                                               minFitness.c_str(),
                                               textColour);
    minFitnessText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), minFitnessMessage);
    SDL_FreeSurface( minFitnessMessage );

    //max
    std::string maxFitness = std::to_string(highestFitnessScore);
    maxFitness.append(".0");
        
    if( maxFitnessText != NULL ) SDL_DestroyTexture( maxFitnessText );
    maxFitnessMessage = TTF_RenderText_Blended(fontTTF,
                                               maxFitness.c_str(),
                                               textColour);
    maxFitnessText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), maxFitnessMessage);
    SDL_FreeSurface( maxFitnessMessage );

    //avg lifespan

    unsigned lifespanTotal = 0;
    for (size_t i = 0; i < TheEnvironment::Instance()->microbes.size(); i++)
    {
      lifespanTotal += (SDL_GetTicks() -  TheEnvironment::Instance()->microbes[i]->microbeSpawnTime)/1000;
    }

    lifespanTotal /= TheEnvironment::Instance()->microbes.size();

    int avgMins = lifespanTotal / 60;
    int avgSeconds = lifespanTotal - (avgMins * 60);
  
    std::string avgLifetime = std::to_string(avgMins);

    if (avgMins < 10)
    {
      avgLifetime.insert(0, "0");
    }
    avgLifetime.append(":");
    if (avgSeconds < 10)
    {
      avgLifetime.append("0");
    }

    avgLifetime.append(std::to_string(avgSeconds)); 
    
    
    if( avgLifespanText != NULL ) SDL_DestroyTexture( avgLifespanText );
    avgLifespanMessage = TTF_RenderText_Blended(fontTTF,
                                               avgLifetime.c_str(),
                                               textColour);
    avgLifespanText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), avgLifespanMessage);
    SDL_FreeSurface( avgLifespanMessage );
    

    //time elapsed

    float timeElapsed = (SDL_GetTicks() - simulationStartTime) / 1000;

    int timeElapsedMins = timeElapsed / 60;
    int timeElapsedSeconds = timeElapsed - (timeElapsedMins * 60);
  
    std::string timeElapsedStr = std::to_string(timeElapsedMins);

    if (timeElapsedMins < 10)
    {
      timeElapsedStr.insert(0, "0");
    }
    timeElapsedStr.append(":");
    if (timeElapsedSeconds < 10)
    {
      timeElapsedStr.append("0");
    }

    timeElapsedStr.append(std::to_string(timeElapsedSeconds)); 
    
    if( timeElapsedText != NULL ) SDL_DestroyTexture( timeElapsedText );
    timeElapsedMessage = TTF_RenderText_Blended(fontTTF,
                                               timeElapsedStr.c_str(),
                                               textColour);
    timeElapsedText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), timeElapsedMessage);
    SDL_FreeSurface( timeElapsedMessage );
    
  }
}

void UI::clean()
{
  TTF_CloseFont( fontTTF );
  fontTTF = NULL;

  //deallocate prev frame texture

  //microbe information text
  if( microbeNumberText != NULL ) SDL_DestroyTexture( microbeNumberText );
  if( widthLabelText != NULL ) SDL_DestroyTexture( widthLabelText );
  if( widthText != NULL ) SDL_DestroyTexture( widthText );
  if( speedLabelText != NULL ) SDL_DestroyTexture( speedLabelText );
  if( speedText != NULL ) SDL_DestroyTexture( speedText );
  if( childLabelText != NULL ) SDL_DestroyTexture( childLabelText );
  if( childText != NULL ) SDL_DestroyTexture( childText );
  if( lifetimeText != NULL ) SDL_DestroyTexture( lifetimeText );
  if( lifetimeLabelText != NULL ) SDL_DestroyTexture( lifetimeLabelText );
  if( statusLabelText != NULL ) SDL_DestroyTexture( statusLabelText );
  if( statusText != NULL ) SDL_DestroyTexture( statusText );
  if( foodLabelText != NULL ) SDL_DestroyTexture( foodLabelText );
  if( foodText != NULL ) SDL_DestroyTexture( foodText );
  if( fitnessLabelText != NULL ) SDL_DestroyTexture( fitnessLabelText );
  if( fitnessText != NULL ) SDL_DestroyTexture( fitnessText );

  //stats
  if( statsLabelText != NULL ) SDL_DestroyTexture( statsLabelText );
  if( maxFitnessAchievedLabelText != NULL ) SDL_DestroyTexture( maxFitnessAchievedLabelText );
  if( maxFitnessAchievedText != NULL ) SDL_DestroyTexture( maxFitnessAchievedText );
  if( numMicrobesLabelText != NULL ) SDL_DestroyTexture( numMicrobesLabelText );
  if( numMicrobesText != NULL ) SDL_DestroyTexture( numMicrobesText );
  if( avgFitnessText != NULL ) SDL_DestroyTexture( avgFitnessText );
  if( avgFitnessLabelText != NULL ) SDL_DestroyTexture( avgFitnessLabelText );
  if( minFitnessText != NULL ) SDL_DestroyTexture( minFitnessText );
  if( minFitnessLabelText != NULL ) SDL_DestroyTexture( minFitnessLabelText );
  if( maxFitnessText != NULL ) SDL_DestroyTexture( maxFitnessText );
  if( maxFitnessLabelText != NULL ) SDL_DestroyTexture( maxFitnessLabelText );
  if( avgLifespanLabelText != NULL ) SDL_DestroyTexture( avgLifespanLabelText );
  if( avgLifespanText != NULL ) SDL_DestroyTexture( avgLifespanText );
  if( timeElapsedLabelText != NULL ) SDL_DestroyTexture( timeElapsedLabelText );
  if( timeElapsedText != NULL ) SDL_DestroyTexture( timeElapsedText );

  //help
  if( helpLabelText != NULL ) SDL_DestroyTexture( helpLabelText );
  if( statsText != NULL ) SDL_DestroyTexture( statsText );
  if( gridText != NULL ) SDL_DestroyTexture( gridText );
  if( terrainText != NULL ) SDL_DestroyTexture( terrainText );
  if( pathText != NULL ) SDL_DestroyTexture( pathText );
  if( READMEText != NULL ) SDL_DestroyTexture( READMEText );

  TTF_Quit();

}

void UI::handleInput()
{
  //BUTTON PRESSES
  if (TheInputHandler::Instance()->keySPressed)
  {
    TheInputHandler::Instance()->keySPressed = false;
    if (displayStats == false) { displayStats = true; displayHelp = false; }
    else { displayStats = false; displayHelp = false; }
  }
  else if (TheInputHandler::Instance()->keyHPressed)
  {
    TheInputHandler::Instance()->keyHPressed = false;
    if (displayHelp == false) { displayHelp = true; displayStats = false; }
    else { displayStats = false; displayHelp = false; }
  }
  else if (TheInputHandler::Instance()->keyRPressed)
  {
    TheInputHandler::Instance()->keyRPressed = false;

    //url to open
    std::string url = "https://www.joshuaweeden.com/microbial-genetic-algorithm";
    
#ifdef _WIN32 //if on Windows
    ShellExecute(NULL, "open", url, NULL, NULL, SW_SHOWNORMAL);
#else //else developing on Mac
    system("open https://www.joshuaweeden.com/microbial-genetic-algorithm");       
#endif
  } 
}
