#include <LiquidCrystal.h>
#include <EEPROM.h>
#include <LedControl.h>

#define LCD_LIGHT_PIN A4
#define DEBOUNCE_DELAY 100
#define INTERVAL_START 3000
#define INTERVAL_INFO 2500
#define SECOND 1000
#define BALL_SPEED 150
#define LAST_ROW 7
#define BLINK 200

//Matrix
LedControl lc = LedControl(12, 11, 10, 1); // DIN, CLK, LOAD, 1 - NO. DRIVER

const bool Arena1[8][8] = 
{
  {1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 0, 1, 1, 0, 1, 1},
  {0, 1, 1, 1, 1, 1, 1, 0},
  {0, 0, 1, 1, 1, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}
};

const bool Arena2[8][8] = 
{
  {1, 1, 1, 1, 1, 1, 1, 1},
  {0, 1, 0, 1, 0, 1, 0, 1},
  {1, 0, 1, 0, 1, 0, 1, 0},
  {1, 1, 1, 1, 1, 1, 1, 1},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}
};

const bool Arena3[8][8] = 
{
  {1, 0, 1, 1, 1, 1, 0, 1},
  {1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1},
  {1, 0, 0, 1, 1, 0, 0, 1},
  {1, 1, 1, 1, 1, 1, 1, 1},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}
};

//LCD Display
const int rsPin = 8;
const int ePin = 6;
const int d4Pin = 5;
const int d5Pin = 4;
const int d6Pin = 3;
const int d7Pin = 2;

LiquidCrystal lcd(rsPin, ePin, d4Pin, d5Pin, d6Pin, d7Pin);

// setting animation speed (delay between frames)
int x = 150;

// START setting all the pixel-art
//setting pixels for standing man:
//step 1 of 1:
  byte stepA1[8] = {B00011,B00111,B00111,B00111,B00111,B00001,B00011,B00111};
  byte stepA2[8] = {B00001,B00001,B00011,B00011,B00011,B00001,B00000,B00001};
  byte stepA3[8] = {B11111,B11111,B11111,B11111,B11111,B11011,B10001,B10001};
  byte stepA4[8] = {B11111,B11111,B11101,B11101,B11111,B11111,B11111,B11111};
  byte stepA5[8] = {B11000,B11100,B11100,B11100,B11100,B10000,B11000,B11100};
  byte stepA6[8] = {B00000,B10000,B11000,B00000,B11000,B11100,B11000,B10000};
  
//setting pixels for running man right:
//step 1 of 3:
  byte stepB1[8] = {B00011,B00011,B00011,B00011,B00001,B00000,B00000,B00000};
  byte stepB2[8] = {B00000,B00001,B00001,B00011,B00011,B00011,B00000,B00001};
  byte stepB3[8] = {B11111,B11111,B11111,B11111,B11111,B11111,B11111,B11110};
  byte stepB4[8] = {B11111,B11111,B11101,B11101,B11111,B11111,B11111,B11111};
  byte stepB5[8] = {B00000,B00000,B10000,B10000,B10000,B00000,B10000,B00000};
  byte stepB6[8] = {B00000,B11000,B00000,B11000,B11100,B11000,B10000,B00000};

//step 2 of 3
  byte stepC1[8] = {B11111,B11111,B11101,B00011,B00111,B01111,B01111,B00111};
  byte stepC2[8] = {B00000,B00001,B00001,B00011,B00011,B00011,B00000,B00111};
  byte stepC3[8] = {B11111,B11111,B11111,B11111,B11111,B10011,B00000,B00000};
  byte stepC4[8] = {B11111,B11111,B11101,B11101,B11111,B11111,B11111,B11111};
  byte stepC5[8] = {B11110,B11110,B01100,B11100,B11100,B11100,B00000,B00000};
  byte stepC6[8] = {B00000,B11000,B00000,B11000,B11100,B11000,B10000,B00000};
  
//step 3 of 3
  byte stepD1[8] = {B00001,B00011,B00111,B00111,B00111,B01111,B01100,B00000};
  byte stepD2[8] = {B00000,B00000,B00001,B00001,B00011,B00011,B00011,B00000};
  byte stepD3[8] = {B11111,B11111,B11111,B11111,B11111,B11111,B11110,B11111};
  byte stepD4[8] = {B00000,B11111,B11111,B11101,B11101,B11111,B11111,B11111};
  byte stepD5[8] = {B10000,B11000,B10000,B00000,B00000,B00000,B00000,B00000};
  byte stepD6[8] = {B00000,B00000,B11000,B00000,B11000,B11100,B11000,B10000};

//Button
const int buttonPin = 7;
int buttonState = 1;

//Joystick
const int pinJoySw = 9;
const int pinX = A0;
const int pinY = A1;

int joySwState = LOW;
int lastJoySwState = LOW;
int joySwitchValue;

int xValue = 0;
int yValue = 0;

bool joyMovedX = false;
bool joyMovedY = false;
const int minThreshold = 300;
const int maxThreshold = 700;

int startingLevel = 0;
const int noOfLevels = 3;
bool selected = false;
bool arenamem[8][8];
int lives;
int crtTime;
int score;
int speedy = 1;
int timePress[3] = {60, 90, 120};
char playerName[10] = "BigBoss  ";
int letterPlace;

int hiScore1;
int hiScore2;
int hiScore3;
char hiName1[10];
char hiName2[10];
char hiName3[10];

byte smile[8] = {B00000, B10001, B00000, B00000, B10001, B01110, B00000};

// START putting all the pixel-art we defined before in his place for each animation part
// standing man animation part

void standingMan()
{
  int a = 0;
  int b = a + 1;
  int c = a + 2;
  lcd.createChar(1, stepA1);
  lcd.createChar(2, stepA2);
  lcd.createChar(3, stepA3);
  lcd.createChar(4, stepA4);
  lcd.createChar(5, stepA5);
  lcd.createChar(6, stepA6);
  lcd.setCursor(a,1);
  lcd.write(1);
  lcd.setCursor(a,0);
  lcd.write(2);
  lcd.setCursor(b,1);
  lcd.write(3);
  lcd.setCursor(b,0);
  lcd.write(4);
  lcd.setCursor(c,1);
  lcd.write(5);
  lcd.setCursor(c,0);
  lcd.write(6);
}

// running man to the right animation part
void runningManR() 
{
  for (int a = 0; a < 11; a += 4)
  {
    int b = a + 1;
    int c = a + 2;
    int d = a + 3;
    int e = a + 4;
    int f = a + 5;
    int g = a + 6;
    lcd.clear();
    lcd.createChar(1, stepB1);
    lcd.createChar(2, stepB2);
    lcd.createChar(3, stepB3);
    lcd.createChar(4, stepB4);
    lcd.createChar(5, stepB5);
    lcd.createChar(6, stepB6);
    lcd.setCursor(b,1);
    lcd.write(1);
    lcd.setCursor(b,0);
    lcd.write(2);
    lcd.setCursor(c,1);
    lcd.write(3);
    lcd.setCursor(c,0);
    lcd.write(4);
    lcd.setCursor(d,1);
    lcd.write(5);
    lcd.setCursor(d,0);
    lcd.write(6);
    delay(x);
    lcd.clear();
    lcd.createChar(1, stepC1);
    lcd.createChar(2, stepC2);
    lcd.createChar(3, stepC3);
    lcd.createChar(4, stepC4);
    lcd.createChar(5, stepC5);
    lcd.createChar(6, stepC6);
    lcd.setCursor(c,1);
    lcd.write(1);
    lcd.setCursor(c,0);
    lcd.write(2);
    lcd.setCursor(d,1);
    lcd.write(3);
    lcd.setCursor(d,0);
    lcd.write(4);
    lcd.setCursor(e,1);
    lcd.write(5);
    lcd.setCursor(e,0);
    lcd.write(6);
    delay(x);
    lcd.clear();
    lcd.createChar(1, stepB1);
    lcd.createChar(2, stepB2);
    lcd.createChar(3, stepB3);
    lcd.createChar(4, stepB4);
    lcd.createChar(5, stepB5);
    lcd.createChar(6, stepB6);
    lcd.setCursor(d,1);
    lcd.write(1);
    lcd.setCursor(d,0);
    lcd.write(2);
    lcd.setCursor(e,1);
    lcd.write(3);
    lcd.setCursor(e,0);
    lcd.write(4);
    lcd.setCursor(f,1);
    lcd.write(5);
    lcd.setCursor(f,0);
    lcd.write(6);
    delay(x);
    lcd.clear();
    lcd.createChar(1, stepD1);
    lcd.createChar(2, stepD2);
    lcd.createChar(3, stepD3);
    lcd.createChar(4, stepD4);
    lcd.createChar(5, stepD5);
    lcd.createChar(6, stepD6);
    lcd.setCursor(e,1);
    lcd.write(1);
    lcd.setCursor(e,0);
    lcd.write(2);
    lcd.setCursor(f,1);
    lcd.write(3);
    lcd.setCursor(f,0);
    lcd.write(4);
    lcd.setCursor(g,1);
    lcd.write(5);
    lcd.setCursor(g,0);
    lcd.write(6);
    delay(x);
  }
}

class Ball 
{
  public:
    int x;
    int y;
    int val;
    bool up;
    bool hit;
    bool bounceUp;
    bool bounceDown;
    Ball();
    void light(LedControl&, int);
    void moveMiddle(bool (&arenamem)[8][8]);
    void moveLeft(bool (&arenamem)[8][8]);
    void moveRight(bool (&arenamem)[8][8]);
};

Ball::Ball() 
{
  x = 4;
  y = 6;
  val = 1;
  up = false;
  hit = true;
  bounceUp = false;
  bounceDown = false;
}

void Ball::moveMiddle(bool (&arenamem)[8][8]) 
{
  if (up == true) 
    {
      --y;
      if (y < 1) 
        {
          y = 0;
          up = !up;
        } 
    } 
  else 
    {
      ++y;
      if (y > 5) 
        {
          y = 6;
          up = !up;
          hit = !hit;
        }
    }
  arenamem[y][x] = 0;
}

void Ball::moveLeft(bool (&arenamem)[8][8]) 
{
  if (up == true) 
    {
      if (bounceUp == true) 
        {
          ++x;
        } 
      else 
        {
          --x;
        }
      --y;
      if (y < 1) 
        {
          up = !up;
          bounceUp = false;
        }  
      else if (x < 1) 
        {
          bounceUp = true;
          x = 0;
        } 
      else if (x > 6) 
        {
          x = 7;
        }
    } 
  else 
    {
      if (bounceDown == true) 
        {
          --x;
        }    
      else 
        {
          ++x;
        }
      y++;
      if (y > 5) 
        {
          up = !up;
          hit = !hit;
          bounceDown = false;
        } 
      else if (x > 6) 
        {
          bounceDown = true;
          x = 7;
        } 
      else if (x < 1) 
        {
          x = 0;
        }
    }
  arenamem[y][x] = 0;
}

void Ball::moveRight(bool (&arenamem)[8][8]) 
{
  if (up == true) 
    {
      if (bounceUp == true) 
        {
          --x;
        } 
      else 
        {
          ++x;
        }
      --y;
      if (y < 1) 
        {
          bounceUp = false;
          up = !up;
        } 
      else if (x > 6)
        {
          x = 7;
          bounceUp = true;
        }  
      else if (x < 1) 
        {
          x = 0;
        } 
    } 
  else 
    {
      if (bounceDown == true) 
        {
          ++x;
        } 
      else 
        {
          --x;
        }
      y++;
      if (y > 5) 
        {
          bounceDown = false;
          hit = !hit;
          up = !up;
        } 
      else if (x < 1) 
        {
          bounceDown = true;
          x = 0;
        } 
      else if (x > 6) 
        {
          x = 7;
        }
    }
  arenamem[y][x] = 0;
}

void Ball::light(LedControl& lc, int state) 
{
  lc.setLed(0, y, x, state);
}

class Paddle 
{
  public:
    int pos;
    Paddle(int screen_width);
    void moveLeft(LedControl& lc);
    void moveRight(LedControl& lc);
    void light(LedControl& lc, int);
    private:
    int screen_width_;
   
};

Paddle::Paddle(int screen_width): screen_width_(screen_width) 
{
  pos = screen_width_ / 2 - 1;  
}

void Paddle::moveLeft(LedControl& lc) 
{
  if (pos > -1) 
    {
      this->light(lc, LOW);
      --pos;
      this->light(lc, HIGH);
    }
}

void Paddle::moveRight(LedControl& lc) 
{
  if (pos + 2 < screen_width_) 
    {
      this->light(lc, LOW);
      ++pos;
      this->light(lc, HIGH);
    } 
}

void Paddle::light(LedControl& lc, int state) 
{
  lc.setLed(0, 7, pos, state);
  lc.setLed(0, 7, pos + 1, state);
  lc.setLed(0, 7, pos + 2, state); 
}

class Faces
{
  public:
    const bool sadFace[8][8] = 
      {
       {0,1,0,0,0,0,1,0},
       {1,0,1,0,0,1,0,1},
       {0,0,0,0,0,0,0,0},
       {0,0,0,0,0,0,0,0},
       {0,0,0,1,1,0,0,0},
       {0,0,1,0,0,1,0,0},
       {0,1,0,0,0,0,1,0},
       {0,1,0,0,0,0,1,0}
      };
    const bool happyFace[8][8] = 
      {
        {0,1,0,0,0,0,1,0},
        {1,1,1,0,0,1,1,1},
        {0,1,0,0,0,0,1,0},
        {0,0,0,0,0,0,0,0},
        {0,1,0,0,0,0,1,0},
        {0,1,0,0,0,0,1,0},
        {0,0,1,0,0,1,0,0},
        {0,0,0,1,1,0,0,0}
     };
};

void createArena(int levelID)
{
  if(levelID == 1)
    {
     for (int row = 0; row < 8; row++)
       for (int col = 0; col < 8; col++)
          {
            lc.setLed(0, row, col, Arena1[row][col]);
            arenamem[row][col] = Arena1[row][col];
          }
    }
  if(levelID == 2)
    {
     for (int row = 0; row < 8; row++)
       for (int col = 0; col < 8; col++)
          {
            lc.setLed(0, row, col, Arena2[row][col]);
            arenamem[row][col] = Arena2[row][col];
          }
    }
  if(levelID == 3)
    {
     for (int row = 0; row < 8; row++)
       for (int col = 0; col < 8; col++)
          {
            lc.setLed(0, row, col, Arena3[row][col]);
            arenamem[row][col] = Arena3[row][col];
          }
    }
}

Faces faces;
Paddle p{8};
Ball b;

int levelID;
unsigned long wait = 0;
unsigned long millises;
bool restart = false;
bool left = false;
bool middle = false;
bool right = false;
bool joyMoved;
bool ok;

void printer(LedControl& lc, bool arenamem[8][8])
{
    for(int i = 0; i < 8; ++i) 
      for(int j = 0; j < 8; ++j) 
      {
        lc.setLed(0, i, j, arenamem[i][j]); 
      }
  
}

void SETUP(LedControl& lc)
{
  printer(lc, arenamem);
  p.light(lc, HIGH);
  b.light(lc, HIGH);
}
    
void movePaddle(LedControl& lc)
{
  int xValue = analogRead(pinX);
  if (xValue < minThreshold && joyMoved == false) 
    {
      p.moveLeft(lc);
      joyMoved = true;
    }
  if (xValue > maxThreshold && joyMoved == false) 
    {
      p.moveRight(lc);
      joyMoved = true;
    }
  if (xValue < maxThreshold && xValue > minThreshold) 
    {
      joyMoved = false;
    }
}

bool finishedGame()
{
  for(int i = 0; i < 6; ++i) 
    {
      for(int j = 0; j < 8; ++j) 
        {
          if (arenamem[i][j] == 1) 
            {
              return false;
            }
         }
    }
  return true;
}
    
void bricks(int level)
{
  createArena(level);
}
    
void resetBricks(int level)
{
  createArena(level);
}

void stopG(LedControl& lc)
{
  p.light(lc, LOW);
  b.light(lc, LOW);
}

void won()
{
  // clear level and add happy winner face :)
  for(int i = 0; i < 8; i++)
    {
      for(int j = 0; j < 8; j++)
        {   
          arenamem[i][j] = faces.happyFace[i][j];
          lc.setLed(0, i, j, arenamem[i][j]);
        }   
    }
}

void lost()
{
  // clear level and add sad loser face :(
  for(int i = 0; i < 8; i++)
    {
      for(int j = 0; j < 8; j++)
        {   
          arenamem[i][j] = faces.sadFace[i][j];
          lc.setLed(0, i, j, arenamem[i][j]);
        }   
    }
}

void startGame(LedControl& lc, float speedy)
{
  unsigned long crtTime = millises - wait;  
  if (crtTime >= BALL_SPEED * speedy) 
    {
      if (restart == false) 
        {
          if (b.hit == true) 
            {
              left = false;
              middle = false;
              right = false;
              if (b.x == p.pos || b.x == p.pos - 1) 
                {
                  left = !left;
                  b.light(lc, LOW);
                  b.moveLeft(arenamem);
                  b.light(lc, HIGH);
                  b.hit = !b.hit;
                } 
              else if (b.x == p.pos + 1) 
                {
                  middle = !middle;
                  b.light(lc, LOW);
                  b.moveMiddle(arenamem);
                  b.light(lc, HIGH);
                  b.hit = !b.hit;
                } 
              else if (b.x == p.pos + 2 || b.x == p.pos + 3) 
                {
                  right = !right;
                  b.light(lc, LOW);
                  b.moveRight(arenamem);
                  b.light(lc, HIGH);
                  b.hit = !b.hit;
                } 
              else 
                {
                  restart = !restart;
                }
            } 
        else 
        {
          if (left == true) 
            {
              b.light(lc, LOW);
              b.moveLeft(arenamem);
              b.light(lc, HIGH);
            }
          if (middle == true) 
            {
              b.light(lc, LOW);
              b.moveMiddle(arenamem);
              b.light(lc, HIGH);
            }
          if (right == true) 
            {
              b.light(lc, LOW);
              b.moveRight(arenamem);
              b.light(lc, HIGH);
            }
        }
    } 
  else 
    {
      p.light(lc, LOW);
      p.pos = 3;
      p.light(lc, HIGH);
      b.light(lc, LOW);
      b.x = 4;
      b.y = 6;
      b.light(lc, HIGH);
      restart = !restart;
    }
    wait = millises;
  }
}

void lcdLight(int buttonState)
{
 if (buttonState == 1)
  {
    // Turn the backlight on.
    digitalWrite(LCD_LIGHT_PIN, HIGH);
    // Display the text on the LCD.
    lcd.display();
  }
 if (buttonState == 0)
  {
    // Stop displaying the text on the LCD.
    lcd.noDisplay();
    // Turn the backlight off
    digitalWrite(LCD_LIGHT_PIN, LOW); 
  }
}

class Setup 
{  
  public:
    int option;
    int level;
    int speed;
    bool pressedButton;
    bool back;
    Setup();
    void print(LiquidCrystal&);
    void printWhenButtonPressed(LiquidCrystal&, int&, bool&);
    void printLevel(LiquidCrystal&);
    void printSpeed(LiquidCrystal&);
    void modifyLevel(int, bool&, int&, float&, int&);
    void modifySpeed(int, bool&, float&);
    void modifyOption(int, bool&);  
};

Setup::Setup() 
{
  pressedButton = false;
  option = 1;
  level = 1;
  speed = 1;
}

void Setup::print(LiquidCrystal& lcd) 
{
  switch (option) 
  {
    case 1: 
      {
        lcd.setCursor(0, 0);
        lcd.print(">Level");
        lcd.setCursor(0, 1);
        lcd.print(" Speed");
        lcd.setCursor(7, 1);
        lcd.print(" Back");
        break;
      }
    case 2: 
      {
        lcd.setCursor(0, 0);
        lcd.print(" Level");
        lcd.setCursor(0, 1);
        lcd.print(">Speed");
        lcd.setCursor(7, 1);
        lcd.print(" Back");
        break;
      }
    case 3: 
      {
        lcd.setCursor(0, 0);
        lcd.print(" Level");
        lcd.setCursor(0, 1);
        lcd.print(" Speed");
        lcd.setCursor(7, 1);
        lcd.print(">Back");
        break;
      }
  }
}

void Setup::printWhenButtonPressed(LiquidCrystal& lcd, int& optionMenu, bool& pressed) 
{
  switch(option) 
  {
    case 1: 
    {
      this->printLevel(lcd);
      break;
    }
    case 2: 
    {
     this->printSpeed(lcd);
     break;
    }
    case 3: 
    {
      lcd.clear();
      pressed = false;
      pressedButton = false;
      optionMenu = 1;
      break;
    }
  }
}

void Setup::printLevel(LiquidCrystal& lcd) 
{
  lcd.setCursor(0, 0);
  lcd.print("Level:");
  lcd.setCursor(0, 1);
  switch(level) 
  {
    case 1: 
    {
      lcd.print("Easy     ");
      break;
    }
    case 2: 
    {
      lcd.print("Medium   ");
      break;
    }
    case 3: 
    {
      lcd.print("Difficult");
      break;
    }
  }
}

void Setup::printSpeed(LiquidCrystal& lcd) 
{
  lcd.setCursor(0, 0);
  lcd.print("Speed:");
  lcd.setCursor(0, 1);
  switch(speed) 
  {
    case 1: 
      {
        lcd.print("1 m/sec");
        break;
      }
    case 2: 
      {
        lcd.print("2 m/sec");
        break;
      }
    case 3: 
      {
        lcd.print("3 m/sec");
        break;
      }
  }
}

void Setup::modifyLevel(int yValue, bool& joyMoved, int& timeLeft, float& score, int& firstDigit) 
{
  if (yValue < minThreshold && joyMoved == false) 
    {
      ++level;
      if (level > 3) 
        {
          level = 1; 
        }
      joyMoved = true;
    } 
  if (yValue > maxThreshold && joyMoved == false) 
    {
      --level;
      if (level < 1) 
        {
          level = 3;
        }
      joyMoved = true;
    }
  if (yValue > minThreshold && yValue < maxThreshold) 
    {
      joyMoved = false;
    }
  switch(level) 
    {
      case 1: 
        {
          firstDigit = 4;
          timeLeft = 240;
          score = 240;
          break;
       }
     case 2: 
       {
        firstDigit = 3;
        timeLeft = 180;
        score = 180 * 1.5;
        break;
      }
    case 3: 
      {
        firstDigit = 2;
        timeLeft = 120;
        score = 120 * 2.5;
        break;
      }
  }  
}

void Setup::modifySpeed(int yValue, bool& joyMoved, float& menuSpeed) 
{
  if (yValue < minThreshold && joyMoved == false) 
    {
      ++speed;
      if (speed > 3) 
        {
          speed = 1; 
        }
      joyMoved = true;
    } 
  if (yValue > maxThreshold && joyMoved == false) 
    {
      --speed;
      if (speed < 1) 
        {
          speed = 3;
        }
      joyMoved = true;
    }
  if (yValue > minThreshold && yValue < maxThreshold) 
    {
      joyMoved = false;
    }
  switch(speed) 
  {
    case 1: 
      {
        menuSpeed = 1;
        break;
      }
    case 2: 
      {
        menuSpeed = 0.75;
        break;
      }
    case 3: 
      {
        menuSpeed = 0.5;
        break;
      }
  }  
}

void Setup::modifyOption(int xValue, bool& joyMoved) 
{
  if (xValue < minThreshold && joyMoved == false) 
    {
      ++option;
      if (option > 3) 
        {
          option = 1; 
        }
      joyMoved = true;
    } 
  if (xValue > maxThreshold && joyMoved == false) 
    {
      --option;
      if (option < 1) 
        {
          option = 3;
        }
      joyMoved = true;
    }
  if (xValue > minThreshold && xValue < maxThreshold) 
    {
      joyMoved = false;
    }
}

class Menu 
{
  public:
    Setup s;
    int option;
    int firstDigit;
    int secondDigit;
    int thirdDigit;
    bool startBreakout;
    bool startGameBreakout;
    bool stopBreakout;
    bool lost;
    bool won;
    bool waitDisplay;
    int timeLeft;
    float score;
    float highScore;
    float speed;
    bool pressedButton;
    unsigned long millis;
    unsigned long wait;
    unsigned long waitDigits;
    unsigned long waitKaneda;
    Menu();
    void modifyOption(int, bool&);
    void print(LiquidCrystal&);
    void printWhenButtonPressed(LiquidCrystal&);
    void printHighScore(LiquidCrystal&);
    void printStart(LiquidCrystal&);
    void printInfo(LiquidCrystal&);
    void changeTime();
};

Menu::Menu() 
{
  option = 1;
  score = 300;
  speed = 1;
  timeLeft = 300;
  firstDigit = 5;
  secondDigit = 0;
  thirdDigit = 0;
  startBreakout = false;
  startGameBreakout = false;
  stopBreakout = false;
  pressedButton = false;
  wait = 0;
  waitDisplay = 0;
  waitDigits = 0;
}

void Menu::print(LiquidCrystal& lcd) 
{
  switch (option) 
    {
      case 1: 
        {
          lcd.setCursor(0, 0);
          lcd.print(">Start");
          lcd.setCursor(7, 0);
          lcd.print(" Setup");
          lcd.setCursor(0, 1);
          lcd.print(" HighScore");
          lcd.setCursor(11, 1);
          lcd.print(" Info");
          break;
        }
      case 2: 
        {
          lcd.setCursor(0, 0);
          lcd.print(" Start");
          lcd.setCursor(7, 0);
          lcd.print(">Setup");
          lcd.setCursor(0, 1);
          lcd.print(" HighScore");
          lcd.setCursor(11, 1);
          lcd.print(" Info");
          break;
        }
      case 3: 
        {
          lcd.setCursor(0, 0);
          lcd.print(" Start");
          lcd.setCursor(7, 0);
          lcd.print(" Setup");
          lcd.setCursor(0, 1);
          lcd.print(">HighScore");
          lcd.setCursor(11, 1);
          lcd.print(" Info");
          break;
        }
    case 4: 
        {
          lcd.setCursor(0, 0);
          lcd.print(" Start");
          lcd.setCursor(7, 0);
          lcd.print(" Setup");
          lcd.setCursor(0, 1);
          lcd.print(" HighScore");
          lcd.setCursor(11, 1);
          lcd.print(">Info");
          break;
        }
    }
}

void Menu::printStart(LiquidCrystal& lcd) 
{
  unsigned long crtTime = millises - wait;
  if (crtTime < INTERVAL_START) 
    {
      lcd.setCursor(0, 0);
      lcd.print(" $Breakout$ ");
      lcd.setCursor(0, 1);
      lcd.print(" Arduino Game ");
    } 
  else if (crtTime > INTERVAL_START && crtTime < INTERVAL_START + 200) 
    {
      lcd.clear();
      waitDigits = millises;
      startBreakout = true;
    } 
  else if (crtTime > INTERVAL_START + 200 && timeLeft > -1 && won == false && lost == false) 
    {
      startBreakout = false;
      startGameBreakout = true;
      lcd.setCursor(0, 0);
      lcd.print("Time Left: ");
      lcd.setCursor(11, 0);
      lcd.print(firstDigit);
      lcd.setCursor(12, 0);
      lcd.print(":");
      lcd.setCursor(13, 0);
      lcd.print(secondDigit);
      lcd.setCursor(14, 0);
      lcd.print(thirdDigit);
      lcd.setCursor(0, 1);
      lcd.print("Score: ");
      lcd.setCursor(7, 1);
      if (score > 99) 
        {
          lcd.print(score);
          lcd.setCursor(10, 1);
          lcd.print(".");
        } 
      else if (score > 9) 
        {
          lcd.print(score);
          lcd.setCursor(9, 1);
          lcd.print(".");
          lcd.setCursor(12, 1);
          lcd.print(" ");
        } 
      else 
        {
          lcd.print(score);
          lcd.setCursor(8, 1);
          lcd.print(".");
          lcd.setCursor(11, 1);
          lcd.print("  ");
        }
      this->changeTime();
    }
}

void Menu::printHighScore(LiquidCrystal& lcd) 
{
  lcd.setCursor(0, 0);
  lcd.print("HighScore:");
  lcd.setCursor(0, 1);
  if (highScore > 99) 
    {
     lcd.print(highScore);
     lcd.setCursor(3, 1);
     lcd.print(".");
    } 
  else if (highScore > 9) 
    {
      lcd.print(highScore);
      lcd.setCursor(2, 1);
      lcd.print(".");
      lcd.setCursor(5, 1);
      lcd.print(" ");
    } 
  else 
    {
      lcd.print(highScore);
      lcd.setCursor(1, 1);
      lcd.print(".");
      lcd.setCursor(4, 1);
      lcd.print("  ");
    }
}

void Menu::printInfo(LiquidCrystal& lcd) 
{
  if ((millises - wait) < INTERVAL_INFO) 
    {
      lcd.setCursor(0, 0);
      lcd.print("Name:");
      lcd.setCursor(0, 1);
      lcd.print("Marin Catalin");
    } 
  else if ( (millises - wait) < INTERVAL_INFO + 200) 
    {
      lcd.clear();
    } 
  else if ((millises - wait) < INTERVAL_INFO * 2) 
    {
      lcd.setCursor(0, 0);
      lcd.print("Github:github");
      lcd.setCursor(0, 1);
      lcd.print(".com/Lewa21");
    } 
  else if ((millises - wait) < INTERVAL_INFO * 2 + 200) 
    {
      lcd.clear();
    } 
  else if ((millises - wait) < INTERVAL_INFO * 3) 
    {
      lcd.setCursor(0, 0);
      lcd.print("@UnibucRobotics");
      lcd.setCursor(0, 1);
    } 
  else 
    {
      lcd.clear();
      pressedButton = false;
    }
}

void Menu::printWhenButtonPressed(LiquidCrystal& lcd) 
{
  switch (option) 
    {
      case 1: 
        {
          this->printStart(lcd);
          break;
        }
      case 2: 
        {
          s.print(lcd);
          break;
        }
      case 3: 
        {
          this->printHighScore(lcd);
          break;
        }
      case 4: 
        {
          this->printInfo(lcd);
          break;
        }
    }
}

void Menu::modifyOption(int xValue, bool& joyMoved) 
{
  if (xValue < minThreshold && joyMoved == false) 
    {
      ++option;
      if (option > 4) 
        {
          option = 1;
        }
      joyMoved = true;
    }
  if (xValue > maxThreshold && joyMoved == false) 
    {
      --option;
      if (option < 1) 
        {
          option = 4;
        }
      joyMoved = true;
    }
  if (xValue > minThreshold && xValue < maxThreshold) 
    {
      joyMoved = false;
    }
}

void Menu::changeTime() 
{
  unsigned long crtTime = millises - waitDigits;
  if (crtTime > SECOND && timeLeft > 0) 
    {
      --timeLeft;
      switch (s.level) 
        {
          case 1: 
            {
              score -= 1;
              break;
            }
          case 2: 
            {
              score -= 1.5;
              break;
            }
          case 3: 
            {
              score -= 2.5;
              break;
            }
        }
      if (secondDigit == 0 && thirdDigit == 0) 
        {
          --firstDigit;
          secondDigit = 5;
          thirdDigit = 10;
        }
      if (thirdDigit == 0) 
        {
          --secondDigit;
          thirdDigit = 10;
        }
      --thirdDigit;
      waitDigits = millises;
    }
}

Menu menu;
unsigned long lastDebounceTime = 0;
int lastButtonState = HIGH;

void pressButton() 
{
  int buttonValue = digitalRead(pinJoySw);
  if (buttonValue != lastButtonState) 
    {
      lastDebounceTime = millis();
    }
  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) 
    {
      if (buttonValue != buttonState) 
        {
          buttonState = buttonValue;
          if (buttonState == LOW) 
            {
              if (menu.option == 2 && menu.pressedButton == true) 
                {
                  menu.s.pressedButton = !menu.s.pressedButton;
                } 
              else 
                {
                  menu.pressedButton = !menu.pressedButton;
                }
              menu.won = false;
              menu.lost = false;
              menu.wait = millis();
              lc.clearDisplay(0);
              lcd.clear();
            }
        }
    }
  lastButtonState = buttonValue;
}

void reset() 
{
  menu.startGameBreakout = false;
  menu.timeLeft = 240;
  menu.s.level = 1;
  menu.s.speed = 1;
  menu.score = 240;
  menu.firstDigit = 4;
  menu.secondDigit = 0;
  menu.thirdDigit = 0;
  resetBricks(1);
  p.pos = 3;
  b.x = 4;
  b.y = 6;
  EEPROM.write(0, menu.highScore);
}

void menuFunction() 
{
  pressButton();
  if (menu.pressedButton == true) 
    {
      if (menu.option == 1) 
        {
          if (menu.startBreakout == true) 
            {
              SETUP(lc);
            }
          if (menu.startGameBreakout == true) 
            {
              wait = millis();
              movePaddle(lc);
              startGame(lc, menu.speed);
            }
          if (finishedGame() == true) 
            {   
              menu.won = true;
            }
          if (menu.timeLeft == 0) 
            {
              menu.lost = true;
            }
          if (menu.won == true) 
            {
              if (menu.highScore < menu.score) 
                {
                 menu.highScore = menu.score;
                }
              reset();
              unsigned time = millis() - wait;
              if (time < 300) 
                {
                  lcd.clear();
                  lc.clearDisplay(0);
                }    
              else if (time > 300 && time < SECOND * 2) 
                {
                  lcd.setCursor(0, 0);
                  lcd.print("Nice save :)");
                } 
              else if (time > SECOND * 2 && time < SECOND * 2 + 300) 
                { 
                  lcd.clear();
                } 
              else if (time > SECOND * 2 + 300 && time < SECOND * 3) 
                {
                  lcd.setCursor(0, 0);
                  lcd.print("Press the button");
                  lcd.setCursor(0, 1);
                  lcd.print("to go back");
                }
            }
          if (menu.lost == true) 
            {
              reset();
              unsigned time = millis() - wait;
              if (time < 300) 
                {
                  lcd.clear();
                  lc.clearDisplay(0);
                } 
              else if (time > 300 && time < SECOND * 2) 
                {
                  lcd.setCursor(0, 0);
                  lcd.print("Sad reacts :(");
                } 
              else if (time > SECOND * 2 && time < SECOND * 2 + 300) 
                {
                  lcd.clear();
                } 
              else if (time > SECOND * 2 + 300 && time < SECOND * 3) 
                {
                  lcd.setCursor(0, 0);
                  lcd.print("Press the button");
                  lcd.setCursor(0, 1);
                  lcd.print("to go back");
                }
              }
            }
    if (menu.s.pressedButton == true) 
        {
          menu.s.printWhenButtonPressed(lcd, menu.option, menu.pressedButton);
          int yValue = analogRead(pinY);
          switch (menu.s.option) 
            {
              case 1: 
                {
                  menu.s.modifyLevel(yValue, joyMoved, menu.timeLeft, menu.score, menu.firstDigit);
                  break;
                }
              case 2: 
                {
                  menu.s.modifySpeed(yValue, joyMoved, menu.speed);
                  break;
                }
            }
        } 
    else 
        {
          int xValue = analogRead(pinX);
          menu.printWhenButtonPressed(lcd);
          menu.s.modifyOption(xValue, joyMoved);
        }
  } 
  else 
  {
    int xValue = analogRead(pinX);
    menu.print(lcd);
    menu.modifyOption(xValue, joyMoved);
  }
}

void setup() 
{
    pinMode(pinJoySw, INPUT_PULLUP);
    pinMode(buttonPin, INPUT_PULLUP);
    pinMode(LCD_LIGHT_PIN, OUTPUT);
    digitalWrite(LCD_LIGHT_PIN, HIGH);  
    lcd.begin (16, 2);
    standingMan();
    lcd.setCursor(4,0);
    lcd.print ("Welcome to ");
    lcd.setCursor (4,1);
    lcd.print ("my game! ");
    delay(3000);
    lcd.clear();
    lcd.createChar (7, smile);
    standingMan();
    lcd.setCursor(4,0);
    lcd.print("Help Keanu! ");
    lcd.setCursor (4,1);
    lcd.print("Smile! ");
    lcd.write (7); 
    delay(3000);
    lcd.clear();
    runningManR();
    lcd.clear();
    lc.shutdown(0,false);
    lc.setIntensity(0,2);
    lc.clearDisplay(0);
}

void loop() 
{
  buttonState = digitalRead(buttonPin);
  lcdLight(buttonState);
  xValue = analogRead(pinX);
  yValue = analogRead(pinY);
  millises = millis();
  menu.millis = millis();
  menuFunction();
  createArena(1);
  delay(2500);
  createArena(2);
  delay(2500);
  createArena(3);
  delay(2500);
  won();
  delay(2500); 
  lost();
  delay(2500);
}  
