#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif

#include <Firebase_ESP_Client.h>
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>
#define WIFI_SSID "Casa642-2.4g"
#define WIFI_PASSWORD "Mcejr151631@"
#define API_KEY "AIzaSyBs3V_GcW_q6gKgvQL2WXvhZlOWqOvFKmE"
#define DATABASE_URL "https://esp32-ab718-default-rtdb.firebaseio.com" 
#define USER_EMAIL "Cerivera2002@gmail.com"
#define USER_PASSWORD "firebase"

FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;

int led1 = 0;
int led2 = 0;
int led3 = 0;
int led4 = 0;

void setup()
{

  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Conectando a Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Conectado con la IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
  config.api_key = API_KEY;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  config.database_url = DATABASE_URL;
  config.token_status_callback = tokenStatusCallback;
#if defined(ESP8266)
    fbdo.setBSSLBufferSize(2048, 2048 );
#endif
  fbdo.setResponseSize(2048);
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
  Firebase.setDoubleDigits(5);
  config.timeout.serverResponse = 10 * 1000;
}

void loop()
{
  if (Firebase.ready() && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0))
  {
    sendDataPrevMillis = millis();

    Serial.printf("LED 1 =  %s\n", Firebase.RTDB.getInt(&fbdo, F("/test/LED1")) ? String(fbdo.to<int>()).c_str() : fbdo.errorReason().c_str());
    Serial.printf("LED 2 =  %s\n", Firebase.RTDB.getInt(&fbdo, F("/test/LED2")) ? String(fbdo.to<int>()).c_str() : fbdo.errorReason().c_str());
    Serial.printf("LED 3 =  %s\n", Firebase.RTDB.getInt(&fbdo, F("/test/LED3")) ? String(fbdo.to<int>()).c_str() : fbdo.errorReason().c_str());
    Serial.printf("LED 4 =  %s\n", Firebase.RTDB.getInt(&fbdo, F("/test/LED4")) ? String(fbdo.to<int>()).c_str() : fbdo.errorReason().c_str());

    Firebase.RTDB.getInt(&fbdo, F("/test/LED1"));
    led1 = fbdo.to<int>();
    Firebase.RTDB.getInt(&fbdo, F("/test/LED2"));
    led2 = fbdo.to<int>();
    Firebase.RTDB.getInt(&fbdo, F("/test/LED3"));
    led3 = fbdo.to<int>();
    Firebase.RTDB.getInt(&fbdo, F("/test/LED4"));
    led4 = fbdo.to<int>();

    if (led1 == 1) {
      Serial.println("LED 1 Encendido");
      
    } else if (led1 == 0) {
      Serial.println("LED 1 Apagado");

    }
    if (led2 == 1) {
      Serial.println("LED 2 Encendido");
      
    } else if (led2 == 0) {
      Serial.println("LED 2 Apagado");

    }
    if (led3 == 1) {
      Serial.println("LED 3 Encendido");
      
    } else if (led3 == 0) {
      Serial.println("LED 3 Apagado");

    }
    if (led4 == 1) {
      Serial.println("LED 4 Encendido");
      
    } else if (led4 == 0) {
      Serial.println("LED 4 Apagado");

    }

    Serial.println();

  }
}
