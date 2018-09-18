const int trigPin = A0;
const int echoPin = A3;
const int buzzer = 4;

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  //pin 7 powers the sonar sensor
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);
}

void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;

  if (distance >= 700 ) {
    Serial.println("Out of range");
  }
  
  //if nothing in sight low beep
  else if (distance > 100) {
  tone(buzzer, 500, 100);
  } 
  
    //high beep if something is close
    else if (distance < 15) {
    tone(buzzer, 2000,300); 
  
      } else {
      //normal beep
      tone(buzzer, 1000, distance*4);
  }

  delay(500);
} 



