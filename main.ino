#include <WiFi.h>
#include <Wire.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <AceButton.h>
#include "pitches.h"
#include <Tone32.h>
using namespace ace_button;

#define BLYNK_TEMPLATE_ID "TMPL4AQ8CUTY"
#define BLYNK_DEVICE_NAME "Quickstart Device"
#define BLYNK_AUTH_TOKEN "mMcQdt-jCPl0wnlUtc9muTAS8s9AOB4e"
#define BLYNK_PRINT Serial
#define BUZZER_PIN 32 // ESP32 GIOP21 pin connected to Buzzer's pin

#define ssid "OnePlus Nord2 5G"
#define pass "12345678"
#define lightbulb 13
#define trigPin 25
#define echoPin 26

ButtonConfig config1;
AceButton button1(&config1);
BlynkTimer timer;bool fetch_blynk_state = true;
String myString;

bool toggleState_1 = LOW;
int wifiFlag = 0;
long duration;
float distance;

void handleEvent1(AceButton *, uint8_t, uint8_t);
void printDistance(int);

BLYNK_WRITE(V1)
{
    toggleState_1 = param.asInt();
    digitalWrite(lightbulb, !toggleState_1);
    Serial.println(toggleState_1);
}

void Ultrasonic()
{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;
    Serial.println(distance);
    printDistance(distance);
}

void checkBlynkStatus()
{
    bool isconnected = Blynk.connected();
    if (isconnected == false)
    {
        wifiFlag = 1;
        Serial.println("Blynk Not Connected");
    }
    if (isconnected == true)
    {
        wifiFlag = 0;
        if (!fetch_blynk_state)
        {
            Blynk.virtualWrite(V1, toggleState_1);
        }
        Serial.println("Blynk Connected");
    }
}

BLYNK_CONNECTED()
{ // Request the latest state from the server
    if (fetch_blynk_state)
    {
        Blynk.syncVirtual(V1);
    }
}

void setup()
{
    Serial.begin(115200);
    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
    pinMode(lightbulb, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(trigPin, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    digitalWrite(lightbulb, !toggleState_1);
    config1.setEventHandler(button1Handler);
    WiFi.begin(ssid, pass);
    timer.setInterval(2000L, checkBlynkStatus); // check if Blynk server is connected every 2 seconds
                                                //  Blynk.config(auth);
    delay(1000);
    if (!fetch_blynk_state)
    {
        Blynk.virtualWrite(V1, toggleState_1);
    }
}

void loop()
{
    Blynk.run();
    timer.run();
    Ultrasonic();
    button1.check();
}

void button1Handler(AceButton *button, uint8_t eventType, uint8_t buttonState)
{
    Serial.println("EVENT1");

    switch (eventType)
    {
    case AceButton::kEventReleased:
        Serial.println("kEventReleased");
        digitalWrite(lightbulb, toggleState_1);
        toggleState_1 = !toggleState_1;
        Blynk.virtualWrite(V1, toggleState_1);
        break;
    }
}

void printDistance(float Distance)
{
    if (Distance >= 900)
    {
        Blynk.virtualWrite(V2, "Too Far\n");
        Blynk.virtualWrite(V3, String(Distance / 100) + " m");
        Serial.println("Too Far");
        digitalWrite(BUZZER_PIN, LOW);
    }
    else if (Distance < 900 and Distance >= 300)
    {
        Blynk.virtualWrite(V2, "Far\n");
        Blynk.virtualWrite(V3, String(Distance / 100) + " m");
        Serial.println("Far");
        digitalWrite(BUZZER_PIN, LOW);
    }
    else if (Distance < 300 and Distance >= 50)
    {
        Blynk.virtualWrite(V2, "Close\n");
        Blynk.virtualWrite(V3, String(Distance / 100) + " m");
        Serial.println("Close");
        digitalWrite(BUZZER_PIN, LOW);
    }
    else
    {
        Blynk.virtualWrite(V2, "Too Close\n");
        Blynk.virtualWrite(V3, String(Distance / 100) + " m");
        Serial.println("Close");
        Serial.println("Buzzer");
        digitalWrite(BUZZER_PIN, HIGH);
    }
}
