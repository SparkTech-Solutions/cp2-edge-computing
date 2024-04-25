#include "DHT.h" // Inclui a biblioteca DHT
#include <LiquidCrystal.h> // Inclui a biblioteca LiquidCrystal

#define DHTPIN 8 // Define o pino ao qual o sensor DHT está conectado
#define DHTTYPE DHT22   // Define o tipo de sensor DHT (DHT22 neste caso)

DHT dht(DHTPIN, DHTTYPE); // Cria um objeto DHT para interagir com o sensor
LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2); // Inicializa o objeto LiquidCrystal para interagir com o LCD

int ValorLDR;        // Variável para armazenar o valor lido pelo sensor LDR
int IntensidadeLuz;  // Variável para armazenar a intensidade da luz calculada
int pinoLDR = A0;    // Define o pino analógico ao qual o sensor LDR está conectado
int ledVerde = 6;    // Define o pino digital ao qual o LED verde está conectado
int ledVerm = 9;    // Define o pino digital ao qual o LED vermelho está conectado
int ledAma = 7;     // Define o pino digital ao qual o LED amarelo está conectado
int buzina = 13;    // Define o pino digital ao qual a buzina está conectada

// Definições de caracteres personalizados para o LCD
byte luzRuim[8] = { B01110, B11111, B11111, B11111, B01110, B01110, B01110, B00100 };
byte luzBoa[8] = { B01110, B10001, B10001, B10001, B01010, B01010, B01110, B00100 };
byte luzMeia[8] = { B01110, B10001, B10001, B10001, B01110, B01110, B01110, B00100 };
byte tempBoa[8] = { B00100, B01010, B01010, B01010, B01010, B11011, B11111, B01110 };
byte tempMeia[8] = { B00100, B01010, B01010, B01010, B01110, B11111, B11111, B01110 };
byte tempRuim[8] = { B00100, B01110, B01110, B01110, B01110, B11111, B11111, B01110 };
byte humBoa[8] = { B00100, B00100, B01010, B01010, B10001, B11011, B11111, B01110 };
byte humMeia[8] = { B00100, B00100, B01010, B01010, B11111, B11111, B11111, B01110 };
byte humRuim[8] = { B00100, B00100, B01110, B01110, B11111, B11111, B11111, B01110 };
byte logoEsqCima[8] = { B00001, B00011, B00011, B00111, B00111, B01111, B01111, B11111 };
byte logoDirCima[8] = { B11110, B11111, B11111, B11110, B11100, B11000, B10000, B11111 };
byte logoEsqBaixo[8] = { B11111, B00011, B00111, B00111, B01111, B01110, B11100, B11000 };
byte logoDirBaixo[8] = { B11110, B11100, B11000, B10000, B00000, B00000, B00000, B00000 };

void setup() {
  lcd.begin(16,2); // Inicializa o LCD com 16 colunas e 2 linhas
  // Cria caracteres personalizados para o LCD
  lcd.createChar(1, luzRuim);
  lcd.createChar(2, luzBoa);
  lcd.createChar(3, tempBoa);
  lcd.createChar(4, humBoa);
  lcd.createChar(5, logoEsqCima);
  lcd.createChar(6, logoDirCima);
  lcd.createChar(7, logoEsqBaixo);
  lcd.createChar(8, logoDirBaixo);
  lcd.clear(); // Limpa o LCD
  // Imprime o nome da empresa no LCD
  lcd.setCursor(2, 0);
  lcd.print("SparkTech");
  lcd.setCursor(2, 1);
  lcd.print("Solutions");
  // Exibe um logo personalizado animado no LCD
  lcd.setCursor(13, 0);
  lcd.write(5);
  lcd.write(6);
  lcd.setCursor(13, 1);
  lcd.write(7);
  lcd.write(8);
  delay(3000);
  lcd.setCursor(13, 0);
  lcd.print(" ");
  lcd.write(5);
  lcd.write(6);
  lcd.setCursor(13, 1);
  lcd.print(" ");
  lcd.write(7);
  lcd.write(8);
  delay(200);
  lcd.setCursor(13, 0);
  lcd.print("  ");
  lcd.write(5);
  lcd.write(6);
  lcd.setCursor(13, 1);
  lcd.print("  ");
  lcd.write(7);
  lcd.write(8);
  delay(200);
  lcd.setCursor(13, 0);
  lcd.print("   ");
  lcd.setCursor(13, 1);
  lcd.print("   ");
  delay(100); // Aguarda 0,1 segundo
  lcd.clear(); // Limpa o LCD
  dht.begin(); // Inicializa o sensor DHT
  pinMode(pinoLDR, INPUT);    // Configura o pino do sensor LDR como entrada
  pinMode(ledVerm, OUTPUT);   // Configura o pino do LED vermelho como saída
  pinMode(ledAma, OUTPUT);    // Configura o pino do LED amarelo como saída
  pinMode(ledVerde, OUTPUT);  // Configura o pino do LED verde como saída
  pinMode(buzina, OUTPUT);    // Configura o pino da buzina como saída
}

void loop() {
  // Arrays para armazenar valores de umidade e temperatura
  

  float mediaCiclosHumi = 0;
  float mediaCiclosTemp = 0;
  float mediaCiclosLuz = 0;

  // Lê e armazena 10 valores de umidade
  
  int cont = 0;

  while(cont < 10){
    cont += 1;

    float humidityValores[10];
    float humiditySoma = 0;
    float temperatureValores[10];
    float temperatureSoma = 0;

    for (int i = 0; i < 10; i++) {
      float humidity = dht.readHumidity();
      // Verifica se a leitura falhou e tenta novamente
      if (isnan(humidity)) {
        Serial.println(F("Failed to read from DHT sensor!"));
        return;
      }
      humidityValores[i] = humidity;
      humiditySoma += humidity;
      delay(10); // Delay entre as leituras
    }
    // Lê e armazena 10 valores de temperatura
    for (int i = 0; i < 10; i++) {
      float temperature = dht.readTemperature();
      // Verifica se a leitura falhou e tenta novamente
      if (isnan(temperature)) {
        Serial.println(F("Failed to read from DHT sensor!"));
        return;
      }
      temperatureValores[i] = temperature;
      temperatureSoma += temperature;
      delay(10); // Delay entre as leituras
    }

    // Calcula a média da umidade e temperatura
    float mediaHumidity = humiditySoma / 10;
    float mediaTemperature = temperatureSoma / 10;
    // Exibe a umidade média no LCD
    lcd.setCursor(0, 0);
    lcd.print(F("Humi.: "));
    lcd.print(mediaHumidity);
    lcd.print(F("%"));
    // Determina o estado da umidade e exibe uma mensagem correspondente no LCD
    if(mediaHumidity < 50){
      lcd.setCursor(0, 1);
      lcd.print("Humidade Media");
      digitalWrite(ledVerm, LOW);    // Acende o LED vermelho
      digitalWrite(ledVerde, LOW);    // Apaga o LED verde
      digitalWrite(ledAma, HIGH);      // Apaga o LED amarelo
      tone(buzina, 1000);
      lcd.setCursor(14, 0);
      lcd.write(4);
      delay(500); //Aguarda 5 segundos
    } else if(mediaHumidity > 70){
        lcd.setCursor(0, 1);
        lcd.print("Humidade Ruim");
        digitalWrite(ledVerm, HIGH);    // Acende o LED vermelho
        digitalWrite(ledVerde, LOW);    // Apaga o LED verde
        digitalWrite(ledAma, LOW);      // Apaga o LED amarelo
        tone(buzina, 1000);
        lcd.setCursor(14, 0);
        lcd.write(4);
        delay(500); //Aguarda 5 segundos
    } else {
        lcd.setCursor(0, 1);
        lcd.print("Humidade Boa");
        digitalWrite(ledVerm, LOW);    // Acende o LED vermelho
        digitalWrite(ledVerde, HIGH);    // Apaga o LED verde
        digitalWrite(ledAma, LOW);      // Apaga o LED amarelo
        lcd.setCursor(14, 0);
        lcd.write(4);
        delay(5000); //Aguarda 5 segundos
      }
      while(mediaHumidity < 50 || mediaHumidity > 70){
      // Aciona o buzzer enquanto a umidade estiver ruim
        tone(buzina, 1000); // Ativa a buzina com tom de 1000 Hz
        delay(100); // Pequeno atraso para evitar oscilações
        // Lê novamente o valor da umidade
        mediaHumidity = dht.readHumidity();
      }
      noTone(buzina);
      mediaCiclosHumi += mediaHumidity;
    
     // Aguarda 3 segundos
    lcd.clear(); // Limpa o LCD
    lcd.setCursor(0, 0);
    lcd.print(F("Temp.: "));
    lcd.print(mediaTemperature);
    lcd.print(F("C"));
    // Determina o estado da temperatura e exibe uma mensagem correspondente no LCD
    if(mediaTemperature < 10){
      lcd.setCursor(0, 1);
      lcd.print("Esta Frio!");
      digitalWrite(ledVerm, LOW);    // Acende o LED vermelho
      digitalWrite(ledVerde, LOW);    // Apaga o LED verde
      digitalWrite(ledAma, HIGH);      // Apaga o LED amarelo
      tone(buzina, 1000);
      lcd.setCursor(14, 0);
      lcd.write(3);
      delay(500); //Aguarda 5 segundos
    } else if(mediaTemperature > 15){
      lcd.setCursor(0, 1);
      lcd.print("Esta Quente!");
      digitalWrite(ledVerm, HIGH);    // Acende o LED vermelho
      digitalWrite(ledVerde, LOW);    // Apaga o LED verde
      digitalWrite(ledAma, LOW);      // Apaga o LED amarelo
      tone(buzina, 1000);
      lcd.setCursor(14, 0);
      lcd.write(3);
      delay(500); //Aguarda 5 segundos
      
    } else {
      lcd.setCursor(0, 1);
      lcd.print("Temperatura Ok!");
      digitalWrite(ledVerm, LOW);    // Acende o LED vermelho
      digitalWrite(ledVerde, HIGH);    // Apaga o LED verde
      digitalWrite(ledAma, LOW);      // Apaga o LED amarelo
      lcd.setCursor(14, 0);
      lcd.write(3);
      delay(5000); //Aguarda 5 segundos
    }
      while(mediaTemperature < 10 || mediaTemperature > 15){
      // Aciona o buzzer enquanto a umidade estiver ruim
        tone(buzina, 1000); // Ativa a buzina com tom de 1000 Hz
        delay(100); // Pequeno atraso para evitar oscilações
        // Lê novamente o valor da umidade
        mediaHumidity = dht.readHumidity();
      }
    noTone(buzina);
    mediaCiclosTemp += mediaTemperature;

     // Aguarda 3 segundos
    lcd.clear(); // Limpa o LCD
    // Lê o valor do sensor LDR e calcula a intensidade da luz
    int ValorLDR = analogRead(pinoLDR);
    IntensidadeLuz = map(ValorLDR, 0, 1023, 101, 0);
    // Exibe a intensidade da luz no LCD
    lcd.setCursor(0, 0);
    lcd.print(F("Luz: "));
    lcd.print(IntensidadeLuz);
    lcd.print(F("%"));
    // Determina o estado da intensidade da luz e exibe uma mensagem correspondente no LCD
    if (IntensidadeLuz >= 60) 
    {
      lcd.setCursor(0, 1);
      lcd.print("A Luz esta forte");
      lcd.setCursor(14, 0);
      lcd.write(1);
      digitalWrite(ledVerm, HIGH);    // Acende o LED vermelho
      digitalWrite(ledVerde, LOW);    // Apaga o LED verde
      digitalWrite(ledAma, LOW);      // Apaga o LED amarelo
      tone(buzina, 1000); // Ativa a buzina com tom de 1000 Hz
      while(IntensidadeLuz >= 60){
        int ValorLDR = analogRead(pinoLDR);
        IntensidadeLuz = map(ValorLDR, 0, 1023, 101, 0);
        digitalWrite(ledVerm, HIGH);
        tone(buzina, 1000);
        delay(10);
      }
      delay(500); //Aguarda 5 segundos // Aguarda 3 segundos
    } else if (IntensidadeLuz > 30) {
      lcd.setCursor(0, 1);
      lcd.print("Meia Luz!");
      lcd.setCursor(14, 0);
      lcd.write(1);
      digitalWrite(ledAma, HIGH);      // Acende o LED amarelo
      digitalWrite(ledVerde, LOW);     // Apaga o LED verde
      digitalWrite(ledVerm, LOW);      // Apaga o LED vermelho
      delay(5000); //Aguarda 5 segundos // Aguarda 3 segundos
    } else {
      lcd.setCursor(0, 1);
      lcd.print("A Luz esta Boa!");
      lcd.setCursor(14, 0);
      lcd.write(2);
      digitalWrite(ledVerde, HIGH);    // Acende o LED verde
      digitalWrite(ledVerm, LOW);      // Apaga o LED vermelho
      digitalWrite(ledAma, LOW);       // Apaga o LED amarelo
      delay(5000); //Aguarda 5 segundos // Aguarda 3 segundos
    }

    mediaCiclosLuz += IntensidadeLuz;
    digitalWrite(ledVerde, LOW);    // Acende o LED verde
    digitalWrite(ledVerm, LOW);      // Apaga o LED vermelho
    digitalWrite(ledAma, LOW);       // Apaga o LED amarelo
    noTone(buzina); // Desativa a buzina
    lcd.clear(); // Limpa o LCD
  }
  //Tira a media dos 3 valores depois de 10 ciclos
  mediaCiclosHumi = mediaCiclosHumi / 10;
  mediaCiclosTemp = mediaCiclosTemp / 10;
  mediaCiclosLuz = mediaCiclosLuz / 10;

  //Mostra a media dos 3 valores no lcd
  lcd.setCursor(0, 0);
  lcd.print("Media Valores:");
  lcd.setCursor(0, 1);
  lcd.write(4);
  lcd.print(round(mediaCiclosHumi));
  lcd.print("%");
  lcd.setCursor(6, 1);
  lcd.write(3);
  lcd.print(round(mediaCiclosTemp));
  lcd.print("C");
  lcd.setCursor(12, 1);
  lcd.write(2);
  lcd.print(round(mediaCiclosLuz));
  lcd.print("%");
  delay(6000); // Aguarda 6 segundos
}
