/* Ode to pthreads:
 * When parallel programing was but a pup
 * before beowulfs, infinibands and Mare Nostrums
 * you came into the light, ... reluctantly
 * Now in the age of gpgpus, mpi and larrabees
 * Your complicated ways are often
 * the only answer to full cpu occupation! */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define MAXTHRDS 124

/* we wrap our "pthread-necessary" variables in a struct */
typedef struct {
    double *A;
    double *my_B;
    double *my_MM;
    double *glob_jnorm;
    double my_jnorm;
    pthread_mutex_t *mutex;
    int my_N;
    int N; /*  dimMat would have been a better name, but ... */
} MM_t;

double GetTime()
{
    /* use microsecond resolution of sys/time.h */
    struct timeval time;
    gettimeofday(&time,NULL);
    return ((double)(time.tv_sec)+(double)(time.tv_usec)/1000000);
}

void initMat( int M, int N, double mat[], double val )
{
    int i, j;
    for (i= 0; i< M; i++)
        for (j= 0; j< N; j++)
            mat[i*N+j] = val;
}

void *serial_MM(void *arg)
{
    int i, j, k;
    double norm;
    MM_t *Md; // declare variable on our struct typedef

    Md = arg;
    Md->my_jnorm = 0.0;
    for(j=0; j< Md->my_N; j++){
        norm = 0.0;
        for(i=0; i< Md->N; i++){
            for(k=0; k< Md->N; k++){
                // it's important in the next line to move the i-index by the original column span of B and MM
                // and NOT the column span of the submatrix. That's why you see Md->N's exclusively here.
                Md->my_MM[i*Md->N+j] += Md->A[i*Md->N+k] * Md->my_B[k*Md->N+j];
            }
            norm += Md->my_MM[i*Md->my_N+j];
        }
        if (norm > Md->my_jnorm)
            Md->my_jnorm = norm;
    }
    if (Md->my_jnorm > *(Md->glob_jnorm)){
        pthread_mutex_lock(Md->mutex);
        *(Md->glob_jnorm) = Md->my_jnorm;
        pthread_mutex_unlock(Md->mutex);
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    // declare variables for main
    double *A, *B, *MM, jnorm, start, end;
    void *status; /*  an archetypal pointer to void */
    pthread_t *working_thread;
    pthread_mutex_t *mutex_jnorm;
    MM_t *thrd_Md; // declare variable based on the struct typedef

    int N, subN, num_of_thrds;

    /* argument accounting */
    if(argc!=3) {
        printf("Usage error. Pls supply 2 args: first, number of threads, second, dimension of (test) matrix.\n");
       exit(EXIT_FAILURE);
    }
    num_of_thrds=atoi(argv[1]);
    N=atoi(argv[2]);

    subN = N/num_of_thrds;

    //allocate and initialize arrays
    A = malloc (N*N*sizeof(double));
    B = malloc (N*N*sizeof(double));
    MM = malloc (N*N*sizeof(double));
    if (!A || !B || !MM) {
        printf( "Out of memory, reduce N value.\n");
        exit(-1);
    }
    initMat(N, N, A, 1.0);
    initMat(N, N, B, 1.0);
    initMat(N, N, MM, 0.0);

    start= GetTime();

    // mem alloc for the threads
    working_thread = malloc(num_of_thrds*sizeof(pthread_t));
    thrd_Md=malloc(num_of_thrds*sizeof(MM_t));
    mutex_jnorm = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(mutex_jnorm, NULL);

    int t;
    /*  pthreads works by creating a simple serial forloop and setting them off in quick succession */
    for(t=0; t<num_of_thrds; t++){
        thrd_Md[t].A = A;
        thrd_Md[t].my_B = B + t*subN; /* one strip of B allocated */
        thrd_Md[t].my_MM = MM + t*subN; // only locates submatrix starting point, nothing else.
        thrd_Md[t].glob_jnorm = &jnorm;
        thrd_Md[t].mutex = mutex_jnorm;
        thrd_Md[t].my_N = (t==num_of_thrds-1)? N-(num_of_thrds-1)*subN : subN;
        thrd_Md[t].N = N;
        /*  finally, once thrd_Md is all set up, the line that does all the work */
        pthread_create(&working_thread[t], NULL, serial_MM, (void*)&thrd_Md[t]);
        /*  yes, that's a function ptr you see, don't forget that fn serial_MM returns a ptr to void 
         *  because its argument id also a void*, we can get away with calling it with zero args */
    }

    for(t=0; t<num_of_thrds; t++){
        pthread_join(working_thread[t], &status);
    }
    // end = time(NULL); //end timing
    end = GetTime();

    // printf("Dot product = %f\n", MM);
    printf("\nThe infinity (aka. column) norm of two multiplied matrices = %f\n", jnorm);
    printf("elapsed = %f\n", end-start);

    free(A);
    free(B);
    free(MM);
    free(working_thread);
    free(thrd_Md);
    pthread_mutex_destroy(mutex_jnorm);
    free(mutex_jnorm);

    return 0;
}
