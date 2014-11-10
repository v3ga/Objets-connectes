// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 7);
LCDRowDisplay rowDisplay0;

void setup() 
{
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  rowDisplay0.set(0,"Passage de Christophe");
}

void loop() 
{
  rowDisplay0.update();

  lcd.setCursor(0, 1);
  lcd.print("Chambre 210");


  delay(250);
}


void lcdPrint(String s)
{
  if (s.length()>16)
  {
    
  }
}

