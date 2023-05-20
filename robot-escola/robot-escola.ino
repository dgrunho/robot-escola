#include <SoftwareSerial.h>

const int pinoRX = 13;
const int pinoTX = 12;
int dadoBluetooth = 0;

SoftwareSerial bluetooth(pinoRX, pinoTX);

int MOTOR_SPEED = 255;
const byte A_IA = 11;
const byte A_IB = 10;
const byte B_IA = 8;
const byte B_IB = 9;

const byte sensorBar = 7;

#define left 6
#define center 4
#define right 5

int lineMode = 0;
int bluetoothMode = 1;
int tableMode = 2;
int currentMode = bluetoothMode;

void setup() {
  pinMode(A_IA, OUTPUT);
  pinMode(A_IB, OUTPUT);
  pinMode(B_IA, OUTPUT);
  pinMode(B_IB, OUTPUT);

  pinMode(sensorBar, OUTPUT);
  digitalWrite(sensorBar, LOW);
  pinMode(left, INPUT);
  pinMode(center, INPUT);
  pinMode(right, INPUT);

  digitalWrite(A_IA, LOW);
  digitalWrite(A_IB, LOW);
  digitalWrite(B_IA, LOW);
  digitalWrite(B_IB, LOW);



  Serial.begin(9600);
  bluetooth.begin(9600);
  bluetooth.print("$");
  bluetooth.print("$");
  bluetooth.print("$");
  delay(100);
}

void loop() {
  if (bluetooth.available()) {
    dadoBluetooth = bluetooth.read();
    if (dadoBluetooth != 83) {
      Serial.println(char(dadoBluetooth));

      if (char(dadoBluetooth) == 'W' || char(dadoBluetooth) == 'w') {
        currentMode = lineMode;
        MOTOR_SPEED = 150;
        digitalWrite(sensorBar, HIGH);
      }
      if (char(dadoBluetooth) == 'U' || char(dadoBluetooth) == 'u') {
        currentMode = tableMode;
        MOTOR_SPEED = 150;
        digitalWrite(sensorBar, HIGH);
      }
      if (char(dadoBluetooth) == 'V' || char(dadoBluetooth) == 'v') {
        currentMode = bluetoothMode;
        MOTOR_SPEED = 255;
        digitalWrite(sensorBar, LOW);
      }



      if (char(dadoBluetooth) == 'F') {
        rotateMotorA(HIGH, MOTOR_SPEED);
        rotateMotorB(HIGH, MOTOR_SPEED);
      }
      if (char(dadoBluetooth) == 'I') {
        rotateMotorA(LOW, 150);
        rotateMotorB(HIGH, MOTOR_SPEED);
      }
      if (char(dadoBluetooth) == 'G') {

        rotateMotorA(HIGH, MOTOR_SPEED);
        rotateMotorB(LOW, 150);
      }
      if (char(dadoBluetooth) == 'L') {
        rotateMotorA(HIGH, MOTOR_SPEED);
        rotateMotorB(LOW, MOTOR_SPEED);
      }
      if (char(dadoBluetooth) == 'R') {
        rotateMotorA(LOW, MOTOR_SPEED);
        rotateMotorB(HIGH, MOTOR_SPEED);
      }
      if (char(dadoBluetooth) == 'J') {
        rotateMotorA(LOW, 0);
        rotateMotorB(LOW, MOTOR_SPEED);
      }
      if (char(dadoBluetooth) == 'H') {
        rotateMotorA(LOW, MOTOR_SPEED);
        rotateMotorB(LOW, 0);
      }
      if (char(dadoBluetooth) == 'B') {
        rotateMotorA(LOW, MOTOR_SPEED);
        rotateMotorB(LOW, MOTOR_SPEED);
      }
    } else {
      rotateMotorA(LOW, 0);
      rotateMotorB(LOW, 0);
    }
  }

  if (currentMode == lineMode) {
    bool leftV = digitalRead(left);
    bool centerV = digitalRead(center);
    bool rightV = digitalRead(right);

    Serial.print(leftV);
    Serial.print(centerV);
    Serial.println(rightV);

    if (leftV == 0 && centerV == 1 && rightV == 0) {
      rotateMotorA(HIGH, MOTOR_SPEED);
      rotateMotorB(HIGH, MOTOR_SPEED);
    } else if (leftV == 1 && centerV == 1 && rightV == 1) {
      rotateMotorA(LOW, 0);
      rotateMotorB(LOW, 0);
    } else if (leftV == 0 && centerV == 0 && rightV == 0) {
      rotateMotorA(LOW, 0);
      rotateMotorB(LOW, 0);
    } else if (leftV == 1 && centerV == 1 && rightV == 0) {
      rotateMotorA(HIGH, MOTOR_SPEED);
      rotateMotorB(LOW, MOTOR_SPEED);
     // delay(50);
    } else if (leftV == 0 && centerV == 1 && rightV == 1) {
      rotateMotorA(LOW, MOTOR_SPEED);
      rotateMotorB(HIGH, MOTOR_SPEED);
     // delay(50);
    } else if (leftV == 1 && centerV == 0 && rightV == 0) {
      rotateMotorA(HIGH, MOTOR_SPEED);
      rotateMotorB(LOW, MOTOR_SPEED);
     // delay(50);
    } else if (leftV == 0 && centerV == 0 && rightV == 1) {
      rotateMotorA(LOW, MOTOR_SPEED);
      rotateMotorB(HIGH, MOTOR_SPEED);
     // delay(50);
    }
  }

  if (currentMode == tableMode) {
    bool leftV = digitalRead(left);
    bool rightV = digitalRead(right);

    Serial.print(leftV);
    Serial.println(rightV);

    if (leftV == 0 && rightV == 0) {
      rotateMotorA(HIGH, MOTOR_SPEED);
      rotateMotorB(HIGH, MOTOR_SPEED);
    } else if (leftV == 1 && rightV == 1) {
      rotateMotorA(LOW, MOTOR_SPEED);
      rotateMotorB(LOW, MOTOR_SPEED);
      delay(250);
      rotateMotorA(HIGH, MOTOR_SPEED);
      rotateMotorB(LOW, MOTOR_SPEED);
      delay(1000);
    } else if (leftV == 1 && rightV == 0) {
      rotateMotorA(LOW, MOTOR_SPEED);
      rotateMotorB(LOW, MOTOR_SPEED);
      delay(250);
     rotateMotorA(LOW, MOTOR_SPEED);
      rotateMotorB(HIGH, MOTOR_SPEED);
      delay(1000);
    } else if (leftV == 0 && rightV == 1) {
      rotateMotorA(LOW, MOTOR_SPEED);
      rotateMotorB(LOW, MOTOR_SPEED);
      delay(250);
      
       rotateMotorA(HIGH, MOTOR_SPEED);
      rotateMotorB(LOW, MOTOR_SPEED);
      delay(1000);
    }
  }
}



void rotateMotorA(int DIR, int SPEED) {
  digitalWrite(A_IA, DIR);
  if (DIR == LOW) {
    analogWrite(A_IB, SPEED);
  } else {
    analogWrite(A_IB, 255 - SPEED);
  }
}

void rotateMotorB(int DIR, int SPEED) {
  digitalWrite(B_IA, DIR);
  if (DIR == LOW) {
    analogWrite(B_IB, SPEED);
  } else {
    analogWrite(B_IB, 255 - SPEED);
  }
}
