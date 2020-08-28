
#include <Servo.h>
Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;
Servo myservo5;

int minAngle=40;
int maxAngle=145;

void setup() {
  Serial.begin(38400);
  
  myservo1.attach(10); 
  myservo1.write(90);

  myservo2.attach(9); 
  myservo2.write(90);
  
  myservo3.attach(6); 
  myservo3.write(90);
  
  myservo4.attach(5); 
  myservo4.write(90);
  
  myservo5.attach(3); 
  myservo5.write(90);
}

// the loop function runs over and over again forever
void loop() {
  while (Serial.available() > 0) {
    int pos1 = Serial.parseInt();
    pos1 = (pos1 < minAngle ? minAngle : (pos1 > maxAngle ? maxAngle : pos1));
    
    int pos2 = Serial.parseInt();
    pos2 = (pos2 < minAngle ? minAngle : (pos2 > maxAngle ? maxAngle : pos2));
        
    int pos3 = Serial.parseInt();
    pos3 = (pos3 < minAngle ? minAngle : (pos3 > maxAngle ? maxAngle : pos3));
    
    int pos4 = Serial.parseInt();
    pos4 = (pos4 < minAngle ? minAngle : (pos4 > maxAngle ? maxAngle : pos4));
    
    int pos5 = Serial.parseInt();
    pos5 = (pos5 < minAngle ? minAngle : (pos5 > maxAngle ? maxAngle : pos5));
    
    Serial.println("Processing");
    
    int cache = Serial.read();
    if (cache == '\r' || cache == '\n')
    {
        myservo1.write(pos1); 
        myservo2.write(pos2); 
        myservo3.write(pos3); 
        myservo4.write(pos4); 
        myservo5.write(pos5); 
        
      delay(15);
      Serial.println("Servo Set");
    }
    delay(50);
  }
  delay(100);
}
