//
// Created by Evgeniy Kramsakov on 14.01.2022.
//

#ifndef RINGCT_REWORK_MATRIX_H
#define RINGCT_REWORK_MATRIX_H

#include "poly.h"


void matrix_shift(poly* dst, poly* src, size_t mLen, int iNumber);
void matrix_const_mul(poly* r, poly* A, uint64_t cof, size_t mLen);
void matrix_sub(poly* dst, poly* A, poly* B, size_t mLen);
void matrix_add(poly* dst, poly* A, poly* B, size_t mLen);
void matrix_poly_mul_matrix(poly* dst, poly* A, poly* p, size_t mLen);
void matrix_matrix_mul_poly(poly* dst, poly* A, poly* s, size_t mLen);
void matrix_copy(poly* dst, poly* src, size_t mLen);
void matrix_uniform(poly **dst, size_t mLen, entropy_t* entropy);



#endif //RINGCT_REWORK_MATRIX_H
