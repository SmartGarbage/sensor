// George Politis Smart Garbage
// physical set up
//VCC to arduino 5v 
//GND to arduino GND
//Echo to Arduino pin 7 
//Trig to Arduino pin 8


//-----------Code-------------//


#define trigPin 7
#define echoPin 6
#define led 13
#define led2 12
#define led3 11
#define led4 10
#define led5 9
#define led6 8
#define buzzer 3


// initialize sound variables
int sound = 250;
// lowest and highest sensor readings for flame:
const int sensorMin = 0;     // sensor minimum for flame
const int sensorMax = 1024;  // sensor maximum for flame

int maximumRange = 60;
int minimumRange = 0;
long duration, distance;

int sensorValue = digitalRead(echoPin);


void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  pinMode(buzzer, OUTPUT);

}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  //distance = (duration / 2) / 29.1;
  distance = duration / 58.2;

  // Disabling sound to use it for
  // the flame sensor
  if (distance <= 60) {
    digitalWrite(led, HIGH);
    Serial.println(sensorValue);
    //sound = 250;
  }
  else {
    digitalWrite(led, LOW);
  }
  if (distance < 45) {
    digitalWrite(led2, HIGH);
    Serial.println(sensorValue);
    //sound = 260;
  }
  else {
    digitalWrite(led2, LOW);
  }
  if (distance < 35) {
    digitalWrite(led3, HIGH);
    Serial.println(sensorValue);
    //sound = 270;
  }
  else {
    digitalWrite(led3, LOW);
  }
  if (distance < 25) {
    digitalWrite(led4, HIGH);
    Serial.println(sensorValue);
    //sound = 280;
  }
  else {
    digitalWrite(led4, LOW);
  }
  if (distance < 18) {
    digitalWrite(led5, HIGH);
    Serial.println(sensorValue);
    //sound = 290;
  }
  else {
    digitalWrite(led5, LOW);
  }
  if (distance < 10) {
    digitalWrite(led6, HIGH);
    Serial.println(distance);
    Serial.println(sensorValue);
    //sound = 300;
  }
  else {
    digitalWrite(led6, LOW);
  }

  if (distance > maximumRange || distance <= minimumRange) {
    Serial.println("Empty Garbgage bin");
    Serial.println(sensorValue);
    //noTone(buzzer);
  }
  else {
    Serial.println(distance);
    Serial.println(" cm");
    Serial.println(sensorValue);
    // tone(buzzer, sound);

  }
  ////////////------------Flame sensor-------------//////
  // read the sensor on analog A0:
  int sensorReading = analogRead(A0);
  // map the sensor range (four options):
  // ex: 'long int map(long int, long int, long int, long int, long int)'
  int range = map(sensorReading, sensorMin, sensorMax, 0, 3);

  // range value:
  switch (range) {
    case 0:    // A fire closer than 1.5 feet away.
      //Serial.println("** Close Fire **");
      sound = 2050;
     // tone(buzzer, sound);
      break;
    case 1:    // A fire between 1-3 feet away.
     // Serial.println("** Distant Fire **");
      sound = 550;
     // tone(buzzer, sound);
      break;
    case 2:    // No fire detected.
     // Serial.println("No Fire");
      // mutes the sound
      noTone(buzzer);
      break;
  }

  delay(500);
}
