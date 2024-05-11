#include "VoiceRecognitionV3.h"
#include <ESP8266WiFi.h>


const char* ssid = "ARANHA"; // Substitua por seu nome de rede Wi-Fi
const char* password = "C0m@nd0delt@"; // Substitua por sua senha de Wi-Fi

const int lampada1Pin = 8;
const int lampada2Pin = 9;

WiFiServer server(80); // Porta do servidor web
VoiceRecognitionV3 moduloVoz; // Declare the voice recognition module

void setup() {
  Serial.begin(9600);

  pinMode(lampada1Pin, OUTPUT);
  pinMode(lampada2Pin, OUTPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado!");
  Serial.println("Servidor web iniciado na porta 80");
  Serial.print("Acesse: http://");
  Serial.println(WiFi.localIP()); // Imprime o IP do Arduino na Serial

  server.begin();
  moduloVoz.begin();
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    while (client.connected()) {
      if (client.available()) {
        String request = client.readStringUntil('\r');
        Serial.println(request);

        if (request.indexOf("/lampada1/on") != -1) {
          digitalWrite(lampada1Pin, HIGH);
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("");
          client.println("<h1>Lâmpada 1 ligada!</h1>");
          break;
        } else if (request.indexOf("/lampada1/off") != -1) {
          digitalWrite(lampada1Pin, LOW);
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("");
          client.println("<h1>Lâmpada 1 desligada!</h1>");
          break;
        } else if (request.indexOf("/lampada2/on") != -1) {
          digitalWrite( lampada2Pin, HIGH);
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("");
          client.println("<h1>Lâmpada 2 ligada!</h1>");
          break;
        } else if (request.indexOf("/lampada2/off") != -1) {
          digitalWrite(lampada2Pin, LOW);
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("");
          client.println("<h1>Lâmpada 2 desligada!</h1>");
          break;
        } else {
          // Envia mensagem de erro para requisições desconhecidas
          client.println("HTTP/1.1 404 Not Found");
          client.println("Content-Type: text/plain");
          client.println("");
          client.println("<h1>Comando desconhecido!</h1>");
          break;
        }
      }
      client.stop(); // Encerra a conexão
    }
  }

  String comandoReconhecido; // Declare a variável para armazenar o comando reconhecido
  // Get recognized voice command (replace with actual function call)
  comandoReconhecido = moduloVoz.getRecognizedCommand();  // Call the actual function

  if (comandoReconhecido != "") {
    Serial.println("Reconhecido: " + comandoReconhecido);
    if (comandoReconhecido.equalsIgnoreCase("acender lampada 1")) {
      digitalWrite(lampada1Pin, HIGH);
    } else if (comandoReconhecido.equalsIgnoreCase("apagar lampada 1")) {
      digitalWrite( lampada1Pin, LOW);
    } else if (comandoReconhecido.equalsIgnoreCase("acender lampada 2")) {
      digitalWrite(lampada2Pin, HIGH);
    } else if (comandoReconhecido.equalsIgnoreCase("apagar lampada 2")) {
      digitalWrite(lampada2Pin, LOW);
    } else {
      Serial.println("Comando desconhecido!");
    }
  }
}

