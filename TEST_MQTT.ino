#define MQTT_MAX_PACKET_SIZE 512
#define TINY_GSM_MODEM_SIM7600
#define TINY_GSM_RX_BUFFER 1024

#include <TinyGsmClient.h>
#include <PubSubClient.h>

#define SIM_RX 16
#define SIM_TX 17

const char apn[] = "airtelgprs.com";

// MQTT Broker
const char* mqttServer = "mqtt.pitambaridigitalcare.com";
const int mqttPort = 1883;
const char* mqttUser = "nitesh";
const char* mqttPass = "root@123";

const char* topicTest = "esp32/test";

HardwareSerial modemSerial(2);

TinyGsm modem(modemSerial);
TinyGsmClient gsmClient(modem);
PubSubClient mqtt(gsmClient);

unsigned long lastPublish = 0;
unsigned long lastReconnect = 0;

void setup() {

  Serial.begin(115200);

  Serial.println("Starting Modem...");

  modemSerial.begin(115200, SERIAL_8N1, SIM_RX, SIM_TX);

  delay(8000);

  modem.restart();

  Serial.println(modem.getModemInfo());

  Serial.println("Waiting for Network...");

  if (!modem.waitForNetwork()) {
    Serial.println("Network Failed");
    while (1);
  }

  Serial.println("Network Connected");

  Serial.println("Connecting GPRS...");

  if (!modem.gprsConnect(apn, "", "")) {
    Serial.println("GPRS Failed");
    while (1);
  }

  Serial.println("GPRS Connected");

  Serial.print("Operator : ");
  Serial.println(modem.getOperator());

  Serial.print("Signal : ");
  Serial.println(modem.getSignalQuality());

  Serial.print("IP : ");
  Serial.println(modem.localIP());

  mqtt.setServer(mqttServer, mqttPort);
}

void mqttReconnect()
{
  if (mqtt.connected())
    return;

  if (millis() - lastReconnect < 5000)
    return;

  lastReconnect = millis();

  Serial.print("Connecting MQTT... ");

  String clientId = "ESP32-";
  clientId += String((uint32_t)ESP.getEfuseMac(), HEX);

  if (mqtt.connect(clientId.c_str(), mqttUser, mqttPass))
  {
    Serial.println("SUCCESS");

    mqtt.subscribe(topicTest);

    mqtt.publish(topicTest, "ESP32 + A7670C MQTT Connected", true);
  }
  else
  {
    Serial.print("FAILED  rc=");
    Serial.println(mqtt.state());
  }
}

void callback(char* topic, byte* payload, unsigned int length)
{
  Serial.print("\nMessage Received [");
  Serial.print(topic);
  Serial.print("] : ");

  for (unsigned int i = 0; i < length; i++)
    Serial.print((char)payload[i]);

  Serial.println();
}

String getNetworkDateTime()
{
    int year, month, day, hour, minute, second;
    float timezone;

    if (modem.getNetworkTime(&year, &month, &day,
                             &hour, &minute, &second,
                             &timezone))
    {
        char buf[32];
        snprintf(buf, sizeof(buf),
                 "%04d-%02d-%02d %02d:%02d:%02d",
                 year, month, day,
                 hour, minute, second);

        return String(buf);
    }

    return "Unknown";
}

void loop()
{
  mqttReconnect();

  mqtt.loop();

  if (mqtt.connected())
  {
    if (millis() - lastPublish > 5000)
    {
      lastPublish = millis();

      String payload = "{";
      payload += "\"imei\":\"";
      payload += modem.getIMEI();
      payload += "\",";
      payload += "\"datetime\":\"";
      payload += getNetworkDateTime();
      payload += "\",";
      payload += "\"signal\":";
      payload += modem.getSignalQuality();
      payload += ",";
      payload += "\"operator\":\"";
      payload += modem.getOperator();
      payload += "\",";
      IPAddress ip = modem.localIP();
      payload += "\"ip\":\"";
      payload += ip.toString();
      payload += "\"";
      payload += "}";

      Serial.println("--------------------------------");
      Serial.println("Publishing:");
      Serial.println(payload);

      if (mqtt.publish(topicTest, payload.c_str(), true))
      {
        Serial.println("Publish OK");
      }
      else
      {
        Serial.print("Publish Failed. MQTT State=");
        Serial.println(mqtt.state());
      }
    }
  }
}