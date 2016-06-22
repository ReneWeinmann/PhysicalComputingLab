
#include "heartrate.h"
#include "visualheart.h"
#include <Filters.h>

int bPin = 3;
int rPin = 5;
int gPin = 6;
int heartPin = 0;
int tOffset = millis();
int t = 0;

float filterFrequency = 5.0;
FilterOnePole lowpassFilter(LOWPASS, filterFrequency);

void setup() {
  Serial.begin(9600);
  pinMode(heartPin, INPUT);
  pinMode(rPin, OUTPUT);
  pinMode(bPin, OUTPUT);
}

void loop() {
  t = millis() - tOffset;
  if(t % 10 == 0){
    int input = analogRead(heartPin);
    lowpassFilter.input(input);
  }
  if(t % 100 == 0){
    float output = lowpassFilter.output();
    addMeasure(output);
    if(countMeasurements >= FFT_N){
      transform();
    }
  }
}


