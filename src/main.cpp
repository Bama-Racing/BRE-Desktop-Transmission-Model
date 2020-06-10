#include <Arduino.h>
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int pot_val;
int rpm;
void potStuff(); //In Atom, you need to define functions. 

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2); // Change to (0x27,20,4) for 20x4 LCD... etc.
Servo ESC_as_Servo; //Define ESC as a Servo


void setup() {
  pinMode(A0, INPUT); //Pot is on pin A0
  pinMode(3, OUTPUT); //ESC is on pin 3


  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("RPM");
  lcd.setCursor(2,1);
  lcd.print("Pot Val");
}


void loop() {
  pot_val = analogRead(A0);
  Serial.println(pot_val); //Allows use of Serial Plotter (CTRL+SHIFT+L) to see pot input

  rpm = map(pot_val,0,1023,0,1200); //Maps pot vals onto RPM saved as Speed

  potStuff();
}


void potStuff() {
  ESC_as_Servo.write(rpm);

  if(millis()%100 == 0) {
    ////Prints Speed calculated above using the Map Function ////
    lcd.setCursor(4,0);
    if (rpm <= 999 && rpm > 10) {
      lcd.print(rpm);
      lcd.print("   ");
    };
    if (rpm > 999) {
      lcd.print(rpm);
      lcd.print("   ");
    };
    if (rpm <= 9) {
      lcd.print(rpm);
      lcd.print("   ");
    };
    ////End////


    ////Prints Pot Raw Reading////
    lcd.setCursor(9,1);
    if (pot_val <= 9999 && pot_val > 999) {
      lcd.print(" ");
      lcd.print(pot_val);
    };
    if (pot_val <= 999 && pot_val > 99) {
      lcd.print(" ");
      lcd.print(pot_val);
      lcd.print(" ");
    };
    if (pot_val <= 99 && pot_val > 9) {
      lcd.print(" ");
      lcd.print(pot_val);
      lcd.print("  ");
    };
    if (pot_val <=9) {
      lcd.print(" ");
      lcd.print(pot_val);
      lcd.print("   ");
    };
    delay(100);
    ////End////
  }
}
