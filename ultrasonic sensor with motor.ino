//ultrasonic sensor pins
const int trigPin = 8;
const int echoPin = 9;

//motor pins
const int In1 = 13;
const int In2 = 12;
const int In3 = 11;
const int In4 = 10;


void setup() {
  //ultrasonic input output
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  // motor control pins outputs
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);

  // initialize serial communication:
  Serial.begin(9600);
}

void turnRight(){
  // turn on motor A
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
}

void turnLeft(){
  // turn on motor A
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
}

void loop(){
  // Variables for duration of ping and the distance in cm
  long duration, cm;
  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
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
    //turn both motors on to move forward
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
