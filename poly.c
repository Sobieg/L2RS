//
// Created by Evgheniy Kramsakov on 13.01.2022.
//

#include "poly.h"
#include "sha3.h"
#include <assert.h>
#include "reduce.h"
#include "ntt.h"
#include <stdio.h>

//uint64_t montgomery_reduce(uint64_t a) {
//
//    static const uint32_t qinv = 2752372467; // -inverse_mod(p,2^32)
//    static const uint32_t rlog = 32;
//
//    uint64_t u;
//
//    u = (a * qinv);
//    u &= (((uint64_t )1 << rlog) - 1);
//    u *= RINGCT_Q;
//    a = a + u;
//    return a >> rlog;
//}

void poly_init(poly *r) {
    for (size_t i = 0; i<RINGCT_N; i++) {
        r->coeffs[i] = 0;
    }
}

void poly_setValue(poly *r, uint64_t v) {
    for (size_t i = 0; i<RINGCT_N; i++ ){
        r->coeffs[i] = v;
    }
}

uint64_t poly_coeff_mod_q(uint64_t x) {
    return x%RINGCT_Q;
}

uint64_t poly_coeff_mod_2q(uint64_t x) {
    return x%RINGCT_2Q;
}

void poly_uniform(poly* a, entropy_t* entropy) {
    //we need sizeof(uint64_t) * RINGCT_N bytes
//    SHA3_shake256((uint8_t*) a->coeffs, sizeof(uint64_t) * RINGCT_N, seed, RINGCT_SYMBYTES);
    for (size_t i = 0; i<RINGCT_N; i++) {
        a->coeffs[i] = entropy_random_uint64(entropy) % RINGCT_Q;
    }
}

void poly_gaussian(poly* a, sampler_t* sampler) {
    for (size_t i = 0; i<RINGCT_N; i++) {
        a->coeffs[i] = sampler_gauss(sampler) % RINGCT_Q;
    }
}

/*************************************************
* Name:        poly_frombytes
*
* Description: De-serialization of a polynomial
*
* Arguments:   - poly *r:                pointer to output polynomial
*              - const unsigned char *a: pointer to input byte array
**************************************************/
void poly_frombytes(poly *r, const unsigned char *a) {
    for (int i = 0; i<RINGCT_N; i++) {
        r->coeffs[i] = (a[4 * i]) | (a[4 * i + 1] << 8) | (a[4 * i + 2] << 16) | (a[4 * i + 3] << 24);
    }
}

/*************************************************
* Name:        poly_tobytes
*
* Description: Serialization of a polynomial
*
* Arguments:   - unsigned char *r: pointer to output byte array
*              - const poly *p:    pointer to input polynomial
**************************************************/
void poly_tobytes(unsigned char *r, const poly *p) {
    for (int i = 0; i < RINGCT_N / 4; i++) {

        r[4*i + 0] = (p->coeffs[i] & 0x000000ff);
        r[4*i + 1] = (p->coeffs[i] & 0x0000ff00);
        r[4*i + 2] = (p->coeffs[i] & 0x00ff0000);
        r[4*i + 3] = (p->coeffs[i] & 0xff000000);
    }
}

void poly_sub(poly *r, const poly *a, const poly *b){
    // len(RINGCT_Q) == 32
    for (int i = 0; i<RINGCT_N; i++) {
        r->coeffs[i] = (a->coeffs[i] + 3*RINGCT_Q - b->coeffs[i]) % RINGCT_Q;
    }
}

void poly_add(poly *r, const poly *a, const poly *b) {
    for (int i = 0; i<RINGCT_N; i++) {
        r->coeffs[i] = (a->coeffs[i] + b->coeffs[i]) % RINGCT_Q;
    }
}

void poly_print(const poly* r) {
    for (int i = 0; i < RINGCT_N; i++) {
        printf("0x%04llX, ", r->coeffs[i]);
    }
    printf("\n");
}

int poly_equal(const poly* a, const poly* b) {
    for (int i = 0; i < RINGCT_N; i++) {
        if (a->coeffs[i] != b->coeffs[i]) {
            return 0;
        }
    }
    return 1;
}

void poly_serial(poly* r) {
    for (int i = 0; i<RINGCT_N; i++) {
        r->coeffs[i] = poly_coeff_mod_q(r->coeffs[i]);
    }
}

void poly_cofcopy(poly* dst, poly* src) {
    for (int i = 0; i<RINGCT_N; i++){
        dst->coeffs[i] = src->coeffs[i];
    }
}

void poly_shift(poly* dst, const poly* r, int iNumber) {
    // smthg wired
}

void poly_mul_pointwise(poly* dst, const poly* a, const poly* b){
    uint64_t t;
    for (int i = 0; i<RINGCT_N; i++) {
//        dst->coeffs[i] = (a->coeffs[i] * b->coeffs[i]) % RINGCT_Q;
    //98198013 is a 2^(2*rlog)%q
        t            = montgomery_reduce(98198013*b->coeffs[i]); /* t is now in Montgomery domain */
        dst->coeffs[i] = montgomery_reduce(a->coeffs[i] * t);  /* dst->coeffs[i] is back in normal domain */
    }
}

void poly_constmul(poly* dst, const poly* a, uint64_t cof) {
    for (int i = 0; i<RINGCT_N; i++) {
        dst->coeffs[i] = (dst->coeffs[i] * cof) % RINGCT_2Q; //checkme: why 2q?
    }
}

void poly_mul(poly* dst, const poly* a, const poly* b) {
//    poly_init(dst);
//
//    for (int i = 0; i<RINGCT_N; i++) {
//        for (int j = 0; j<RINGCT_Q; j++) {
//            dst->coeffs[(i+j)%RINGCT_Q] = dst->coeffs;
//        }
//    }
//
//
//
//    for (int i = 0; i<RINGCT_N; i++) {
//        for (int j = 0; j<RINGCT_N; j++) {
//            dst->coeffs[(i+j)%RINGCT_N] = (dst->coeffs[(i+j)%RINGCT_N] + (a->coeffs[j] * b->coeffs[i]) % RINGCT_Q) % RINGCT_Q;
//        }
//    }
}

/*************************************************
* Name:        poly_newhope_ntt_newhope
*
* Description: Forward ntt_newhope transform of a polynomial in place
*              Input is assumed to have coefficients in bitreversed order
*              Output has coefficients in normal order
*
* Arguments:   - poly_newhope *r: pointer to in/output polynomial
**************************************************/
void poly_ntt(poly *r)
{
    bitrev_vector(r->coeffs);
    mul_coefficients(r->coeffs, gammas_bitrev_montgomery);
    ntt((uint64_t *)r->coeffs, gammas_bitrev_montgomery);
}

/*************************************************
* Name:        poly_newhope_invntt_newhope
*
* Description: Inverse ntt_newhope transform of a polynomial in place
*              Input is assumed to have coefficients in normal order
*              Output has coefficients in normal order
*
* Arguments:   - poly_newhope *r: pointer to in/output polynomial
**************************************************/
void poly_invntt(poly *r)
{
    bitrev_vector(r->coeffs);
    ntt((uint64_t *)r->coeffs, omegas_inv_bitrev_montgomery);
    mul_coefficients(r->coeffs, gammas_inv_montgomery);
}