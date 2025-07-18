#include <Arduino.h>
#include "EspUsbHost.h"

class MyEspUsbHost : public EspUsbHost
{
  void onKeyboardKey(uint8_t ascii, uint8_t keycode, uint8_t modifier)
  {
    if (' ' <= ascii && ascii <= '~')
    {
      Serial.printf("%c", ascii);
    }
    else if (ascii == '\r')
    {
      Serial.println();
    }
  };
};

MyEspUsbHost usbHost;

void setup()
{
  Serial.begin(115200);
  delay(500);

  usbHost.begin();
}

void loop()
{
  usbHost.task();

  if (Serial.available() > 0)
  {
    String cmd = Serial.readString();
    Serial.println("We got command from serial " + cmd);

    if (cmd.indexOf("C") > -1)
    {
      usbHost.close();
      Serial.println("USB client close");
      cmd = "";
    }
    else if (cmd.indexOf("R") > -1)
    {
      usbHost.closePrecess = false;
      usbHost.isReady = true;
      Serial.println("USB client re-open");
      cmd = "";
    }

    Serial.flush();
    delay(100);
  }
}
