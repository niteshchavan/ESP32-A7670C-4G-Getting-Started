#include <HardwareSerial.h>

HardwareSerial modem(2);

String cmd = "";

void sendAT(const char *cmd)
{
  Serial.print("\n>> ");
  Serial.println(cmd);

  modem.println(cmd);

  unsigned long start = millis();

  while (millis() - start < 2000)
  {
    while (modem.available())
      Serial.write(modem.read());
  }
}

void setup()
{
  Serial.begin(115200);
  modem.begin(115200, SERIAL_8N1, 16, 17);

  Serial.println("Waiting for modem...");
  delay(8000);

  sendAT("ATE0");
  sendAT("ATI");

  Serial.println("\n==========================");
  Serial.println("Interactive AT Terminal");
  Serial.println("==========================");
}

void loop()
{
  while (Serial.available())
  {
    char c = Serial.read();

    if (c == '\r' || c == '\n')
    {
      if (cmd.length())
      {
        modem.println(cmd);
        cmd = "";
      }
    }
    else
    {
      cmd += c;
    }
  }

  while (modem.available())
  {
    Serial.write(modem.read());
  }
}
