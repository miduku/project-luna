/*
 * Project project-luna-photon
 * Description:
 * Author: Dustin Kummer
 * Date: 2017-01-23
 */

// Shift register 74HC595:
const int dataPin = D2;  // DS
const int storePin = D4; // ST_CP (also: latchPin)
const int shiftPin = D5; // SH_CP (also: clockPin)
const int resetPin = D6; // MR (active low)

// Motor speed pins
const int speedA = D0;
const int speedB = D1;

// Led
const int led = D7;

/*
 * See setMove() function for movements
 * Motor-groups:
 *             A     A     B     B
 * Motor-numbers:
 *             M3    M4    M1    M2
 * Motor-sides:
 *             R- R+ L- L+ F- F+ B- B+
 */
int STOP[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int FWRD[8] = {1, 0, 0, 1, 0, 0, 0, 0};
int BKWD[8] = {0, 1, 1, 0, 0, 0, 0, 0};
int STRT[8] = {0, 0, 0, 0, 0, 1, 1, 0};
int STLT[8] = {0, 0, 0, 0, 1, 0, 0, 1};
int TRCW[8] = {1, 0, 1, 0, 1, 0, 1, 0};
int TRCC[8] = {0, 1, 0, 1, 0, 1, 0, 1};

/*// test the motors
int M1[8] = {0, 0, 0, 0, 0, 1, 0, 0};
int M2[8] = {0, 0, 0, 0, 0, 0, 0, 1};
int M3[8] = {1, 0, 0, 0, 0, 0, 0, 0};
int M4[8] = {0, 0, 0, 1, 0, 0, 0, 0};*/

// the setup routine runs once when you press reset:
void setup() {
  // Declare Particle.function for sending a command to setMove() from the
  // webapp
  Particle.function("command", command);

  // just for testing
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);

  // Shift register:
  // initialize the digital pins as an output.
  pinMode(dataPin, OUTPUT);
  pinMode(storePin, OUTPUT);
  pinMode(shiftPin, OUTPUT);
  pinMode(resetPin, OUTPUT);

  // Motor speed pins
  pinMode(speedA, OUTPUT);
  pinMode(speedB, OUTPUT);
  analogWrite(speedA, 255);
  analogWrite(speedB, 255);

  // befor initializing set storePin to LOW just in case ...
  digitalWrite(storePin, LOW);

  // ... and reset everything stored
  digitalWrite(resetPin, LOW);
  delayMicroseconds(5);
  digitalWrite(resetPin, HIGH);

  // Aaaaand stop the movement just in case
  setMove(STOP);
}

void loop() {}

/*
 * function of how the motors should move with the shift register
 */
void setMove(int movementArray[]) {

  String arrayOutput = "array: ";

  // set storePin to LOW before shifting values to the register
  digitalWrite(storePin, LOW);

  for (int i = 0; i < 8; i++) {

    // set shiftPin to LOW first, it will shift the value in the register when
    // changed from LOW to HIGH
    digitalWrite(shiftPin, LOW);

    // store the value to dataPin
    digitalWrite(dataPin, movementArray[i]);
    arrayOutput.concat(movementArray[i]);
    delayMicroseconds(5);

    // now set shiftPin to HIGH to shift the value in the register
    digitalWrite(shiftPin, HIGH);
  }

  Particle.publish("arrayOutput", arrayOutput);

  // when everything is stored, copy all values to output pins by setting
  // storePin from LOW to HIGH
  digitalWrite(storePin, HIGH);
}

/*
 * Speed control for motors
 * Groups:
 *  x = both A and B
 *  a = A
 *  b = B
 */
/*void setNewSpeed(int speed = 0, int speed2 = -1, char motorGroup = 'x',
              float speedTime = 1000) {

  // this is basically for the for-loops delay(speedtime / timeTicksDivider)
  int timeTicksDivider = 10;

  // from speed to speed 2
  if (speed2 != -1) {
    int speedDiv = speed2 - speed;
    int speedNew;

    for (int i = 0; i < timeTicksDivider - 1; i++) {
      speedNew = speed + speedDiv / (timeTicksDivider * (1 / i));
      if (speedNew > 255) {
        speedNew = 255;
      };
      setSpeed(speedNew, motorGroup);
      delay(speedTime / timeTicksDivider);
    }
  } else {
    setSpeed(speed, motorGroup);
  }
}*/

/*
 * Set speed to a specified motor group
 * use with setSpeed();
 */
void setSpeed(int sPd, char mGr = 'x') {
  // Motor groups
  // mGr = "x" | "a" | "b"
  if (mGr == 'x') {
    analogWrite(speedA, sPd);
    analogWrite(speedB, sPd);

  } else if (mGr == 'a') {
    analogWrite(speedA, sPd);
    analogWrite(speedB, 0);

  } else if (mGr == 'b') {
    analogWrite(speedA, 0);
    analogWrite(speedB, sPd);
  }
}

/*
 * show percentage value for voltage of batterie
 */
/*float percentageOfBatteryLeft(float voltageRead) {
  float vMin = 3.4;
  float vMax = 4.1;
  float percentage = (voltageRead - vMin) / (vMax - vMin) * 100;

  return percentage;
}*/

/*
 * Function to command the damn thing
 *
 * Movements:
 *   FRWD: Forward
 *   BKWD: Backward
 *     STRT: Sidestrafe to the right
 *     STLT: Sidestrafe to the left
 *     TRCW: Turn clockwise
 *     TRCC: Turn counter-clockwise
 *     STOP: Stop, don't move!
*/
int command(String cmd) {
  Particle.publish("Movement: ", cmd);

  if (cmd == "FWRD") {
    setSpeed(255);
    setMove(FWRD);
    return 6;
  }

  else if (cmd == "BKWD") {
    setSpeed(255);
    setMove(BKWD);
    return 5;
  }

  else if (cmd == "STRT") {
    setSpeed(255);
    setMove(STRT);
    return 4;
  }

  else if (cmd == "STLT") {
    setSpeed(255);
    setMove(STLT);
    return 3;
  }

  else if (cmd == "TRCW") {
    setSpeed(255);
    setMove(TRCW);
    return 2;
  }

  else if (cmd == "TRCC") {
    setSpeed(255);
    setMove(TRCC);
    return 1;
  }

  else if (cmd == "STOP") {
    setMove(STOP);
    return 0;
  }

  else if (cmd == "LED7") {
    digitalWrite(led, HIGH);
    delay(500);
    digitalWrite(led, LOW);
    delay(500);
    digitalWrite(led, HIGH);
    delay(500);
    digitalWrite(led, LOW);
    return 9;
  }

  else if (cmd == "ON") {
    analogWrite(speedA, 255);
    analogWrite(speedB, 255);
    return 10;
  }

  else if (cmd == "OFF") {
    analogWrite(speedA, 0);
    analogWrite(speedB, 0);
    return 10;
  }

  else if (cmd == "MEDIUM") {
    analogWrite(speedA, 150);
    analogWrite(speedB, 150);
    return 10;
  }

  else if (cmd == "P1") {
    setSpeed(255);
    setMove(FWRD);
    delay(750);

    setMove(BKWD);
    delay(750);

    setMove(FWRD);
    delay(750);

    setMove(BKWD);
    delay(750);

    setMove(FWRD);
    delay(750);


    setMove(STOP);
    return 0;
  }

  else {
    return -1;
  }
}

// TODO: make motors run individually
/* Motor Arrays
 * Arrays are setup so that the robot drives forward or right by default
 * This is taken from the turn direction of the Motors
 * Motor Positions on the robot (M2: Front, M3: Left, etc.)
 *
 *    M2
 *  M3  M4
 *    M1
 */
/*int M1[2] = {0,1};
int M2[2] = {0,1};
int M3[2] = {1,0};
int M4[2] = {1,0};*/
