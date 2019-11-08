const int potPin1 = A0;
const int ledPin1 = 9; //blue

const int potPin2 = A1;
const int ledPin2 = 10; //green

const int potPin3 = A2; 
const int ledPin3 = 11; //red

int potValue1 = 0;
int ledValue1 = 0; //blue

int potValue2 = 0;
int ledValue2 = 0; //green

int potValue3 = 0;
int ledValue3 = 0; //red

void setup() {
  // put your setup code here, to run once:
  pinMode(potPin1,INPUT);
  pinMode(ledPin1,OUTPUT);
  
  pinMode(potPin2,INPUT);
  pinMode(ledPin2,OUTPUT);
  
  pinMode(potPin3,INPUT);
  pinMode(ledPin3,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  potValue1 = analogRead(potPin1);
  ledValue1 = map(potValue1,0,1023,0,255);
  analogWrite(ledPin1,ledValue1);
 
  potValue2 = analogRead(potPin2);
  ledValue2 = map(potValue2,0,1023,0,255);
  analogWrite(ledPin2,ledValue2);

  potValue3 = analogRead(potPin3);
  ledValue3 = map(potValue3,0,1023,0,255);
  analogWrite(ledPin3,ledValue3);
}
