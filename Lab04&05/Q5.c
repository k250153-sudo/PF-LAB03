#include <stdio.h>
#include <math.h>

int main() {
  double a, b, c,D;

  printf("The format of a quadratic equation is ax^2 + bx + c\nPlease enter a, b and c: ");
  scanf("%lf %lf %lf", &a, &b, &c);


  if (a==0) {
    printf("This is not a quadratic equation");
  }
  else {
    D = b*b- 4*a*c;
    if (D>0) {
      double x1 = (-b + sqrt(D)) / (2*a);
      double x2 = (-b - sqrt(D)) / (2*a);
      printf("There are two real and distinct solutions. Solutions %.2lf,%.2lf ", x1, x2);
    }
    else if (D<0) {

      double real = -b / (2*a);
      double imag = sqrt(-D) / (2*a);
      printf("Two complex roots: %.2lf + %.2lfi and %.2lf - %.2lfi\n", real, imag, real, imag);
    }
    else {
      double x = -b / (2*a);
      printf("There are two real and equal roots.Root = %.2lf",x);
    }
  }

}
