#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>

int maxx=1023 ;
#define relay D1 // conected to waterPump relay
#define Humsensor A0  // conected to humidity sensor

// WiFi network info.
char ssid[] = "XXXXXX";    //type your wifi name here
char wifiPassword[] = "XXXXXX"; 

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "XXXXXX";
char password[] = "XXXXXX";
char clientID[] = "XXXXXX";

void setup() {
  Serial.begin(9600);
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);

      pinMode(D1 , OUTPUT);
    delay(10);
    digitalWrite(relay , HIGH);
}

void loop() {
  Cayenne.loop();
  int x = analogRead(Humsensor);
  if (x<maxx)
  maxx = x ;
  int y = map(x, 1024, maxx , 0, 100);
Cayenne.virtualWrite(1,y, "soil_moist" , "p" );
delay(5000);
}

CAYENNE_IN(2)
  {
    digitalWrite(relay , !getValue.asInt());
  }

