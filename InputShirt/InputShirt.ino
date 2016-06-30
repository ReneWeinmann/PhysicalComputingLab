
#include "heartrate.h"
#include "visualheart.h"
#include <Filters.h>

#define HEARTPIN 7
#define TEMPPIN 2
#define TEMPONOFF 7
#define MIN_TEMP 28
#define MAX_TEMP 35

int tOffset = millis();
unsigned long t = 0;
int tempTrigger = 0;
unsigned long startTempMeasure = 0;
bool measureTemp = false;

float filterFrequency = 3.0;
FilterOnePole lowpassFilter(LOWPASS, filterFrequency);


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
      setFrequency(heartrate);
  }
  if(t % 1000 == 0){
    tempSensor(true);
    startTempMeasure = millis();
  }
  
  if(millis() - startTempMeasure >= 104 && measureTemp){
    tempSensor(false);
    float temp = (tempTrigger / (float)4096) * 256 - 50;
    float colorTemp = min(255, max(0, (temp - MIN_TEMP) / (MAX_TEMP - MIN_TEMP) * 255));
    Serial.println(temp);
    Serial.println(colorTemp);
    setTemperatur(colorTemp);
    tempTrigger = 0;
  }
}

void countTrigger(){
  tempTrigger += 1;
}

