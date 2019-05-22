/* answers the question: can we use omp_get functions outside of
 * a parallel region? You may say "of course", but it really does need a test and this is it.
*/
#include <iostream>
#include <omp.h>

using namespace std;

int main()
{
	// omp_get_max_threads() and many other functions are declared in omp.h
	int mxt = omp_get_max_threads();
	cout << "OpenMP will use " << mxt << " threads maximum." << endl;
	return 0;
}

// XXX: execute with OMP_NUM_THREADS=2 and OMP_NUM_THREADS=3
