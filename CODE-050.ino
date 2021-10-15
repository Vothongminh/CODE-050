//#VTM https://www.youtube.com/c/VTMVlogVoThongMinh
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
const int stepPin = 12;//clk+
const int dirPin = 10;//cw+
int on = 6;
int len = 7;
int xuong = 8;
void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(on, INPUT_PULLUP);
  pinMode(len, INPUT_PULLUP);
  pinMode(xuong, INPUT_PULLUP);
}
void loop() {
set:
  long bb = analogRead(A0);
  long aa = analogRead(A1);
  long cc = analogRead(A2);
  double b = map(bb, 0, 1023, 1, 100);//speed
  long a = map(aa, 0, 1023, 1, 100);//distance
  double c = map(cc, 0, 1023, 1, 50);//delay
  //Serial.println(bb);
  //lcd.clear();
  ///////////////////////////////////////////////////////
  lcd.setCursor(0, 0);
  lcd.print("Speed:");
  lcd.setCursor(10, 0);
  lcd.print(b / 10);
  lcd.setCursor(15, 0);
  lcd.print("(v/s)");

  lcd.setCursor(0, 1);
  lcd.print("Distance:");
  lcd.setCursor(10, 1);
  lcd.print(a);
  lcd.setCursor(15, 1);
  lcd.print("(v)");

  lcd.setCursor(0, 2);
  lcd.print("Delay:");
  lcd.setCursor(10, 2);
  lcd.print(c / 10);
  lcd.setCursor(15, 2);
  lcd.print("(s)");

  lcd.setCursor(0, 3);
  lcd.print("");
  lcd.setCursor(10, 3);
  lcd.print("");
  lcd.setCursor(0, 3);
  lcd.print("                    ");

  ///////////////////////////////////////////////////////
  if (a < 100)
  {
    lcd.setCursor(12, 1);
    lcd.print(" ");
  }
  if (a < 10)
  {
    lcd.setCursor(11, 1);
    lcd.print(" ");
  }
  if (b < 100)
  {
    lcd.setCursor(14, 0);
    lcd.print(" ");
  }
  ///////////////////////////////////////////////////////
  if (digitalRead(len) == LOW) {
    lcd.setCursor(8, 3);
    lcd.print(" UP--->");
    while (digitalRead(len) == LOW) {
      //Serial.println("len");
      digitalWrite(dirPin, HIGH);
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(3125 / b);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(3125 / b);
    }
  }
  ///////////////////////////////////////////////////////
  if (digitalRead(xuong) == LOW) {
    lcd.setCursor(4, 3);
    lcd.print("<---DOWN");
    while (digitalRead(xuong) == LOW) {
      //Serial.println("xuong");
      digitalWrite(dirPin, LOW);
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(3125 / b);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(3125 / b);
    }
  }
  ///////////////////////////////////////////////////////
  if (digitalRead(on) == LOW) {
    Serial.println("ON");
    lcd.setCursor(0, 3);
    lcd.print("--------------------");
    digitalWrite(dirPin, HIGH);
    for (int x = 0; x < a * 1600 ; x++) {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(3125 / b);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(3125 / b);
    }
    delay(c * 100);
    digitalWrite(dirPin, LOW);
    for (int x = 0; x < a * 1600 ; x++) {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(3125 / b);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(3125 / b);
    }
    goto set;
  }
}
