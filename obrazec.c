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

#define Aa 2
#define Bb -1.3
#define C 0.02
#define D 0.14


double e[5] = {0.1, 0.01, 0.001, 0.0001, 0.00001};
int N0, k, i;


double
df (double x1, double x2) {
  N0++;
  return Aa * x1 + Bb * x2 + exp(C * pow(x1, 2) + D * pow(x2, 2));
}

void
obrazec(FILE *file) {
  double x[2][6]; double y[6];
  x[0][0] = -1;
  x[1][0] = 0;
  double h = 0.8;
  y[0] = df(x[0][0], x[1][0]);
  int t = 0, k=1;
  metka:
    if (t!=1) {
      x[0][1]=x[0][0]-h;  
      x[1][1]=x[1][0]-h;
      y[1]=df(x[0][1],x[1][1]);
    }
    if (t!=2) {
      x[0][2]=x[0][0]-h;
      x[1][2]=x[1][0]+h;
      y[2]=df(x[0][2],x[1][2]);
    }
    if (t!=3) {
      x[0][3]=x[0][0]+h;
      x[1][3]=x[1][0]+h;
      y[3]=df(x[0][3],x[1][3]);
    }
    if(t!=4) {
    x[0][4]=x[0][0]+h;
    x[1][4]=x[1][0]-h;
    y[4]=df(x[0][4],x[1][4]);
    }
    t=0;
    int j, l=1;
    for (j=1; j<5; j++) {
      if (y[j]<y[l]) {
        l=j;
      }
    }
    if (y[l]<y[0]) {
      if (l>2) {
        x[0][l-2] = x[0][0];
        x[1][l-2] = x[1][0];
        y[l-2] = y[0];
        t=l-2;
      }
      else {
        x[0][l+2]=x[0][0];
        x[1][l+2]=x[1][0];
        y[l+2]=y[0];t=l+2;
      }
      x[0][0]=x[0][l];x[1][0]=x[1][l];y[0]=y[l];
      if (i==0) fprintf(file, "%f\t%f\n", x[0][0], x[1][0]); 
      k++;
      goto metka;
    }
    else {
      h/=2;
      if (h>e[i]) {
        k++;
        goto metka;
      }
      else {
        double x1min, x2min, ymin;
        x1min = x[0][0]; x2min = x[1][0];
        ymin = y[0];
        fprintf(file, "%f\t%f\t%f\t%d\t%d\n", 
               x1min, x2min, ymin, N0, k);
      }
    }



}

int
main() {
  FILE *file = fopen("result/obrazec.txt", "w+");
  for (i=0; i < 5; i++) {
  printf("Iteration %d with e = %lf\n", i+1, e[i]);
  obrazec(file);
  }
  fclose(file);
  return 0;
}