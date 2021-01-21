#include "ESP8266WiFi.h"
#include <Wire.h>
#include <MFRC522.h>        //library responsible for communicating with the module RFID-RC522
#include <SPI.h>      //library responsible for communicating of SPI bus
#define SS_PIN    21
#define RST_PIN   22

// RFID
MFRC522 mfrc522(SS_PIN, RST_PIN); // Defined pins to module RC522

// WiFi parameters to be configured
const char* ssid = "Vodafone :-)";
const char* password = "casa1234";

// HTTP Request
WiFiClient client;
const int    HTTP_PORT   = 5000;
const String HTTP_METHOD = "GET"; // or "POST"
const char   HOST_NAME[] = "192.168.1.220"; // hostname of web server:
const String PATH_NAME   = "";

void leituraDados();

void make_request(String card){
  if(client.connect(HOST_NAME, HTTP_PORT)) {
    Serial.println("Connected to server");
  } else {
    Serial.println("connection failed");
  }

  String url = "/card";
  url += "?value=";
  client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + HOST_NAME + "\r\n" + "Connection: close\r\n\r\n");

  // send HTTP request header
  client.println(HTTP_METHOD + " " + PATH_NAME + " HTTP/1.1");
  client.println("Host: " + String(HOST_NAME));
  client.println("Connection: close");
  client.println(); // end HTTP request header

}


void setup(void)
{ 
  /////////////////////////
  // RFID
  SPI.begin(); //INICIALIZA O BARRAMENTO SPI
  mfrc522.PCD_Init(); //INICIALIZA MFRC522

  /////////////////////////
  // Wifi Module Configuration

  // Connect to WiFi
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  // while wifi not connected yet, print '.' then after it connected, get out of the loop
  while (WiFi.status() != WL_CONNECTED) {
     delay(1000);
     Serial.print(".");
  }
  
  // Print the IP address
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());
  Serial.println();
}


void loop() {
  
   // Aguarda a aproximacao do cartao
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  
  // Seleciona um dos cartoes
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }

  /***INICIO BLOCO DE CÓDIGO RESPONSÁVEL POR GERAR A TAG RFID LIDA***/
  String strID = "";
  for (byte i = 0; i < 4; i++) {
    strID +=
    (mfrc522.uid.uidByte[i] < 0x10 ? "0" : "") +
    String(mfrc522.uid.uidByte[i], HEX) +
    (i!=3 ? ":" : "");
  }
  strID.toUpperCase();
  /***FIM DO BLOCO DE CÓDIGO RESPONSÁVEL POR GERAR A TAG RFID LIDA***/
 
  Serial.print("Identificador (UID) da tag: "); //IMPRIME O TEXTO NA SERIAL
  Serial.println(strID); //IPRIME NA SERIAL O UID DA TAG RFID
  make_request(strID);

  mfrc522.PICC_HaltA(); //PARADA DA LEITURA DO CARTÃO
  mfrc522.PCD_StopCrypto1(); //PARADA DA CRIPTOGRAFIA NO PCD
 
}
