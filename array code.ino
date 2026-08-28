#include <QTRSensors.h>
QTRSensors qtrD;
const uint8_t SensorCount = 4;
uint16_t sensorValuesD[SensorCount];

void setup(){
  qtrD.setTypeRC();
  qtrD.setSensorPins((const uint8_t[]){2, 3, 4, 5}, SensorCount);
  for (uint16_t i = 0; i < 400; i++){
    qtrD.calibrate();
  }
  
  Serial.begin(9600);
}

void loop(){
  digitalArray();
  delay(250);
}

void digitalArray(){
  uint16_t position = qtrD.readLineBlack(sensorValuesD);
  Serial.print("Sensors: ");
  for (uint8_t i = 0; i < SensorCount; i++){
    Serial.print(sensorValuesD[i]);
    Serial.print('\t');
  }
  Serial.println(position);
}
