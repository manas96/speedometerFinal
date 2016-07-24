/*
 * facing sensor:
 * LEFT:+5V
 * RIGHT:OUTPUT
 * MIDDLE:GROUND
 * pull up resistor between +5V and GND
 */
const int hallSwitch=2;
const double radius=0.275;//meters
const double pi=3.1415;
double distance=0;
float speedMps;
long rpm=0;
unsigned int revolutions=0;
unsigned long currentTime,previousTime=0;
int sensorState;
void setup() {
  // put your setup code here, to run once:
  pinMode(hallSwitch,INPUT);
  pinMode(13,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorState=digitalRead(hallSwitch);
  currentTime=millis();
  unsigned long elapsedTime=currentTime-previousTime;
  if(sensorState==0)
     digitalWrite(13,HIGH);
     else
      digitalWrite(13,LOW);
  if(elapsedTime>10){     //consider sensorState only if more than half second has passed
    if(sensorState==0){   //if magnet is detected
      revolutions++;  
     
      Serial.println("                                                                    DETECTED");    
    } 
    previousTime=currentTime;
  }
  else{
  speedMps=(float)(2*pi*radius*revolutions)/(float)elapsedTime;
  distance=distance+(float)(2*pi*radius*revolutions);
  revolutions=0;
  Serial.print("Speed is :");
  Serial.print(speedMps,4);
  Serial.print(" m/s or ");
  Serial.print((float)(speedMps*3.6),4);
  Serial.println(" km/hr");
  Serial.print("Total distance is :");
  Serial.print(distance);
  Serial.println("meters");

  }

  

}
