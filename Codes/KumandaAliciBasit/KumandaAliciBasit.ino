
#include <SPI.h>
#include "RF24.h"
#include <Servo.h>
#include <SoftwareSerial.h>

RF24 radio(10,9); //CE,CSN

Servo motorServo1;
Servo motorServo2;
SoftwareSerial sfSerial(7,8); //RX,TX

byte addresses[][6] = {"NRFTRX"};

uint16_t received_data[12] ;
uint8_t num_received_data = sizeof(received_data);

uint16_t roboKolData[5];

const int motorPin1 = 3;
const int motorPin2 = 5;

void setup() {
  Serial.begin(115200);
  sfSerial.begin(38400);

  motorServo1.attach(motorPin1);
  motorServo2.attach(motorPin2);
  
  radio.begin();
  radio.setPALevel(RF24_PA_MAX);
  
  radio.openReadingPipe(1,addresses[0]);
  radio.startListening();
  radio.printDetails();
}

int syc = 0;
void loop() {
    
    if (radio.available())
    {      
      syc++;
      radio.read( received_data, num_received_data);

      motorServo1.write(map((1023 - received_data[0]), 0, 1023, 0, 180));
      motorServo2.write(map(received_data[2], 0, 1023, 0, 180));

      roboKolData[4] = map(received_data[5], 0, 1023, 0, 180);
      roboKolData[3] = map((1023 - received_data[4]), 0, 1023, 0, 180);
      roboKolData[2] = map(received_data[6], 0, 1023, 0, 180);
      roboKolData[1] = map((1023 - received_data[7]), 0, 1023, 0, 180);
      roboKolData[0] = map(received_data[8], 1, 0, 30, 135);

      String data = "";
      
      for(int syc = 0; syc < 12 ; syc++)
        data += String(received_data[syc]) + ",";
        
      String data2 = "";
      for(int syc = 0; syc < 5 ; syc++)
        data2 += String(roboKolData[syc]) + ",";
        
      if(data2 != "")
        data2 = data2.substring(0,data2.length() - 1);

      if(syc % 14 == 0)
      {
        syc = 0;
        sfSerial.println(data2);
      }
      
      Serial.println(data);
    }
    
  delay(30);
}
