#include <Wire.h>
#include <Adafruit_NFCShield_I2C.h>

/* Setup shield-specific #include statements */
#include <SPI.h>
#include <Dhcp.h>
#include <Dns.h>

#define IRQ   (2)
#define RESET (3)  // Not connected by default on the NFC Shield

Adafruit_NFCShield_I2C nfc(IRQ, RESET);

void setup(void) {
  Serial.begin(115200);

  nfc.begin();

  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {
    Serial.print("Didn't find PN53x board");
    while (1); // halt
  }

  // configure board to read RFID tags
  nfc.SAMConfig();

  
  }
  Serial.println("OK");
  delay(5000);

  Serial.println("Setup complete.\n");


  Serial.println("Waiting for an ISO14443A Card ...");
}


void loop(void) {
  uint8_t success;
  uint8_t uid[] = { 
    0, 0, 0, 0, 0, 0, 0   };  // Buffer to store the returned UID
  uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)

  // Wait for an ISO14443A type cards (Mifare, etc.).  When one is found
  // 'uid' will be populated with the UID, and uidLength will indicate
  // if the uid is 4 bytes (Mifare Classic) or 7 bytes (Mifare Ultralight)
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);

  if (success) {
    // Display some basic information about the card
/*    Serial.println("Found an ISO14443A card");
    Serial.print("  UID Length: ");
    Serial.print(uidLength, DEC);
    Serial.println(" bytes");
    Serial.print("  UID Value: ");
*/
    nfc.PrintHex(uid, uidLength);
    //Serial.println("");

    if (uidLength == 4)
    {
      // We probably have a Mifare Classic card ... 
//      Serial.println("Seems to be a Mifare Classic card (4 byte UID)");

      // Now we need to try to authenticate it for read/write access
      // Try with the factory default KeyA: 0xFF 0xFF 0xFF 0xFF 0xFF 0xFF
  //    Serial.println("Trying to authenticate block 4 with default KEYA value");
      uint8_t keya[6] = { 
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF       };

      // Start with block 4 (the first block of sector 1) since sector 0
      // contains the manufacturer data and it's probably better just
      // to leave it alone unless you know what you're doing
      //success = nfc.mifareclassic_AuthenticateBlock(uid, uidLength, 4, 0, keya);

      if (success)
      {
//        Serial.println("Sector 1 (Blocks 4..7) has been authenticated");
        //uint8_t data[16];

        // If you want to write something to block 4 to test with, uncomment
        // the following line and this text should be read back in a minute
        //memcpy(data, (const uint8_t[]){ 'a', 'd', 'a', 'f', 'r', 'u', 'i', 't', '.', 'c', 'o', 'm', 0, 0, 0, 0 }, sizeof data);
        //success = nfc.mifareclassic_WriteDataBlock (4, data);

        // Try to read the contents of block 4
        //success = nfc.mifareclassic_ReadDataBlock(4, data);

        if (success)
        {
          //delay(500);
          // Data seems to have been read ... spit it out
          //Serial.println("Reading Block 4:");
          //nfc.PrintHexChar(data, 16);
          //Serial.println("");

          // ***************************************

//          Serial.println("Running AppendRow - Run #" + String(numRuns++));

          TembooChoreo AppendRowChoreo(client);

          // Invoke the Temboo client
          Serial.println("begin");
          AppendRowChoreo.begin();

          // Set Temboo account credentials
          Serial.println("credentials");
          AppendRowChoreo.setAccountName(TEMBOO_ACCOUNT);
          AppendRowChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
          AppendRowChoreo.setAppKey(TEMBOO_APP_KEY);

          // Set Choreo inputs
          Serial.println("inputs");
          String UsernameValue = "azibou.oussama@gmail.com";
          AppendRowChoreo.addInput("Username", UsernameValue);
          String PasswordValue = "rjkdjxptesequkmm";
          AppendRowChoreo.addInput("Password", PasswordValue);
          String RowDataValue = "30,40,50";
          AppendRowChoreo.addInput("RowData", RowDataValue);
          String SpreadsheetTitleValue = "seniorconnecte";
          AppendRowChoreo.addInput("SpreadsheetTitle", SpreadsheetTitleValue);

          // Identify the Choreo to run
          Serial.println("setChoreo");
          AppendRowChoreo.setChoreo("/Library/Google/Spreadsheets/AppendRow");

          // Run the Choreo; when results are available, print them to serial
          Serial.println("run");
          AppendRowChoreo.run();

          Serial.println("answer");
          while(AppendRowChoreo.available()) {
            char c = AppendRowChoreo.read();
            Serial.print(c);
          }

          Serial.println("close");
          AppendRowChoreo.close();

          Serial.println("done");

          // ***************************************



          // Wait a bit before reading the card again
          delay(1000);
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


