/*
  Countdown on a single DMD display
 */

#include <SPI.h>
#include <DMD2.h>
#include <fonts/Arial14.h>
#include <fonts/digit_16.h>

const int COUNTDOWN_FROM = 30;
int counter = COUNTDOWN_FROM;
const byte Button_20S = 2;
const byte Button_RESET = 3;
const byte Button_Start = 4;
const byte Buzzer_pin = 12;
bool Set_20S = false;
bool start =true;
bool digit_state = false;

SoftDMD dmd(1,2);  // DMD controls the entire display
DMD_TextBox box(dmd, 6, 8);  // "box" provides a text box to automatically write to/scroll the display

// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);
  dmd.setBrightness(255);
  dmd.selectFont(digit_16);
  dmd.begin();
  pinMode(Button_20S, INPUT_PULLUP);
  pinMode(Button_RESET, INPUT_PULLUP);
  pinMode(Button_Start, INPUT_PULLUP);
  pinMode(Buzzer_pin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(Button_20S), Set_to_20S, FALLING);
  attachInterrupt(digitalPinToInterrupt(Button_RESET), Reset_Time, FALLING);
}

// the loop routine runs over and over again forever:
void loop() {
  if(digitalRead(Button_Start) == LOW){
    start = true;
  }
  if(start){
  Serial.print(counter);
  Serial.println(F(""));
  
  if(counter <= 9){digit_state = false;} else { digit_state = true;}
  if (digit_state){
  box.print(counter);}
  if (!digit_state){
    if(counter == 9){ box.print("09");}
    if(counter == 8){ box.print("08");}
    if(counter == 7){ box.print("07");}
    if(counter == 6){ box.print("06");}
    if(counter == 5){ box.print("05");}
    if(counter == 4){ box.print("04");}
    if(counter == 3){ box.print("03");}
    if(counter == 2){ box.print("02");}
    if(counter == 1){ box.print("01");}
    //if(counter == 0){ box.print("00");}
  }
  
  counter--;
  delay(1000);
  box.clear();
  }

  if(counter == 0) {
    box.print("00");
    digitalWrite(Buzzer_pin, HIGH);
    delay(1000);
    box.clear();
    delay(500);
    box.print("00");
    delay(1000);
    box.clear();
    delay(500);
    box.print("00");
    delay(1000);
    box.clear();
    delay(500);
    digitalWrite(Buzzer_pin, LOW);
    counter = 30;
    start = false;
  }
}
void Set_to_20S(){
  counter = 20;
  Set_20S = true;
}
void Reset_Time(){
  
    counter = 30;
}
