# airconditiot
AIR CONDItioning for the IOT

Goal
----
To control my (General air conditioner (model: ar-rcd1e) with and ESP8266)

Links
-----
https://github.com/zeroflow/ESPAircon/

http://www.instructables.com/id/ESP8266-WiFi-Controlled-Aircon-Remote/?ALLSTEPS

https://github.com/ToniA/arduino-heatpumpir

https://hackaday.com/2016/09/08/reverse-engineering-and-networking-the-ac-remote-control/

http://www.instructables.com/id/Arduino-Esp8266-Post-Data-to-Website/?ALLSTEPS

https://github.com/SmingHub/Sming

http://www.jpellerin.info/espui.html

AREST
https://openhomeautomation.net/control-a-lamp-remotely-using-the-esp8266-wifi-chip/

https://github.com/marcoschwartz/aREST_UI

http://irdb.tk/decode/

https://github.com/probonopd/arduino-infrared-pronto

http://www.hifi-remote.com/wiki/index.php?title=DecodeIR

Pinout
https://github.com/esp8266/esp8266-wiki/wiki/Pin-definition

Maximum Current (http://www.esp8266.com/wiki/doku.php?id=esp8266_gpio_pin_allocations)

When using a GPIO as output (i.e. to drive something such as an LED) it is important to note that the maximum output current is 12mA. (IMAX=12mA per Espressif datasheet) If you try and output more current than that, you run the risk of damaging the device. Since many LEDs are able to draw 20mA you should adjust your current limiting resistor to be 12mA or less. Using https://en.wikipedia.org/wiki/LED_circuit - R=(Vout-Vled)/I so (3.3V-1.8Vred) at 12mA = 125Ω min for a red LED.

