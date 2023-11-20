#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

const int PinAnalog=36;

const int VBMotor = 15;

int Threshold = 3000;
boolean ThresholdStat = true;

unsigned long previousMillisGetHR = 0;
const long intervalGetHR = 10;

//LED to detect when the heart is beating
const int LED_D1 = 22;
const int LED_D2 = 19;
const int LED_D3 = 23;
const int LED_D4 = 18;
const int LED_D5 = 5;
const int LED_D6 = 17;

int cntHB = 0;
int bpm = 0;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_Control");
  
  pinMode(PinAnalog,INPUT);

  pinMode(VBMotor, OUTPUT);

  pinMode(LED_D1, OUTPUT); 
  pinMode(LED_D2, OUTPUT); 
  pinMode(LED_D3, OUTPUT); 
  pinMode(LED_D4, OUTPUT); 
  pinMode(LED_D5, OUTPUT); 
  pinMode(LED_D6, OUTPUT); 

}

String sdata="";
int sensor;

void GetHeartRate() {

  
    
  unsigned long currentMillisGetHR = millis();

  if (currentMillisGetHR - previousMillisGetHR >= intervalGetHR) {
    previousMillisGetHR = currentMillisGetHR;

    sensor=analogRead(PinAnalog);
    sdata=sdata+String(sensor)+",";
    Serial.println(sensor);
     

    if (sensor > Threshold && ThresholdStat == true) {
      cntHB++;
      ThresholdStat = false;
      digitalWrite(LED_D1, HIGH);
      digitalWrite(LED_D4, HIGH);

      digitalWrite(VBMotor, HIGH);
      
    }

    if (sensor < Threshold) {
      ThresholdStat = true;
      digitalWrite(LED_D1, LOW);
      digitalWrite(LED_D4, LOW);

      digitalWrite(VBMotor, LOW);
      
    }
    
    
  }
  
}


void loop() {
  
  digitalWrite(LED_D5, HIGH);
  digitalWrite(LED_D2, HIGH);

  
  int ch=SerialBT.read();
    if(ch==1)
    {
      GetHeartRate();
    }
    else if (ch==0)
    {
      SerialBT.println(sdata);
    }

}
