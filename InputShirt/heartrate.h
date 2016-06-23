#ifndef HEARTRATE_H
#define HEARTRATE_H

#define FFT_N 128
#define LIN_OUT8  1
#define SAMPLING_FREQUENCY 10

#include <stdio.h>
#include <stdlib.h>
#include <FFT.h>

int measurementsArray[FFT_N];
int currentPos = 0;
int countMeasurements = 0;

void addMeasure(int val){
  measurementsArray[currentPos] = val;
  currentPos = (currentPos + 1) % FFT_N;
  countMeasurements += 1;
}

void transform(){
  int pos = 0;
  for(int i = currentPos; i < FFT_N; i++){
    fft_input[pos] = measurementsArray[i];
    pos += 1;
  }
  for(int i = 0; i < currentPos - 1; i++){
    fft_input[pos] = measurementsArray[i];
    pos += 1;
  }
  fft_window();
  fft_reorder();
  fft_run();
}

float getHeartFrequency(){
  int i_max = 0;
  int max_val = 0;
  transform();
  for(int i = 0; i < 2 * FFT_N - 2; i += 2){
    unsigned int val = 0;
    if(i / 2.0 < 50 && i / 2.0 > 10){
      val = fft_input[i] * fft_input[i] + fft_input[i + 1] * fft_input[i + 1];
    }
    if(max_val <= val){
      i_max = i;
      max_val = val;
    }
  }
  return (i_max / 2.0) * (((float)SAMPLING_FREQUENCY) / FFT_N);
}

void debug(){
  transform();
  for(int i = 0; i < 2 * FFT_N - 2; i += 2){
    unsigned int val = 0;
    if(i / 2.0 < 50 && i / 2.0 > 10){
      val = fft_input[i] * fft_input[i] + fft_input[i + 1] * fft_input[i + 1];
    }
    Serial.print(val);
    Serial.print(",");
  }
  Serial.println("");
}
#endif /*HEARRATE_H */
