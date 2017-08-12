//ARDUINO HOCAM UZAKTAN KUMANDALI GEMİ YAPIMI PROJESİ
//VERİCİ KODLARI

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN   9
#define CSN_PIN 10
#define JOYSTICKX A0 //X ekseni Analog 0 pinine bağlı olduğu için bleirtiyoruz.
#define JOYSTICKY A1
const uint64_t pipe = 0xE8E8F0F0E1LL;  // nrf24l01 için iletişim kanal ismi
RF24 radio(CE_PIN, CSN_PIN);
int joystick[2];  //gönderilecek veriler

void setup() {
  
  radio.begin();//nrf24l01 başlatılıyor
  radio.openWritingPipe(pipe); 
  
}

void loop() {
  
  joystick[0] = analogRead(JOYSTICKX);//x ekseni verileri 
  joystick[1] = analogRead(JOYSTICKY);//y ekseni verileri
  radio.write( joystick, sizeof(joystick) ); //Gönderim yapılıyor
 
}
