
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>

 bool wifi_State = false;
 int32_t frequency = 100;
const int ledPin1 = 16;
const int ledPin2 = 17;
const int ledPin3 = 4;

// задаём свойства ШИМ-сигнала
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;



// Replace with your network credentials
const char* ssid = "MGTS_GPON_C771";
const char* password = "qdxSHgHm";

// www.howsmyssl.com root certificate authority, to verify the server
// change it to your server root CA
const char* rootCACertificate= 
          "-----BEGIN CERTIFICATE-----\n" 
          "MIIDdzCCAl+gAwIBAgIEAgAAuTANBgkqhkiG9w0BAQUFADBaMQswCQYDVQQGEwJJ\n" 
          "RTESMBAGA1UEChMJQmFsdGltb3JlMRMwEQYDVQQLEwpDeWJlclRydXN0MSIwIAYD\n" 
          "VQQDExlCYWx0aW1vcmUgQ3liZXJUcnVzdCBSb290MB4XDTAwMDUxMjE4NDYwMFoX\n" 
          "DTI1MDUxMjIzNTkwMFowWjELMAkGA1UEBhMCSUUxEjAQBgNVBAoTCUJhbHRpbW9y\n" 
          "ZTETMBEGA1UECxMKQ3liZXJUcnVzdDEiMCAGA1UEAxMZQmFsdGltb3JlIEN5YmVy\n" 
          "VHJ1c3QgUm9vdDCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAKMEuyKr\n" 
          "mD1X6CZymrV51Cni4eiVgLGw41uOKymaZN+hXe2wCQVt2yguzmKiYv60iNoS6zjr\n" 
          "IZ3AQSsBUnuId9Mcj8e6uYi1agnnc+gRQKfRzMpijS3ljwumUNKoUMMo6vWrJYeK\n" 
          "mpYcqWe4PwzV9/lSEy/CG9VwcPCPwBLKBsua4dnKM3p31vjsufFoREJIE9LAwqSu\n" 
          "XmD+tqYF/LTdB1kC1FkYmGP1pWPgkAx9XbIGevOF6uvUA65ehD5f/xXtabz5OTZy\n" 
          "dc93Uk3zyZAsuT3lySNTPx8kmCFcB5kpvcY67Oduhjprl3RjM71oGDHweI12v/ye\n" 
          "jl0qhqdNkNwnGjkCAwEAAaNFMEMwHQYDVR0OBBYEFOWdWTCCR1jMrPoIVDaGezq1\n" 
          "BE3wMBIGA1UdEwEB/wQIMAYBAf8CAQMwDgYDVR0PAQH/BAQDAgEGMA0GCSqGSIb3\n" 
          "DQEBBQUAA4IBAQCFDF2O5G9RaEIFoN27TyclhAO992T9Ldcw46QQF+vaKSm2eT92\n" 
          "9hkTI7gQCvlYpNRhcL0EYWoSihfVCr3FvDB81ukMJY2GQE/szKN+OMY3EU/t3Wgx\n" 
          "jkzSswF07r51XgdIGn9w/xZchMB5hbgF/X++ZRGjD8ACtPhSNzkE1akxehi/oCr0\n" 
          "Epn3o0WC4zxe9Z2etciefC7IpJ5OCBRLbf1wbWsaY71k5h+3zvDyny67G7fyUIhz\n" 
          "ksLi4xaNmjICq44Y3ekQEe5+NauQrz4wlHrQMz2nZQ/1/I6eYs9HRCwBXbsdtTLS\n" 
          "R9I4LtD+gdwyah617jzV/OeBHRnDJELqYzmp\n" 
          "-----END CERTIFICATE-----\n" ;












void setup() {
   ledcSetup(ledChannel, freq, resolution);
  
  // привязываем канал к портам светодиодов


  
  pinMode(5, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  Serial.begin(115200);
  Serial.println();
  // Initialize Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    digitalWrite(ledPin3,HIGH);
    delay(100);
    digitalWrite(ledPin3,LOW);
    delay(100);
    digitalWrite(ledPin3,HIGH);
    delay(100);
    digitalWrite(ledPin3,LOW);
    delay(100);
    digitalWrite(ledPin3,HIGH);
    delay(100);
    digitalWrite(ledPin3,LOW);
    delay(100);
     digitalWrite(ledPin3,HIGH);
    delay(100);
    digitalWrite(ledPin3,LOW);
    delay(100);
     digitalWrite(ledPin3,HIGH);
    delay(100);
    digitalWrite(ledPin3,LOW);
    delay(100);
   
   
   



  }
  wifi_State = true;
  Serial.println(WiFi.localIP());
}

void loop() {

  
  if (WiFi.status() != WL_CONNECTED && wifi_State == false){
    Serial.print(millis());
    Serial.println("Reconnecting to WiFi...");
    WiFi.disconnect();
       digitalWrite(ledPin3,HIGH);
    delay(100);
    digitalWrite(ledPin3,LOW);
    delay(100);
    digitalWrite(ledPin3,HIGH);
    delay(100);
    digitalWrite(ledPin3,LOW);
    delay(100);
    digitalWrite(ledPin3,HIGH);
    delay(100);
    digitalWrite(ledPin3,LOW);
    delay(100);
     digitalWrite(ledPin3,HIGH);
    delay(100);
    digitalWrite(ledPin3,LOW);
    delay(100);
     digitalWrite(ledPin3,HIGH);
    delay(100);
    digitalWrite(ledPin3,LOW);
    delay(100);
    WiFi.reconnect();
    wifi_State = true;

  }
  if ((WiFi.status() == WL_CONNECTED) && (wifi_State =! true)){
      wifi_State = true;

  }
  WiFiClientSecure *client = new WiFiClientSecure;
  if(client) {
    // set secure client with certificate
    client->setCACert(rootCACertificate);
    //create an HTTPClient instance
    HTTPClient https;

    //Initializing an HTTPS communication using the secure client
    Serial.print("[HTTPS] begin...\n");
    if (https.begin(*client, "https://mains-h5w5.onrender.com/api/house/1")) {  // HTTPS
      Serial.print("[HTTPS] GET...\n");
      // start connection and send HTTP header
      int httpCode = https.GET();
      // httpCode will be negative on error
      if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
       Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
      // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
            
           String payload = https.getString();
          
           JSONVar myObject = JSON.parse(payload);
                Serial.println(myObject);
            Serial.println(myObject[0]);
            Serial.println(myObject[0]["State"]);
            int32_t x = myObject[0]["State"];
      
              frequency = myObject[0]["frequency"];
               Serial.println(frequency);
            
     Serial.println(x);
            digitalWrite(5,x);

           
        }
      }
      else {
        Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
      }
      https.end();
    }
  }
  else {
    Serial.printf("[HTTPS] Unable to connect\n");
  }
  Serial.println();
  Serial.println("Waiting 2min before the next round...");
  delay(frequency);
}
