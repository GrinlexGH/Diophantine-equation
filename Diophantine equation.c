#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int iabs(int a) { return (a < 0) ? -a : a; }

int eu_mod(int a, int b) {
  int r;
  assert(b != 0);
  r = a % b;
  if (r < 0)
    r += iabs(b);
  return r;
}

int eu_div(int a, int b) {
  int q;
  assert(b != 0);
  q = a / b;
  if (a % b < 0 && b < 0)
    q += 1;
  else if (a % b < 0)
    q -= 1;
  return q;
}

int gcd(int a, int b) {
  int q;
  q = eu_mod(a, b);
  while(q != 0) {
    a = b;
    b = q;
    q = eu_mod(a, q);
  }
  return b;
}

int gcd_ext(int a, int b, int* x, int* y) {
  int r2;
  int x0 = 1, x1 = 0, y0 = 0, y1 = 1;

  r2 = eu_mod(a, b);
  *x = x0 - x1 * eu_div(a, b);
  *y = y0 - y1 * eu_div(a, b);

  if(r2 == 0) {
    *x = 0;
    *y = 1;
  }

  while(r2 != 0) {
    a = b;
    b = r2;
    r2 = eu_mod(a, r2);

    if(r2 != 0) {
      x0 = x1;
      x1 = *x;
      *x = x0 - x1 * eu_div(a, b);

      y0 = y1;
      y1 = *y;
      *y = y0 - y1 * eu_div(a, b);
    }
  }
  return b;
}

void lde(int a, int b, int c, int* x, int* y) {
    int d;
    d = gcd_ext(a, b, &*x, &*y);
    *x = (c/d) * (*x);
    *y = (c/d) * (*y);
}

int main(void) {
  int a = 0, b = 0, c = 0, x, y, d, u, v;
  int res;

  printf("Enter values of a, b, and c in equation ax + by = c: \n");
  res = scanf("%i %i %i", &a, &b, &c);
  assert(res == 3);

  d = gcd_ext(a, b, &x, &y);
  printf("GCD(%i, %i) = %i\n", a, b, d);

  printf("Bézout's coefficients for equation %ix + %iy = %i: x = %i, y = %i\n", a, b, d, x, y);

  if(c % gcd(a, b) != 0) {
    printf("Linear diophantine equation %iu + %iv = %i is not solvable\n", a, b, c);
    return 0;
  }

  lde(a, b, c, &u, &v);
  printf("Coefficients for linear diophantine equation %iu + %iv = %i: u = %i, v = %i\n", a, b, c, u, v);

  return 0;
}
