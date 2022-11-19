#include <Arduino.h>
#include <VL53L0X.h>  // Biblioteca do lidar
#include <Wire.h>     //Biblioteca do I2C
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define LEDPIN D6
#define DHTPIN D5
#define DHTTYPE DHT22 

int limit = 500;

VL53L0X sensor;  // objeto sensor
DHT_Unified dht(DHTPIN, DHTTYPE);

void initDHT() {
  dht.begin();
  sensor_t sensordht;
  dht.temperature().getSensor(&sensordht);
  dht.humidity().getSensor(&sensordht);
}

void setup() {
    Serial.begin(9600);  // Estabelece a comunicação com o computador
    Wire.begin();        // inicia o I2C
    pinMode(LEDPIN, OUTPUT);
    initDHT();
    
    sensor.setTimeout(500);

    // verificação de integridade do sensor
    if (!sensor.init()) {
        Serial.println("Failed to detect and initialize sensor!");
        while (1) {}
    }

    sensor.startContinuous();
}

void limiar(int distancia) {
  if(distancia < limit) {
    digitalWrite(LEDPIN, HIGH);
  }
  else {
    digitalWrite(LEDPIN, LOW);
  }
}

void niveis(int distancia) {
  int limiteS = 700;
  int limiteI = 30;
  if(distancia < limiteS && distancia > limiteI) {
    int out = map(distancia, limiteI, limiteS, 255, 0);
    analogWrite(LEDPIN, out);
  }
}

void readTH() {
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  Serial.print("Temperature: ");
  Serial.print(event.temperature);
  Serial.println("°C");
  dht.humidity().getEvent(&event);
  Serial.print(F("Humidity: "));
  Serial.print(event.relative_humidity);
  Serial.println(F("%"));
  delay(2000);
}

void loop() {
    int dist = sensor.readRangeContinuousMillimeters();
    Serial.println(dist);
    //limiar(dist);
    niveis(dist);
    readTH();
}