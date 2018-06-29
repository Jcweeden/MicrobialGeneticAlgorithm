#include "UI.h"

#include "Environment.h"


UI::UI() :
    microbeIndex(0), foodEatenPercentage(0)
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
  foodLabelRect.w = TheGame::Instance()->getWindowWidth()/3 + 45; // controls the width of the rect
  foodLabelRect.h = (TheGame::Instance()->getUIHeight()/10)*2; // controls the height of the rect

  foodMessage = TTF_RenderText_Blended(fontTTF, "89%", textColour); // as TTF_RenderText_Blended could only be used on SDL_Surface then you have to create the surface first
  foodText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), foodMessage); 
  foodRect.x = 250  + (TheGame::Instance()->getUIHeight()/10)*2 + TheGame::Instance()->getWindowWidth()/3 + 10;  //controls the rect's x coordinate 
  foodRect.y = TheGame::Instance()->getWindowHeight() + (TheGame::Instance()->getUIHeight()/10)*2 + 6; // controls the rect's y coordinte
  foodRect.w = TheGame::Instance()->getWindowWidth()/18; // controls the width of the rect
  foodRect.h = (TheGame::Instance()->getUIHeight()/10)*2; // controls the height of the rect
}

void UI::draw()
{
  //UI box background
  boxRGBA(TheGame::Instance()->getRenderer(),
          0, TheGame::Instance()->getWindowHeight(),
          TheGame::Instance()->getWindowWidth(), TheGame::Instance()->getUIHeight() + TheGame::Instance()->getWindowHeight(),
          229, 154, 157, 255);

  

  
  //selected microbe number box

  //if none selected draw in gray
  if (microbeIndex == -1) {
    boxRGBA(TheGame::Instance()->getRenderer(),
            0, TheGame::Instance()->getWindowHeight(),
            TheGame::Instance()->getWindowWidth()/12,
            TheGame::Instance()->getWindowHeight() + TheGame::Instance()->getWindowWidth()/12,
            102, 102, 102, 255);

    //set microbe number to -, as none have been selected
    microbeNumberMessage = TTF_RenderText_Blended(fontTTF, "-", textColour);
    microbeNumberText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), microbeNumberMessage);
    SDL_RenderCopy(TheGame::Instance()->getRenderer(), microbeNumberText, NULL, &microbeNumberRect); 
  }
  else //draw same colour as selected microbe
  {
    boxRGBA(TheGame::Instance()->getRenderer(),
            0, TheGame::Instance()->getWindowHeight(),
            TheGame::Instance()->getWindowWidth()/12,
            TheGame::Instance()->getWindowHeight() + TheGame::Instance()->getWindowWidth()/12,
            TheEnvironment::Instance()->microbes[microbeIndex]->colourR,
            TheEnvironment::Instance()->microbes[microbeIndex]->colourG,
            TheEnvironment::Instance()->microbes[microbeIndex]->colourB,
            TheEnvironment::Instance()->microbes[microbeIndex]->colourA);

    //set microbe number
    microbeNumberMessage = TTF_RenderText_Blended(fontTTF, std::to_string(microbeIndex+1).c_str(), textColour);
    microbeNumberText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), microbeNumberMessage);
    SDL_RenderCopy(TheGame::Instance()->getRenderer(), microbeNumberText, NULL, &microbeNumberRect); 

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

  ///FOOD EATEN

  float barFull = 0.0f;

  barFull = 210 * (float)(foodEatenPercentage/100);
  
  //if (foodEatenPercentage == 0) barFull = 210;
  //else  (foodEatenPercentage/100) * 210;
  
  //red bar for food eaten
  boxRGBA(TheGame::Instance()->getRenderer(),
          240+barFull, TheGame::Instance()->getWindowHeight() + (TheGame::Instance()->getUIHeight()/10)*2 + 54,
          550, TheGame::Instance()->getWindowHeight() + (TheGame::Instance()->getUIHeight()/10)*2 + 74,
          255, 0, 0, 255);

  //green bar for food eaten
  boxRGBA(TheGame::Instance()->getRenderer(),
          240, TheGame::Instance()->getWindowHeight() + (TheGame::Instance()->getUIHeight()/10)*2 + 54,
          550 - barFull, TheGame::Instance()->getWindowHeight() + (TheGame::Instance()->getUIHeight()/10)*2 + 74,
          0, 255, 0, 255);

  //draw outline box for food eaten
  rectangleRGBA(TheGame::Instance()->getRenderer(),
                240, TheGame::Instance()->getWindowHeight() + (TheGame::Instance()->getUIHeight()/10)*2 + 54,
                550, TheGame::Instance()->getWindowHeight() + (TheGame::Instance()->getUIHeight()/10)*2 + 74,
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
}

void UI::update()
{
  //reset the selected microbe index
  microbeIndex = TheEnvironment::Instance()->selectedMicrobeIndex;

  //if a microbe has been selected
  if (microbeIndex != -1)
  {
    std::string width = std::to_string(TheEnvironment::Instance()->microbes[microbeIndex]->width/15);
    width = width.substr(0,4);
    width.insert(0," ");
    width.append(" ");
    widthMessage = TTF_RenderText_Blended(fontTTF,
                                        width.c_str(),
                                        textColour);
    widthText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), widthMessage);

    std::string speed = std::to_string(TheEnvironment::Instance()->microbes[microbeIndex]->speedMultiplier/10);
    speed = speed.substr(0,4);
    speed.insert(0," ");
    speed.append(" ");
    speedMessage = TTF_RenderText_Blended(fontTTF,
                                        speed.c_str(),
                                        textColour);
    speedText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), speedMessage);


    std::string children = std::to_string(TheEnvironment::Instance()->microbes[microbeIndex]->childrenProduced);
    if (children.length() == 1) children.insert(0, "0");
    children.insert(2, "  ");
    children.insert(0, "  ");
    childMessage = TTF_RenderText_Blended(fontTTF,
                                        children.c_str(),
                                        textColour);
    childText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), childMessage);


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

    int status = TheEnvironment::Instance()->microbes[microbeIndex]->currentStatus;
    std::string statusStr;
    switch (status)
    {
      case 0:
        statusStr = "seeking food                     ";
        break;
      case 1:
        statusStr = "waiting for available food       ";
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

    statusMessage = TTF_RenderText_Blended(fontTTF,
                                           statusStr.c_str(),
                                           textColour);
    statusText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), statusMessage);


    foodEatenPercentage = (float)TheEnvironment::Instance()->microbes[microbeIndex]->foodEaten /
        TheEnvironment::Instance()->microbes[microbeIndex]->foodRequiredToMate * 100;
    std::string foodStr = std::to_string(foodEatenPercentage);
    foodStr.append("%");
    foodMessage = TTF_RenderText_Blended(fontTTF,
                                         foodStr.c_str(),
                                         textColour);
    foodText = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), foodMessage);
  }
  else
  {
    foodEatenPercentage = 0;
  }
}
