#include <stdio.h>
#include <stdlib.h>
#include "sampler.h"
#include "entropy.h"
#include "poly.h"
#include "L2RS.h"


void LRCT_Setup_Test()
{
    poly A[2], H[2];
    poly S[2];
    poly L[2];
    poly h;
    poly u[3];
    poly c1;
    poly* t[2];
    unsigned char msg[2] = { 0x01, 0x02 }; //-V808
    int msgLen = 2;
//    unsigned char bt[RINGCT_POLYBYTES] = { 0 };
    size_t mLen = 2;
    size_t i = 0;
    size_t k = 0;
    int result = 0;
    int w = 2;
    int pai = 1;

    entropy_t entropy;
    unsigned char entropy_seed[SHA3_512_DIGEST_LENGTH] = {0xff};
    entropy_init(&entropy, entropy_seed);

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
    L2RS_setup(A, H, &entropy, 2);
    L2RS_keyGen(L, S, A, &entropy, mLen);
//    L2RS_Setup(A, H, 2);
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

//    LRCT_Setup_Test();

    //want to NTT^-1(NTT(a)) == a


    poly a, b, c;
    poly_uniform(&a, &entropy);
    poly_uniform(&b, &entropy);
    poly_init(&c);
    poly_print(&a);
    poly_print(&b);
    poly_print(&c);
    printf("\n\n");

    poly_ntt(&a);
    poly_ntt(&b);
    poly_print(&a);
    poly_print(&b);
    poly_print(&c);
    printf("\n\n");

    poly_invntt(&a);
    poly_invntt(&b);
    poly_print(&a);
    poly_print(&b);
    poly_print(&c);
    printf("\n\n");


//    poly_mul_pointwise(&c, &a, &b);
//    poly_print(&a);
//    poly_print(&b);
//    poly_print(&c);
//    printf("\n\n");
//    poly_invntt(&c);
//    poly_print(&a);
//    poly_print(&b);
//    poly_print(&c);
//    printf("\n\n");


    return 0;
}
