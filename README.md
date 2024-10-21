# Часы на ESP8266 + RTC SD1302 с синхронизацией по Network Time Protocol (NTP) :alarm_clock:

![MCU](https://img.shields.io/badge/MCU-ESP8266-476695)
![RTC](https://img.shields.io/badge/RTC-SD1302-476695)
[![Arduino IDE](https://img.shields.io/badge/Arduino_IDE-%3E=2.3.3-008184?logo=arduino)](https://www.arduino.cc/en/software)
[![Telegram](https://img.shields.io/badge/Telegram-@devSokolovsky-26A5E4?logo=telegram&logoColor=FFFFFF)](https://t.me/devSokolovsky)

## Схема подключения:

Для подключения LCD 16x2 I2C задействуем всем известную схему:

| ESP8266 | LCD 16x2 I2C |
|---------|--------------|
| GND     | GND          |
| VIN     | VCC          |
| D2      | SDA          |
| D1      | SCL          |

![изображение](https://github.com/user-attachments/assets/5472c256-737c-49ab-827d-fb657a531a46)

Для подключения RTC SD1302 следуем следующей схеме:

| ESP8266 | SD1302 |
|---------|--------|
| 3V      | VCC    |
| GND     | GND    |
| D5      | CLK    |
| D4      | DAT    |
| D0      | RST    |

## Библиотеки:

> Составляется список.

## Перед прошивкой:

### Wi-Fi:

Что бы ESP8266 мог подключится к Wi-Fi и синхронизироваться с NTP сервером, задайте значения для SSID и PASSWORD.

```c++
const char *SSID = "R2-D2";
const char *PASSWORD = "1234567890QWERTY";
```
### NTP Сервер:

Можно указать любой, для этого измените значение у NTP_SERVER:

```c++
const char* NTP_SERVER = "pool.ntp.org";
```

| Страна        | Сервер                               |
|---------------|--------------------------------------|
| :ru: Россия   | ru.pool.ntp.org или ntp1.vniiftri.ru |
| :de: Германия | de.pool.ntp.org или ntp.web.de       |
| :us: США      | us.pool.ntp.org                      |

Ещё больший список можно найти тут: [mutin-sa/Top_Public_Time_Servers.md](https://gist.github.com/mutin-sa/eea1c396b1e610a2da1e5550d94b0453)
