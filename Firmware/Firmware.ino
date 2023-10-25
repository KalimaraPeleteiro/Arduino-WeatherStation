// Módulos
#include "DHT.h"
#include "ESP8266.h"


// Pinos e Constantes
#define DHTPIN	2
#define DHTTYPE 22

const char* ssid = ""; // Mudar para o nome da Rede Wi-Fi
const char* password = ""; // Mudar para a senha da Rede
const char* rotaAPI = ""; // Mudar para a rota de envio da API
const unsigned long umaHora = 3600000; // Uma hora
bool foiSilenciado = false; // Se a Estação foi Silenciada ou não.
unsigned long ultimaHoraEnvio = 0; // Para registro.
const char* ChaveEstacao = "UHW234D9A0S"; // Exemplo de Chave


DHT dht(DHTPIN, DHTTYPE);


// Preparação
void setup() {
    Serial.begin(115200);
    delay(10);

    WiFi.begin(ssid, password); // Iniciando Conexão
    while (WiFi.status() != WL_CONNECTED) { // Esperando concluir a conexão
        delay(1000);
        Serial.println("Aguardando Conexão...")
    }

    Serial.println("Conectado!")
    
    dht.begin(); // Iniciando o Sensor
}

void loop() {
    // Caso a estação tenha sido silenciada, cheque se passou uma hora.
    if (foiSilenciado){
        unsigned long horarioAtual = millis();
        if (horarioAtual - ultimaHoraEnvio >= umaHora){ // Caso tenha passado, retire o silenciamento.
            foiSilenciado = false;
        }
    }

    // Caso a estação não tenha sido silenciada, execute a leitura.
    if (!foiSilenciado){
        float temperatura = dht.readTemperature();
        float umidade = dht.readHumidity();

        if (!isnan(temperatura) && !isnan(umidade) && WiFi.status() == WL_CONNECTED) {
            String dadosJSON = "{\"Temperatura\":" + String(temperatura, 1) + ",\"Umidade\":" + String(umidade, 1) + ",\"Horário\":" + String(millis(), 1) + ",\"Chave\":" + String(ChaveEstacao, 1) + "}";

            HTTPClient http;

            http.begin(rotaAPI);
            http.addHeader("Content-Type", "application/json");

            int resposta = HTTP.POST(dadosJSON);

            if(resposta == 200){
                ultimaHoraEnvio = millis();
            } else {
                foiSilenciado = true;
            }

            http.end();
        } else {
            Serial.println("Erro na medição dos sensores ou na conexão Wi-Fi.");
            foiSilenciado = true;
        }
    }

    // Caso tenha sido silenciado, espere uma hora para a próxima medição. Caso contrário, 8 horas.
    if (foiSilenciado){
        delay(umaHora);
    } else {
        delay(umaHora * 8);
    }

    

    if (isnan(temperatura) || isnan(umidade)){
        Serial.println("Erro ao ler o Sensor!");
        return;
    }

    delay (8 * 3600 * 1000);
}