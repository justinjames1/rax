int speed = 80;
int motorstat = 1;
int transmit = 1;
#define rx5 6
#define tx5 7
#include <Arduino.h> //so people can compile using g++
#include "RAX.h"
#include "Arduino_LED_Matrix.h"   // Include the LED_Matrix library
#include "frames.h"     
#include "WiFiS3.h"
#include "arduino_secrets.h" 
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = "ssid";        // your network SSID (name)
char pass[] = "paasword";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;                 // your network key index number (needed only for WEP)

int led =  LED_BUILTIN;
int status = WL_IDLE_STATUS;
WiFiServer server(80);
 
int distance = 0;
ArduinoLEDMatrix Matrix;
void setup() {
  Matrix.begin(); 
Serial.begin(115200);           // Initialize serial communication at a baud rate of 115200


  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

  pinMode(rx5, INPUT);
  pinMode(tx5, OUTPUT); //enable the radars commuication protocol

//webserver part below

  Serial.begin(9600);      // initialize serial communication
  pinMode(led, OUTPUT);      // set the LED pin mode

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);                   // print the network name (SSID);

    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection:
delay(1000);
  }
  server.begin();                           // start the web server on port 80
  printWifiStatus();  

}
int TRX1 = 0;
void loop() {

  Matrix.begin(); 

if (motorstat == 1){
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);}
  if (motorstat == 2){
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);}
  if (motorstat == 0){
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);}

if(transmit == 1){
  digitalWrite(tx5,HIGH); TRX1 = 1;
  while(TRX1==1){distance++; if(digitalRead(rx5) == HIGH) {TRX1 = 0; Serial.print("RXA ECHOE DETECTED.\n");}} //transmit 
delay(100);distance = 0;
  digitalWrite(tx5,LOW);
    digitalWrite(tx5,HIGH); TRX1 = 1;
  while(TRX1==1){distance++; if(digitalRead(rx5) == HIGH) {TRX1 = 0; Serial.print("RXA ECHOE DETECTED.\n");}} //transmit 
delay(100);distance = 0;
  digitalWrite(tx5,LOW);
    digitalWrite(tx5,HIGH); TRX1 = 1;
  while(TRX1==1){distance++; if(digitalRead(rx5) == HIGH) {TRX1 = 0; Serial.print("RXA ECHOE DETECTED.\n");}} //transmit 
delay(100);distance = 0;
  digitalWrite(tx5,LOW);
    digitalWrite(tx5,HIGH); TRX1 = 1;
  while(TRX1==1){distance++; if(digitalRead(rx5) == HIGH) {TRX1 = 0; Serial.print("RXA ECHOE DETECTED.\n");}} //transmit 
delay(100);distance = 0;
  digitalWrite(tx5,LOW);
}

  delay(1);

  analogWrite(8, speed);
     
//webserver part below

 WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("new client");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out to the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:

                        client.print("<p style=\"font-size:2vw;\">RAX-L293D40P1 CONTROL PANEL<br></p>");
            client.print("<p style=\"font-size:2vw;\">Click <a href=\"/H\">here</a> turn the LED on<br></p>");
            client.print("<p style=\"font-size:2vw;\">Click <a href=\"/L\">here</a> turn the LED off<br></p>");
            
            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(LED_BUILTIN, HIGH);               // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(LED_BUILTIN, LOW);                // GET /L turns the LED off
        }
      }
      
    }
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  // print where to go in a browser:
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);



//led matrix


  // Load and display the "chip" frame on the LED matrix
  Matrix.loadFrame(chip);
 


  // Turn off the display

  // Print the current value of millis() to the serial monitor
  Serial.println(millis());


} //i hope you read allat mate
