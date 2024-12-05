#include <Arduino.h>
#include "secrets/wifi.h"
#include "wifi_connect.h"
#include <WiFiClientSecure.h>
#include "ca_cert.h"
#include "secrets/mqtt.h"
#include <PubSubClient.h>
#include <Ticker.h>

namespace
{
    const char *ssid = WiFiSecrets::ssid;
    const char *password = WiFiSecrets::pass;
    const char *relay_topic = "esp32/relay";
    const char *soil_topic = "esp32/soil";
    const char *mode_topic = "esp32/mode";
    unsigned int publish_count = 0;
    uint16_t keepAlive = 15;
    uint16_t socketTimeout = 5;
    const int soilSensorPin = 34;
    const int relayPin = 26;
    const long interval = 100;
    bool manualControl = false;
}

WiFiClientSecure tlsClient;
PubSubClient mqttClient(tlsClient);

Ticker soilPublishTicker;
unsigned long previousMillis = 0;

void mqttCallback(char *topic, byte *payload, unsigned int length)
{
    Serial.printf("From %s:  ", topic);
    String message = "";
    for (unsigned int i = 0; i < length; i++)
    {
        message += (char)payload[i];
        Serial.print((char)payload[i]);
    }
    Serial.println();

    if (String(topic) == relay_topic)
    {
        if (message == "ON")
        {
            manualControl = true;
            digitalWrite(relayPin, LOW);
        }
        else if (message == "OFF")
        {
            manualControl = true;
            digitalWrite(relayPin, HIGH);
        }
    }

    if (String(topic) == mode_topic)
    {
        if (message == "AUTO")
        {
            manualControl = false;
            Serial.println("Switched to AUTO mode");
        }
        else if (message == "MANUAL")
        {
            manualControl = true;
            Serial.println("Switched to MANUAL mode");
        }
    }
}

void publishSoilData()
{
    int soilMoistureValue = analogRead(soilSensorPin);
    int maxSoilValue = 4095;
    float soilPercentage = (soilMoistureValue / float(maxSoilValue)) * 100;

    if (!manualControl)
    {
        if (soilPercentage > 80.0)
        {
            digitalWrite(relayPin, LOW);
            Serial.println("Relay ON (Soil Moisture > 80%)");
        }
        else
        {
            digitalWrite(relayPin, HIGH);
            Serial.println("Relay OFF (Soil Moisture <= 80%)");
        }
    }

    String moisture = String(soilPercentage, 2);
    mqttClient.publish(soil_topic, moisture.c_str(), false);
    Serial.printf("Published Soil Moisture: %s%%\n", moisture.c_str());
}

void mqttReconnect()
{
    while (!mqttClient.connected())
    {
        Serial.println("Attempting MQTT connection...");
        String client_id = "esp32-client-";
        client_id += String(WiFi.macAddress());
        if (mqttClient.connect(client_id.c_str(), MQTT::username, MQTT::password))
        {
            Serial.print(client_id);
            Serial.println(" connected");
            mqttClient.subscribe(relay_topic);
            mqttClient.subscribe(mode_topic);
        }
        else
        {
            Serial.print("MQTT connect failed, rc=");
            Serial.print(mqttClient.state());
            Serial.println(" try again in 1 second");
            delay(1000);
        }
    }
}

void setup()
{
    Serial.begin(115200);
    delay(10);

    pinMode(soilSensorPin, INPUT);
    pinMode(relayPin, OUTPUT);
    digitalWrite(relayPin, HIGH);

    setup_wifi(ssid, password);
    tlsClient.setCACert(ca_cert);

    mqttClient.setCallback(mqttCallback);
    mqttClient.setServer(MQTT::broker, MQTT::port);

    soilPublishTicker.attach_ms(interval, publishSoilData);
}

void loop()
{
    if (!mqttClient.connected())
    {
        mqttReconnect();
    }
    mqttClient.loop();
}
