#include<LiquidCrystal.h>

const int RS = 12;
const int E = 11;
const int D4 = 5;
const int D5 = 4;
const int D6 = 3;
const int D7 = 2;

int lineCursor = 0;

const int pinSW = 10;
const int pinX = A1;
const int pinY = A0;

int valueSW;
int valueX = 0;
int valueY = 0;

bool joyMoved = false;
int minThreshold = 450;
int maxThreshold = 550;

LiquidCrystal lcd(RS, E, D4, D5, D6, D7);

int buttonState = 0;
unsigned long lastButtonTime = 0;
unsigned long currentTime = 0;
const int periodSW = 200;

unsigned long lastLevelTime = 0;
unsigned long lastGameTime = 0;
const int levelTime = 2000;
const int gameTime = 10000;
int level = 0;
int Hscore = 0;
int lives = 3;
int verGame = 0;
int verScore = 0;
int verFinishedGame = 0;
int score;

void Menu() 
{
  lcd.setCursor(1, 0);
  lcd.print("Start ");
  lcd.setCursor(8, 0);
  lcd.print("Settings");
  lcd.setCursor(1, 1);
  lcd.print("HighScore      ");
}

void cursor() 
{
  lcd.setCursor(0, 0);
  lcd.print(" ");
  lcd.setCursor(7, 0);
  lcd.print(" ");
  lcd.setCursor(0, 1);
  lcd.print(" ");


  if (lineCursor < 0) lineCursor = 2;
  if (lineCursor > 2) lineCursor = 0;
  if (lineCursor == 0) lcd.setCursor(0, 0);
  else if (lineCursor == 1) lcd.setCursor(7, 0);
  else if (lineCursor == 2) lcd.setCursor(0, 1);
  lcd.print(">");

}

void verPushButton() 
{
  if (valueSW == 0 && currentTime - lastButtonTime >= periodSW) 
  {
    if (buttonState == 0) {
      buttonState = 1;
    }
    else 
    {
      buttonState = 0;
    }
    lastButtonTime = currentTime;
  }
}

void lcdClearLine(int line) {
  lcd.setCursor(0, line);
  for (int i = 0; i < 16; ++i) {
    lcd.write(' ');
  }
}

void setup() 
{
  pinMode(pinSW, INPUT_PULLUP);
  lcd.begin(16, 2);
  Serial.begin(9600);
}

void loop() 
{
  currentTime = millis();
  valueSW = digitalRead(pinSW);

  verPushButton();

  if (buttonState == 0) 
  {
    Menu();
    verGame = 0;
    verScore = 0;
    verFinishedGame = 0;
    valueY = analogRead(pinY);
    if (valueY < minThreshold && joyMoved == true) 
    {
      lineCursor++;
      cursor();
      joyMoved = false;
    }

    if (valueY > maxThreshold && joyMoved == true) 
    {
      lineCursor--;
      cursor();
      joyMoved = false;
    }
    if (valueY >= minThreshold && valueY <= maxThreshold) 
    {
      joyMoved = true;
      cursor();
    }
  }
  else
  {

    if (lineCursor == 0) 
    {
      if (verFinishedGame == 0) 
      { 
        lcd.setCursor(0, 0);
        lcd.print("Lives:");
        lcd.print(lives);
        lcd.print(" Level:");
        lcd.print(level);
        lcd.print(" ");
        lcd.setCursor(0, 1);
        lcd.print("Score: ");
        score = level * 3;
        lcd.print(score);
        lcd.print("     ");
        if (verScore == 0) 
        {
          lastLevelTime = millis();
          verScore = 1;
        }
        if (millis() - lastLevelTime >= levelTime) 
        {
          level++;
          if (level > 50) level = 0;
          lastLevelTime = millis();
        }
        if (verGame == 0) 
        {
          lastGameTime = millis();
          verGame = 1;
        }
      }
      Serial.println(millis() - lastGameTime);
      if (millis() - lastGameTime >= gameTime) 
      {
        lcd.setCursor(0, 0);
        lcd.print("Congrats, you  f ");
        lcd.setCursor(0, 1);
        lcd.print("inished the game");
        verFinishedGame = 1;
        if (score > Hscore)
            Hscore = score;
        delay(2500);
        lcd.setCursor(0, 0);
        lcd.print("press the button");
        lcdClearLine(1);
        lcd.setCursor(0, 1);
        lcd.print("to exit");
        lastGameTime = millis();
      }
    }

    else if (lineCursor == 2) 
    {
      lcd.setCursor(0, 1);
      lcd.print("                ");
      lcd.setCursor(0, 0);
      lcd.print("High Score: ");
      lcd.print(Hscore);
      lcd.print("   ");
    }
    else 
    {
      lcd.setCursor(0, 1);
      valueY = analogRead(pinY);
      if (valueY < minThreshold && joyMoved == true) 
      {
        level--;
        joyMoved = false;
      }

      if (valueY > maxThreshold && joyMoved == true) 
      {
        level++;
        joyMoved = false;
      }
      if (valueY >= minThreshold && valueY <= maxThreshold) 
      {
        joyMoved = true;
      }

      if (level < 0) level = 50;
      if (level > 50) level = 0;

      lcd.setCursor(0, 0);
      lcd.print("Start level: ");
      lcd.print(level);
      lcd.print("  ");
      lcd.setCursor(0, 1);
      lcd.print("           ");
    }
  }
}
