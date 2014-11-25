import processing.serial.*;
import com.temboo.core.*;
import com.temboo.Library.Google.Spreadsheets.*;


Serial myPort;  // Create object from Serial class
int val;      // Data received from the serial port

TembooSession session = new TembooSession("oussama", "myFirstApp", "####");
String googleProfile = "seniorconnecte";


void setup() 
{
  size(200, 200);
  String[] ports = Serial.list();
  for (int i=0; i<ports.length; i++){
    println("["+i+"] "+ports[i]);
  } 
  println(  );
  String portName = Serial.list()[7];
  myPort = new Serial(this, portName, 9600);
}

void draw()
{
  if ( myPort.available() > 0) 
  {  // If data is available,
    int rfid = myPort.read();         // read it and store it in val

    println(rfid);
    runAppendRowChoreo(rfid);
  }
  background(random(255));             // Set background to white
}




/*

// Wiring / Arduino Code
// Code for sensing a switch status and writing the value to the serial port.

int switchPin = 4;                       // Switch connected to pin 4

void setup() {
  pinMode(switchPin, INPUT);             // Set pin 0 as an input
  Serial.begin(9600);                    // Start serial communication at 9600 bps
}

void loop() {
  if (digitalRead(switchPin) == HIGH) {  // If switch is ON,
    Serial.write(1);               // send 1 to Processing
  } else {                               // If the switch is not ON,
    Serial.write(0);               // send 0 to Processing
  }
  delay(100);                            // Wait 100 milliseconds
}

*/
