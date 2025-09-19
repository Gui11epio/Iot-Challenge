#include <WiFi.h>
#include <HTTPClient.h>
#include <SPI.h>
#include <MFRC522.h>

// Definição dos pinos RFID
#define SS_PIN 21
#define RST_PIN 22
MFRC522 rfid(SS_PIN, RST_PIN);

// LEDs para indicação de erro
#define LED_302  2   // LED para erro 302
#define LED_ERRO 4   // LED para outros erros

// Configuração Wi-Fi
const char* ssid = "Pedro";
const char* password = "obrigadopedro";

// URL do seu Google Apps Script (Web App)
const char* scriptURL = "https://script.google.com/macros/s/AKfycbxwcDphs8s4ZEZg72Wbke6IX3wD4M0ilnqzBuBqWuPIR4Wap7EkL8Mfn67yq4ladbAu/exec";

// Função de configuração
void setup() {
  Serial.begin(115200);
  
  // Configura LEDs como saída
  pinMode(LED_302, OUTPUT);
  pinMode(LED_ERRO, OUTPUT);
  digitalWrite(LED_302, LOW);
  digitalWrite(LED_ERRO, LOW);

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
  String modelo = "Modelo: Mottu E";
  String placa = "Placa: hoh-5561";
  String localizacao = "Localizacao: Patio de saida";
  
  // Obtém o timestamp atual
  String timestamp = getFormattedTimestamp();
  
  // Status do acesso
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

    // Envia os dados via POST
    int httpCode = http.POST(json);
    Serial.println("Resposta: " + String(httpCode));

    // Piscar LEDs em caso de erro
    if (httpCode == 302) {
      for (int i = 0; i < 3; i++) {
        digitalWrite(LED_302, HIGH);
        delay(300);
        digitalWrite(LED_302, LOW);
        delay(300);
      }
    } else if (httpCode < 200 || httpCode >= 300) { // Outros erros
      for (int i = 0; i < 3; i++) {
        digitalWrite(LED_ERRO, HIGH);
        delay(300);
        digitalWrite(LED_ERRO, LOW);
        delay(300);
      }
    }
    // Caso de sucesso: nenhum LED acende

    http.end();
  }
}

// Função para gerar um timestamp legível (Data e Hora)
String getFormattedTimestamp() {
  unsigned long currentMillis = millis();
  
  // Converte os milissegundos para segundos
  unsigned long seconds = currentMillis / 1000;
  unsigned long minutes = seconds / 60;
  unsigned long hours = minutes / 60;
  
  // Formatação: YYYY-MM-DD HH:MM:SS
  String formattedDate = "2023-05-15 "; // Data fixa (para teste, pode usar NTP depois)
  String timeStr = String(hours % 24) + ":" + String(minutes % 60) + ":" + String(seconds % 60);
  
  formattedDate += timeStr;
  return formattedDate;
}
