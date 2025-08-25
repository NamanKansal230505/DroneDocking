/*
  Code to control two gates with two motors each (open/close)
  using two L298N motor drivers.

  -- UPDATED PIN ASSIGNMENTS --

  - Driver 1 controls Gate 1:
    - Motor A: MO1 (Motor Open 1)  -> ina1, ina2
    - Motor B: MC1 (Motor Close 1) -> ina3, ina4

  - Driver 2 controls Gate 2:
    - Motor A: MO2 (Motor Open 2)  -> inb1, inb2
    - Motor B: MC2 (Motor Close 2) -> inb3, inb4
*/

// ## Pin Definitions for L298N Driver 1 (Gate 1) ##
// Connect to Motor A output on Driver 1
const int ina1 = 23; // Motor Open 1 (MO1)
const int ina2 = 22; // Motor Open 1 (MO1)

// Connect to Motor B output on Driver 1
const int ina3 = 1; // Motor Close 1 (MC1)
const int ina4 = 3; // Motor Close 1 (MC1)


// ## Pin Definitions for L298N Driver 2 (Gate 2) ##
// Connect to Motor A output on Driver 2
const int inb1 = 21; // Motor Open 2 (MO2)
const int inb2 = 19; // Motor Open 2 (MO2)

// Connect to Motor B output on Driver 2
const int inb3 = 18; // Motor Close 2 (MC2)
const int inb4 = 5; // Motor Close 2 (MC2)


void setup() {
  // Set all motor control pins as OUTPUTs
  pinMode(ina1, OUTPUT);
  pinMode(ina2, OUTPUT);
  pinMode(ina3, OUTPUT);
  pinMode(ina4, OUTPUT);
  pinMode(inb1, OUTPUT);
  pinMode(inb2, OUTPUT);
  pinMode(inb3, OUTPUT);
  pinMode(inb4, OUTPUT);

  // Ensure all motors are stopped at the beginning
  stop_all_motors();
  gate1_open();
  gate2_open();
  gate2_close();
  gate1_close();
}

void loop() {
  // --- This is an example sequence. ---
  // --- Edit the function calls and delays to fit your needs. ---

//  // Open Gate 1
//  gate1_open();
//  delay(2000); // <-- EDIT this delay for how long it takes to open Gate 1
//
//  // Close Gate 1
//  gate1_close();
//  delay(2000); // <-- EDIT this delay for how long it takes to close Gate 1
//
//  // Open Gate 2
//  gate2_open();
//  delay(2000); // <-- EDIT this delay for how long it takes to open Gate 2
//
//  // Close Gate 2
//  gate2_close();
//  delay(2000); // <-- EDIT this delay for how long it takes to close Gate 2
//
//  // Stop everything for a moment before repeating
//  stop_all_motors();
//  delay(3000);
}

// ======================================================
// ## Gate 1 Control Functions ##
// ======================================================

void gate1_open() {
  // Stop the "close" motor first to be safe
  digitalWrite(ina1, LOW);
  digitalWrite(ina2, LOW);
  digitalWrite(ina3, LOW);
  digitalWrite(ina4, LOW);
  
  digitalWrite(ina4, HIGH);
  digitalWrite(ina3, LOW);

  delay(1000);

  digitalWrite(ina1, HIGH);
  digitalWrite(ina2, LOW);

  delay(2000);

  digitalWrite(ina1, LOW);
  digitalWrite(ina2, LOW);

  delay(9000);

  digitalWrite(ina4, LOW);
  digitalWrite(ina3, LOW);
  
  
}

void gate1_close() {
  // Stop the "open" motor first to be safe
  digitalWrite(ina1, LOW);
  digitalWrite(ina2, LOW);
  digitalWrite(ina3, LOW);
  digitalWrite(ina4, LOW);

  // Run the "close" motor (MC1)
  digitalWrite(ina2, HIGH);
  digitalWrite(ina1, LOW);
  digitalWrite(ina3, HIGH);
  digitalWrite(ina4, LOW);
  delay(2000);
  digitalWrite(ina1, LOW);
  digitalWrite(ina2, LOW);
  delay(10000);
  digitalWrite(ina3, LOW);
  digitalWrite(ina4, LOW);
  
}

// ======================================================
// ## Gate 2 Control Functions ##
// ======================================================

void gate2_open() {
  // Stop the "close" motor first to be safe
  // Stop the "close" motor first to be safe
  digitalWrite(inb1, LOW);
  digitalWrite(inb2, LOW);
  digitalWrite(inb3, LOW);
  digitalWrite(inb4, LOW);
  
  digitalWrite(inb4, HIGH);
  digitalWrite(inb3, LOW);

  delay(1000);

  digitalWrite(inb1, HIGH);
  digitalWrite(inb2, LOW);

  delay(3000);

  digitalWrite(inb1, LOW);
  digitalWrite(inb2, LOW);

  delay(8000);

  digitalWrite(inb4, LOW);
  digitalWrite(inb3, LOW);
  

}

void gate2_close() {
  // Stop the "open" motor first to be safe
  digitalWrite(inb1, LOW);
  digitalWrite(inb2, LOW);
  digitalWrite(inb3, LOW);
  digitalWrite(inb4, LOW);

  // Run the "close" motor (MC1)
  digitalWrite(inb2, HIGH);
  digitalWrite(inb1, LOW);
  digitalWrite(inb3, HIGH);
  digitalWrite(inb4, LOW);
  delay(3000);
  digitalWrite(inb1, LOW);
  digitalWrite(inb2, LOW);
  delay(11000);
  digitalWrite(inb3, LOW);
  digitalWrite(inb4, LOW);
}

// ======================================================
// ## Helper Function ##
// ======================================================

// Stops all four motors
void stop_all_motors() {
  // Stop Gate 1 motors
  digitalWrite(ina1, LOW);
  digitalWrite(ina2, LOW);
  digitalWrite(ina3, LOW);
  digitalWrite(ina4, LOW);
  
  // Stop Gate 2 motors
  digitalWrite(inb1, LOW);
  digitalWrite(inb2, LOW);
  digitalWrite(inb3, LOW);
  digitalWrite(inb4, LOW);
}
