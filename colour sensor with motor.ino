//motor pins
const int In1 = 13;
const int In2 = 12;
const int In3 = 11;
const int In4 = 10;

//colour sensor pins
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

//calibration ranges
int redMin = 23; 
int redMax = 191;
int greenMin = 20;
int greenMax = 219;
int blueMin = 16;
int blueMax = 161;

int redPW = 0;
int greenPW = 0;
int bluePW = 0;

int redValue;
int greenValue;
int blueValue;

void setup() {
//motor setup
pinMode(In1, OUTPUT);
pinMode(In2, OUTPUT);
pinMode(In3, OUTPUT);
pinMode(In4, OUTPUT);

//colour sensor setup
pinMode(S0, OUTPUT);
pinMode(S1, OUTPUT);
pinMode(S2, OUTPUT);
pinMode(S3, OUTPUT);
pinMode(sensorOut, INPUT);

digitalWrite(S0,HIGH);
digitalWrite(S1,LOW);

Serial.begin(9600);
}

void loop() {
redPW = getRedPW();
redValue = map(redPW, redMin,redMax,255,0);
delay(200);

greenPW = getGreenPW();
greenValue = map(greenPW, greenMin,greenMax,255,0);
delay(200);

bluePW = getBluePW();
blueValue = map(bluePW, blueMin,blueMax,255,0);
delay(200);

//identify colour and move
if(blueValue < 239 && greenValue < 187 && redValue < 220){
 Serial.println("purple");
 //turn right
 digitalWrite(In1, HIGH);
 digitalWrite(In2, LOW);
 digitalWrite(In3, LOW);
 digitalWrite(In4, HIGH);
 delay(250);
 motorsOFF();
} else if(blueValue < 213 && greenValue < 257 && redValue < 272 && redValue > 232){
 Serial.println("yellow");
 //turn left
 digitalWrite(In1, LOW);
 digitalWrite(In2, HIGH);
 digitalWrite(In3, HIGH);
 digitalWrite(In4, LOW);
 delay(250);
 motorsOFF();
} else if(blueValue < 188 && blueValue > 124 && greenValue < 246 && redValue < 229){
 Serial.println("green");
 //turn around
 digitalWrite(In1, HIGH);
 digitalWrite(In2, LOW);
 digitalWrite(In3, LOW);
 digitalWrite(In4, HIGH);
 delay(500);
 motorsOFF();
} else{
motorsOFF();
}
}

// read red
int getRedPW() {
digitalWrite(S2,LOW);
digitalWrite(S3,LOW);
int PW;
PW = pulseIn(sensorOut, LOW);
return PW;
}

// read green
int getGreenPW() {
digitalWrite(S2,HIGH);
digitalWrite(S3,HIGH);
int PW;
PW = pulseIn(sensorOut, LOW);
return PW;
}

// read blue
int getBluePW() {
digitalWrite(S2,LOW);
digitalWrite(S3,HIGH);
int PW;
PW = pulseIn(sensorOut, LOW);
return PW;
}

void motorsOFF(){
 digitalWrite(In1, LOW);
 digitalWrite(In2, LOW);
 digitalWrite(In3, LOW);
 digitalWrite(In4, LOW);
}
