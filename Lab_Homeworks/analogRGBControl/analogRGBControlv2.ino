const int bluePin = 9;
const int greenPin = 10;
const int redPin = 11; 

void setup() {
  // put your setup code here, to run once:
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Romania
  setColor(0, 0, 255);//blue
  delay(1000);
  setColor(255, 255, 0);//yellow
  delay(1000);
  setColor(255, 0, 0);//red
  delay(2500);
  
  //France
  setColor(0, 0, 255);//blue
  delay(1000);
  setColor(255, 255, 255);//white
  delay(1000);
  setColor(255, 0, 0);//red
  delay(2500);
  
  //Random
  setColor(255, 0, 255);
  delay(1000);
  setColor(0, 255, 255);
  delay(1000);
  setColor(255, 255, 100);
  delay(2500);
  
  //Italy
  setColor(0, 255, 0);//green
  delay(1000);
  setColor(255, 255, 255);//white
  delay(1000);
  setColor(255, 0, 0);//red
  delay(2500);
}

void setColor(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}
