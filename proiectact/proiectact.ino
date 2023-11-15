#include <IRremote.h>
#include <Stepper.h>

const int stepsPerRevolution = 1000;
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

const int receiverPin = 2;
const int delayy = 8;
IRrecv irrecv(receiverPin);
decode_results results;

int aux = 0;
int aux2 = 0;
int speed = 50;

const int redPin = 6;
const int greenPin = 5;
const int bluePin = 7;

void setup() {
  myStepper.setSpeed(speed);
  irrecv.enableIRIn();
  Serial.begin(9600);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void ledOn(){
    digitalWrite(greenPin, HIGH);   // Turn on the blue LED
}

void ledOff(){
    digitalWrite(greenPin, LOW);   // Turn on the blue LED
}

void loop() {
  if (irrecv.decode(&results)) {
    if (results.value == 0xFFFFFFFF && aux == 0) {
      for (int i = 0; i < stepsPerRevolution / 2; i++) {
        myStepper.step(1);
        delay(delayy);
        aux = 1;
        ledOn();
      }
    } else if (results.value == 0xFFFFFFFF && aux == 1) {
      for (int i = 0; i < stepsPerRevolution / 2; i++) {
        myStepper.step(-1);
        delay(delayy);
        aux = 0;
        ledOff();
      }
    }
    irrecv.resume();
  }
}