#include <stdio.h>
#include <stdlib.h>
#include "sampler.h"
#include "entropy.h"
#include "poly.h"
#include "L2RS.h"


void LRCT_Setup_Test()
{
    const int omega = 5;
    poly A[RINGCT_M], H[RINGCT_M]; //todo: maybe special Matrix struct?
    poly S[RINGCT_M];
    poly S_pi[RINGCT_M];
    poly L[omega];
    poly h;
//    poly u[3];
    poly c1;
    poly* t[2];
    unsigned char msg[2] = { 0x01, 0x02 }; //-V808
    int msgLen = 2;
//    unsigned char bt[RINGCT_POLYBYTES] = { 0 };
    size_t i = 0;
    size_t k = 0;
    int result = 0;
    int pi = 1;

    entropy_t entropy;
    sampler_t sampler;
    unsigned char entropy_seed[SHA3_512_DIGEST_LENGTH] = {0xff};
    entropy_init(&entropy, entropy_seed);
    sampler_init(&sampler, RINGCT_SIGMA, 0, 0, &entropy);

    t[0] = (poly *)malloc((3) * sizeof(poly));
    t[1] = (poly *)malloc((3) * sizeof(poly));

    //add check for malloc

    for (i = 0; i < 2; i++)
    {
        for (k = 0; k < 3; k++)
        {
            poly_init(t[i] + k);
        }

    }
    L2RS_setup(A, H, &entropy);
    //debug

//    poly_print(A);
//    poly_print(A+1);
//    printf("\n");
//    poly_print(H);
//    poly_print(H+1);

    //end debug

    printf("pi = %d\n", pi);

    for (int i = 0; i<omega; i++){
        L2RS_keyGen(L+i, S, A, &entropy);
//        poly_print(S);
//        poly_print(S+1);
//        printf("==\n");
        if (i == pi) {
            for (int j = 0; j<RINGCT_M; j++) {
                poly_cofcopy(S_pi+j, S+j);
            }
        }
    }

    //debug
//
//    for(int i = 0; i<omega; i++) {
//        poly_print(L+i);
//    }

    //end debug


    L2RS_sigGen(&c1, t, &h, S_pi, (char *) msg, msgLen, L, H, A, pi, &entropy, NULL);


//    L2RS_SampleKey(S, 2);
//    L2RS_KeyGen(L, A, S, 2);
//    L2RS_SampleKey(S, 2);
//    L2RS_KeyGen(L+1, A, S, 2);

    for (k = 0; k < 3; k++)
    {

        // u[k] = gaussian poly
//        randombytes(bt, RINGCT_POLYBYTES);
//        poly_frombytes(u + k, bt);
//        poly_serial(u + k);
        ///poly_print(u+k);
    }
    //printf("====================================\n");
//    L2RS_SigGen(&c1, t, &h, A, H,S, u, mLen, L, w,pai, msg, msgLen);
    //printf("c1\n");
//	poly_print(&c1);
    //printf("=================\n");
//    result = L2RS_SigVer(&c1, t, A, H, mLen, &h, L,w, msg, msgLen);
//    if (result ==1)
//    {
//	   printf("Successful!\n");
//    }
//    else
//    {
//        printf("fail\n");
//    }
    free(t[0]);
    free(t[1]);

}


int main() {
    entropy_t entropy;
    sampler_t sampler;
//
//
    unsigned char seed[SHA3_512_DIGEST_LENGTH] = {0xff};
//
//
    entropy_init(&entropy, seed);
    sampler_init(&sampler, 283754, 42, 100, &entropy);
//
//    for (int i = 0; i<10; i++) {
//        printf("%d ", sampler_gauss(&sampler));
//    }

    LRCT_Setup_Test();



    return 0;
}
