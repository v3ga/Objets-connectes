/* Setup shield-specific #include statements */
#include <SPI.h>
#include <Dhcp.h>
#include <Dns.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <Temboo.h>
#include "TembooAccount.h" // Contains Temboo account information


byte ethernetMACAddress[] = ETHERNET_SHIELD_MAC;
EthernetClient client;

int numRuns = 1;   // Execution count, so this doesn't run forever
int maxRuns = 10;   // Maximum number of times the Choreo should be executed


void setup() {
  Serial.begin(9600);

  // For debugging, wait until the serial console is connected.
  delay(4000);
  while(!Serial);

  Serial.print("DHCP:");
  if (Ethernet.begin(ethernetMACAddress) == 0) {
    Serial.println("FAIL");
    while(true);
  }
  Serial.println("OK");
  delay(5000);

  Serial.println("Setup complete.\n");
}

void loop() {
  if (numRuns <= maxRuns) {
    Serial.println("Running RetrieveWorksheet - Run #" + String(numRuns++));

    TembooChoreo RetrieveWorksheetChoreo(client);

    // Invoke the Temboo client
    RetrieveWorksheetChoreo.begin();

    // Set Temboo account credentials
    RetrieveWorksheetChoreo.setAccountName(TEMBOO_ACCOUNT);
    RetrieveWorksheetChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
    RetrieveWorksheetChoreo.setAppKey(TEMBOO_APP_KEY);

    // Set Choreo inputs
    String WorksheetNameValue = "Feuille 1";
    RetrieveWorksheetChoreo.addInput("WorksheetName", WorksheetNameValue);
    String UsernameValue = "azibou.oussama@gmail.com";
    RetrieveWorksheetChoreo.addInput("Username", UsernameValue);
    String PasswordValue = "rjkdjxptesequkmm";
    RetrieveWorksheetChoreo.addInput("Password", PasswordValue);
    String SpreadsheetNameValue = "seniorconnecte";
    RetrieveWorksheetChoreo.addInput("SpreadsheetName", SpreadsheetNameValue);

    // Identify the Choreo to run
    RetrieveWorksheetChoreo.setChoreo("/Library/Google/Spreadsheets/RetrieveWorksheet");

    // Run the Choreo; when results are available, print them to serial
    RetrieveWorksheetChoreo.run();

    while(RetrieveWorksheetChoreo.available()) {
      char c = RetrieveWorksheetChoreo.read();
      Serial.print(c);
    }
    RetrieveWorksheetChoreo.close();
  }

  Serial.println("\nWaiting...\n");
  delay(30000); // wait 30 seconds between RetrieveWorksheet calls
}

