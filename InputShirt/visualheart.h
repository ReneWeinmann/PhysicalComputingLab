#ifndef VISUALHEART_H
#define VISUALHEART_H

#define RPIN 5
#define GPIN 6
#define BPIN 3
#define REPEAT_TIME_PER_SECOND 100

int maxR = 0;
int maxB = 255;
float frequency = 0;

bool fadeDown = true;

int rgb[] = {255 - maxR, 255, 255 - maxB};

float fadeFac(){
  return ((float)frequency * 2) / REPEAT_TIME_PER_SECOND;
}

void setRGB(int r, int g, int b){
  rgb[0] = 255 - r;
  rgb[1] = 255 - g;
  rgb[2] = 255 - b;
}

int *getRGB(){
  int *c = (int*)malloc(sizeof(int) * 3);
  c[0] = 255 - rgb[0];
  c[1] = 255 - rgb[1];
  c[2] = 255 - rgb[2];
  return c;
}

void fade(){
  float speed = fadeFac();
  float rrem = speed * maxR;
  float brem = speed * maxB;

  int *c = getRGB();
  if(fadeDown){
    setRGB(c[0] - rrem, c[1], c[2] - brem);
  }
  else{
    setRGB(c[0] + rrem, c[1], c[2] + brem);
  }
  free(c);
  
  int *b = getRGB();
  if(b[0] < 0 || b[2] < 0){
    setRGB(0, b[1], 0);
    fadeDown = false;
  }
  if(b[0] > maxR || b[2] > maxB){
    setRGB(maxR, b[1], maxB);
    fadeDown = true;
  }
  free(b);
}

void setTemperatur(int val) {
  maxR = val;
  maxB = 255 - val;
  setRGB(maxR, 0, maxB);
}

void setFrequency(float val){
  frequency = val;
}

void step(){
  fade();
  analogWrite(RPIN, rgb[0]);
  analogWrite(GPIN, rgb[1]);
  analogWrite(BPIN, rgb[2]);
}

#endif /*VISUALHEART_H */
