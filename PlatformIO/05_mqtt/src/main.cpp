#include <Arduino.h>
#include <WiFi.h>
#include "WiFiClientSecure.h"
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>


#define WLAN_SSID "C111"
#define WLAN_PASS "abcdefabcdef987654321"

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  8883
#define AIO_USERNAME "unomartino"
#define AIO_KEY      "aio_fAjT09eo8uRNJOdPrQ7Btx8MOVPt"

#define PIN        21
#define NUMPIXELS 1
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_RGB + NEO_KHZ800);

#define I2C_SCL 10
#define I2C_SDA 9

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C



WiFiClientSecure client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
const char* adafruitio_root_ca = \
      "-----BEGIN CERTIFICATE-----\n"
      "MIIEjTCCA3WgAwIBAgIQDQd4KhM/xvmlcpbhMf/ReTANBgkqhkiG9w0BAQsFADBh\n"
      "MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\n"
      "d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBH\n"
      "MjAeFw0xNzExMDIxMjIzMzdaFw0yNzExMDIxMjIzMzdaMGAxCzAJBgNVBAYTAlVT\n"
      "MRUwEwYDVQQKEwxEaWdpQ2VydCBJbmMxGTAXBgNVBAsTEHd3dy5kaWdpY2VydC5j\n"
      "b20xHzAdBgNVBAMTFkdlb1RydXN0IFRMUyBSU0EgQ0EgRzEwggEiMA0GCSqGSIb3\n"
      "DQEBAQUAA4IBDwAwggEKAoIBAQC+F+jsvikKy/65LWEx/TMkCDIuWegh1Ngwvm4Q\n"
      "yISgP7oU5d79eoySG3vOhC3w/3jEMuipoH1fBtp7m0tTpsYbAhch4XA7rfuD6whU\n"
      "gajeErLVxoiWMPkC/DnUvbgi74BJmdBiuGHQSd7LwsuXpTEGG9fYXcbTVN5SATYq\n"
      "DfbexbYxTMwVJWoVb6lrBEgM3gBBqiiAiy800xu1Nq07JdCIQkBsNpFtZbIZhsDS\n"
      "fzlGWP4wEmBQ3O67c+ZXkFr2DcrXBEtHam80Gp2SNhou2U5U7UesDL/xgLK6/0d7\n"
      "6TnEVMSUVJkZ8VeZr+IUIlvoLrtjLbqugb0T3OYXW+CQU0kBAgMBAAGjggFAMIIB\n"
      "PDAdBgNVHQ4EFgQUlE/UXYvkpOKmgP792PkA76O+AlcwHwYDVR0jBBgwFoAUTiJU\n"
      "IBiV5uNu5g/6+rkS7QYXjzkwDgYDVR0PAQH/BAQDAgGGMB0GA1UdJQQWMBQGCCsG\n"
      "AQUFBwMBBggrBgEFBQcDAjASBgNVHRMBAf8ECDAGAQH/AgEAMDQGCCsGAQUFBwEB\n"
      "BCgwJjAkBggrBgEFBQcwAYYYaHR0cDovL29jc3AuZGlnaWNlcnQuY29tMEIGA1Ud\n"
      "HwQ7MDkwN6A1oDOGMWh0dHA6Ly9jcmwzLmRpZ2ljZXJ0LmNvbS9EaWdpQ2VydEds\n"
      "b2JhbFJvb3RHMi5jcmwwPQYDVR0gBDYwNDAyBgRVHSAAMCowKAYIKwYBBQUHAgEW\n"
      "HGh0dHBzOi8vd3d3LmRpZ2ljZXJ0LmNvbS9DUFMwDQYJKoZIhvcNAQELBQADggEB\n"
      "AIIcBDqC6cWpyGUSXAjjAcYwsK4iiGF7KweG97i1RJz1kwZhRoo6orU1JtBYnjzB\n"
      "c4+/sXmnHJk3mlPyL1xuIAt9sMeC7+vreRIF5wFBC0MCN5sbHwhNN1JzKbifNeP5\n"
      "ozpZdQFmkCo+neBiKR6HqIA+LMTMCMMuv2khGGuPHmtDze4GmEGZtYLyF8EQpa5Y\n"
      "jPuV6k2Cr/N3XxFpT3hRpt/3usU/Zb9wfKPtWpoznZ4/44c1p9rzFcZYrWkj3A+7\n"
      "TNBJE0GmP2fhXhP1D/XVfIW/h0yCJGEiV9Glm/uGOa3DXHlmbAcxSyCRraG+ZBkA\n"
      "7h4SeM6Y8l/7MBRpPCz6l8Y=\n"
      "-----END CERTIFICATE-----\n";


Adafruit_MQTT_Publish test = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/test");

Adafruit_MQTT_Subscribe onoffbutton = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/onoff", MQTT_QOS_1);
Adafruit_MQTT_Subscribe color = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/color", MQTT_QOS_1);

Adafruit_MQTT_Publish onoffbuttonpublish = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/onoff");

Adafruit_MQTT_Publish bme_humid = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/bme_humid");
Adafruit_MQTT_Publish bme_pres = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/bme_pres");
Adafruit_MQTT_Publish bme_temp = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/bme_temp");

bool onoffvalue;
bool b0state = 0;
bool b0laststate = 0;
char colorvalue[7]; 
// uint32_t x=0;

unsigned long lockTime = 0;
bool lock = 0;

void pin_ISR();
void MQTT_connect();
void onoffcallback(char *data, uint16_t len);
void colorcallback(char *data, uint16_t len);


void setup() {
  pinMode(0, INPUT);
  Serial.begin(115200);

  unsigned status;
  Wire.begin(I2C_SDA, I2C_SCL);
  status = bme.begin(0x76); 

  if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
        Serial.print("SensorID was: 0x"); Serial.println(bme.sensorID(),16);
        Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
        Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
        Serial.print("        ID of 0x60 represents a BME 280.\n");
        Serial.print("        ID of 0x61 represents a BME 680.\n");
        while (1) delay(10);
  }

  Serial.println(F("Adafruit IO MQTTS (SSL/TLS) Example"));

  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

  client.setCACert(adafruitio_root_ca);

  onoffbutton.setCallback(onoffcallback);
  mqtt.subscribe(&onoffbutton);

  color.setCallback(colorcallback);
  mqtt.subscribe(&color);

  attachInterrupt(0, pin_ISR, CHANGE);

}


void loop() {
  MQTT_connect();

  mqtt.processPackets(1000);

  if (b0laststate) {
    b0laststate = 0;
    if (onoffvalue) {
      onoffbuttonpublish.publish("0");
    } else {
      onoffbuttonpublish.publish("1");
    }
  }

  if (Serial.available()) {
    char c = Serial.read();
    if (c == '1') {
      Serial.println(F("Sending 1"));
      onoffbuttonpublish.publish("1");
    }
    if (c == '0') {
      Serial.println(F("Sending 0"));
      onoffbuttonpublish.publish("0");
    }
  }

  if(! mqtt.ping()) {
    mqtt.disconnect();
  }

  if (millis() - lockTime < 10000) {lock = 1;}
  else if (millis() - lockTime > 10000) {lock = 0;}

  if (!lock) {
    lockTime = millis();
    float temp = bme.readTemperature();
    float humid = bme.readHumidity();
    float pres = bme.readPressure() / 100.0F;

    bme_humid.publish(humid);
    bme_pres.publish(pres);
    bme_temp.publish(temp);
  }

}

void MQTT_connect() {
  int8_t ret;

  if (mqtt.connected()) {return;}
  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         while (1);
       }
  }

  Serial.println("MQTT Connected!");
}

void onoffcallback(char *data, uint16_t len) {
  Serial.print(F("Feed onoff got: "));
  Serial.println(data);
  onoffvalue = atoi(data);

  if (onoffvalue) {
    pixels.clear();
    pixels.setPixelColor(0, strtol(colorvalue, NULL, 16));
    pixels.show();
  } else {
    pixels.clear();
    pixels.setPixelColor(0, pixels.Color(0, 0, 0));
    pixels.show();
  }

}

void colorcallback(char *data, uint16_t len) {
  Serial.print(F("Feed color got: "));
  Serial.println(data);
  strncpy(colorvalue, data + 1, len - 1);
  colorvalue[len - 1] = '\0';

  pixels.clear();
  pixels.setPixelColor(0, strtol(colorvalue, NULL, 16));
  pixels.show();
}


void pin_ISR() {
  bool button = digitalRead(0);
  if (!button) {
    if (b0state == 0) {
      b0state = 1;
      b0laststate = 1;
    }
  }
  else {
    b0state = 0;
  }
}