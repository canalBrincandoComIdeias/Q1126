#include <ESP32Servo.h> 

Servo myservo;  

// Pinos PWM no ESP32: 0(usado pelo botão na placa),2,4,5(usado pelo LED da placa),12-19,21-23,25-27,32-33 
// Pinos PWM no ESP32: 0(usado pelo botão na placa),1-17,18(usado pelo LED da placa),19-21,26,33-42
// Pinos PWM no ESP32: 0(usado pelo botão na placa),1-21,35-45,47,48(usado pelo LED da placa)
// Pinos PWM no ESP32: 0(usado pelo botão na placa),1-7,8(usado pelo LED da placa),9-10,18-21
int servoPin = 21;

// Pinos ADC no ESP32: 0,2,4,12-15,32-39; 34-39 são recomendados para input analógico
// Pinos ADC no ESP32-S2: 1-20 são recomendados para input analógico
#if defined(CONFIG_IDF_TARGET_ESP32S2) || defined(CONFIG_IDF_TARGET_ESP32S3)
int potPin = 10;       
#elif defined(CONFIG_IDF_TARGET_ESP32C3)
int potPin = 4;         
#else
int potPin = 34;        
#endif

int ADC_Max = 4096;     // Este é o valor máximo padrão do ADC no ESP32 (ADC de 12 bits);
                        // essa largura pode ser configurada (em código de baixo nível) de 9 a 12 bits,
                        // para um intervalo de valores máximos de 512 a 4096
  
int val;    

void setup()
{
	// Permitir a alocação de todos os timers
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
  myservo.setPeriodHertz(50);// Frequencia padrão para os servo motores comuns: 50hz
  myservo.attach(servoPin, 500, 2400);  // conecta o servo no pino 18 ao objeto servo
                                        // usando os valores mínimos/máximos do servo SG90 de 500µs e 2400µs
                                        // para o servo grande MG995, use 1000µs e 2000µs,
                                        // que são os valores padrão, então esta linha poderia ser
                                        // "myservo.attach(servoPin);"
}

void loop() {
  val = analogRead(potPin);            // lê o valor do potenciômetro (valor entre 0 e 1023)
  val = map(val, 0, ADC_Max, 0, 180);  // converte a escala para usar com o servo (valor entre 0 e 180)
  myservo.write(val);                  // define a posição do servo de acordo com o valor escalado
  delay(50);                          // espera o servo chegar lá
}
