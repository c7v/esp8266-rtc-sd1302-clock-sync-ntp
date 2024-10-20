#include <Wire.h>
#include <RtcDS1302.h>
#include <ESP8266WiFi.h>
#include <LiquidCrystal_I2C.h>

const char *SSID = "{Название Wi-Fi}";
const char *PASSWORD = "{Пароль от Wi-Fi}";

// Подключение модуля DS1302 к пинам ESP8266.
const int DAT_PIN = 2; // (DAT/IO)
const int CLK_PIN = 14; // (CLK/SCLK)
const int RST_PIN = 16; // (RST/CE)

// Настройка I2C.
const uint8_t LCD_COLS = 16;
const uint8_t LCD_ROWS = 2;
const uint8_t LCD_ASSRES = 0x27;

// NTP Сервер для запроса времени.
const char* NTP_SERVER = "pool.ntp.org";

// Временная зона в секундах.
const long TIMEZONE = 0;

// Сдвиг времени в секундах.
const int OFFSET_SEC = 0;

ThreeWire myWire(DAT_PIN, CLK_PIN, RST_PIN);
RtcDS1302<ThreeWire> Rtc(myWire);

LiquidCrystal_I2C LCD(LCD_ASSRES, LCD_COLS, LCD_ROWS);

void setup() {
  Serial.begin(115200);
  // Иницируем модуль RTC.
  LCD.init();
  LCD.clear();
  LCD.backlight();

  // Иницируем модуль RTC.
  Rtc.Begin();

  // Инициируем подключение к Wi-Fi.
  initWiFi();

  // Указываем настройки временной зоны, смещения и NTP сервер и синхронизируем локальное время ESP8266.
  configTime(TIMEZONE, OFFSET_SEC, NTP_SERVER);

  // Настраиваем время RTC DS1302 модуле с локального времени ESP8266.
  settingsTime();

  // Прирываем соединение и отключаемся от Wi-Fi.
  disconnectWiFi();
}

/**
* Подключение к Wi-Fi.
*/
void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASSWORD);

  while(WiFi.status() != WL_CONNECTED) {
    delay (500);
    Serial.print(".");
  }
  Serial.println(".");
  Serial.println("Подключенио к Wi-Fi");
}

/**
* Отключение от Wi-Fi.
*/
void disconnectWiFi() {
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}

/**
* Настраиваем время на модуле RTC DS1302 модуле с локального времени ESP8266.
*/
void settingsTime() {
  struct tm timeinfo;
  getLocalTime(&timeinfo);

  int dayOfMonth = timeinfo.tm_mday;
  int month = timeinfo.tm_mon + 1;
  int year = timeinfo.tm_year + 1900;
  int hour = timeinfo.tm_hour;
  int minute = timeinfo.tm_min;
  int second = timeinfo.tm_sec;

  Rtc.SetDateTime(RtcDateTime(year, month, dayOfMonth, hour, minute, second));
}

void loop() {
  RtcDateTime now = Rtc.GetDateTime();
  if (now.Minute() == 30 && now.Second() == 0) {
      LCD.clear();         
      LCD.backlight();
      LCD.setCursor(0, 0);
      LCD.print("Synchronization:");
      LCD.setCursor(2, 1);
      LCD.print(NTP_SERVER);

      // Инициируем подключение к Wi-Fi.
      initWiFi();

      // Указываем настройки временной зоны, смещения и NTP сервер и синхронизируем локальное время ESP8266.
      configTime(TIMEZONE, OFFSET_SEC, NTP_SERVER);

      // Настраиваем время RTC DS1302 модуле с локального времени ESP8266.
      settingsTime();

      // Прирываем соединение и отключаемся от Wi-Fi.
      disconnectWiFi();
      LCD.clear();         
      LCD.backlight();
  } else {
    RtcDateTime now = Rtc.GetDateTime();
    
    char datestring[20];
    char timestring[20];

    snprintf_P(datestring, 
            countof(datestring),
            PSTR("%02u.%02u.%04u"),
            now.Day(),
            now.Month(),
            now.Year());

    snprintf_P(timestring, 
            countof(timestring),
            PSTR("%02u:%02u:%02u"),
            now.Hour(),
            now.Minute(),
            now.Second());

    LCD.setCursor(3,0);
    LCD.print(datestring);
    LCD.setCursor(4,1);
    LCD.print(timestring);
    LCD.setCursor(4,1);
  }

  delay(1000);
}
