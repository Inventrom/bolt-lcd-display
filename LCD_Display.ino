
#include <LiquidCrystal_I2C.h>

String Trending[10];

int Trending_Count=0,max_received=0,top_on_display=0;


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
      while(Serial.available()>0){
        Trending[Trending_Count++]=Serial.readString();
        if(Trending_Count>max_received){
          max_received=Trending_Count;
        }
        if(Trending_Count>9){
          Trending_Count=0;
        }
      }
    }
    if(max_received<1){
      return;
    }
    lcd.clear();
    lcd.print(Trending[top_on_display]);
    if(max_received<2){
      return;
    }
    lcd.setCursor(0,1);
    lcd.print(Trending[(top_on_display+1)%max_received]);
    top_on_display++;
    top_on_display=top_on_display%max_received;
  }
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
//  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
//  lcd.print(millis()/1000,DEC);
}
