#define BLYNK_TEMPLATE_ID "TMPL4n2v69b-o"
#define BLYNK_TEMPLATE_NAME "友人"
#define BLYNK_AUTH_TOKEN "hEJN0SE_RJ78hqcyI9L7Up6J2B4AOzzi"

#include <SPI.h>
#include <WiFiNINA.h>
#include <BlynkSimpleWiFiNINA.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "4G-Gateway-E6F8";
char pass[] = "EE5NTMT4TGB";
BlynkTimer timer;

int value = 0;

void myTimerEvent() {
  Blynk.virtualWrite(V2, millis()/1000);
  analogValue = analogRead(A1);
  V_out = 3.3 * (double)analogValue / 4095;
  T_A = V_out / 0.010 - 273.15;
  Blynk.virtualWriteBinary(V1, T_A);
//Esimerkkisovellus: Jos lämpötila > 25 kirjoitetaan V1 1, muuten 0.

if(T_A >= 25) {
  Blynk.virtualWrite(V4, 1);
  Blynk.virtualWrite(V5, 0);
  Blynk.virtualWrite(V6, 0);
  Blynk.virtualWrite(V7, 0);
} 
else if (25 > T_A >= 26) {
  Blynk.virtualWrite(V5, 1);
  Blynk.virtualWrite(V4, 0);
  Blynk.virtualWrite(V6, 0);
  Blynk.virtualWrite(V7, 0);
}
else if (26 > T_A >= 27) {
  Blynk.virtualWrite(V6, 1);
  Blynk.virtualWrite(V4, 0);
  Blynk.virtualWrite(V5, 0);
  Blynk.virtualWrite(V7, 0);
}
else {
  Blynk.virtualWrite(V7, 1);
  Blynk.virtualWrite(V4, 0);
  Blynk.virtualWrite(V5, 0);
  Blynk.virtualWrite(V6, 0);
}
}

/*
BLYNK_WRITE(V0) {
  value = param.asInt();
  if (value == 1) {
   digitalWrite(5, 1);
  }
  if (value == 0) {
    digitalWrite(5, 0);
  }
}
*/

void setup() {
  Blynk.begin(auth,ssid,pass);
  timer.setInterval(1000L, myTimerEvent);
  analogReadResolution(12);
  pinMode(0, OUTPUT);
  pinMode(3, INPUT_PULLDOWN);
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  timer.run();
  switchStatus = digitalRead(3);
  digitalWrite(0, switchStatus);
}
