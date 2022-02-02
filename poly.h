//
// Created by Evgeniy Kramsakov on 13.01.2022.
//

#ifndef RINGCT_REWORK_POLY_H
#define RINGCT_REWORK_POLY_H

#include <stdint.h>
#include <stddef.h>
#include "params.h"
#include "entropy.h"
#include "sampler.h"

typedef struct {
    uint64_t coeffs[RINGCT_N];
} poly;

void poly_init(poly *r);
void poly_setValue(poly *r, uint64_t v);
uint64_t poly_coeff_mod_q(uint64_t x);
uint64_t poly_coeff_mod_2q(uint64_t x);
void poly_frombytes(poly *r, const unsigned char *a);
void poly_tobytes(unsigned char *r, const poly *p);
void poly_sub(poly *r, const poly *a, const poly *b);
void poly_add(poly *r, const poly *a, const poly *b);
void poly_print(const poly* r);
int poly_equal(const poly* a, const poly* b);
void poly_uniform(poly* a, entropy_t* entropy);
void poly_gaussian(poly* a, sampler_t* sampler);
void poly_serial(poly* r);
void poly_cofcopy(poly* dst, poly* src);
void poly_shift(poly* dst, const poly* r, int iNumber);
void poly_mul_pointwise(poly* dst, const poly* a, const poly* b);
void poly_constmul(poly* dst, const poly* a, uint64_t cof, uint64_t q);
void poly_mul(poly* dst, const poly* a, const poly* b);


//uint64_t montgomery_reduce(uint64_t a);

void poly_ntt(poly *r);
void poly_invntt(poly *r);

#endif //RINGCT_REWORK_POLY_H
