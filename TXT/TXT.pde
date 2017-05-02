import processing.serial.*;
import java.awt.*;
import java.awt.event.InputEvent;
import java.io.IOException;
import java.awt.Robot;
import processing.core.PApplet;
Serial myPort;
String data = "";
String[] list = new String[1];
void setup() {
  myPort = new Serial(this, "COM5", 9600);
  myPort.bufferUntil('\n'); 
  
}
void serialEvent (Serial myPort) { // Checks for available data in the Serial Port
  data = myPort.readStringUntil('\n'); //Reads the data sent from the Arduino (the String "LED: OFF/ON) and it puts into the "ledStatus" variable
}
void draw() {
  /*
  double[] data1 = {0,0,0,0,0,0};
   data1[2] = Math.random()*10;
   data1[3] = Math.random()*10;
   data1[4] = Math.random()*10;
   data1[5] = Math.random()*10;
   String data = "" +(int)data1[0] + (int)data1[1] + (int)data1[2] + (int)data1[3] + (int)data1[4] + (int)data1[5];
  */
   list[0] = data;
   System.out.println(data);
   saveStrings("1.txt",list);
   delay(15);
}