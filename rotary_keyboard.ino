#include <Keyboard.h>
#include <Mouse.h>

// GLOBALS

// Operation signal goes to Pin 8
int pin_op = 8;
// Pulse signal goes to Pin 9
int pin_pulse = 9;
// For counting the pulses
int pulses = 0;
// For keeping operation state
int last_op = LOW;
// For keeping pulse state
int last_pulse = HIGH;
// Array for characters to be emitted.
// This may seem weird.  You could put "0" at position 0 and use % 10 when addressing this array.
// But I liked this one. Just moving the wheel a little but not pulling all the way to "1" allows
// you to enter a space (or whatever you put in the array at position 0).
String characters[] = {" ","1","2","3","4","5","6","7","8","9","0"};

// ONCE

void setup() {
  // Runs once (initialization)
  pinMode(pin_op, INPUT);
  pinMode(pin_pulse, INPUT);
  pulses = 0;
}

// CONTINUOUS 

void loop() {
  // Read pin values
  int op = digitalRead(pin_op);
  int pulse_status = digitalRead(pin_pulse);
  
  // Logic
  if (op == HIGH && last_op == LOW) {
    // Op line on Pin 8 just changed from LOW to HIGH -> Dialing started
    // Uncomment for debug: Keyboard.print("// Dialing started");
    last_op = HIGH;
  }
  else if (op == HIGH && last_op == HIGH) {
    // Op line (Pin 8) remains high. We just have to count the pulses (on 
    // Pin 9) here. https://en.wikipedia.org/wiki/Pulse_dialing
    // Uncomment for (verbose) debug: Keyboard.print(pulse_status);
    if (pulse_status == LOW and last_pulse == HIGH) {
      // Pulse (Pin 9) goes from HIGH to LOW -> increment and keep the state
      pulses += 1;
      last_pulse = LOW;
    } else if (pulse_status == HIGH and last_pulse == LOW) {
      // Pulse (Pin 9) goes from LOW to HIGH -> just keep the state
      last_pulse = HIGH;
    }
  }
  else {
    // We get here when op line (Pin 8) is LOW
    if (last_op == HIGH) {
      // Op line on Pin 8 just changed from HIGH to LOW -> Dialing finished.
      // We need to emit the character from the array at the position of the
      // pulses we counted.
      Keyboard.print(characters[pulses]);
      // Uncomment for debug: Keyboard.println(" Dialing ended");
      // Save state
      last_op = op;
      // Reset pulse counter
      pulses = 0;
    }
  }
  
  // Let it breathe
  delay(5);
}
