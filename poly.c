// poly.c - initial version of the polynomial evaluation


/* purpose: evaluate a polynomial a_0 + _a1 x + a_2 x^2 + ... + a_n x^n
 * input:   the coefficients a, value for x, the degree of the polynomial, and
            a pointer for the result value.
 * output:  the value of the polynomial at x
 */
void poly0(long a[], long x, long degree, long *value)
{
  long i;
  *value = a[0];

  for(i=1; i<= degree; i++)
  {
    int j;
    long x_to_the_i = 1;
    for(j=0; j<i; j++)
      x_to_the_i *= x;

    (*value) += a[i] * x_to_the_i;
  }
}



/* start by cloning poly0 to the function poly and then work on 
 * making poly crazy fast.
 */
void poly(long a[], long x, long degree, long *value)
{
  long i;
  *value = a[0];

  for(i=1; i<= degree; i++)
  {
    int j;
    long x_to_the_i = 1;
    for(j=0; j<i; j++)
      x_to_the_i *= x;

    (*value) += a[i] * x_to_the_i;
  }
}


