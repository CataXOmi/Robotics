#include <LiquidCrystal.h>

#define TEMP_PIN A0
#define RED_PIN 9
#define GREEN_PIN 10
#define BLUE_PIN 11

#define N_B0  31
#define N_C1  33
#define N_CS1 35
#define N_D1  37
#define N_DS1 39
#define N_E1  41
#define N_F1  44
#define N_FS1 46
#define N_G1  49
#define N_GS1 52
#define N_A1  55
#define N_AS1 58
#define N_B1  62
#define N_C2  65
#define N_CS2 69
#define N_D2  73
#define N_DS2 78
#define N_E2  82
#define N_F2  87
#define N_FS2 93
#define N_G2  98
#define N_GS2 104
#define N_A2  110
#define N_AS2 117
#define N_B2  123
#define N_C3  131
#define N_CS3 139
#define N_D3  147
#define N_DS3 156
#define N_E3  165
#define N_F3  175
#define N_FS3 185
#define N_G3  196
#define N_GS3 208
#define N_A3  220
#define N_AS3 233
#define N_B3  247
#define N_C4  262
#define N_CS4 277
#define N_D4  294
#define N_DS4 311
#define N_E4  330
#define N_F4  349
#define N_FS4 370
#define N_G4  392
#define N_GS4 415
#define N_A4  440
#define N_AS4 466
#define N_B4  494
#define N_C5  523
#define N_CS5 554
#define N_D5  587
#define N_DS5 622
#define N_E5  659
#define N_F5  698
#define N_FS5 740
#define N_G5  784
#define N_GS5 831
#define N_A5  880
#define N_AS5 932
#define N_B5  988
#define N_C6  1047
#define N_CS6 1109
#define N_D6  1175
#define N_DS6 1245
#define N_E6  1319
#define N_F6  1397
#define N_FS6 1480
#define N_G6  1568
#define N_GS6 1661
#define N_A6  1760
#define N_AS6 1865
#define N_B6  1976
#define N_C7  2093
#define N_CS7 2217
#define N_D7  2349
#define N_DS7 2489
#define N_E7  2637
#define N_F7  2794
#define N_FS7 2960
#define N_G7  3136
#define N_GS7 3322
#define N_A7  3520
#define N_AS7 3729
#define N_B7  3951
#define N_C8  4186
#define N_CS8 4435
#define N_D8  4699
#define N_DS8 4978

const int activePin = 7;
const int passivePin = A1;
int const TEMPO = 1200;

int melody[] = {
  N_D3, N_D3, N_D4, N_A3, 0, N_GS3, N_G3, N_F3, N_D3, N_F3, N_G3, N_C3, N_C3, N_D4, N_A3, 0, N_GS3, N_G3, N_F3, N_D3, N_F3, N_G3, N_B2, N_B2, N_D4, N_A3, 0, N_GS3, N_G3, N_F3, N_D3, N_F3, N_G3, N_AS2, N_AS2, N_D4, N_A3, 0, N_GS3, N_G3, N_F3, N_D3, N_F3, N_G3, N_D3, N_D3, N_D4, N_A3, 0, N_GS3, N_G3, N_F3, N_D3, N_F3, N_G3, N_C3, N_C3, N_D4, N_A3, 0, N_GS3, N_G3, N_F3, N_D3, N_F3, N_G3, N_B2, N_B2, N_D4, N_A3, 0, N_GS3, N_G3, N_F3, N_D3, N_F3, N_G3, N_AS2, N_AS2, N_D4, N_A3, 0, N_GS3, N_G3, N_F3, N_D3, N_F3, N_G3, N_D4, N_D4, N_D5, N_A4, 0, N_GS4, N_G4, N_F4, N_D4, N_F4, N_G4, N_C4, N_C4, N_D5, N_A4, 0, N_GS4, N_G4, N_F4, N_D4, N_F4, N_G4, N_B3, N_B3, N_D5, N_A4, 0, N_GS4, N_G4, N_F4, N_D4, N_F4, N_G4, N_AS3, N_AS3, N_D5, N_A4, 0, N_GS4, N_G4, N_F4, N_D4, N_F4, N_G4, N_D4, N_D4, N_D5, N_A4, 0, N_GS4, N_G4, N_F4, N_D4, N_F4, N_G4, N_C4, N_C4, N_D5, N_A4, 0, N_GS4, N_G4, N_F4, N_D4, N_F4, N_G4, N_B3, N_B3, N_D5, N_A4, 0, N_GS4, N_G4, N_F4, N_D4, N_F4, N_G4, N_AS3, N_AS3, N_D5, N_A4, 0, N_GS4, N_G4, N_F4, N_D4, N_F4, N_G4, N_F4, N_F4, N_F4, N_F4, N_F4, N_D4, N_D4, N_D4, N_F4, N_F4, N_F4, N_G4, N_GS4, N_G4, N_F4, N_D4, N_F4, N_G4, 0, N_F4, N_F4, N_F4, N_G4, N_GS4, N_A4, N_C5, N_A4, N_D5, N_D5, N_D5, N_A4, N_D5, N_C5, N_F4, N_F4, N_F4, N_F4, N_F4, N_D4, N_D4, N_D4, N_F4, N_F4, N_F4, N_F4, N_D4, N_F4, N_E4, N_D4, N_C4, 0, N_G4, N_E4, N_D4, N_D4, N_D4, N_D4, N_F3, N_G3, N_AS3, N_C4, N_D4, N_F4, N_C5, 0, N_F4, N_D4, N_F4, N_G4, N_GS4, N_G4, N_F4, N_D4, N_GS4, N_G4, N_F4, N_D4, N_F4, N_F4, N_F4, N_GS4, N_A4, N_C5, N_A4, N_GS4, N_G4, N_F4, N_D4, N_E4, N_F4, N_G4, N_A4, N_C5, N_CS5, N_GS4, N_GS4, N_G4, N_F4, N_G4, N_F3, N_G3, N_A3, N_F4, N_E4, N_D4, N_E4, N_F4, N_G4, N_E4, N_A4, N_A4, N_G4, N_F4, N_DS4, N_CS4, N_DS4, 0, N_F4, N_D4, N_F4, N_G4, N_GS4, N_G4, N_F4, N_D4, N_GS4, N_G4, N_F4, N_D4, N_F4, N_F4, N_F4, N_GS4, N_A4, N_C5, N_A4, N_GS4, N_G4, N_F4, N_D4, N_E4, N_F4, N_G4, N_A4, N_C5, N_CS5, N_GS4, N_GS4, N_G4, N_F4, N_G4, N_F3, N_G3, N_A3, N_F4, N_E4, N_D4, N_E4, N_F4, N_G4, N_E4, N_A4, N_A4, N_G4, N_F4, N_DS4, N_CS4, N_DS4, 
};

int noteDurations[] = {
  16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 8, 16, 8, 8, 8, 8, 4, 16, 8, 16, 8, 8, 8, 16, 16, 16, 16, 16, 8, 8, 16, 8, 8, 8, 8, 8, 8, 8, 8, 16, 16, 16, 2, 8, 16, 8, 8, 8, 8, 4, 16, 8, 16, 8, 8, 8, 8, 8, 16, 8, 16, 8, 8, 8, 8, 8, 8, 8, 16, 8, 15, 8, 8, 2, 3, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 8, 2, 16, 8, 16, 8, 16, 16, 16, 16, 16, 16, 8, 8, 8, 8,  8, 8, 16, 16, 16, 2, 8, 8, 8, 8, 4, 4, 4, 4, 4, 4, 2, 8, 8, 8, 8, 2, 2, 3, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 8, 2, 16, 8, 16, 8, 16, 16, 16, 16, 16, 16, 8, 8, 8, 8,  8, 8, 16, 16, 16, 2, 8, 8, 8, 8, 4, 4, 4, 4, 4, 4, 2, 8, 8, 8, 8, 2, 2
};

LiquidCrystal lcd(12, 6, 5, 4, 3, 2);

int adc = 0;
int blue = 0, red = 0;

byte smile[8] = {B00000, B10001, B00000, B00000, B10001, B01110, B00000};

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


double ReadThermistor(int adc) {

  double resistance = ((1024.0/adc) - 1);    //calculate from voltage divider, for 10k resistor
  double Temp = log(resistance);

  // calculate the temperature, in K, using 4 thermistor model/material specific parameters A, B, C, D
  // here we use the values for the Sparkfun/Hactronics version of the Vishay 10k NTC thermistor
  Temp = 1 / (0.003354016 + 0.0002569850 * Temp + 0.000002620131 * Temp * Temp + 0.00000006383091 * Temp * Temp * Temp);
  Temp = Temp - 273.15;            // Convert Kelvin to Celsius
  return Temp;
}

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

void setLED(int blue, int red){
  analogWrite(BLUE_PIN, blue);
  analogWrite(RED_PIN, red);
}

void setup(){
  Serial.begin(9600);
  pinMode(BLUE_PIN, OUTPUT); 
  pinMode(RED_PIN, OUTPUT); 
  pinMode(GREEN_PIN, OUTPUT);  
  pinMode(TEMP_PIN, INPUT);
  pinMode(passivePin, INPUT);
  pinMode(activePin, OUTPUT);
  lcd.begin (16, 2);
  standingMan();
  lcd.setCursor(4,0);
  lcd.print ("Welcome to ");
  lcd.setCursor (4,1);
  lcd.print ("my project! ");
  delay(3000);
  lcd.clear();
  lcd.createChar (7, smile);
  standingMan();
  lcd.setCursor(4,0);
  lcd.print("Temperature ");
  lcd.setCursor (4,1);
  lcd.print("Smile! RGB ");
  lcd.write (7); 
  delay(3000);
  lcd.clear();
  runningManR();
  lcd.clear();
}

void loop(){
  
  adc = analogRead(TEMP_PIN);
  int temp = ReadThermistor(adc);
  Serial.println(temp);

  lcd.print("Temp = ");
  lcd.print(temp);   
  lcd.print(" C");
  
  delay(1000);            
  lcd.clear();
  
  red = map(temp, 20, 40, 0, 255);
  blue = 255 - red;
  
  setLED(blue, red);
  
  if(temp > 86)
    {
      int melody_len = sizeof(melody)/sizeof(melody[0]);
      
      for (int thisNote = 0; thisNote < melody_len; thisNote++) 
        { 
          
          int noteDuration = TEMPO / noteDurations[thisNote];
          tone(activePin, melody[thisNote], noteDuration);
          int pauseBetweenNotes = noteDuration * 1.45;
          delay(pauseBetweenNotes);
          noTone(activePin);
         
        }
    }
  else
    {  
       noTone(activePin);
    }
}
