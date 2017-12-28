
#include <LiquidCrystal_I2C.h>

long previous_print_time=millis();
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x3F, 16, 2);

void setup()
{
  // initialize the LCD
  Serial.begin(9600);
  lcd.begin();

  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.print("Hello, world!");
}

void loop() {
  long current_time=millis();
  if((current_time-previous_print_time)>=1000){
    previous_print_time+=1000;
    if(Serial.available()>0){
      int start=0;
      lcd.clear();
    while(Serial.available()>0){
      char data=Serial.read();
      if(start==16){
        lcd.setCursor(0,1);
      }
      if(start==32){
        lcd.setCursor(0,0);
        start=0;
      }
      lcd.print(data);
      start++;
    }
    }
  }
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
//  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
//  lcd.print(millis()/1000,DEC);
}
