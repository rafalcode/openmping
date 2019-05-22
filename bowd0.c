//compute the sum of two arrays in parallel 
//// from http://www.bowdoin.edu/~ltoma/teaching/cs3225-GIS/fall17/Lectures/openmp.html
#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

#define N 1000000

int main(void) 
{ 
    // float a[N], b[N], c[N]; // would work with c99 yes
    float *a=malloc(N*sizeof(float));
    float *b=malloc(N*sizeof(float));
    float *c=malloc(N*sizeof(float));
    int i;

    /* Initialize arrays a and b */
    for (i = 0; i < N; i++) {
        a[i] = (i+1) * 2.0;
        b[i] = (i+1) * 3.0;
    }

    /* Compute values of array c = a+b in parallel. */
    #pragma omp parallel shared(a, b, c) private(i)
    { 
        #pragma omp for             
        for (i = 0; i < N; i++)
            c[i] = a[i] + b[i];
    }
    printf("One example value at index 10:\n"); 
    printf ("%4.4f\n", c[10]);

    free(a);
    free(b);
    free(c);

    return 0;
}
