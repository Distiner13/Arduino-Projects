#include <Servo.h>

Servo servo1;

float t0 = 0.0; 

void setup() {

  servo1.attach(7);  //pin 7 to servo
  Serial.begin(115200);
  t0 = micros()*1.0e-6;
}

void loop() {
  float t;
  float A, w, phi1;
  int theta1_d;

  A = 45.0;
  w = 1.0;
  phi1 = 0.0;
  
  t = micros()*1.0e-6 - t0; //substract t0 because it accounts for setup()
    
  theta1_d = A*( 1.0 + sin(w*t + phi1) );

  servo1.write(theta1_d);

  if(t > 30.0) exit(1); // end program at t=30s

}
