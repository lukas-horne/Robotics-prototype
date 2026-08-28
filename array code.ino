#include <QTRSensors.h>
QTRSensors qtrD;
const uint8_t SensorCount = 4;
uint16_t sensorValuesD[SensorCount];

void setup(){
  // configure the sensors
  qtrD.setTypeRC();
  qtrD.setSensorPins((const uint8_t[]){2, 3, 4, 5}, SensorCount);
  delay(500);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH); // turn on Arduino's LED to indicate we are in calibration mode

  // 0.1 ms per sensor * 4 samples per sensor read (default) * 6 sensors
  // * 10 reads per calibrate() call = ~24 ms per calibrate() call.
  // Call calibrate() 400 times to make calibration take about 10 seconds.

  for (uint16_t i = 0; i < 400; i++){
    qtrD.calibrate();
  }
 
  digitalWrite(LED_BUILTIN, LOW); // turn off Arduino's LED to indicate we are through with calibration
  // print the calibration minimum values measured when emitters were on
  Serial.begin(9600);
  for (uint8_t i = 0; i < SensorCount; i++){
    Serial.print(' ');
    Serial.print(qtrD.calibrationOn.minimum[i]);
    Serial.println();
  }


  Serial.println();
  // print the calibration maximum values measured when emitters were on
  for (uint8_t i = 0; i < SensorCount; i++){
    Serial.print(' ');
    Serial.print(qtrD.calibrationOn.maximum[i]);
    Serial.println();
  }
  Serial.println();
  Serial.println();
  delay(1000);
}

void loop(){
  digitalArray();
  delay(250);
}

void digitalArray(){
  // read calibrated sensor values and obtain a measure of the line position
  // from 0 to 5000 (for a white line, use readLineWhite() instead)
  uint16_t position = qtrD.readLineBlack(sensorValuesD);
  // print the sensor values as numbers from 0 to 1000, where 0 means maximum
  // reflectance and 1000 means minimum reflectance, followed by the line
  // position
  Serial.print("Digital: ");
  for (uint8_t i = 0; i < SensorCount; i++){
    Serial.print(sensorValuesD[i]);
    Serial.print('\t');
  }
  Serial.println(position);
}
