#ifndef HEARTRATE_H
#define HEARTRATE_H

#define FFT_N 128
#define LIN_OUT8  1

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
#endif /*HEARRATE_H */
