#include <Wire.h>
#include <Adafruit_NFCShield_I2C.h>
#include <LiquidCrystal.h>


#define IRQ   (2)
#define RESET (3)  // Not connected by default on the NFC Shield

Adafruit_NFCShield_I2C nfc(IRQ, RESET);
LiquidCrystal lcd(12, 11, 5, 4, 3, 7);

int DEL = 0;

// 0 = visites
// 1 = personne dans la chambre
int state = 0;


String personnesPassees = "";
String personnesPasseesAffichage = "";
int personnesNb=0;


void setup(void) 
{
  Serial.begin(115200);
  Serial.println("Hello!");
  pinMode(13, OUTPUT);
  lcd.begin(16, 2);


  nfc.begin();

  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {
    Serial.print("Didn't find PN53x board");
    while (1); // halt
  }
  // Got ok data, print it out!
  Serial.print("Found chip PN5"); 
  Serial.println((versiondata>>24) & 0xFF, HEX); 
  Serial.print("Firmware ver. "); 
  Serial.print((versiondata>>16) & 0xFF, DEC); 
  Serial.print('.'); 
  Serial.println((versiondata>>8) & 0xFF, DEC);

  // configure board to read RFID tags
  nfc.SAMConfig();

  Serial.println("Waiting for an ISO14443A Card ...");
}


void loop(void) {
  uint8_t success;
  uint8_t uid[] = { 
    0, 0, 0, 0, 0, 0, 0     };  // Buffer to store the returned UID
  uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)

  // Wait for an ISO14443A type cards (Mifare, etc.).  When one is found
  // 'uid' will be populated with the UID, and uidLength will indicate
  // if the uid is 4 bytes (Mifare Classic) or 7 bytes (Mifare Ultralight)
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);

  if (success) {
    // Display some basic information about the card
    Serial.println("Found an ISO14443A card");
    Serial.print("  UID Length: ");
    Serial.print(uidLength, DEC);
    Serial.println(" bytes");
    Serial.print("  UID Value: ");
    nfc.PrintHex(uid, uidLength);
    Serial.println("");

    if (uidLength == 4)
    {
      // We probably have a Mifare Classic card ... 
      Serial.println("Seems to be a Mifare Classic card (4 byte UID)");

      // Now we need to try to authenticate it for read/write access
      // Try with the factory default KeyA: 0xFF 0xFF 0xFF 0xFF 0xFF 0xFF
      Serial.println("Trying to authenticate block 4 with default KEYA value");
      uint8_t keya[6] = { 
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF             };

      // Start with block 4 (the first block of sector 1) since sector 0
      // contains the manufacturer data and it's probably better just
      // to leave it alone unless you know what you're doing
      success = nfc.mifareclassic_AuthenticateBlock(uid, uidLength, 4, 0, keya);

      if (success)
      {
        Serial.println("Sector 1 (Blocks 4..7) has been authenticated");
        uint8_t data[16];

        // If you want to write something to block 4 to test with, uncomment
        // the following line and this text should be read back in a minute
        //memcpy(data, (const uint8_t[]){ 'a', 'd', 'a', 'f', 'r', 'u', 'i', 't', '.', 'c', 'o', 'm', 0, 0, 0, 0 }, sizeof data);
        //success = nfc.mifareclassic_WriteDataBlock (4, data);

        // Try to read the contents of block 4
        success = nfc.mifareclassic_ReadDataBlock(4, data);

        if (success)
        {
          // Data seems to have been read ... spit it out
          Serial.println("Reading Block 4:");
          nfc.PrintHexChar(data, 16);
          Serial.println("");

          // ************************************************************************************
          // ************************************************************************************
          // ************************************************************************************
          // ************************************************************************************
          if (uid[0] == 0xB3 && uid[1] == 0xA4 && uid[2] == 0x17 && uid[3] == 0x99)
          {
            changeState(0); 
            ajoutePersonnePassee("Bernard");   
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Bernard");           
            lcd.setCursor(0, 1);
            lcd.print("Ch.302");
            delay(1000);
            lcd.clear();
          }  
          else if (uid[0] == 0xC3 && uid[1] == 0x40 && uid[2] == 0x1D && uid[3] == 0xD4)
          {
            changeState(0); 
            ajoutePersonnePassee("Jacqueline");           

            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Jacqueline");           
            lcd.setCursor(0, 1);
            lcd.print("Ch.152");           
            delay(1000);
            lcd.clear();
          }  
          else if (uid[0] == 0x64 && uid[1] == 0xEF && uid[2] == 0x41 && uid[3] == 0xF4)
          {
            changeState(0); 
            ajoutePersonnePassee("Maurice");           
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Maurice");           
            lcd.setCursor(0, 1);
            lcd.print("Ch.040");           
            delay(1000);
            lcd.clear();
          }  
          else if (uid[0] == 0xC3 && uid[1] == 0xE8 && uid[2] == 0x26 && uid[3] == 0xD0)
          {
            changeState(1); 
          }  

          // ************************************************************************************
          // ************************************************************************************
          // ************************************************************************************
          // ************************************************************************************


        }
        else
        {
          Serial.println("Ooops ... unable to read the requested block.  Try another key?");
        }
      }
      else
      {
        Serial.println("Ooops ... authentication failed: Try another key?");
      }

    }



  }
}








