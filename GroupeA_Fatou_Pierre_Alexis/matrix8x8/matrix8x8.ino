/*************************************************** 
 * This is a library for our I2C LED Backpacks
 * 
 * Designed specifically to work with the Adafruit LED Matrix backpacks 
 * ----> http://www.adafruit.com/products/872
 * ----> http://www.adafruit.com/products/871
 * ----> http://www.adafruit.com/products/870
 * 
 * These displays use I2C to communicate, 2 pins are required to 
 * interface. There are multiple selectable I2C addresses. For backpacks
 * with 2 Address Select pins: 0x70, 0x71, 0x72 or 0x73. For backpacks
 * with 3 Address Select pins: 0x70 thru 0x77
 * 
 * Adafruit invests time and resources providing this open source code, 
 * please support Adafruit and open-source hardware by purchasing 
 * products from Adafruit!
 * 
 * Written by Limor Fried/Ladyada for Adafruit Industries.  
 * BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include <Time.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

// type de personne
int qui = 0;
//horaire
int time = 0;
// sortie entree
boolean etat;
// nom de la personne
String nom;
// valide
boolean valide;
int switchState = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("8x8 LED Matrix Test");

  matrix.begin(0x70);  // pass in the address
  
  
 pinMode(2, INPUT);
}



static const uint8_t PROGMEM
vide_bmp[] =
{ 
  B00111100,
  B01111110,
  B11011011,
  B11111111,
  B11011011,
  B11100111,
  B01111110,
  B00111100 }
,
smile_bmp[] =
{ 
  B00111100,
  B01000010,
  B10100101,
  B10000001,
  B10100101,
  B10011001,
  B01000010,
  B00111100 }
,
love_bmp[] =
{ 
  B00000000,
  B01100110,
  B10011001,
  B10000001,
  B01000010,
  B00100100,
  B00011000,
  B00000000 }
,

canne_bmp[] =
{ 
  B00011100,
  B00111110,
  B00110110,
  B00110110,
  B00110110,
  B00000110,
  B00000110,
  B00001111}
  ,
fleche_bmp[] =
{ 
  B00001000,
  B00001100,
  B00001110,
  B11111111,
  B11111111,
  B00001110,
  B00001100,
  B00001000 },


spacial_bmp[] =
{ 
  B01100110,
  B11111111,
  B11111111,
  B11111111,
  B01111110,
  B00111100,
  B00111100,
  B00111100, 
  B00111100,
  B00111100,
  B00111100,
  B00111100,
  B00011110,
  B00001111,
  B00001111,
  B00001111,
  B00001111,
  B00011110,
  B00111100,
  B01111000,
  B11110000,
  B11110000,
  B11110000,
  B01111000,
  B00111100,
  B00111100,
  B00111100,
  B00111100,
  B00111100,
  B00111100,
  B01111110,
  B01111110,
  B00111100,
  B00011000,
  B00000000,
  B00011000,
  B00111100,
  B01011010,
  B10011010,
  B00011000,
  B00011000,
  B00011000,
  B00111100,
  B00111100,
  B00011000,
  B00000000 };

void loop() {
  
  
  
  // ecoute bouton
  switchState = digitalRead(2);
  if(switchState == HIGH){
    valide = true;
  }
  
  // type de personne
  qui = 2;
  //horaire
  


  // sortie entree 
  etat = false ;
  // nom de la personne
  nom = "Lola";
  
  
  // si c'est un vieux
  if(valide == false){
    if(qui == 1)
    {
      for(int i=0; i<3; i++){
        // coeur vide
        matrix.clear();
        matrix.drawBitmap(0, 0, canne_bmp, 8, 8, LED_ON);
        matrix.writeDisplay();      
        
      }
      
    }
    
    // si c'est un ami
    else if(qui == 1)
    {
      for(int i=0; i<3; i++){
        
       // coeur vide
        matrix.clear();
        matrix.drawBitmap(0, 0, smile_bmp, 8, 8, LED_ON);
        matrix.writeDisplay();       
      }
    } 
    
    // si c'est un personnel
    if(qui == 2)
    {
      for(int i=0; i<3; i++){
        
        // coeur vide
        matrix.clear();
        matrix.drawBitmap(0, 0, love_bmp, 8, 8, LED_ON);
        matrix.writeDisplay();

      }
    }
  }else{
    
   matrix.setTextSize(0);
   matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
   matrix.setTextColor(LED_ON);
   
   for (int x=8; x>=-40; x--) {
   matrix.clear();
   matrix.setCursor(x,0);
   matrix.print(nom);
   matrix.writeDisplay();
   delay(80);
   
   }
   
   //si le vieux sort
   if(etat == true){
     matrix.setRotation(1);
       for (int  x=8; x>=-7; x--) {
            matrix.clear();
            matrix.drawBitmap(-x, 0, fleche_bmp, 8, 8, LED_ON);
            matrix.writeDisplay();
            delay(100);
       }
        matrix.setRotation(-1);
       for (int x=10; x>=-40; x--) {
         matrix.clear();
         matrix.setCursor(x,0);
         matrix.print("18:25");
         matrix.writeDisplay();
         delay(100);
       }
        matrix.setRotation(0);
   }else{        
       matrix.setRotation(-1);
       for (int  x=8; x>=-7; x--) {
            matrix.clear();
            matrix.drawBitmap(-x, 0, fleche_bmp, 8, 8, LED_ON);
            matrix.writeDisplay();
            delay(100);
       }
       matrix.setRotation(1);
       for (int x=10; x>=-40; x--) {
         matrix.clear();
         matrix.setCursor(x,0);
         matrix.print("18:25");
         matrix.writeDisplay();
         delay(100);
       }
       
       
      matrix.setRotation(0);

   }
   
   
   
  } 
}

