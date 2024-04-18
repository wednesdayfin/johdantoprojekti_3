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
double analogValue = 0;
double V_out = 0;
double T_A = 0;
double fahr = 0;

void myTimerEvent() {
  Blynk.virtualWrite(V2, millis()/1000);
  analogValue = analogRead(A1);
  V_out = 3.3 * (double)analogValue / 4095;
  T_A = V_out / 0.010 - 273.15;
  fahr = 1.8 * T_A + 32;
  Blynk.virtualWrite(V1, T_A);
  Blynk.virtualWrite(V4, fahr);
}

BLYNK_WRITE(V1) {
  value = param.asInt();
  if (value == 0) {
    digitalWrite(0, 0);
    digitalWrite(1, 0);
    digitalWrite(2, 0);      
  }
  if (value == 1) {
    digitalWrite(0, 1);
    digitalWrite(1, 1);
    digitalWrite(2, 1);
    
  }
}

void setup() {
  Blynk.begin(auth,ssid,pass);
  timer.setInterval(1000L, myTimerEvent);
  analogReadResolution(12);
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
}

void loop() {
  Blynk.run();
  timer.run();
  if (value == 1) {
    digitalWrite(0, 1);
    digitalWrite(1, 1);
    digitalWrite(2, 1);      
  }
  else
  {
    if (T_A <= 25) {
      digitalWrite(0, 0);
      digitalWrite(1, 0);
      digitalWrite(2, 0);
      }
      else if (25 < T_A && T_A <= 26) {
      digitalWrite(0, 1);
      digitalWrite(1, 0);
      digitalWrite(2, 0);
      }
      else if (26 < T_A && T_A <= 27) {
      digitalWrite(0, 1);
      digitalWrite(1, 1);
      digitalWrite(2, 0);
      }
      else {
      digitalWrite(0, 1);
      digitalWrite(1, 1);
      digitalWrite(2, 1);
    }
  }
}
