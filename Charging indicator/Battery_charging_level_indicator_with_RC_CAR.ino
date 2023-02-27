
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <LcdBarGraphRobojax.h>
#include <AFMotor.h>

//initial motors pin
AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);



int val;
int Speeed = 255;
int offset =20;

byte lcdNumCols = 20; // -- number of columns in the LCD
byte lcdLine = 4; // -- number of line in the LCD
byte sensorPin = 0; // -- value for this example

LiquidCrystal_I2C lcd(0x27, 20, 4); // -- creating LCD instance
LcdBarGraphRobojax lbg(&lcd, 16, 0, 0);  // -- creating 16 character long bargraph starting at char 0 of line 0 
  

unsigned long previousTime_1 = 0; 
unsigned long previousTime_2 = 0;



void setup()
{
  Serial.begin(9600);  //Set the baud rate to your Bluetooth module.

    // -- initializing the LCD
  lcd.begin();
  lcd.clear();
  lcd.print("Battery Voltage"); 
  lcd.setCursor (0,1); //  
  lcd.print("Level Indicator"); 
  delay(2000);
  lcd.clear();
}


void loop(){

  unsigned long currentTime = millis();



  // lbg.clearLine(1);// clear line 1 to display fresh voltage value
  int inpuValue = analogRead(A0);
  int volt = analogRead(A0);
  double voltage = map(volt,0,1023, 0, 2500) + offset;// map 0-1023 to 0-2500 and add correction offset
  voltage /=12.8;// divide by 100 to get the decimal values
  // -- draw bar graph from the analog value read
  // // if ( currentTime - previousTime_1 >= 0){
  lbg.drawValue( inpuValue, 520);
  // // -- do some delay: frequent draw may cause broken visualization
  lcd.setCursor (0,1); //
  lcd.print("Bat Charge:"); 
  // lcd.setCursor (11,1); //
  // lcd.print("87"); // print
  // lcd.print(voltage); // print
  lcd.setCursor (13,1); //  
  lcd.print(voltage);   
  // // delay(100);
  // previousTime_1 = currentTime;
  // // }



  if(Serial.available() > 0){                //stored bytes from the serial port that are available for reading.
    val = Serial.read();                      //read out the first available byte from the serial receive buffer.
      
    Stop(); //initialize with motors stoped
    
          if (val == 'F'){
          forward();
          }
  
          if (val == 'B'){
          back();
          }
  
          if (val == 'L'){
          left();
          }
  
          if (val == 'R'){
          right();
          }
          if (val == 'I'){
          topright();
          }
  
          if (val == 'J'){
          topleft();
          }
  
          if (val == 'K'){
          bottomright();
          }
  
          if (val == 'M'){
          bottomleft();
          }
          if (val == 'T'){
          Stop();
          }

          // ----speed
          // if (val == '0'){
          // speeed = 100;
          // }
          // if (val == '1'){
          // speeed = 200;
          // }
          // if (val == '3'){
          // speeed = 255;
          // }
  }

}
           
  
void forward()
{
  motor1.setSpeed(Speeed); //Define maximum velocity
  motor1.run(FORWARD); //rotate the motor clockwise
  motor2.setSpeed(Speeed); //Define maximum velocity
  motor2.run(FORWARD); //rotate the motor clockwise
  motor3.setSpeed(Speeed);//Define maximum velocity
  motor3.run(FORWARD); //rotate the motor clockwise
  motor4.setSpeed(Speeed);//Define maximum velocity
  motor4.run(FORWARD); //rotate the motor clockwise
}
  
void back()
{
  motor1.setSpeed(Speeed); //Define maximum velocity
  motor1.run(BACKWARD); //rotate the motor anti-clockwise
  motor2.setSpeed(Speeed); //Define maximum velocity
  motor2.run(BACKWARD); //rotate the motor anti-clockwise
  motor3.setSpeed(Speeed); //Define maximum velocity
  motor3.run(BACKWARD); //rotate the motor anti-clockwise
  motor4.setSpeed(Speeed); //Define maximum velocity
  motor4.run(BACKWARD); //rotate the motor anti-clockwise
}
  
void left()
{
  motor1.setSpeed(Speeed); //Define maximum velocity
  motor1.run(BACKWARD); //rotate the motor anti-clockwise
  motor2.setSpeed(Speeed); //Define maximum velocity
  motor2.run(BACKWARD); //rotate the motor anti-clockwise
  motor3.setSpeed(Speeed); //Define maximum velocity
  motor3.run(FORWARD);  //rotate the motor clockwise
  motor4.setSpeed(Speeed); //Define maximum velocity
  motor4.run(FORWARD);  //rotate the motor clockwise
}
  
void right()
{
  motor1.setSpeed(Speeed); //Define maximum velocity
  motor1.run(FORWARD); //rotate the motor clockwise
  motor2.setSpeed(Speeed); //Define maximum velocity
  motor2.run(FORWARD); //rotate the motor clockwise
  motor3.setSpeed(Speeed); //Define maximum velocity
  motor3.run(BACKWARD); //rotate the motor anti-clockwise
  motor4.setSpeed(Speeed); //Define maximum velocity
  motor4.run(BACKWARD); //rotate the motor anti-clockwise
}
  
void topleft(){
  motor1.setSpeed(Speeed); //Define maximum velocity
  motor1.run(FORWARD); //rotate the motor clockwise
  motor2.setSpeed(Speeed); //Define maximum velocity
  motor2.run(FORWARD); //rotate the motor clockwise
  motor3.setSpeed(Speeed/3.1);//Define maximum velocity
  motor3.run(FORWARD); //rotate the motor clockwise
  motor4.setSpeed(Speeed/3.1);//Define maximum velocity
  motor4.run(FORWARD); //rotate the motor clockwise
}
  
void topright()
{
  motor1.setSpeed(Speeed/3.1); //Define maximum velocity
  motor1.run(FORWARD); //rotate the motor clockwise
  motor2.setSpeed(Speeed/3.1); //Define maximum velocity
  motor2.run(FORWARD); //rotate the motor clockwise
  motor3.setSpeed(Speeed);//Define maximum velocity
  motor3.run(FORWARD); //rotate the motor clockwise
  motor4.setSpeed(Speeed);//Define maximum velocity
  motor4.run(FORWARD); //rotate the motor clockwise
}
  
void bottomleft()
{
  motor1.setSpeed(Speeed); //Define maximum velocity
  motor1.run(BACKWARD); //rotate the motor anti-clockwise
  motor2.setSpeed(Speeed); //Define maximum velocity
  motor2.run(BACKWARD); //rotate the motor anti-clockwise
  motor3.setSpeed(Speeed/3.1); //Define maximum velocity
  motor3.run(BACKWARD); //rotate the motor anti-clockwise
  motor4.setSpeed(Speeed/3.1); //Define maximum velocity
  motor4.run(BACKWARD); //rotate the motor anti-clockwise
}
  
  
void bottomright()
{
  motor1.setSpeed(Speeed/3.1); //Define maximum velocity
  motor1.run(BACKWARD); //rotate the motor anti-clockwise
  motor2.setSpeed(Speeed/3.1); //Define maximum velocity
  motor2.run(BACKWARD); //rotate the motor anti-clockwise
  motor3.setSpeed(Speeed); //Define maximum velocity
  motor3.run(BACKWARD); //rotate the motor anti-clockwise
  motor4.setSpeed(Speeed); //Define maximum velocity
  motor4.run(BACKWARD); //rotate the motor anti-clockwise
}
  
  
void Stop()
{
  motor1.setSpeed(0); //Define minimum velocity
  motor1.run(RELEASE); //stop the motor when release the button
  motor2.setSpeed(0); //Define minimum velocity
  motor2.run(RELEASE); //rotate the motor clockwise
  motor3.setSpeed(0); //Define minimum velocity
  motor3.run(RELEASE); //stop the motor when release the button
  motor4.setSpeed(0); //Define minimum velocity
  motor4.run(RELEASE); //stop the motor when release the button
}
