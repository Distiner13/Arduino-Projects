#include <Servo.h>

/*This program is a memory game, basically, the servo motor 
 * will move to three different angles (multiples of 10 between 0-18) 
 * by using random numbers. Once the 3 angles are shown, you then 
 * can guess the angles using the joyStick and your memory. 
 * The sensitivity of the joystick is extremely high, and therefore
 * using your hands with surgical precision is also a requirment.
 * Granted, you can just look at the answer in the beginning and
 * simply make it a game about your hands' movement precision rather than memory.
*/

//it is possible to use arrays for more guesses and more angles, I just wrote this simpler version for the sake of saving time 
//lots of delays are used in order to give the serial moniter enough time to print everything

Servo servo;
const int theta = 90;
int ra1=10*random(1,18), ra2=10*random(1,18), ra3=10*random(1,18); 
//these are the random angles, I choose to use the as global variables because it is easier

#define servoP 9
#define jsGN A3 //joystick ground as A3
#define js5V A2 //joystick +5 V as A2
#define jsX A1  //X axis reading from joystick as A1
#define jsSW 2  //Switch reading from joystick as 2

void initial_pos();   //move the servo at the initial angle of 90deg
void printvalues();   //print values of stuff to reduce the print lines
void servogamefunc(); //the function which allows the servo to move to 3 random angles
void JStoServo();     //The function which takes input from the joystick and converts it to angles for the servo, it also checks the answer

void setup() {
  Serial.begin(115200);       //make sure to open the serial monitor in order to understand what is happening
  
  servo.attach(9);            //pin 13 to servo

  pinMode(js5V, OUTPUT);      //pin A3 as output
  pinMode(jsGN, OUTPUT);      //pin A2 as output
  digitalWrite(js5V, HIGH);
  digitalWrite(jsGN,LOW);
  pinMode(jsSW, INPUT_PULLUP);

//randomSeed input from any pin, when the memory is already filled with the same values, it will not work properly
  randomSeed(analogRead(0));  // I use 0 because it is not connected to anything
  
//This function should run only once at the beginning of the program
  servogamefunc();
}

void initial_pos(){
  servo.write(theta);
  delay(1000);
  }

void printvalues(int ra, String valuename){
  Serial.print("The value for ");
  Serial.print(valuename);
  Serial.print(" is: ");
  Serial.println(ra);
  }

void servogamefunc(){
  initial_pos();

//this is meant for seeing the answers when needed
  printvalues(ra1, "ra1");
  printvalues(ra2, "ra2");
  printvalues(ra3, "ra3");

//writing a random angle and reverting to the initial one
  servo.write(ra1);
  delay(1000);
  initial_pos();
  servo.write(ra2);
  delay(1000);
  initial_pos();
  servo.write(ra3);
  delay(1000);
  initial_pos();
  delay(1000); 
  }

void JStoServo() {
   delay (500);
   static int g1=190, g2=190, g3=190;         //static guesses 1 to 3, you can guess each angle once
   delay(200);                    

//the following lines will print the joystick values dynamically
   delay(200);                    
   int xpos = analogRead(jsX);
   printvalues(xpos, "xpos");
   int SW = digitalRead(jsSW);
   printvalues(SW, "SW");

//the following lines will print the servo values dynamically
//the values for xpos vary between 1019 and 0. The angles vary between 0-18 so:
   int servo_output = (xpos/(1019/18))*10; 
   printvalues(servo_output, "servo_output");
   Serial.println();
   servo.write((xpos/(1019/18))*10);          //write the calculated value to the servo  

   printvalues(g1,"g1");printvalues(g2,"g2");printvalues(g3,"g3");
   
   delay(200);
   
//if else statements for capturing the answer of the user (
//granted, nested if/else statements aren't the best way to do it if you increase the number of guesses and angles)
   if (SW == 0) {
     if (g1>180) {
      g1 = servo_output;
      printvalues(g1, "your first guess");
      initial_pos();
      delay (1000);
      }
     else if (g1<=180 && g2>180) {
      g2 = servo_output;
      printvalues(g2, "your second guess");
      initial_pos();
      delay (1000);
      }
     else if (g1<=180 && g2<=180 && g3>180) {
      g3 = servo_output;
      printvalues(g3, "your third guess");
      initial_pos();
      delay (1000);
      } 
     if (g1<=180 && g2<=180 && g3<=180) {
      Serial.println();
      printvalues(g1, "your first guess");  //print all guesses
      printvalues(g2, "your second guess");
      printvalues(g3, "your third guess");
      initial_pos();
      delay (1000);
      printvalues(ra1, "the first angle");  //print answers
      printvalues(ra2, "the second angle");
      printvalues(ra3, "the third angle");
      if (g1==ra1 && g2==ra2 && g3==ra3){
        Serial.println();
        Serial.println("YOU WINN!!");
        }else {Serial.println();Serial.println("BETTER LUCK NEXT TIME");}
      delay(1000);
      exit(1);                              // once the result is shown this is used to exit the loop
      } 
       }                                    //end of the if/else statements 
}

void loop() {
  //loop the function until it encounters an exit line
  JStoServo();
  
}
