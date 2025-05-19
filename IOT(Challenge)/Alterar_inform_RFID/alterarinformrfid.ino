#include <WiFi.h>
#include <HTTPClient.h>
#include <SPI.h>
#include <MFRC522.h>

// Definição dos pinos
#define SS_PIN 21
#define RST_PIN 22
MFRC522 rfid(SS_PIN, RST_PIN);

// Configuração Wi-Fi
const char* ssid = "Pedro";
const char* password = "obrigadopedro";

// URL do seu Google Apps Script (Web App)
const char* scriptURL = "https://script.google.com/macros/s/AKfycby24qo2FJaD3fK6KPWHUyjJu1x4mIFwF_aP2yU33xmI6Z-52S-dk658PzhVcvyjkZl2QA/exec"; // Substitua com seu link do Apps Script

// Função de configuração
void setup() {
  // Inicializa a comunicação serial
  Serial.begin(115200);
  
  // Conexão Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(50);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi conectado!");

  // Inicializa SPI e RFID
  SPI.begin();
  rfid.PCD_Init();

  Serial.println("Aproxime uma tag...");
}

// Função principal de loop
void loop() {
  // Verifica se há um cartão RFID presente
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) return;

  // Obtém o UID do cartão
  String uid = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    uid += String(rfid.uid.uidByte[i], HEX);
    if (i < rfid.uid.size - 1) uid += " ";
  }
  uid.toUpperCase();

  // Informações a serem gravadas
  String modelo = "Modelo: Mottu Sport";
  String placa = "Placa: ABC-1234";
  String localizacao = "Localizacao: Entrada Principal";
  
  // Obtém o timestamp atual como um valor legível (Data e Hora)
  String timestamp = getFormattedTimestamp(); // Função que retorna data e hora formatados
  
  // Como qualquer cartão RFID agora é considerado "autorizado"
  String status = "Acesso autorizado";

  // Envia os dados para o Google Sheets
  sendToSheet(uid, modelo, placa, localizacao, status, timestamp);
  
  delay(3000);  // Espera 3 segundos para próxima leitura
}

// Função para enviar os dados para o Google Sheets
void sendToSheet(String uid, String modelo, String placa, String localizacao, String status, String timestamp) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(scriptURL);
    http.addHeader("Content-Type", "application/json");

    // Formata os dados em JSON
    String json = "{\"uid\":\"" + uid + "\",\"modelo\":\"" + modelo + "\",\"placa\":\"" + placa + "\",\"localizacao\":\"" + localizacao + "\",\"status\":\"" + status + "\",\"timestamp\":\"" + timestamp + "\"}";

    // Envia os dados para o Google Apps Script via POST
    int httpCode = http.POST(json);
    Serial.println("Resposta: " + String(httpCode));
    http.end();
  }
}

// Função para gerar um timestamp legível (Data e Hora)
String getFormattedTimestamp() {
  unsigned long currentMillis = millis();
  
  // Converte o milissegundos para segundos
  unsigned long seconds = currentMillis / 1000;
  unsigned long minutes = seconds / 60;
  unsigned long hours = minutes / 60;
  unsigned long days = hours / 24;
  
  // Formatação: YYYY-MM-DD HH:MM:SS
  String formattedDate = "2023-05-15 "; // Exemplo de data (você pode integrar um RTC aqui para uma data dinâmica)
  
  // Hora formatada (HH:MM:SS)
  String timeStr = String(hours % 24) + ":" + String(minutes % 60) + ":" + String(seconds % 60);
  
  formattedDate += timeStr;
  return formattedDate;
}