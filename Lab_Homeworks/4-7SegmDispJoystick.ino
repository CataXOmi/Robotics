const int pinA = 12;
const int pinB = 8;
const int pinC = 5;
const int pinD = 3;
const int pinE = 2;
const int pinF = 11;
const int pinG = 6;
const int pinDP = 4;
const int pinD1 = 7;
const int pinD2 = 9;
const int pinD3 = 10;
const int pinD4 = 13;

const int pinX = A0;
const int pinY = A1;
const int pinSw = A2;

const int segSize = 8;
const int noOfDisplays = 4;
const int noOfDigits = 10;

int dpState = LOW;
int dpPlace = 0;
int dpRealPlace = 0;
int selection = 0;
int digit1 = 0;
int digit2 = 0;
int digit3 = 0;
int digit4 = 0;

int valueSw = 0;
int lastSwValue = 0;
int valueX = 0;
int valueY = 0;

bool joyMoved = false;
int minThreshold = 400; // min Value of the default joystick state
int maxThreshold = 600; // max Value of the default joystick state

unsigned long currentMillis = 0;
unsigned long anteriorMillis = 0;
const long period = 500;

// segments array, similar to before
int segments[segSize] = {
  pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
};

// digits array, to switch between them easily

int digits[noOfDisplays] = {
  pinD1, pinD2, pinD3, pinD4
 };   

int digitNumbers[noOfDisplays] = {
  digit1, digit2, digit3, digit4
};

byte digitMatrix[noOfDigits][segSize - 1] = {
// a  b  c  d  e  f  g
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9
};

void displayNumber(byte digit, byte decimalPoint) 
{
  for (int i = 0; i < segSize - 1; i++) 
  {
   digitalWrite(segments[i], digitMatrix[digit][i]);
  }

  // write the decimalPoint to DP pin
  digitalWrite(segments[segSize - 1], decimalPoint);
}

// activate the display no. received as param
void showDigit(int num) 
{
  for (int i = 0; i < noOfDisplays; i++) 
  {
   digitalWrite(digits[i], HIGH);
  }
  
  digitalWrite(digits[num], LOW);
}
         
void setup() {
  for (int i = 0; i < segSize ; i++)
  {
   pinMode(segments[i], OUTPUT);  
  }
  
  for (int i = 0; i < noOfDisplays; i++)
  {
   pinMode(digits[i], OUTPUT);  
  }
  
  pinMode(pinSw, INPUT_PULLUP);

  for (int i = 0; i < noOfDisplays; i++)
    {
      showDigit(i);
      if (i == dpPlace)
        dpState = HIGH;
      else 
        dpState = LOW;
      displayNumber(digitNumbers[i], dpState);
      delay(5);
    }
}

void loop() 
{
  for (int i = 0; i < noOfDisplays; i++)
    {
      showDigit(i);
      if (i == dpPlace)
        dpState = HIGH;
      else 
        dpState = LOW;
      displayNumber(digitNumbers[i], dpState);
      delay(5);
    }
    
  valueX = analogRead(pinX);
  valueY = analogRead(pinY);
  
  if (valueY < minThreshold && joyMoved == false && selection == 0) 
    {
      if (dpPlace < 3)
        {
          dpPlace++;
          dpRealPlace++;
        }
      else
        {
          dpPlace = 0;
          dpRealPlace = 0;
        }
      joyMoved = true;
    }
  if (valueY > maxThreshold && joyMoved == false && selection == 0)
    {
      if (dpPlace > 0)
        {
          dpPlace--;
          dpRealPlace--;
        }
      else
        {
          dpPlace = 3;
          dpRealPlace = 3;
        }
      joyMoved = true;
    }
  if (valueY >= minThreshold && valueY <= maxThreshold && selection == 0) 
        joyMoved = false;
   
  if(valueX < minThreshold && joyMoved == false && selection == 1)
    {
      if(digitNumbers[dpRealPlace] > 0)
          digitNumbers[dpRealPlace]--;
      else 
          digitNumbers[dpRealPlace] = 9;
      joyMoved = true;
    }
  if(valueX > maxThreshold && joyMoved == false && selection == 1)
    {
      if(digitNumbers[dpRealPlace] < 9)
          digitNumbers[dpRealPlace]++;
      else 
          digitNumbers[dpRealPlace] = 0;
      joyMoved = true;
    }
  if(valueX >= minThreshold && valueX <= maxThreshold && selection == 1)
    {
      joyMoved = false;    
    }
 
 //DP
  valueSw = digitalRead(pinSw);
  if(valueSw != lastSwValue && valueSw == LOW)
    {
      selection = !selection;
      dpPlace = dpRealPlace;
    }
  lastSwValue = valueSw;

  currentMillis = millis();

  if(currentMillis - anteriorMillis >= period && selection == 1)
    {
      anteriorMillis = currentMillis;
      if (dpPlace < 4) 
          dpPlace = 4;
      else 
          dpPlace = dpRealPlace;
    }
    
  delay(1);
}
