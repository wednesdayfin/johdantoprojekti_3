#define BLYNK_TEMPLATE_ID "TMPL40hswbSc8"

#define BLYNK_TEMPLATE_NAME "Ardu"

#define BLYNK_AUTH_TOKEN "VfEhpPEoKc2fHISKe2Chfb1de9TkBTZj"

 

#include <SPI.h>

#include <WiFiNINA.h>

#include <BlynkSimpleWiFiNINA.h>

 

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "verkko";

char pass[] = "salasana";

 

BlynkTimer timer;

double V_out, T_A, fahr;

 

int analogValue;

int controlState = 0;  

 

BLYNK_WRITE(V0) {

  controlState = param.asInt();

}

 

void updateTemperature() {

  analogValue = analogRead(A1);

  V_out = 3.3 * (double)analogValue / 4095;

  T_A = V_out / 0.010 - 273.15;

  fahr = 1.8 * T_A + 32;  

 

  Blynk.virtualWrite(V1, T_A);

  Blynk.virtualWrite(V3, fahr);

}

 

void controlOutputs() {

  if (controlState == 1) {

   

    digitalWrite(0, 1);

    digitalWrite(1, 1);

    digitalWrite(2, 1);

  } else if (controlState == 0) {

   

    if (T_A < 25) {

      digitalWrite(0, 0);

      digitalWrite(1, 0);

      digitalWrite(2, 0);

    } else if (T_A >= 25 && T_A < 26) {

      digitalWrite(0, 1);

      digitalWrite(1, 0);

      digitalWrite(2, 0);

    } else if (T_A >= 26 && T_A < 70) {

      digitalWrite(2, 0);

      digitalWrite(1, 1);

      digitalWrite(0, 1);

    } else {

      digitalWrite(1, 1);

      digitalWrite(0, 1);

      digitalWrite(2, 1);

    }

  }

}

 

void timerEvent() {

  Blynk.virtualWrite(V2, millis() / 1000);

  updateTemperature();

  controlOutputs();

}

 

void setup() {

  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);

  timer.setInterval(1000L, timerEvent);

  analogReadResolution(12);

  pinMode(0, OUTPUT);

  pinMode(1, OUTPUT);

  pinMode(2, OUTPUT);

}

 

void loop() {

  Blynk.run();

  timer.run();

}
