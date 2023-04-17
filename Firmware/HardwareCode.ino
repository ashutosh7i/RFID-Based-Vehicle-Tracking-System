#include <SPI.h>
#include <MFRC522.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <U8g2lib.h>


#define SS_PIN  5   // ESP32 pin GPIO5
#define RST_PIN 27  // ESP32 pin GPIO27
#define OLED_SDA 21
#define OLED_SCL 22

#define dataSent 25 //green led 
#define cardTapped 26 //red led
#define wifiConnectionLed 27  //connection
#define Buzzer 33

MFRC522 rfid(SS_PIN, RST_PIN);

// Replace with your network credentials
const char* ssid = "SomeWifi";
const char* password = "244466666";

// API endpoint
const char* apiEndpoint = "http://165.232.180.53/card";

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R2, OLED_SCL, OLED_SDA, U8X8_PIN_NONE);

void setup() {
  Serial.begin(9600);

  pinMode(dataSent, OUTPUT);
  pinMode(cardTapped, OUTPUT);
  pinMode(wifiConnectionLed, OUTPUT);
  pinMode(Buzzer, OUTPUT);

  u8g2.begin();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  SPI.begin(); // init SPI bus
  rfid.PCD_Init(); // init MFRC522

  // Connect to Wi-Fi network
  WiFi.begin(ssid, password);
  
  Serial.print("Connecting to Wi-Fi");
  u8g2.firstPage();
  do {
  u8g2.setCursor(0, 10);
  u8g2.print("Connecting to Wi-Fi");
  } while (u8g2.nextPage());

  while (WiFi.status() != WL_CONNECTED) {
  digitalWrite(wifiConnectionLed, HIGH);
  digitalWrite(Buzzer, HIGH);
    delay(500);
    Serial.print(".");
  digitalWrite(wifiConnectionLed, LOW);
  digitalWrite(Buzzer, LOW);
  delay(500);
  }
  Serial.println("");
  
    Serial.print("Connected to Wi-Fi");
  u8g2.firstPage();
  do {
  u8g2.setCursor(0, 10);
  u8g2.print("Connected to Wi-Fi");
  } while (u8g2.nextPage());
  
  digitalWrite(wifiConnectionLed, HIGH);
    digitalWrite(Buzzer, LOW);
    delay(500);
}

void loop() {
  u8g2.firstPage();
  do {
  u8g2.setCursor(0, 30);
  u8g2.println("-> TAP RFID CARD");
  } while (u8g2.nextPage());
  
  if (rfid.PICC_IsNewCardPresent()) { // new tag is available
    if (rfid.PICC_ReadCardSerial()) { // NUID has been read
      MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
      
      Serial.println("Card Type: ");
      Serial.println(rfid.PICC_GetTypeName(piccType));
      digitalWrite(cardTapped, HIGH);
      digitalWrite(Buzzer, HIGH);delay(100);digitalWrite(Buzzer, LOW);

      // Convert UID to a string
      String uidStr = "";
      for (int i = 0; i < rfid.uid.size; i++) {
        uidStr += String(rfid.uid.uidByte[i], HEX);
      }
      Serial.println("Card data= "+uidStr);

      //showing in oled display
  u8g2.firstPage();
  do {
  u8g2.setCursor(0, 10);
  u8g2.println("-< CARD Detected >-");
  u8g2.setCursor(0, 20);
  u8g2.println("Card Type: ");
  u8g2.setCursor(0, 30);
  u8g2.print("-> ");
  u8g2.println(rfid.PICC_GetTypeName(piccType));
  u8g2.setCursor(0, 40);
  u8g2.println("Card Data: ");
  u8g2.setCursor(0, 50);
  u8g2.print("-> ");
  u8g2.println(uidStr);
  u8g2.setCursor(0, 60);
  } while (u8g2.nextPage());
  delay(1000);
  
      // Build JSON payload
      String payload = "{\"uid\": \"" + uidStr + "\"}";

      // Send POST request to API endpoint
      HTTPClient http;
      http.begin(apiEndpoint);
      http.addHeader("Content-Type", "application/json");
      int httpResponseCode = http.POST(payload);
      http.end();

      // Check for successful request
      if (httpResponseCode == 200) {
        Serial.println("Data sent to Backend using API");
        Serial.println("---------------------------------------------------------------------");
        digitalWrite(dataSent, HIGH);
        digitalWrite(Buzzer, HIGH);delay(150);digitalWrite(Buzzer, LOW);

         u8g2.firstPage();
  do {
  u8g2.setCursor(0, 30);
  u8g2.println("Data sent to Backend");
  u8g2.setCursor(0, 40);
  u8g2.println("SUCCESSFULLY");
  } while (u8g2.nextPage());
        
        delay(2000);
      } else {
        Serial.print("Error sending data: ");
        digitalWrite(Buzzer, HIGH);delay(50);digitalWrite(Buzzer, LOW);
        digitalWrite(Buzzer, HIGH);delay(50);digitalWrite(Buzzer, LOW);
        digitalWrite(Buzzer, HIGH);delay(50);digitalWrite(Buzzer, LOW);
        digitalWrite(Buzzer, HIGH);delay(50);digitalWrite(Buzzer, LOW);
        Serial.println(httpResponseCode);
                 u8g2.firstPage();
  do {
  u8g2.setCursor(0, 10);
  u8g2.println("Error sending data: ");
    u8g2.println(httpResponseCode);
    delay(2000);
  } while (u8g2.nextPage());
      }

      digitalWrite(cardTapped, LOW);
      digitalWrite(dataSent, LOW);
      rfid.PICC_HaltA(); // halt PICC
      rfid.PCD_StopCrypto1(); // stop encryption on PCD
    }
  }
}
