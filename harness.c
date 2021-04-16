// CPE calculation test harness for polynomial evaluation code

#include <stdio.h>
#include <stdlib.h>
#include "cpe.h"

extern void poly(long a[], long x, long degree, long *value);
extern void poly0(long a[], long x, long degree, long *value);

static const int MAX_DEGREE=973;
static const int SAMPLES=200;
static const int X_VALUE=3;

// call back from CPE calculation requires "passing" these two 
// variables as file globals
static long *as;
static long poly_value;
static int count_used;

/* Used to make sure code doesn't get optimized away */
volatile long sink; 

/* purpose: initialize the polynomial's coefficients
 * input:   nothing
 * output:  coefficients a_i are given random values (either -1 or 1)
 */
static void setup()
{
  long i;
  as = (long *) malloc((MAX_DEGREE+1) * sizeof(long));

  for (i = 0; i <= MAX_DEGREE; i++)           /* Initialize array  */
    as[i] = (random() & 0x1) ? 1 : -1;

  sink = (long) 0;
}


/* purpose: print a polynomial 
 * input:   the coefficients a, the degree of the polynomial, and
 *          a post print message (e.g., an optional "\n")
 * output:  nothing (printing is a side effect)
 */
void print_poly(long a[], long degree, char *tail)
{
  long i;
  printf("%ld ", a[0]);
  for(i=1; i<=degree; i++)
    printf(" + %ldx^%ld ", a[i], i);

  printf("%s", tail);
}


/* purpose: test the polynomial evaluation
 * input:   none, old test was hard coded, new is that from cpe calc
 * output:  1 if poly matches the reference
 */
int test()
{
  long *ts = as;//{2, 4, 6};  // 2 + 4x + 6x^2
  long degree = MAX_DEGREE; //sizeof(ts)/sizeof(long) - 1;
  long v1 = 0;
  long v2 = 0;  

  poly0(ts, X_VALUE, degree, &v1);
  poly(ts, X_VALUE, degree, &v2);

  return v1 == v2;
}


/* purpose: call-back from the CPE calculating code
 * input:   the number of elements to use
 * output:  nothing 
 */
void run_p(long count) 
{
  count_used = count;
  poly(as, X_VALUE, count, &poly_value);
}
   


int main()
{
  setup();
  // test(); exit(0);

  FILE *f = NULL; // fopen("log", "w");
  double cpe = find_cpe_full(run_p, MAX_DEGREE, SAMPLES, f, RAN_SAMPLE, 0.3, 2);
  printf("Poly pace %.2f cycles per element\n", cpe);
  if (test()){
     printf("Poly still works\n");
  } else {
     printf("You broke poly\n");
  }

  return 0;
}

