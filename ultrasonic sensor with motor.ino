//ultrasonic sensor pins
const int trigPin = 8;
const int echoPin = 9;

//motor pins
const int In1 = 13;
const int In2 = 12;
const int In3 = 11;
const int In4 = 10;


void setup() {
  //setup ultrasonic sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  //setup motor
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);

  Serial.begin(9600);
}

void turnRight(){
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
}

void turnLeft(){
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
}

void loop(){
  long duration, cm;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  // convert the time into a distance
  cm = microsecondsToCentimetres(duration);
  
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();  
  delay(10);

  if(cm < 6 && cm != 0){
    //move forward
    turnLeft();
    turnRight();
  }
  else{
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  }
}

long microsecondsToCentimetres(long microseconds){
  return microseconds / 29 / 2;
}
