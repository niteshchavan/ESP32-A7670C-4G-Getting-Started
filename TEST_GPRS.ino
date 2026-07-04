#define TINY_GSM_MODEM_SIM7600
#define TINY_GSM_RX_BUFFER 1024

#include <TinyGsmClient.h>

HardwareSerial SerialAT(2);

TinyGsm modem(SerialAT);

void setup() {
  Serial.begin(115200);

  Serial.println("Starting modem...");

  SerialAT.begin(115200, SERIAL_8N1, 16, 17);

  delay(8000);

  modem.restart();

  Serial.println("Modem Info:");
  Serial.println(modem.getModemInfo());

  if (!modem.waitForNetwork()) {
    Serial.println("Network failed");
    return;
  }

  Serial.println("Network connected");

  if (!modem.gprsConnect("airtelgprs.com", "", "")) {
    Serial.println("GPRS Failed");
    return;
  }

  Serial.println("GPRS Connected");

  Serial.print("Operator : ");
  Serial.println(modem.getOperator());

  Serial.print("Signal : ");
  Serial.println(modem.getSignalQuality());

  Serial.print("Local IP : ");
  Serial.println(modem.localIP());
}

void loop() {
}