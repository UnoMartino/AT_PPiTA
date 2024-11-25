#include <Arduino.h>
#include <WiFi.h>
#include <Adafruit_NeoPixel.h>

#define PIN        21
#define NUMPIXELS 1

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_RGB + NEO_KHZ800);


// const char* ssid     = "C111";
// const char* password = "abcdefabcdef987654321";
const char* ssid     = "madaniu";
const char* password = "qwertyuiop";

WiFiServer server(80);

void setup()
{
    Serial.begin(115200);
    // pinMode(21, OUTPUT);      // set the LED pin mode
    pixels.begin();


    delay(10);

    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    // You can remove the password parameter if you want the AP to be open.
    // a valid password must have more than 7 characters
    if (!WiFi.softAP(ssid, password)) {
      log_e("Soft AP creation failed.");
      while(1);
    }
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);
    server.begin();

    Serial.println("Server started");

}

void loop(){
 WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
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
            client.print("Click <a href=\"/R\">here</a> to turn the LED red.<br>");
            client.print("Click <a href=\"/G\">here</a> to turn the LED green.<br>");
            client.print("Click <a href=\"/B\">here</a> to turn the LED blue.<br>");

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

        if (currentLine.endsWith("GET /R")) {
          pixels.clear();
          pixels.setPixelColor(0, pixels.Color(255, 0, 0));
          pixels.show(); 
        }
        if (currentLine.endsWith("GET /G")) {
          pixels.clear();
          pixels.setPixelColor(0, pixels.Color(0, 255, 0));
          pixels.show();
        }
        if (currentLine.endsWith("GET /B")) {
          pixels.clear();
          pixels.setPixelColor(0, pixels.Color(0, 0, 255));
          pixels.show();
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}