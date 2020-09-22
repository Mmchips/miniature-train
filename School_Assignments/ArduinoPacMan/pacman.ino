#include <EEPROM.h>
#include <SPI.h>
#include <GD2.h> 
#include "myassets.h"
  int rectRad = 8;

  int rectPosX = 16;
  int rectPosY = 4;

  int xPin = 15;
  int yPin = 14;
  int xVal = 0;                  // variable to read the value from the analog pin 0
  int yVal = 0;

  int playerPosX = 0;
  int playerPosY = 0;

  //anim variables
  int pacmanDir = 0;
  int anim = 0;
  int defaultAnim = PACMANLEFT_HANDLE;
  int limit = 3;
  int frame = 0;
  int ghostAnim = 0;
  int scaredAnim = 0;

  //ghost variables
  int inkyPosX;
  int inkyPosY;
  int blinkyPosX;
  int blinkyPosY;
  int pinkyPosX;
  int pinkyPosY;
  int clydePosX;
  int clydePosY;
  bool scaredGhosts = false;
  int scaredTimer = 0;
  int blinkyDir = 0;
  int pinkyDir = 0;
  int inkyDir = 0;
  int clydeDir = 0;

  int left = 0;
  int right = 1;
  int up = 2;
  int down = 3;

  int score = 0;
  int lives = 3;
  int pluttCounter = 0;
  int inkyResetCounter = 0;
  int pinkyResetCounter = 0;
  int clydeResetCounter = 0;

  float pixelDivider = 1/8;

  struct currentTile
  {
    int currentX = 0;
    int currentY = 0;
  };

  currentTile curTile;
  currentTile pinkyCurTile;
  currentTile blinkyCurTile;
  currentTile inkyCurTile;
  currentTile clydeCurTile;
  
  //the map of pac-man 
  //0 is a wall
  //1 is a small power pill
  //2 is a large power pill
  //3 is an empty space
  //4 is spawnpos for ghosts
  //5 is spawnpos for pac-man
  //7 signals the end of the line
  //8 is a teleportation tile
  const int rows = 31;
  const int cols = 28;
  byte levelMap[rows][cols] = 
  {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0},
    {0,2,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,2,0},
    {0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0},
    {0,1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0},
    {0,1,1,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,1,1,0},
    {0,0,0,0,0,0,1,0,0,0,0,0,3,0,0,3,0,0,0,0,0,1,0,0,0,0,0,0},
    {3,3,3,3,3,0,1,0,0,0,0,0,3,0,0,3,0,0,0,0,0,1,0,3,3,3,3,3},
    {3,3,3,3,3,0,1,0,0,3,3,3,3,6,6,3,3,3,3,0,0,1,0,3,3,3,3,3},
    {3,3,3,3,3,0,1,0,0,3,0,0,0,0,0,0,0,0,3,0,0,1,0,3,3,3,3,3},
    {0,0,0,0,0,0,1,0,0,3,0,4,4,4,4,4,4,0,3,0,0,1,0,0,0,0,0,0},
    {8,3,3,3,3,3,1,3,3,3,0,4,4,4,4,4,4,0,3,3,3,1,3,3,3,3,3,8},
    {0,0,0,0,0,0,1,0,0,3,0,4,4,4,4,4,4,0,3,0,0,1,0,0,0,0,0,0},
    {3,3,3,3,3,0,1,0,0,3,0,0,0,0,0,0,0,0,3,0,0,1,0,3,3,3,3,3},
    {3,3,3,3,3,0,1,0,0,3,3,3,3,3,3,3,3,3,3,0,0,1,0,3,3,3,3,3},
    {3,3,3,3,3,0,1,0,0,3,0,0,0,0,0,0,0,0,3,0,0,1,0,3,3,3,3,3},
    {0,0,0,0,0,0,1,0,0,3,0,0,0,0,0,0,0,0,3,0,0,1,0,0,0,0,0,0},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0},
    {0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0},
    {0,2,1,1,0,0,1,1,1,1,1,1,1,5,5,1,1,1,1,1,1,1,0,0,1,1,2,0},
    {0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0},
    {0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0},
    {0,1,1,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,1,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
  };
  
void setup() 
{ 
  GD.begin();
  LOAD_ASSETS();
  loadSprites();
  calculateStartTile();
  
  //load joystick
  Serial.begin(9600);
}

void loop() 
{
  GD.Clear();
  scorePoints();
  GD.Begin(BITMAPS);
  GD.Vertex2ii(0, 5, PM_HANDLE, 0);                                         //draw map
  DrawMap();
  PacManMovement();
  
  GhostMovement();
  
  drawPacMan();
  if(scaredGhosts == true)
  {
    scaredTimer++;
    drawScaredGhost();
    huntGhosts();
  }
  if(scaredGhosts == false)
  {
    drawGhosts();   
  }

  gameOver();
  delay(75);                     //add a delay to fix the delay
  GD.swap();

  inkyResetCounter++;
  pinkyResetCounter++;
  clydeResetCounter++;
  frame++;                        //for the animations to know when to change sprite

  if(scaredTimer >= 90)
  {
    scaredAnim = 0;
    scaredGhosts = false;
    scaredTimer = 0;
  }
  
  //check when to change sprite
  if(frame >= limit)
  {
    if(scaredGhosts == true)
    {
      scaredAnim++;
    }
    anim++;
    ghostAnim++;
    frame = 0;
    //if anim > 3 the anim should restart and therefore we reset the values
    if(anim == 3)
    {
      anim = 0;
    }
    //same thing but for the ghost anims
    if(ghostAnim == 2)
    {
      ghostAnim = 0;
    }
    if(scaredAnim ==2)
    {
      scaredAnim = 0;
   }
  }
}

void DrawMap()
{
  rectPosX = 16;
  rectPosY = 6;
  //GD.Begin(RECTS);
  GD.LineWidth(5);
  for(int curRow=0; curRow < rows; curRow++)
  {
    for(int curCol = 0; curCol <= cols; curCol++)
    {
      if(curCol == 28)
      {
         rectPosX = 16;
         rectPosY = rectPosY + rectRad;
      }
      else if(levelMap[curRow][curCol] == 1)
      {
        GD.ColorRGB(0xff8000);
        GD.PointSize(16 * 1);
        GD.Begin(POINTS);
        GD.Vertex2ii(rectPosX + (rectRad*0.5), rectPosY + (rectRad*0.5));
  
        rectPosX += rectRad;
      }
      else if (levelMap[curRow][curCol] == 2)
      {
        GD.ColorRGB(0xff8000);
        GD.PointSize(16 * 4);
        GD.Begin(POINTS);
        GD.Vertex2ii(rectPosX + (rectRad*0.5), rectPosY + (rectRad*0.5));
  
        rectPosX += rectRad;
      }
      else
      {
        rectPosX += rectRad;
      }
    }
    
  }
}

void DrawGrid()
{
  GD.ColorRGB(0xffffff);
  GD.Begin(LINES);
  GD.LineWidth(5);
  //loop through the rows of pixels
  for(int i=0; i < 34; i++)
  {
    GD.Vertex2ii(0, i * 8);
    GD.Vertex2ii(480, i * 8);
  }
  //loop through the columns of pixels
  for(int j=0; j < 60; j++)
  {
    GD.Vertex2ii(j*8, 0);
    GD.Vertex2ii(j*8, 272);
  }
}

void drawPacMan()
{
  GD.ColorRGB(0xffffff);
  GD.Begin(BITMAPS);
  if(pacmanDir == 0)
  {
    defaultAnim = PACMANLEFT_HANDLE;
  }
  else if(pacmanDir == 1)
  {
      defaultAnim = PACMANRIGHT_HANDLE;
  }
  else if(pacmanDir == 2)
  {
      defaultAnim = PACMANUP_HANDLE;
  }
  else if(pacmanDir == 3)
  {
    defaultAnim =  PACMANDOWN_HANDLE;
  }
  GD.Vertex2ii(playerPosX-7, playerPosY-8, defaultAnim, anim);
}

void PacManMovement()
{
  xVal = analogRead(xPin);
  yVal = analogRead(yPin);

  if(xVal < 474)
  {
    if(levelMap[curTile.currentY][curTile.currentX-1] != 0)
    {
      if(levelMap[curTile.currentY][curTile.currentX-1] == 8)
      {
        curTile.currentX = 26;
        playerPosX = 228;
      }
      playerPosX = playerPosX -8;
      curTile.currentX -= 1;
      pacmanDir = 0;                                          //moving pacman to the left
    }
  }
  else if(xVal > 550)
  {
    if(levelMap[curTile.currentY][curTile.currentX+1] != 0)
    {
      if(levelMap[curTile.currentY][curTile.currentX+1] == 8)
      {
        curTile.currentX = 0;
        playerPosX = 20;
      }
      playerPosX = playerPosX +8;
      curTile.currentX += 1;
      pacmanDir = 1;                                      //moving pacman to the right
    }
  }
  
  //y-axis is inverted on gameduino
  else if(yVal < 474)
  {
    if(levelMap[curTile.currentY+1][curTile.currentX] != 0)
    {
      playerPosY = playerPosY +8;
      curTile.currentY += 1;
      pacmanDir = 3;                                      //moving pacman down
    }
  }
  else if(yVal > 550)
  {
    if(levelMap[curTile.currentY-1][curTile.currentX] != 0)
    {
      playerPosY = playerPosY -8;
      curTile.currentY -= 1;
      pacmanDir = 2;                                      //moving pacman up
    }
  }
  else 
    return;
}

void GhostMovement()
{
  //BLINKY
  if(blinkyDir == left)
  {
    if(levelMap[blinkyCurTile.currentY][blinkyCurTile.currentX-1] == 0)
    {
      blinkyDir = ghostAI();
    }
    //if the next tile to the left isn't a wall blinky keeps moving
    else 
    {
      blinkyPosX -= 8;
      blinkyCurTile.currentX -= 1;     
    }
  }
  if(blinkyDir == right)
  {
    if(levelMap[blinkyCurTile.currentY][blinkyCurTile.currentX+1] == 0)
    {
      blinkyDir = ghostAI();
    }
    else 
    {
      blinkyPosX += 8;
      blinkyCurTile.currentX += 1;     
    }
  }
  if(blinkyDir == up)
  {
    if(levelMap[blinkyCurTile.currentY-1][blinkyCurTile.currentX] == 0)
    {
      blinkyDir = ghostAI();
    }
    else 
    {
      blinkyPosY -= 8;
      blinkyCurTile.currentY -= 1;     
    }
  }
  if(blinkyDir == down)
  {
    if(levelMap[blinkyCurTile.currentY+1][blinkyCurTile.currentX] == 0)
    {
      blinkyDir = ghostAI(); 
    }
    else 
    {
      blinkyPosY += 8;
      blinkyCurTile.currentY += 1;     
    }
  }

  //INKY
  if(pluttCounter == 30)
  {
    inkyPosX = 128;
    inkyPosY = 100;
    inkyCurTile.currentX = 14;
    inkyCurTile.currentY = 11;
  }
  if(inkyDir == left)
  {
    if(levelMap[inkyCurTile.currentY][inkyCurTile.currentX-1] == 0)
    {
      inkyDir = ghostAI();
    }
    //if the next tile to the left isn't a wall inky keeps moving
    else 
    {
      inkyPosX -= 8;
      inkyCurTile.currentX -= 1;     
    }
  }
  if(inkyDir == right)
  {
    if(levelMap[inkyCurTile.currentY][inkyCurTile.currentX+1] == 0)
    {
      inkyDir = ghostAI();
    }
    else 
    {
      inkyPosX += 8;
      inkyCurTile.currentX += 1;     
    }
  }
  if(inkyDir == up)
  {
    if(levelMap[inkyCurTile.currentY-1][inkyCurTile.currentX] == 0)
    {
      inkyDir = ghostAI();
    }
    else 
    {
      inkyPosY -= 8;
      inkyCurTile.currentY -= 1;     
    }
  }
  if(inkyDir == down)
  {
    if(levelMap[inkyCurTile.currentY+1][inkyCurTile.currentX] == 0)
    {
      inkyDir = ghostAI(); 
    }
    else 
    {
      inkyPosY += 8;
      inkyCurTile.currentY += 1;     
    }
  }


  //PINKY
  if(pluttCounter == 1)
  {
    pinkyPosX = 128;
    pinkyPosY = 100;
    pinkyCurTile.currentX = 14;
    pinkyCurTile.currentY = 11;
  }
  if(pinkyDir == left)
  {
    if(levelMap[pinkyCurTile.currentY][pinkyCurTile.currentX-1] == 0)
    {
      pinkyDir = ghostAI();
    }
    //if the next tile to the left isn't a wall pinky keeps moving
    else 
    {
      pinkyPosX -= 8;
      pinkyCurTile.currentX -= 1;     
    }
  }
  if(pinkyDir == right)
  {
    if(levelMap[pinkyCurTile.currentY][pinkyCurTile.currentX+1] == 0)
    {
      pinkyDir = ghostAI();
    }
    else 
    {
      pinkyPosX += 8;
      pinkyCurTile.currentX += 1;     
    }
  }
  if(pinkyDir == up)
  {
    if(levelMap[pinkyCurTile.currentY-1][pinkyCurTile.currentX] == 0)
    {
      pinkyDir = ghostAI();
    }
    else 
    {
      pinkyPosY -= 8;
      pinkyCurTile.currentY -= 1;     
    }
  }
  if(pinkyDir == down)
  {
    if(levelMap[pinkyCurTile.currentY+1][pinkyCurTile.currentX] == 0)
    {
      pinkyDir = ghostAI(); 
    }
    else 
    {
      pinkyPosY += 8;
      pinkyCurTile.currentY += 1;     
    }
  }

  //CLYDE
  if(pluttCounter == 60)
  {
    clydePosX = 128;
    clydePosY = 100;
    clydeCurTile.currentX = 14;
    clydeCurTile.currentY = 11;
  }
  if(clydeDir == left)
  {
    if(levelMap[clydeCurTile.currentY][clydeCurTile.currentX-1] == 0)
    {
      clydeDir = ghostAI();
    }
    //if the next tile to the left isn't a wall blinky keeps moving
    else 
    {
      clydePosX -= 8;
      clydeCurTile.currentX -= 1;     
    }
  }
  if(clydeDir == right)
  {
    if(levelMap[clydeCurTile.currentY][clydeCurTile.currentX+1] == 0)
    {
      clydeDir = ghostAI();
    }
    else 
    {
      clydePosX += 8;
      clydeCurTile.currentX += 1;     
    }
  }
  if(clydeDir == up)
  {
    if(levelMap[clydeCurTile.currentY-1][clydeCurTile.currentX] == 0)
    {
      clydeDir = ghostAI();
    }
    else 
    {
      clydePosY -= 8;
      clydeCurTile.currentY -= 1;     
    }
  }
  if(clydeDir == down)
  {
    if(levelMap[clydeCurTile.currentY+1][clydeCurTile.currentX] == 0)
    {
      clydeDir = ghostAI(); 
    }
    else 
    {
      clydePosY += 8;
      clydeCurTile.currentY += 1;     
    }
  }
}

int ghostAI()
{
  //int ghostAI(int ghostTileX, int ghostTileY, int ghostDir)
  //pythagoras to calculate the shortest path to pacman
//  float a = sqrt(pow( (curTile.currentX - ghostTileX), 2) + pow( curTile.currentY - (ghostTileY-1), 2)); //UP
//  float b = sqrt(pow( (curTile.currentX - ghostTileX), 2) + pow( curTile.currentY - (ghostTileY+1), 2)); //DOWN
//  float c = sqrt(pow( (curTile.currentY - ghostTileY), 2) + pow( curTile.currentX - (ghostTileX-1), 2)); //RIGHT
//  float d = sqrt(pow( (curTile.currentY - ghostTileY), 2) + pow( curTile.currentX - (ghostTileX+1), 2)); //LEFT
//  if(a < b && a <= c && a <= d && ghostDir != down && levelMap[ghostTileY-1][ghostTileX] !=0) ghostDir = up;
//  else if(b < a && b <= c && b <= d && ghostDir != up && levelMap[ghostTileY+1][ghostTileX] !=0) ghostDir = down;
//  else if(c <= a && c <= b && c < d && ghostDir != right && levelMap[ghostTileY][ghostTileX-1] !=0) ghostDir = left;
//  else if(d <= a && d <= b && d < c && ghostDir != left && levelMap[ghostTileY][ghostTileX+1] !=0) ghostDir = right;

  int ghostDir = random(4);

  return ghostDir;
}

void loadSprites()
{
  //Mrs. Pacman
  GD.BitmapHandle(PACMANLEFT_HANDLE);
  GD.BitmapLayout(ARGB4, 2 * 15, 15);

  GD.BitmapHandle(PACMANRIGHT_HANDLE);
  GD.BitmapLayout(ARGB4, 2 * 15, 15);

  GD.BitmapHandle(PACMANUP_HANDLE);
  GD.BitmapLayout(ARGB4, 2 * 15, 15);
  
  GD.BitmapHandle(PACMANDOWN_HANDLE);
  GD.BitmapLayout(ARGB4, 2 * 15, 15);

  //map
  GD.BitmapHandle(PM_HANDLE);
  GD.BitmapLayout(ARGB4, 2 * 256, 256);

  //blinky 
  GD.BitmapHandle(BLINKYDOWN_HANDLE);
  GD.BitmapLayout(ARGB4, 2 * 16, 16);

  //pinky
  GD.BitmapHandle(PINKYDOWN_HANDLE);
  GD.BitmapLayout(ARGB4, 2 * 16, 16);

  //inky
  GD.BitmapHandle(INKYDOWN_HANDLE);
  GD.BitmapLayout(ARGB4, 2 * 16, 16);

  //clyde
  GD.BitmapHandle(CLYDEDOWN_HANDLE);
  GD.BitmapLayout(ARGB4, 2 * 16, 16);

  //scared ghost
  GD.BitmapHandle(SCAREDGHOST_HANDLE);
  GD.BitmapLayout(ARGB4, 2 * 16, 16); 
}

//calculates the index for our current tile via using the current pixel-position
void calculateStartTile()
{  
  for(int curRow=0; curRow < rows; curRow++)
  {
    for(int curCol = 0; curCol <= cols; curCol++)
    {
      if(curCol == 28)
      {
         rectPosX = 16;
         rectPosY = rectPosY + rectRad;
      }
      //pacman
      else if(levelMap[curRow][curCol] == 5)
      {
        playerPosX = rectPosX + (rectRad*0.5);
        playerPosY = rectPosY + (rectRad*0.5)+4;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      ;
        curTile.currentX = curCol;
        curTile.currentY = curRow;
        rectPosX += rectRad;
      }
      //ghosts
      else if(levelMap[curRow][curCol] == 4)
      {
        clydePosX = rectPosX + (rectRad*0.5)-4;
        clydePosY = rectPosY + (rectRad*0.5);
        clydeCurTile.currentX = curCol;
        clydeCurTile.currentY = curRow;

        pinkyPosX = clydePosX - 16;
        pinkyPosY = clydePosY;
        pinkyCurTile.currentX = curCol-2;
        pinkyCurTile.currentY = curRow;

        inkyPosX = clydePosX - 32;
        inkyPosY = clydePosY;
        inkyCurTile.currentX = curCol-4;
        inkyCurTile.currentY = curRow;
        
        rectPosX += rectRad;
      }
      else if(levelMap[curRow][curCol] == 6)
      {
        blinkyPosX = rectPosX + (rectRad*0.5)-4;
        blinkyPosY = rectPosY + (rectRad*0.5)+4;
        blinkyCurTile.currentX = curCol;
        blinkyCurTile.currentY = curRow;
        rectPosX += rectRad;
      }
      else
      {
        rectPosX += rectRad;
      }
    }
  }
}

void scorePoints()
{
  if(levelMap[curTile.currentY][curTile.currentX] == 1)
  {
    GD.play(MUSICBOX, 30);
    score += 10;
    levelMap[curTile.currentY][curTile.currentX] = 3;
    pluttCounter++;
  }
  else if(levelMap[curTile.currentY][curTile.currentX] == 2)
  {
    GD.play(TUBA, 60);
    score += 50;
    levelMap[curTile.currentY][curTile.currentX] = 3;
    scaredGhosts = true;
    pluttCounter++;
  }
  //GD.ColorRGB(0xff69b4);
  GD.cmd_text(275, 10, 20, OPT_CENTER, "Score: ");
  GD.cmd_number(300, 10, 20, OPT_CENTER, score);
}

void drawGhosts()
{
  GD.ColorRGB(0xffffff);
  GD.Begin(BITMAPS);
  GD.Vertex2ii(clydePosX-7, clydePosY-8, CLYDEDOWN_HANDLE, ghostAnim);
  GD.Vertex2ii(inkyPosX-7, inkyPosY-8, INKYDOWN_HANDLE, ghostAnim);
  GD.Vertex2ii(pinkyPosX-7, pinkyPosY-8, PINKYDOWN_HANDLE, ghostAnim);
  GD.Vertex2ii(blinkyPosX-7, blinkyPosY-8, BLINKYDOWN_HANDLE, ghostAnim);
}

void gameOver()
{
  GD.cmd_text(275, 20, 20, OPT_CENTER, "Lives: ");
  GD.cmd_number(300, 20, 20, OPT_CENTER, lives);
  if(curTile.currentY == blinkyCurTile.currentY && curTile.currentX == blinkyCurTile.currentX && scaredGhosts != true)
  {
    if(lives > 0)
    {
      lives--;
      //delete blinky and set the startpos for it again
      blinkyPosX = 128;
      blinkyPosY = 100;
      blinkyCurTile.currentX = 14;
      blinkyCurTile.currentY = 11;
      
      //reset inky 
      inkyPosX = 112;
      inkyPosY = 128;
      inkyCurTile.currentX = 12;
      inkyCurTile.currentY = 15;
      
      
      //delete pinky and set the startpos for him again
      pinkyPosX = 128;
      pinkyPosY = 128;
      pinkyCurTile.currentX = 14;
      pinkyCurTile.currentY = 15; 
      
      
      //delete clyde and set the startpos for him again
      clydePosX = 144;
      clydePosY = 128;
      clydeCurTile.currentX = 16;
      clydeCurTile.currentY = 15;

      playerPosX = 132;
      playerPosY = 196;
      curTile.currentX = 14;
      curTile.currentY = 23;
      
      clydeResetCounter = 0;
      pinkyResetCounter = 0;
      inkyResetCounter = 0;
    }
  }
  if(curTile.currentY == inkyCurTile.currentY && curTile.currentX == inkyCurTile.currentX && scaredGhosts != true)
  {
    if(lives > 0)
    {
      lives--;
      //delete blinky and set the startpos for it again
      blinkyPosX = 136;
      blinkyPosY = 100;
      blinkyCurTile.currentX = 14;
      blinkyCurTile.currentY = 11;
      
      //reset inky 
      inkyPosX = 112;
      inkyPosY = 128;
      inkyCurTile.currentX = 12;
      inkyCurTile.currentY = 15;
      
      
      //delete pinky and set the startpos for him again
      pinkyPosX = 128;
      pinkyPosY = 128;
      pinkyCurTile.currentX = 14;
      pinkyCurTile.currentY = 15; 
      
      
      //delete clyde and set the startpos for him again
      clydePosX = 144;
      clydePosY = 128;
      clydeCurTile.currentX = 16;
      clydeCurTile.currentY = 15;
      
      clydeResetCounter = 0;
      pinkyResetCounter = 0;
      inkyResetCounter = 0;
    }
  }
  if(curTile.currentY == pinkyCurTile.currentY && curTile.currentX == pinkyCurTile.currentX && scaredGhosts != true)
  {
    if(lives > 0)
    {
      lives--;
      //delete blinky and set the startpos for it again
      blinkyPosX = 136;
      blinkyPosY = 100;
      blinkyCurTile.currentX = 14;
      blinkyCurTile.currentY = 11;
      
      //reset inky 
      inkyPosX = 112;
      inkyPosY = 128;
      inkyCurTile.currentX = 12;
      inkyCurTile.currentY = 15;
      
      
      //delete pinky and set the startpos for him again
      pinkyPosX = 128;
      pinkyPosY = 128;
      pinkyCurTile.currentX = 14;
      pinkyCurTile.currentY = 15; 
      
      
      //delete clyde and set the startpos for him again
      clydePosX = 144;
      clydePosY = 128;
      clydeCurTile.currentX = 16;
      clydeCurTile.currentY = 15;
      
      clydeResetCounter = 0;
      pinkyResetCounter = 0;
      inkyResetCounter = 0;
    }
  }
  if(curTile.currentY == clydeCurTile.currentY && curTile.currentX == clydeCurTile.currentX && scaredGhosts != true)
  {
    if(lives > 0)
    {
      lives--;
      //delete blinky and set the startpos for it again
      blinkyPosX = 136;
      blinkyPosY = 100;
      blinkyCurTile.currentX = 14;
      blinkyCurTile.currentY = 11;
      
      inkyPosX = 112;
      inkyPosY = 128;
      inkyCurTile.currentX = 12;
      inkyCurTile.currentY = 15;
      
      
      //delete pinky and set the startpos for him again
      pinkyPosX = 128;
      pinkyPosY = 128;
      pinkyCurTile.currentX = 14;
      pinkyCurTile.currentY = 15; 
      
      
      //delete clyde and set the startpos for him again
      clydePosX = 144;
      clydePosY = 128;
      clydeCurTile.currentX = 16;
      clydeCurTile.currentY = 15;
      
      clydeResetCounter = 0;
      pinkyResetCounter = 0;
      inkyResetCounter = 0;
    }
  } 
  if(pinkyResetCounter == 20)
  {
    pinkyPosX = 128;
    pinkyPosY = 100;
    pinkyCurTile.currentX = 14;
    pinkyCurTile.currentY = 11;
  }
  if(inkyResetCounter == 40)
  {
    inkyPosX = 128;
    inkyPosY = 100;
    inkyCurTile.currentX = 14;
    inkyCurTile.currentY = 11;
  }
  if(clydeResetCounter == 60)
  {
    clydePosX = 128;
    clydePosY = 100;
    clydeCurTile.currentX = 14;
    clydeCurTile.currentY = 11;       
  }
  if(lives == 0)
  {
    GD.cmd_text(240, 136, 31, OPT_CENTER, "GAME OVER!");
  }
}

void drawScaredGhost()
{
  GD.ColorRGB(0xffffff);
  GD.Begin(BITMAPS);
  GD.Vertex2ii(clydePosX-7, clydePosY-8, SCAREDGHOST_HANDLE, ghostAnim);
  GD.Vertex2ii(inkyPosX-7, inkyPosY-8, SCAREDGHOST_HANDLE, ghostAnim);
  GD.Vertex2ii(pinkyPosX-7, pinkyPosY-8, SCAREDGHOST_HANDLE, ghostAnim);
  GD.Vertex2ii(blinkyPosX-7, blinkyPosY-8, SCAREDGHOST_HANDLE, ghostAnim);
}

void huntGhosts()
{
  //if we catch blinky
  if(curTile.currentY == blinkyCurTile.currentY && curTile.currentX == blinkyCurTile.currentX && scaredGhosts == true)
  {
    GD.play(XYLOPHONE, 21);
    score += 200; 
    //delete ghost and set the startpos for it again
    blinkyPosX = 136;
    blinkyPosY = 100;
    blinkyCurTile.currentX = 14;
    blinkyCurTile.currentY = 11;
  }
  
  //if we catch inky
  else if(curTile.currentY == inkyCurTile.currentY && curTile.currentX == inkyCurTile.currentX && scaredGhosts == true)
  {
    GD.play(XYLOPHONE, 21);
    score += 200;
    //reset ghost 
    inkyPosX = 112;
    inkyPosY = 128;
    inkyCurTile.currentX = 12;
    inkyCurTile.currentY = 15;

    inkyResetCounter = 0;
  }
  
  //if we catch pinky
  else if(curTile.currentY == pinkyCurTile.currentY && curTile.currentX == pinkyCurTile.currentX && scaredGhosts == true)
  {
    GD.play(XYLOPHONE, 21);
    score += 200;
    
    //delete ghost and set the startpos for it again
    pinkyPosX = 128;
    pinkyPosY = 128;
    pinkyCurTile.currentX = 14;
    pinkyCurTile.currentY = 15;
    
    pinkyResetCounter = 0;
  }

  //if we catch clyde
  else if(curTile.currentY == clydeCurTile.currentY && curTile.currentX == clydeCurTile.currentX && scaredGhosts == true)
  {
    GD.play(XYLOPHONE, 21);
    score += 200;
    //delete ghost and set the startpos for it again
    clydePosX = 144;
    clydePosY = 128;
    clydeCurTile.currentX = 16;
    clydeCurTile.currentY = 15;

    clydeResetCounter = 0;
  }

  //check when ghosts are allowed to leave house
  if(clydeResetCounter == 30)
  {
    clydePosX = 128;
    clydePosY = 100;
    clydeCurTile.currentX = 14;
    clydeCurTile.currentY = 11;
  }
  if(pinkyResetCounter == 30)
  {
    pinkyPosX = 128;
    pinkyPosY = 100;
    pinkyCurTile.currentX = 14;
    pinkyCurTile.currentY = 11;
  }
  if(inkyResetCounter == 30)
  {
    inkyPosX = 128;
    inkyPosY = 100;
    inkyCurTile.currentX = 14;
    inkyCurTile.currentY = 11;
  }
  
}

