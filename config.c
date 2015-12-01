/*
##################################################
##################################################
####                                          ####
####      LabWork 2 Optimization Methods      ####
####        Student: Eugene Dementyev         ####
####          Group: BZI-104m                 ####
####                                          ####
##################################################
##################################################
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double a = 2, b = -1.3, c = 0.02, d = 0.14;
double e[5] = {0.1, 0.01, 0.001, 0.0001, 0.00001};
int N0, N1, N2, N, k, i;
double x1[1000], x2[1000], y[4];
double z1, z2;
double A, B;


void config (FILE *file);

double
dz (double x1, double x2) {
  N0++;
  return a * x1 + b * x2 + exp(c * pow(x1, 2) + d * pow(x2, 2));
}

int
main() {
  FILE *file = fopen("config.txt", "w+");
  for (i=0; i < 5; i++) {
  printf("Iteration %d with e = %lf\n", i+1, e[i]);
  config(file);
  }
    fclose(file);
}

void
config (FILE *file) {
  double x1min, x2min, ymin;
  N0 = 0; N1 = 0; N2 = 0; N = 0;
  x1[0] = -1; x2[0] = 0;
  double l = 1, h = 1;
  int s = 1;
  k = 0;

  y[0] = dz (x1[0], x2[0]);
  do {
    s=1; y[1]=dz (x1[k]+h,x2[k]);
    if(y[0]>y[1]) {
      x1[k + 1]=x1[k]+h;
    }
    else {
      y[1] = dz (x1[k] - h,x2[k]);
      if(y[0] > y[1]) {
        x1[k + 1] = x1[k] - h;
      }
      else {
        y[1] = y[0];
        x1[k + 1] = x1[k];
      }
    }
    y[2] = dz (x1[k + 1],x2[k] + h);
    if(y[1] > y[2]) {
      x2[k + 1]=x2[k] + h;
    }
    else {
      y[2] = dz (x1[k + 1],x2[k] - h);
      if(y[1] > y[2]) {
        x2[k + 1] = x2[k] - h;
      }
      else {
        y[2] = y[1];
        x2[k + 1] = x2[k];
      }
    }
    if (i == 0) {
      fprintf(file, "%f\t%f\n", x1[k], x2[k]);
      fprintf(file, "%f\t%f\n", x1[k + 1], x2[k + 1]);
    }
    if((x1[k + 1] == x1[k]) && (x2[k + 1] == x2[k])) {
      if(h > e[i]) {
        s = 0; h = h / 2;
      }
    }
    else {
      s = 0;
      do {
        l = l / 2;
        x1[k + 2]=x1[k + 1] + l * (x1[k + 1] - x1[k]);
        x2[k + 2] = x2[k + 1] + l * (x2[k + 1] - x2[k]);
        y[3] = dz (x1[k + 2], x2[k + 2]);
      } while(y[2] < y[3]);
      y[0] = y[3];
      k = k + 2;
    }
  } while(s == 0);
  x1min = x1[k]; x2min = x2[k]; ymin = y[0];
  N = N0 + N1 + N2;
  fprintf(file, "%f\t%f\t%f\t%d\t%d\n", x1min, x2min, ymin, N, k);
}
