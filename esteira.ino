#include <Wire.h>
#include <Servo.h>
#include "Adafruit_TCS34725.h"
  
#define ESTEIRA A0
#define SERVO 8
#define SERVO2 9

#define ROTACAO_INICIAL 90
#define ROTACAO_VERMELHO 30
#define ROTACAO_VERDE 150

uint16_t r, g, b, c, colorTemp, lux; // Variáveis leitura das cores
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);

Servo servo1;
Servo servo2;
int pos;

void setup() {
  Serial.begin(9600);
  pinMode(ESTEIRA, OUTPUT);
  
  configurarServos();
}

void loop() {
  analogWrite(ESTEIRA, 150);
  
  lerCores();
  selecionarCor();
}

/**
 * Responsável por realizar a leitura do atual estado do sensor RGB, retorando o valor de cada cor a sua respectiva variável.
 * 
 */
void lerCores() {
    tcs.getRawData(&r, &g, &b, &c);
    colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c);
    lux = tcs.calculateLux(r, g, b);  
}

/**
 * Realiza a comparação de qual cor está com o valor mais alto após a leitura, selecionando qual cor será separada.
 * 
 * Apenas realiza a validação caso uma das cores tenha o valor acima de 100, 
 * pois o sensor continua captando cor mesmo sem nada abaixo, por conta da luz ambiente.
 * 
 */
int selecionarCor(){
      if(r > 100 && r > g && r > b){
        movimentarVermelho();
      } else if (g > 100 && g > r && g > b){
        movimentarVerde();
      }
}

/**
 * Realiza a movimentação do servo motor quando a leitura retornar vermelho.
 * 
 */
void movimentarVermelho(){
  servo1.write(ROTACAO_VERMELHO);
  servo2.write(ROTACAO_VERMELHO);
  delay(2300);  
    
  movimentarPosicaoInicial();
}

/**
 * Realiza a movimentação do servo motor quando a leitura retornar verde.
 * 
 */
void movimentarVerde(){
  servo1.write(ROTACAO_VERDE);
  servo2.write(ROTACAO_VERDE);
  delay(2300);
  
  movimentarPosicaoInicial();
}

/**
 * Realiza a movimentação do servo motor para posicionar as hastes em sua posição inicial.
 * 
 */
void movimentarPosicaoInicial(){
  servo1.write(ROTACAO_INICIAL);
  servo2.write(ROTACAO_INICIAL);
}

/**
 * Realiza a configuração dos servos motores, inserindo as portas de saída.
 * 
 */
void configurarServos(){
  servo1.attach(SERVO);
  servo2.attach(SERVO2);
  servo1.write(ROTACAO_INICIAL);
}
