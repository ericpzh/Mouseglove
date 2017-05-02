////////////////////////////////////////////
#include <Wire.h>
#include "Adafruit_MPR121.h"
Adafruit_MPR121 cap = Adafruit_MPR121();
uint16_t lasttouched = 0;
uint16_t currtouched = 0;
////////////////////////////////////////////
#include<Wire.h>
const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
////////////////////////////////////////////
int modeA = 8;//11    
int modeB = 9;//01
int modeC = 10;//00
int modeD = 11;//10
////////////////////////////////////////////
void setup() {
  Serial.begin(9600);
  pinMode(modeA,INPUT);
  pinMode(modeB,INPUT);
  pinMode(modeC,INPUT);
  pinMode(modeD,INPUT);
  while (!Serial){
    delay(10);
  }
  if (!cap.begin(0x5A)) {
    while (1);
  }
  ////////////////////////////////////////////
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
}
////////////////////////////////////////////
void loop() {
  int A = digitalRead(modeA);
  int B = digitalRead(modeB);
  int C = digitalRead(modeC);
  int D = digitalRead(modeD);
  if(A==1){
    Serial.println("000000");
    return;
  }
  ///////////////////////////////////////
  currtouched = cap.touched();
  uint8_t v11 = 11;
  uint8_t v8 = 8;
  String data="";
  if ((currtouched & _BV(v11))) {
    data+=1;
  }else{
    data+="0";
  }
  if ((currtouched & _BV(v8)) ) {
    data+=2;
  }else{
    data+="0";
  }
  lasttouched = currtouched;
  ////////////////////////////////////////////
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  //Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
 //GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  //GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  //GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)        
  //if XY
  if(C == 1){
    if(AcY> 1500 ){
      data += "3"; //left
    }else {
      data+="0";
    }
    if(AcY < -8000 ){
      data += "4"; //right
    }else{
      data+="0";
    }
    if(AcX > 4500 ){
      data += "5"; //up
    }else{
      data+="0";
    }if(AcX < -3000 ){
      data += "6"; //down
    }else{
      data+="0";
    }
  }
  //if YZ
  //right AcY >-7000    left < 5000
  //down AcZ < 0    up AcZ>11000
  if(B == 1 || D == 1){
    if(AcY > 5000){
      data += "3";
    }else{
      data+="0";
    }
    if(AcY < -7000 ){
      data += "4";
    }else{
      data+="0";
    }
    if(AcZ > 7500 ){
      data += "5";
    }else{
      data+="0";
    }
    if(AcZ < -4500 ){
      data += "6";
    }else{
      data+="0";
    }
  }   
  ////////////////////////////////////////////
 Serial.println(data);
  ////////////////////////////////////////////  
  delay(15);
}
