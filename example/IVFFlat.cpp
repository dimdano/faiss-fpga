#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <faiss_fpga/IndexFlat.h>
#include <faiss_fpga/IndexIVFFlat.h>

int main() {
    int d = 192;                            // dimension (do not change)
    int nb = 500000;                       // database size
    int nq = 1000;                        // number of queries

    float *xb = new float[d * nb];
    float *xq = new float[d * nq];

    //assign random data
    for(int i = 0; i < nb; i++) {
        for(int j = 0; j < d; j++)
            xb[d * i + j] = drand48();
        xb[d * i] += i / 1000.;
    }

    //assign random queries
    for(int i = 0; i < nq; i++) {
        for(int j = 0; j < d; j++)
            xq[d * i + j] = drand48();
        xq[d * i] += i / 1000.;
    }


    int nlist = 512;	//Inverted List size
    int k = 10;		//Nearest Neighbors
    
    //FAISS IVFFlat index
    faiss::IndexFlatL2 quantizer(d);       
    faiss::IndexIVFFlat index(&quantizer, d, nlist, faiss::METRIC_L2);
    assert(!index.is_trained);
    //train Index
    index.train(nb, xb);
    assert(index.is_trained);
    index.add(nb, xb);

    	printf("*********************\n");
	printf("**Nearest Neighbors**\n");
    	printf("*********************\n");
   
       	{
        long *I = new long[k * nq];
        float *D = new float[k * nq];

	index.nprobe = 10;		// specify search space
        index.search(nq, xq, k, D, I);	// Neighbor Search

        /*printf("Results for last 5 queries\n");
        for(int i = nq - 5; i < nq; i++) {
            printf("NN %d: ", i);
	    for(int j = 0; j < k; j++)
                printf("%5ld ", I[i * k + j]);
            printf("\n");
        }*/

        printf("Results for first 5 queries\n");
        for(int i = 0; i < 5; i++) {
           	printf("NN %d: ", i);
	       	for(int j = 0; j < k; j++)
                printf("%5ld ", I[i * k + j]);
            printf("\n");
        }


        delete [] I;
        delete [] D;
    }



    delete [] xb;
    delete [] xq;

    return 0;
}
