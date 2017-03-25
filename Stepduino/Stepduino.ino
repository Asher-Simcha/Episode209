// Look at your driver board and you will see pins labeled "IN1", "IN2", "IN3", & "IN4"
// These are the pins that need to be connected to digital out pins on your Arduino.
// The variables below give you an easy way to assign which pins on the driver board are
// connected to corresponding pins on the Arduino.

int IN1 = 4;    
int IN2 = 5;
int IN3 = 6;
int IN4 = 7;

int Speed = 1;        // This controls how long we wait between pulses (In seconds)
int Distance = 0;        // Creating an integer variable named "Distance" that counts the number of steps we've made
int FullRotation = 4096; // How many steps are in a full revolution of the motor shaft?
int lookup[8] = {B01000, B01100, B00100, B00110, B00010, B00011, B00001, B01001};
                          // This array contains bimary values that will be pushed to the outpur pins to properly pulse the stepper

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  // We set the mode of our 4 pins to output
  Serial.begin(9600);
  // And open up a serial port so we can debug our program
}

void loop(){
  if(Distance < FullRotation/8 )
    CW();
  // This looks at "Distance" and calls the "CW()" function as long as its less than "FullRotation"/8
  
  else if (Distance == FullRotation/8 * 2 )
    Distance = 0;
  // This looks at "Distance" and resets the variable to "0" once two full rotations have been made (one CW, and one CCW)  
  
  else
    CCW();
  // While "Distance" is equal to or greater than "FullRotation"/8, but less that "FullRoation/8 * 2"
  // this calls the function "CCW()" to turn the motor counterclockwise
    
  Serial.print(Distance);
  Serial.print("\n");
  //For debugging: This prints the value of "Distance" to the serial monitor
  
  Distance = Distance+1;
  // Adds 1 to the value of "Distance"
}

// This function turns the motor clockwise
// Everytime the function is invoked, it moves the motor CW 8 steps
// (Each iteration of the for loop is one step)fa
// THIS is why we divide "FullRotation" by 8 in the main loop
void CW()
{
  for(int stepper = 7; stepper >= 0; stepper--)
  {
    MoveStep(stepper);
    delay(Speed);
  }
}

// This function turns the motor counterclockwise
// Everytime the function is invoked, it moves the motor CCW 8 steps
// (Each iteration of the for loop is one step)
// THIS is why we divide "FullRotation" by 8 in the main loop
void CCW()
{
  for(int stepper = 0; stepper < 8; stepper++)
  {
    MoveStep(stepper);
    delay(Speed);
  }
}


// This function will move the motor one step in either direction (depending on which function called this function)
void MoveStep(int eighth)
{
  digitalWrite(IN1, bitRead(lookup[eighth], 0));
  digitalWrite(IN2, bitRead(lookup[eighth], 1));
  digitalWrite(IN3, bitRead(lookup[eighth], 2));
  digitalWrite(IN4, bitRead(lookup[eighth], 3));

// Below is debug: writes the bits to the serial monitor  
  Serial.print(bitRead(lookup[eighth], 0));  
  Serial.print(bitRead(lookup[eighth], 1));  
  Serial.print(bitRead(lookup[eighth], 2));  
  Serial.print(bitRead(lookup[eighth], 3));  
  Serial.print("\t");
}

