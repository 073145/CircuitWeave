/*Componentes: 
Chave deslizante: liga/desliga dispositivo
Arduino uno: Le sensores e aciona transistor
Sensor PIR: Saida 1 se detectar presença
Sensor TMP36: Sinal de Mv proporcional a temperatura 
Relé: chaveia a energia de acionamento da carga
Motor: representa ventilador a ser acionado
Pilhas AA: representa a fonte de energia da carga 
Display: exibe a temperatura do ambiente
Resistores: para controle de corrente no display*/

#include <LiquidCrystal.h>
// biblioteca de controle do display
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
const int pinoPIR = 2; 
const int pinoLED = 4;
int sensorPin = 0;
// variaveis de entrada e saída

void setup(){
  lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode(pinoLED, OUTPUT); 
  pinMode(pinoPIR, INPUT); 
}
// configuração dos pinos

void loop(){
int reading = analogRead(sensorPin);
//le a entrada analogica
float voltage = reading * 5.0;
voltage /= 1024.0; 
//converte o valor em tensão
Serial.print(voltage); Serial.println(" volts");
//mostra no monitor serial a tensão equivalente
float temperatureC = (voltage - 0.5) * 100 ;  
//converte o valor de tensao em temperatura 
Serial.print(temperatureC); Serial.println(" degrees C");
//mostra  a temperatura no monitor serial

//Print a message to the LCD.
  	lcd.println("Temp. atual:");
//set the cursor to column 0, line 1
//(note: line 1 is the second row, since counting begins with 0):
	lcd.setCursor(0, 1);
  	lcd.println(temperatureC); lcd.print("grau celsius");
//print the number of seconds since reset:
//lcd.println(millis() / 1000);
  
if(temperatureC > 32){ 
   if (digitalRead(pinoPIR) == HIGH) {
   digitalWrite(pinoLED, HIGH);
   } 
// se a temperatura maior que 32°C, le sensor de presença
// se o sensor detectar presença, aciona motor
}else{ 
  digitalWrite(pinoLED, LOW); 
}
//caso contrario, desliga relé ("ventilador")
delay (500);
//aguarda 500 ms e refaz o loop
}
