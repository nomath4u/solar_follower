#include <Servo.h>
#include <LiquidCrystal.h>
#define XPIN 10
#define BOTTOM_LEFT A1
#define BOTTOM_RIGHT A0
#define SERVMAX 175
#define SERVMIN 10
#define THRESHOLD 25
#define XFLAT 90
#define YFLAT 90
Servo x_servo;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int xval;
int yval;
int sense;

/* A higher number on the photo sense means more shadow */
int prev_sense;
void setup(){
  x_servo.attach(XPIN);
  Serial.begin(9600);
  xval = XFLAT;
  yval = YFLAT;
  sense = 0;
  lcd.begin(16, 2);
  lcd.print("hello, world!");
}

void loop(){
  int xmove = 0;
  //val++;
  //if(val > SERVMAX){
  //  val = SERVMIN;
//  }
//  else if(val < SERVMIN){
//    val = SERVMAX;
//  }
//  x_servo.write(val);
//  prev_sense = sense;
//  sense = analogRead(SENSEPIN);
//  if(prev_sense > sense ){
//    val = val - 3; //Go back 3 so we are back 2 when we add one later
//  }
//  Serial.println(x_servo.read());
//  delay(100);

  movex(check_movex());
  lcd.setCursor(0, 1);
  lcd.print(analogRead(BOTTOM_LEFT));
  delay(10);
//    Serial.print("Left: ");
//    Serial.print(analogRead(BOTTOM_LEFT));
//    Serial.print("   Right: ");
//    Serial.print(analogRead(BOTTOM_RIGHT));
//    Serial.print("   Xval: ");
//    Serial.println(xval);
}

/*If left is greater than right return 1
  else return 0                       */
int check_movex(){
  int left = 0;
  int right = 0;
  left = analogRead(BOTTOM_LEFT);
  right = analogRead(BOTTOM_RIGHT);
  if ((left - THRESHOLD) > right){
    return 1;
  }
  else if( (right - THRESHOLD) > left ){
    return -1;
  }
  else{
    return 0;
  }
}

void movex(int dir){
  switch(dir){
    case 1:
      xval++;
      break;
    case -1:
      xval--;
      break;
    /*Intentionally do nothing here*/   
    case 0:
    default:
      break;
  }
  if(xval < SERVMIN){
    xval = SERVMIN;
  }
  if(xval > SERVMAX ){
    xval = SERVMAX;
  }
  x_servo.write(xval);
}
