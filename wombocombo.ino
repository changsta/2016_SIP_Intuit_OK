#include "VirtualWire.h"
#include "ServoTimer2.h"

int time;
int penstate;
ServoTimer2 servoLeft;
ServoTimer2 servoRight;
ServoTimer2 servoPen;
int xpin = 0;
int ypin = 1;
int led = 6;
int led2 =5;
const int button = 7;
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;

void stopmove(){
  servoLeft.write(1500);
  servoRight.write(1500);
}

void forward(int time){
  servoLeft.write(1300);
  servoRight.write(1700);  
  delay(time);
  stopmove();
}

void backward(int time){
  servoLeft.write(1700);
  servoRight.write(1300);  
  delay(time);
  stopmove();
}

void spinleft(int time){
  servoLeft.write(1700);
  servoRight.write(1700);  
  delay(time);
  stopmove();
}

void spinright(int time){
  servoLeft.write(1300);
  servoRight.write(1300);
  delay(time);  
  stopmove();
}

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(button, INPUT);
  servoLeft.attach(13);
  servoRight.attach(12);
  servoPen.attach(10);
}

void loop() {
  buttonState = digitalRead(button);

  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      // if the current state is HIGH then the button
      // wend from off to on:
      buttonPushCounter++;
    } else {
      // if the current state is LOW then the button
      // wend from on to off:
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state,
  //for next time through the loop
  lastButtonState = buttonState;


  // turns on the LED every four button pushes by
  // checking the modulo of the button push counter.
  // the modulo function gives you the remainder of
  // the division of two numbers:
  if (digitalRead(button)!= LOW){
  if (buttonPushCounter % 2 == 0) {

    servoPen.write(1400);
    delay(200);
    servoPen.write(1500);

  } 
  else {
    servoPen.write(1600);
    delay(200);
    servoPen.write(1500);
      }
  }

  
  // put your main code here, to run repeatedly:
  int xval = analogRead(xpin);
  int yval = analogRead(ypin);
    
  if ((xval<360 && xval>290) && (yval<370 && yval>300)){
    stopmove();
    digitalWrite(led, LOW);
    delay(100);
  }
  if(xval>360){
    digitalWrite(led, HIGH);
    forward(100);
  }
  if(xval<290){
    backward(100);
    digitalWrite(led, HIGH);
  }
  
  if(yval>370){
    spinleft(100);
    digitalWrite(led, HIGH);
  }
  
  if(yval<300){
    spinright(100);
    digitalWrite(led, HIGH);
  }
}
