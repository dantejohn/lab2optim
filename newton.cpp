#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define Aa 2
#define Bb -1.3
#define C 0.02
#define D 0.14


int N = 0, N0 = 0, N1 = 0, N2 = 0, k = 0, ii;
double e[5] = {0.1, 0.01, 0.001, 0.0001, 0.00001};

double df(double x1, double x2);
double dfx1(double x1, double x2);
double dfx2(double x1, double x2);
double dfx1x1(double x1, double x2);
double dfx1x2(double x1, double x2);
double dfx2x2(double x1, double x2);
double W(double alfa, double x[2][2], double p[2]);
double DihMet(double a,double b,double E2, double xa[1][2],double p[2]);
void newtonopt (FILE *file);

int
main() {
    FILE *file = fopen("result/newtonOPT.txt", "w+");
  for (ii=0; ii < 5; ii++) {
  printf("Iteration %d with e = %lf\n", ii+1, e[ii]);
  newtonopt(file);
}
fclose(file);
return 0;
}

void newtonopt(FILE *file)
{
        double x[2][2],y[2];
        x[0][0]=1;
        x[0][1]=0;
        double f1[2],f2[2][2],p[2],d;
        f1[0]=dfx1(x[0][0],x[0][1]);
        f1[1]=dfx2(x[0][0],x[0][1]);
        int n=0;
        double alfa=0.05,a,b,h=0.05;
        do
        {
                n++;
                f2[0][0]=dfx1x1(x[0][0],x[0][1]);
                f2[0][1]=dfx1x2(x[0][0],x[0][1]);
                f2[1][0]=f2[0][1];
                f2[1][1]=dfx2x2(x[0][0],x[0][1]);

                p[1]=(f1[1]-f1[0]*f2[1][0]/f2[0][0])/(f2[1][1]-f2[0][1]*f2[1][0]/f2[0][0]);
                p[0]=(f1[0]-p[1]*f2[0][1])/f2[0][0];

                k=0;
                y[1]=df(x[0][0],x[0][1]);
                do
                {
                  y[0]=y[1];
                  y[1]=W((k+1)*h,x,p);
                  k++;
                }
                while(y[1]>y[0]);
                b=k*h;
                if(k==1)
                {
                  a=0;
                }
                else
                {
                  a=(k-2)*h;
                }
                alfa=DihMet(a,b,e[ii],x,p);

                x[1][0]=x[0][0]-alfa*p[0];
                x[1][1]=x[0][1]-alfa*p[1];
                    if (ii==0) {
      fprintf(file, "%f\t%f\n", x[1][0], x[1][1]);
    } 
                f1[0]=dfx1(x[1][0],x[1][1]);
                f1[1]=dfx2(x[1][0],x[1][1]);
                x[0][0]=x[1][0];
                x[0][1]=x[1][1];
                d=sqrt(pow(f1[0],2)+pow(f1[1],2));
        }
        while(d>e[ii]);
        fprintf(file, "%lf\t%lf\t%lf\t%d\t%d\t%d\t%d\t%d\n",
                  x[1][0], x[1][1], df(x[1][0],x[1][1]), N0-1, N1, N2, N0+N1+N2-1, k);
}

double
df (double x1, double x2) 
{
  N0++;
  return Aa * x1 + Bb * x2 + exp(C * pow(x1, 2) + D * pow(x2, 2));
}

double
dfx1 (double x1, double x2) 
{
  N1++;
  return Aa + 2 * C * x1 * exp(C * pow(x1, 2) + D * pow(x2, 2));
}

double
dfx2 (double x1, double x2) 
{
  N1++;
  return Bb + 2 * D * x2 * exp(C * pow(x1, 2) + D * pow(x2, 2));
}

double
dfx1x1 (double x1, double x2) 
{
  N2++;
  return (pow(2 * C, 2) * pow(x1, 2) + 2 * C) * exp(C * pow(x1, 2) + D * pow(x2, 2));
}

double
dfx2x2 (double x1, double x2) 
{
  N2++;
  return (pow(2 * D, 2) * pow(x2, 2) + 2 * D) * exp(C * pow(x1, 2) + D * pow(x2, 2));
}

double
dfx1x2 (double x1, double x2) 
{
  N2++;
  return 4 * C * D * x1 * x2 * exp(C * pow(x1, 2) + D * pow(x2, 2));
}

double W(double alfa, double x[1][2], double p[2])
{
        double W=df(x[0][0]-alfa*p[0],x[0][1]-alfa*p[1]);
        return W;
}

double DihMet(double a,double b,double E2, double xa[1][2],double p[2])
{
  double f[2],l;
  double r;
  r=E2/100;
  do
  {
    l=(a+b)/2;
    f[0]=W(l-r,xa,p);
    f[1]=W(l+r,xa,p);
    if(f[0]<f[1])
      b=l+r;
    else
      a=l-r;
  }
  while(b-a>2*E2);
        return (a+b)/2;
}