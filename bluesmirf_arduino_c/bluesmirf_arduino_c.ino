/*
  Example Bluetooth Serial Passthrough Sketch
 by: Jim Lindblom
 SparkFun Electronics
 date: February 26, 2013
 license: Public domain

 This example sketch converts an RN-42 bluetooth module to
 communicate at 9600 bps (from 115200), and passes any serial
 data between Serial Monitor and bluetooth module.
 */
#include <SoftwareSerial.h>  

int bluetoothTx = 8;  // Pin TX-O del BlueSMiRF al puerto D8 del Arduino Micro
int bluetoothRx = 9;  // Pin RX-I del BlueSMiRF al puerto D9 del Arduino Micro
char command;

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

void setup() {
  Serial.begin(9600);  // Configura el monitor serial a 9600bps
  Serial1.begin(9600);  // Configura el monitor serial a 9600bps
  
  bluetooth.begin(115200);    // El BlueSMiRF esta configurado a 115200bps por defecto
  bluetooth.print("$$$");    // $$$ es la secuencia para ingresar al modo de comandos
  delay(100);  // Espera arbitraria para que el BlueSMiRF responda CMD
  bluetooth.println("U,9600,N");  // Comando para cambiar el baudrate a 9600bps, sin paridad
  // 115200 suele ser muy rapido para NewSoftSerial, por lo que es mejor reducir la tasa de transferencia
  bluetooth.begin(9600);  // Configura el BlueSMiRF a 9600
  
  pinMode(13, OUTPUT);
}
  
void loop() {
  // Si el modulo Bluetooth envia datos:
  if (bluetooth.available()) {
    // Enviar los datos recibidos del Bluetooth al monitor serial
    command = (char)bluetooth.read();
    Serial.print(command); 
  }
  // Si se ingresan datos en el monitor serial:
  if (Serial.available()) {
    // Enviar los datos del monitor serial al modulo Bluetooth
    bluetooth.print((char)Serial.read());
  }
}

