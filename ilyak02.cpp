/* From ilyak/openmp-tutorial 02-parallel
 Immediately rang into trouble here: */ 
#include <iostream> // cout and endl wouldn't work without this.
#include <vector>
#include <string>
#include <omp.h>

#define STRSZ 128

using namespace std;

int main(void)
{
    int j, t, mxt = omp_get_max_threads();
    char s[STRSZ];
    vector<string> msgs(mxt);
    #pragma omp parallel shared(msgs, mxt) private(t, s)
    {
        // this will be executed in parallel by N threads
        // printf("Hello from thread %d of %d\n", omp_get_thread_num(), omp_get_num_threads());
        t = omp_get_thread_num();
        // msgs[t].assign("Hello from thread %d of %d\n", t, mxt);
        #pragma omp for
        for(j=0;j<mxt;++j) {
            sprintf(s, "Hello from thread %d of %d", t, mxt);
            // msgs[j].assign("Hello from thread %d of %d\n", t, mxt);
            msgs[j] = s;
        }
    }


    unsigned i;
    for(i = 0; i < msgs.size(); i++)
        cout << msgs[i] << endl; // why is endl not accepted? You didn't have iostream included.

    return 0;
}

// XXX: execute with OMP_NUM_THREADS=2 and OMP_NUM_THREADS=3
// XXX: add num_threads(5) to pragma omp parallel
