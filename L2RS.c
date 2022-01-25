//
// Created by Evgeniy Kramsakov on 14.01.2022.
//

#include "L2RS.h"
#include "matrix.h"

void L2RS_setup(poly* A, poly* H, entropy_t* entropy, uint64_t mLen) {
//    A = R_q_m1([Rq([randint(0, q) for i in range(n+1)]) for j in range(m-1)])
//    H = R_q_m1([Rq([randint(0, q) for i in range(n+1)]) for j in range(m-1)])
//    return (A, H)
    for (int i = 0; i<mLen; i++) {
        poly_uniform(A + i, entropy);
        poly_uniform(H + i, entropy);
//        for (int j = 0; j<RINGCT_N; j++) {
//
////            A[i].coeffs[j] = entropy_random_uint64(entropy)%RINGCT_Q;
////            H[i].coeffs[j] = entropy_random_uint64(entropy)%RINGCT_Q;
//        }
    }
}

void L2RS_keyGen(poly* a, poly* S, poly* A, entropy_t* entropy, uint64_t mLen) {
//    S = R_q_m1([Rq([randint(-2^ceil(gamma), 2^ceil(gamma)) for i in range(n+1)]) for j in range(m-1)]).transpose()
//    a = (A * S)[0].Mod(q)
//    return a, S
    uint64_t tmp;
    for (int i = 0; i<mLen; i++) {
        for (int j = 0; j<RINGCT_N; j++) {
#if RINGCT_GAMMAPOWER <= 65535
            tmp = entropy_random_uint16(entropy) % RINGCT_GAMMAPOWER;
#else
            tmp = entropy_random_uint64(entropy) % RINGCT_GAMMAPOWER;
#endif
            if (entropy_random_bit(entropy)) {
                S[i].coeffs[j] = RINGCT_Q - tmp;
            }
            else {
                S[i].coeffs[j] = tmp;
            }
        }
    }
    // A as a row, and S is a column. output a is a row
    matrix_matrix_mul_poly(a, A, S, mLen);

}