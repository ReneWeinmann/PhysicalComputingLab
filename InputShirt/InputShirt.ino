
#include "heartrate.h"
#include "visualheart.h"
#include <SoftwareSerial.h> 
#include <Filters.h>

#define HEARTPIN 7
#define TEMPPIN 2
#define TEMPONOFF 7
#define MIN_TEMP 32
#define MAX_TEMP 36
#define FREQ_SCALE 0.5
#define BLUETOOTH_TX 4
#define BLUETOOTH_RX  3

SoftwareSerial bluetooth(BLUETOOTH_TX, BLUETOOTH_RX);

int tOffset = millis();
unsigned long t = 0;
int tempTrigger = 0;
unsigned long startTempMeasure = 0;
bool measureTemp = false;

float filterFrequency = 3.0;
float smoothFrequency = 0.01;
FilterOnePole lowpassFilter(LOWPASS, filterFrequency);
FilterOnePole smoothFilter(LOWPASS, smoothFrequency);


void tempSensor(bool on){
  measureTemp = on;
  if(on == true){
    digitalWrite(TEMPONOFF, HIGH);
  }
  else{
    digitalWrite(TEMPONOFF, LOW);
  }
}

void setup() {
  Serial.begin(9600);
  //setup bluetooth
  bluetooth.begin(115200);  // The Bluetooth Mate defaults to 115200bps
  bluetooth.print("$");  // Print three times individually
  bluetooth.print("$");
  bluetooth.print("$");  // Enter command mode
  delay(100);  // Short delay, wait for the Mate to send back CMD
  bluetooth.println("C,00066663A042");
  delay(1000);
  bluetooth.println("U,9600,N");  // Temporarily Change the baudrate to 9600, no parity
  delay(100); 
  // 115200 can be too fast at times for NewSoftSerial to relay the data reliably
  bluetooth.begin(9600);  // Start bluetooth serial at 9600
  
  pinMode(HEARTPIN, INPUT);
  pinMode(RPIN, OUTPUT);
  pinMode(GPIN, OUTPUT);
  pinMode(BPIN, OUTPUT);
  pinMode(TEMPONOFF, OUTPUT);
  tempSensor(false);
  setFrequency(1);
  setTemperatur(0);
  pinMode(TEMPPIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(TEMPPIN), countTrigger, RISING);
}

void loop() {
  t = millis() - tOffset;
  if(t % 10 == 0){
    step();
    int input = analogRead(HEARTPIN);
    lowpassFilter.input(input);
  }
  if(t % 100 == 0){
    int output = round(lowpassFilter.output());
    addMeasure(output);
  }
  if(t % 1000 == 0 && countMeasurements >= FFT_N){
      float heartrate = getHeartFrequency();
      smoothFilter.input(heartrate);
      //Serial.println(smoothFilter.output()*60);
      setFrequency(smoothFilter.output() * FREQ_SCALE);
  }
  
  if(t % 1000 == 0){
    //trigger temperatur measurement
    tempSensor(true);
    startTempMeasure = millis();
    // send heartrate via bluetooth
  }

    if(t % 5000 == 0){
          // send heartrate via bluetooth
    //bluetooth.write((unsigned int)(frequency*100));
    //bluetooth.write((int)(smoothFilter.output()*60));
    //Serial.print((int)(smoothFilter.output()*60));
    }
  
  if(millis() - startTempMeasure >= 104 && measureTemp){
    tempSensor(false);
    float temp = (tempTrigger / (float)4096) * 256 - 50;
    int a = (int)(temp*100) >> 8;
    int b = ((int)(temp*100) << 8) >> 8;
    bluetooth.write(a);
    bluetooth.write(b);
    Serial.println((int)(temp * 100));
    float colorTemp = min(255, max(0, (temp - MIN_TEMP) / (MAX_TEMP - MIN_TEMP) * 255));
    setTemperatur(colorTemp);
    tempTrigger = 0;
  }

}

void countTrigger(){
  tempTrigger += 1;
}

