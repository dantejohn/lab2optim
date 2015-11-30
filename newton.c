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
int N0, N1, N2, N, k, i;


double
df (double x1, double x2) {
  N0++;
  return Aa * x1 + Bb * x2 + exp(C * pow(x1, 2) + D * pow(x2, 2));
}

double
dfx1 (double x1, double x2) {
  N1++;
  return Aa + 2 * C * x1 * exp(C * pow(x1, 2) + D * pow(x2, 2));
}

double
dfx2 (double x1, double x2) {
  N1++;
  return Bb + 2 * D * x2 * exp(C * pow(x1, 2) + D * pow(x2, 2));
}

double
dfx1x1 (double x1, double x2) {
  N2++;
  return (pow(2 * C, 2) * pow(x1, 2) + 2 * C) * exp(C * pow(x1, 2) + D * pow(x2, 2));
}

double
dfx2x2 (double x1, double x2) {
  N2++;
  return (pow(2 * D, 2) * pow(x2, 2) + 2 * D) * exp(C * pow(x1, 2) + D * pow(x2, 2));
}

double
dfx1x2 (double x1, double x2) {
  N2++;
  return 4 * C * D * x1 * x2 * exp(C * pow(x1, 2) + D * pow(x2, 2));
}

double fi(int ki,double dalf,double x1,double x2,double z)

{return df(x1-dalf*z,x2);}

void
newtonopt() {
  double x[1000][2];
  double y[2][2];
  k=0, N1 = 0; N2 = 0; N0 = 0;
  int l,j;
  double y1, y2, del, det, p1, p2;
  int n = 10;
  double m, a1, b1, ym1, ym2, min, ma, kan;
  double dalf = 1;
  x[0][0] = -1;
  x[0][1] = 0;
  y1 = dfx1 (x[0][0], x[0][1]);
  y2 = dfx2 (x[0][0], x[0][1]);

  p1:
    y[0][0] = dfx1x1(x[k][0], x[k][1]);
    y[0][1]=dfx1x2(x[k][0],x[k][1]);
    y[1][0]=y[0][1];
    y[1][1]=dfx2x2(x[k][0],x[k][1]);
    det = y[0][0]*y[1][1]-y[0][1]*y[1][0];
    p1=(y1*y[1][1]-y2*y[0][1])/det;
    p2=(y[0][0]*y2-y[1][0]*y1)/det;
    m=0;
    ym1 = df(x[k][0], x[k][1]);
  ab:
    ym2 = fi(k, dalf*(m+1), x[k][0], x[k][1], y1);
    if (ym2<ym1)
{m++;ym1=ym2;goto ab;}
else
{ b1=(m+1)*dalf;
if (m==0) a1=0; else a1=(m-1)*dalf;}
ma=a1+(b1-a1)/n;
min=df(x[k][0]-ma*y1,x[k][1]-ma*y2);N1++;
l=1;
for (j=2;j<=n;j++)
{ ma=a1+j*(b1-a1)/n;
kan=df(x[k][0]-ma*y1,x[k][1]-ma*y2);N1++;
if (min>kan) {min=kan;l=i;}
}
x[k+1][0]=x[k][0]-(l*(b1-a1)/n)*p1;

x[k+1][1]=x[k][1]-(l*(b1-a1)/n)*p2;

y1=dfx1(x[k][0],x[k][1]);
y2=dfx2(x[k][1],x[k][2]);
N0-=2;
del=pow(y1*y1+y2*y2,0.5);
k++;
if (del > e[i]) goto p1;
else
{
  printf ("x1 = %lf\n x2 = %lf\n y = %lf\n N0 = %d\n N1 = %d\n N2 = %d\n N = %d\n k = %d\n",
          x[k][0], x[k][1], df(x[k][0], x[k][1]), N0-1, N1, N2, N-1, k);

}
}


int
main() {
  for (i=0; i < 5; i++) {
  printf("Iteration %d with e = %lf\n", i+1, e[i]);
  newtonopt();
}
return 0;
}