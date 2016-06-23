
#include "heartrate.h"
#include "visualheart.h"
#include <Filters.h>

#define HEARTPIN 0

int tOffset = millis();
int t = 0;

float filterFrequency = 3.0;
FilterOnePole lowpassFilter(LOWPASS, filterFrequency);

void setup() {
  Serial.begin(9600);
  pinMode(HEARTPIN, INPUT);
  pinMode(RPIN, OUTPUT);
  pinMode(GPIN, OUTPUT);
  pinMode(BPIN, OUTPUT);
  setFrequency(1);
  setTemperatur(0);
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
}
