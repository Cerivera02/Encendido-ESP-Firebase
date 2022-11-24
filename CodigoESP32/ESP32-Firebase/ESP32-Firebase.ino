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

int habitacion1 = 2;
int habitacion2 = 3;
int habitacion3 = 4;
int habitacion4 = 5;

int ledR = 13;
int ledG = 14;
int ledB = 15;

int led1 = 0;
int led2 = 0;
int led3 = 0;
int led4 = 0;

int ledRGB = 0;
int r = 0;
int g = 0;
int b = 0;



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
  Serial.printf("Vercion de Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
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

  pinMode(habitacion1, OUTPUT);
  pinMode(habitacion2, OUTPUT);
  pinMode(habitacion3, OUTPUT);
  pinMode(habitacion4, OUTPUT);

  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);

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
    Serial.printf("Tira RGB =  %s\n", Firebase.RTDB.getInt(&fbdo, F("/rgb/rgb")) ? String(fbdo.to<int>()).c_str() : fbdo.errorReason().c_str());
    Serial.printf("Tira RGB LED R =  %s\n", Firebase.RTDB.getInt(&fbdo, F("/rgb/r")) ? String(fbdo.to<int>()).c_str() : fbdo.errorReason().c_str());
    Serial.printf("Tira RGB LED G =  %s\n", Firebase.RTDB.getInt(&fbdo, F("/rgb/g")) ? String(fbdo.to<int>()).c_str() : fbdo.errorReason().c_str());
    Serial.printf("Tira RGB LED B =  %s\n", Firebase.RTDB.getInt(&fbdo, F("/rgb/b")) ? String(fbdo.to<int>()).c_str() : fbdo.errorReason().c_str());

    delay(200);

    Firebase.RTDB.getInt(&fbdo, F("/test/LED1"));
    led1 = fbdo.to<int>();
    Firebase.RTDB.getInt(&fbdo, F("/test/LED2"));
    led2 = fbdo.to<int>();
    Firebase.RTDB.getInt(&fbdo, F("/test/LED3"));
    led3 = fbdo.to<int>();
    Firebase.RTDB.getInt(&fbdo, F("/test/LED4"));
    led4 = fbdo.to<int>();
    Firebase.RTDB.getInt(&fbdo, F("/rgb/rgb"));
    ledRGB = fbdo.to<int>();
    Firebase.RTDB.getInt(&fbdo, F("/rgb/r"));
    r = fbdo.to<int>();
    Firebase.RTDB.getInt(&fbdo, F("/rgb/g"));
    g = fbdo.to<int>();
    Firebase.RTDB.getInt(&fbdo, F("/rgb/b"));
    b = fbdo.to<int>();

    if (led1 == 1) {
      Serial.println("LED 1 Encendido");
      digitalWrite(habitacion1,HIGH);
      
    } else if (led1 == 0) {
      Serial.println("LED 1 Apagado");
      digitalWrite(habitacion1,LOW);

    }
    if (led2 == 1) {
      Serial.println("LED 2 Encendido");
      digitalWrite(habitacion2,HIGH);

    } else if (led2 == 0) {
      Serial.println("LED 2 Apagado");
      digitalWrite(habitacion2,LOW);

    }
    if (led3 == 1) {
      Serial.println("LED 3 Encendido");
      digitalWrite(habitacion3,HIGH);

    } else if (led3 == 0) {
      Serial.println("LED 3 Apagado");
      digitalWrite(habitacion3,LOW);

    }
    if (led4 == 1) {
      Serial.println("LED 4 Encendido");
      digitalWrite(habitacion4,HIGH);
      
    } else if (led4 == 0) {
      Serial.println("LED 4 Apagado");
      digitalWrite(habitacion4,LOW);

    }
    if (ledRGB == 1) {
      Serial.print("Se encendio la tira led");
      analogWrite(ledR, r);
      analogWrite(ledG, g);
      analogWrite(ledB, b);      
    } else if (ledRGB == 0 ) {
      Serial.print("Se apago la tira led");
    }

    Serial.println();

  }
}
