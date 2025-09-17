#include <Servo.h> 

#define pinServo 18
#define pinPot 26

Servo myservo;  

void setup()
{
	analogReadResolution(12); // Pico tem ADC de 12 bits (0..4095)
  myservo.attach(pinServo, 500, 2400);  // ajuste os limites conforme seu servo.
                                        // Os valores mínimos/máximos do servo SG90 de 500µs e 2400µs
                                        // e para o servo grande MG995, use 1000µs e 2000µs
}

void loop() {
  int val = analogRead(pinPot);                 // 0..4095
  int ang = map(val, 0, 4095, 0, 180);          // 0..180 graus
  myservo.write(ang);
  delay(10);
}
