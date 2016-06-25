#include <Servo.h>

int LED_PIN = 13;
int SERVO_PIN = 9;
int BUTTON_PIN = 8;

Servo servo;
int servo_pos = 0;
int servo_state = 0;
int servo_delay = 0;

void setup() {
  Serial.begin(9600);

  // Initialize LED output
  pinMode(LED_PIN, OUTPUT);
  
  // Initialize button input
  pinMode(BUTTON_PIN, INPUT);

  // Initialize servo
  servo.attach(SERVO_PIN);

  Serial.println("Setup complete");
}

void loop() {
  pollButton();
  updateServo();
  delay(10);
}

void updateServo() {
  if (servo_state == 0) {
    if (servo_pos <= 90) {
      servo_pos += 1;
      servo.write(servo_pos);
    }
  }
  else if (servo_state == 1) {
    if (servo_pos <= 90) {
      servo_pos += 1;
      servo.write(servo_pos);
    } 
    else {
      servo_state = 2;
      servo_delay = 0;
    }
  }
  else if (servo_state == 2) {
    if (servo_delay >= 200) {
      servo_state = 3;
    } 
    else {
      servo_delay += 1;
    }
  }
  else if (servo_state == 3) {
    if (servo_pos >= 0) {
      servo_pos -= 1;
      servo.write(servo_pos);
    } 
    else {
      servo_state = 1;
    }
  }
}

void pollButton() {
  if (digitalRead(BUTTON_PIN) == HIGH) {
    Serial.println("Button pushed");

    if (servo_state != 0) {
      Serial.println("Servo disabled");
      digitalWrite(LED_PIN, LOW);
      servo_state = 0;
    } 
    else {
      Serial.println("Servo enabled");
      digitalWrite(LED_PIN, HIGH);
      servo_state = 1;
    }

    while (digitalRead(BUTTON_PIN) == HIGH) { 
      // Do nothing
    }
  }
}






