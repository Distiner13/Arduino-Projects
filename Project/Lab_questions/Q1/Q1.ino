void setup() {
  Serial.begin(115200);
}

double analogToVolt (double value) {
  //convert analog input into voltage
  double v = (value/1023)*5;
  return v;
 } 

void lightSensor (double value, int iter) {
  //This function prints out the voltage read by the light sensor over a number of iterations
  double maxv = -100000000000, minv = 100000000000;
  double total = 0, V;
  
  for (int i = 0; i<iter; i++){
    V = analogToVolt(value);
    maxv = max(V, maxv);
    minv = min(V,minv);
    total += V;
    }

  double delta = maxv - minv;
  double noise = delta/2;
  double delta_avg = (0.5*delta)/sqrt(iter);
  double avg = total/iter;

  Serial.print("Voltage is :");
  Serial.println(V);
  }

void loop() {
  int N = 1000;
  double value = analogRead(A0);
  lightSensor(value, N);
}
