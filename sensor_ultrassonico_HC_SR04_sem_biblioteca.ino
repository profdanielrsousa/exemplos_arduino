/* EXEMPLO DE CÓDIGO - SENSOR ULTRASSÔNICO SEM BIBLIOTECA
 * ARDUINO UNO
 * SENSOR HC-SR04
 * PLACA PL2 - First Robot - GBK ROBOTICS (https://gbkrobotics.wixsite.com/gbkrobotics/boards)
 * AUTOR: DANIEL RODRIGUES DE SOUSA 01/11/2022 */

//DEFINIÇÃO DOS PINOS DE I/O

//PINOS HC-SR04 PARA ENCAIXAR DIRETAMENTE NOS PINOS SEM PUXAR FIO
#define VCC_FAKE  A0
#define ECHO      A2
#define TRIGGER   A1
#define GND_FAKE  A3

//PINOS PLACA PL2 - First Robot ENCAIXADO DIRETAMENTE USANDO O GND COMO REFERÊNCIA
#define AMARELO       8
#define VERDE         9
#define BUZZER        10
#define VERMELHO      11
#define OLHO_DIREITO  12
#define OLHO_ESQUERDO 13

//definição cm ou pol
#define MEDIDA_CM

unsigned long int tempo_atual;   // temporizadores
unsigned long int tempo_500ms;
unsigned int distancia;

void setup() {

  pinMode(VERDE, OUTPUT);
  pinMode(AMARELO, OUTPUT);  
  pinMode(VERMELHO, OUTPUT);

  pinMode(BUZZER, OUTPUT);
  pinMode(OLHO_ESQUERDO, OUTPUT);  
  pinMode(OLHO_DIREITO, OUTPUT); 
    
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(VCC_FAKE, OUTPUT);
  pinMode(GND_FAKE, OUTPUT);
  
  digitalWrite(GND_FAKE, LOW);
  digitalWrite(VCC_FAKE, HIGH);
  delay(500);
  
  Serial.begin(9600);

  //Inicializaçao da temporiração usando o metodo millis()
  tempo_500ms = millis();
}

void loop() {

  tempo_atual = millis();

  if ((tempo_atual - tempo_500ms) >= 500) //temporizaçao a cada 500ms
  {
    tempo_500ms = millis(); //recarrega temporizador
    digitalWrite(OLHO_ESQUERDO, !digitalRead(OLHO_ESQUERDO));
    digitalWrite(OLHO_DIREITO, !digitalRead(OLHO_ESQUERDO));

    distancia = le_sensor();
    Serial.print(distancia);
    
    #ifdef  MEDIDA_CM
      Serial.println(" cm");
    #elif
      Serial.println(" pol");
    #endif
  }
  
  if(distancia > 100)
  {
    digitalWrite(VERMELHO, LOW);
    digitalWrite(VERDE, HIGH);
  }
  else
  {
    digitalWrite(VERDE, LOW);
    digitalWrite(VERMELHO, HIGH);    
  }
}

int le_sensor( void )
{
  long duracao;
  
  #ifdef  MEDIDA_CM
    int distanciaCm;
  #elif
    int distanciaPol;
  #endif
   
  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER, LOW);
  duracao = pulseIn(ECHO, HIGH);

  #ifdef  MEDIDA_CM
    distanciaCm = duracao*0.034/2;
    return( distanciaCm );
  #elif
    distanciaPol = duracao*0.0133/2;
    return( distanciaPol );
  #endif
}
