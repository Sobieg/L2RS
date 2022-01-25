//
// Created by Evgeniy Kramsakov on 18.01.2022.
//

#ifndef RINGCT_REWORK_NTT_H
#define RINGCT_REWORK_NTT_H

#include <stdint.h>

extern uint64_t omegas_inv_bitrev_montgomery[];
extern uint64_t gammas_bitrev_montgomery[];
extern uint64_t gammas_inv_montgomery[];

void bitrev_vector(uint64_t* poly);
void mul_coefficients(uint64_t* poly, const uint64_t* factors);
void ntt(uint64_t* a, const uint64_t* omega);


#endif //RINGCT_REWORK_NTT_H
