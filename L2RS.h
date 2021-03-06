//
// Created by Evgeniy Kramsakov on 14.01.2022.
//

#ifndef RINGCT_REWORK_L2RS_H
#define RINGCT_REWORK_L2RS_H

#include "poly.h"
#include "entropy.h"

void H1(poly* hash, poly* L, poly* H2q, char* mu, uint64_t mu_len, poly* A2qpi_mult, poly* H2q_mult); // L, H2q, mu, A2qpi_mult, H2q_mult
void L2RS_setup(poly* A, poly* H, entropy_t* entropy); //paramset?
void L2RS_keyGen(poly* a, poly* S, poly* A, entropy_t* entropy);
void L2RS_lift(poly* A_lifted, poly* A, poly* a);
void
L2RS_sigGen(poly *c1, poly *ts[2], poly *h, poly *S_pi, char *mu, uint64_t mu_len, poly *L, poly *H, poly *A, int pi,
            entropy_t *entropy, sampler_t *sampler);
int L2RS_sigVer(poly* c1, poly* t, poly* h, char* mu, uint64_t mu_len, poly* L, poly* H, poly* A);

#endif //RINGCT_REWORK_L2RS_H
