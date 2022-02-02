//
// Created by Evgeniy Kramsakov on 14.01.2022.
//

#include "L2RS.h"
#include "matrix.h"

void L2RS_lift(poly* A_lifted, poly* A, poly* a) {
    for (int i = 0; i<RINGCT_M; i++) {
        poly_constmul(A_lifted + i, A + i, 2, RINGCT_2Q);
    }
    for (int i = 0; i<RINGCT_N; i++) {
        A_lifted[RINGCT_M].coeffs[i] = (RINGCT_2Q + RINGCT_Q - a->coeffs[i] * 2) % RINGCT_2Q; // -2a + q
    }
}

void L2RS_setup(poly* A, poly* H, entropy_t* entropy) {
//    A = R_q_m1([Rq([randint(0, q) for i in range(n+1)]) for j in range(m-1)])
//    H = R_q_m1([Rq([randint(0, q) for i in range(n+1)]) for j in range(m-1)])
//    return (A, H)
    for (int i = 0; i<RINGCT_M; i++) {
        poly_uniform(A + i, entropy);
        poly_uniform(H + i, entropy);
    }
}

void L2RS_keyGen(poly* a, poly* S, poly* A, entropy_t* entropy) {
//    S = R_q_m1([Rq([randint(-2^ceil(gamma), 2^ceil(gamma)) for i in range(n+1)]) for j in range(m-1)]).transpose()
//    a = (A * S)[0].Mod(q)
//    return a, S
    uint64_t tmp;
    for (int i = 0; i<RINGCT_M; i++) {
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

    //debug
//    poly_print(S);
//    poly_print(S+1);
    //end of debug

    matrix_matrix_mul_poly(a, A, S);

    //debug
//    poly_print(a);

}


void
L2RS_sigGen(poly *c1, poly *ts[2], poly *h, poly *S_pi, char *mu, uint64_t mu_len, poly *L, poly *H, poly *A, int pi,
            entropy_t *entropy, sampler_t *sampler) {
//    h = (H*S_pi)[0]
//    hh = h.change_ring(R2q)
//    HH = H.change_ring(R2q)
//    H2q = R_2q_m([elem for elem in (2*HH)[0]] + [-2 * hh[0] + R2q(q)])
//    S2qpi = R_2q_m([elem for elem in S_pi.columns()[0]] + [1]).transpose()
//    A2qpi = lift(A, L[pi])
//    upi = R_2q_m([gaussian_poly() for _ in range(m)]).transpose()
//    c = omega * [0]
//    if pi == omega-1:
//    index = 0
//    else:
//    index = pi+1
//    c[index] = H1(L, H2q, mu, A2qpi*upi, H2q*upi)
//    t = omega * [m * [0]]
//
//    for i in range(pi+1, omega):
//    t[i] = R_2q_m([gaussian_poly() for _ in range(m)]).transpose()
//    if i == omega-1:
//    index = 0
//    else:
//    index = i+1
//    A2qi = lift(A, L[i])
//    c[index] = H1(L, H2q, mu, A2qi * t[i] + R2q(q)*c[i], H2q * t[i] + R2q(q) * c[i])
//    for i in range(0, pi):
//    t[i] = R_2q_m([gaussian_poly() for _ in range(m)]).transpose()
//    if i == omega-1:
//    index = 0
//    else:
//    index = i+1
//    A2qi = lift(A, L[i])
//    c[index] = H1(L, H2q, mu, A2qi * t[i] + R2q(q)*c[i], H2q * t[i] + R2q(q) * c[i])
//
//
//    t[pi] = upi + S2qpi * c[pi] * (-1)^(randint(0,1))
//# t[pi] = upi + S2qpi * c[pi] * 1 # (-1)^(randint(0,1))
//
//# Should use Rejection sampling
//
//    return c[0], t, h

    poly H2q[RINGCT_M+1];
    poly A2qpi[RINGCT_M+1];
    poly S2qpi[RINGCT_M+1];
    poly upi[RINGCT_M+1];

    matrix_matrix_mul_poly(h, H, S_pi);

    //debug
//    poly_print(h);
    //end debug
    L2RS_lift(H2q, H, h);
    //debug
//    for (int i = 0; i<RINGCT_M+1; i++) {
//        poly_print(H2q+i);
//    }
    //end debug

    for (int i = 0; i<RINGCT_M; i++) {
        poly_cofcopy(S2qpi+i, S_pi+i);
    }
    poly_init(S2qpi+RINGCT_M);
    S2qpi[RINGCT_M].coeffs[0] = 1;
    //debug
//    for (int i = 0; i<RINGCT_M+1; i++) {
//        poly_print(A2qpi+i);
//    }
    //end debug

    L2RS_lift(A2qpi, A, L+pi);
    //debug
//    for (int i = 0; i<RINGCT_M+1; i++) {
//        poly_print(A2qpi+i);
//    }
    //end debug

    for (int i = 0; i<RINGCT_M+1; i++) {
        poly_gaussian(upi, sampler);
    }

}