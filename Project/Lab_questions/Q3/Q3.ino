#include <Servo.h>

Servo servo1;

void setup() {
  servo1.attach(7);  //pin 7 to servo
  Serial.begin(115200); 
}

void initial_pos(int &theta1_d){
  // move to the initial position of 0 deg
  theta1_d = 0; 
  servo1.write(theta1_d);
  delay(1000);
  }

double analogToVolt (double value) {
  //convert analog input into voltage
  double v = (value/1023)*5;
  return v;
}

void printData (float x, float y, float z){
  Serial.print("\n");
  Serial.print(x);
  Serial.print(", ");
  Serial.print(y);
  Serial.print(", ");
  Serial.print(z);
  }


void loop() {
  int analog_input0; // analog input for pin A0
  int theta1_d; // desired servo angle
  float voltage0; // voltage input for pin A0
  float minv;
  int theta1_d_min; // servo angle for minimum voltage / maximum light
  float t;

  // move to the initial position of 0 deg
  initial_pos(theta1_d);

  // move servo between 0 and 180 deg in 1 deg increments and
  // find the maximum light using voltage     
  minv = 1000000000;
  for(theta1_d = 0;theta1_d<=180;theta1_d++) {
    servo1.write(theta1_d);
    delay(50);
  
    analog_input0 = analogRead(A0); 
    voltage0 = analogToVolt(analog_input0); // convert input to V (0 to 5V)

    t = micros()*1.0e-6;  
  
    if(voltage0 < minv) {
      minv = voltage0;
      theta1_d_min = theta1_d;
    }
  
    // print out values compatible with Excel in form (x,y,z)
    printData(t, voltage0, theta1_d);
  }
  
  servo1.write(theta1_d_min);
  
  delay(10000);
  exit(1);
}
