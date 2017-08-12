//ARDUINO HOCAM UZAKTAN KUMANDALI GEMİ PROJESİ
//ALICI KODLARI

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include<Servo.h>

Servo servo;

#define CE_PIN   8
#define CSN_PIN 9

const int soli = 7; //l298n in1 bağlantısı
const int solg = 5;//in2
const int sagi = 4;//in3
const int sagg = 2;//in4
const int e1 = 6;//enable a
const int e2 = 3;//enable b

const uint64_t pipe = 0xE8E8F0F0E1LL;

RF24 radio(CE_PIN, CSN_PIN);
int joystick[2];  //gelen veriler

void setup() {
  servo.attach(A0);
  radio.begin();
  radio.openReadingPipe(1, pipe);
  radio.startListening();;
  Serial.begin(9600);
  servo.write(90);
  pinMode(soli, OUTPUT);
  pinMode(solg, OUTPUT);
  pinMode(sagi, OUTPUT);
  pinMode(sagg, OUTPUT);
  pinMode(e1, OUTPUT);
  pinMode(e2, OUTPUT);
}

void loop() {



  if (radio.available())
  {
    radio.read( joystick, sizeof(joystick) ); //Gelen veriler 2 elemanlı olarak okunacak
    gemi(joystick[0], joystick[1]); // Sonra bu verileri kullanacağım "gemi" adlı fonksiyonu yazıyoruz

  }


}
void gemi(int X_ekseni, int Y_ekseni) {

  int  hiz1 = map(Y_ekseni, 0, 1023, 0, 255);
  int  hiz3 = map(X_ekseni, 0, 1023, 0, 180);//servo için değerler
  
servo.write(hiz3);  
  
  if (hiz1 < 122) //geri giderken
  {
    int  hiz2 = 255 - hiz1;

   
    analogWrite(e2, hiz2 );
    digitalWrite(soli, hiz2);
    digitalWrite(solg, LOW);
    digitalWrite(sagg, hiz2);
    digitalWrite(sagi
    , LOW);
  }

  if (hiz1 > 133)//ileri giderken
  { 
    analogWrite(e2, hiz1);
    digitalWrite(solg,  hiz1);
    digitalWrite(soli, LOW);
    digitalWrite(sagi,  hiz1);
    digitalWrite(sagg, LOW);
  }
  if (hiz1 >= 122 && hiz1 <= 133) //dururken
  { analogWrite(e1, hiz1);
    analogWrite(e2, hiz1);
    digitalWrite(solg, HIGH);
    digitalWrite(soli, HIGH);
    digitalWrite(sagi, HIGH);
    digitalWrite(sagg, HIGH);
  }






}




