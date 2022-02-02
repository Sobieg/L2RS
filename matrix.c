//
// Created by Evgeniy Kramsakov on 14.01.2022.
//

#include "matrix.h"


void matrix_shift(poly* dst, poly* src, int iNumber){
    for (int i = 0; i<RINGCT_M; i++){
        poly_shift(dst+i, src+i, iNumber);
    }
}

void matrix_const_mul(poly* r, poly* A, uint64_t cof){
    for (int i = 0; i<RINGCT_M; i++) {
        for (int j = 0; j<RINGCT_N; j++) {
            r[i].coeffs[j] = cof * A[i].coeffs[j];
        }
    }
}

void matrix_sub(poly* dst, poly* A, poly* B) {
    for (int i = 0; i<RINGCT_M; i++){
        poly_sub(dst+i, A+i, B+i);
    }
}

void matrix_add(poly* dst, poly* A, poly* B){
    for (int i = 0; i<RINGCT_M; i++){
        poly_add(dst+i, A+i, B+i);
    }
}

void matrix_poly_mul_matrix(poly* dst, poly* A, poly* p){
    for (int i = 0; i<RINGCT_M; i++) {
        poly_mul_pointwise(dst+i, A+i, p);
    }
}

void matrix_matrix_mul_poly(poly* dst, poly* A, poly* s){
    poly tmp, tmpA, tmps;
    poly_init(dst);
    for (int i = 0; i<RINGCT_M; i++) {
//        poly_cofcopy(&tmpA, A+i);
//        poly_cofcopy(&tmps, s+i);
//        poly_mul_pointwise(&tmp, &tmpA, &tmps);
        poly_mul(&tmp, A+i, s+i);
        poly_add(dst, dst, &tmp);
    }
}

void matrix_copy(poly* dst, poly* src) {
    for (int i = 0; i<RINGCT_M; i++) {
        poly_cofcopy(dst + i, src+i);
    }
}

void matrix_uniform(poly **dst, entropy_t* entropy) {
    for (int i = 0; i<RINGCT_M; i++){
        poly_uniform(dst[i], entropy);
    }
}
