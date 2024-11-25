#include "WiFi.h"
#include "AsyncUDP.h"

const char* ssid     = "madaniu";
const char* password = "qwertyuiop";


AsyncUDP udp;

void setup()
{
    Serial.begin(115200);

    if (!WiFi.softAP(ssid, password)) {
      log_e("Soft AP creation failed.");
      while(1);
    }

    if(udp.listen(1234)) {
        Serial.print("UDP Listening on IP: ");
        Serial.println(WiFi.softAPIP());
        udp.onPacket([](AsyncUDPPacket packet) {
            Serial.print("UDP Packet Type: ");
            Serial.print(packet.isBroadcast()?"Broadcast":packet.isMulticast()?"Multicast":"Unicast");
            Serial.print(", From: ");
            Serial.print(packet.remoteIP());
            Serial.print(":");
            Serial.print(packet.remotePort());
            Serial.print(", To: ");
            Serial.print(packet.localIP());
            Serial.print(":");
            Serial.print(packet.localPort());
            Serial.print(", Length: ");
            Serial.print(packet.length());
            Serial.print(", Data: ");
            Serial.write(packet.data(), packet.length());
            Serial.println();
            //reply to the client
            packet.printf("Got %u bytes of data", packet.length());
        });
    }
}

void loop()
{
    delay(1000);
    //Send broadcast
    udp.broadcast("Anyone here?");
}