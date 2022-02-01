//
// Created by Evgeniy Kramsakov on 18.01.2022.
//

#include "reduce.h"
#include "params.h"

static const uint64_t qinv = 1767374847; // -inverse_mod(p,2^rlog)
static const uint64_t rlog = 32; // first power of two after RINGCT_Q

/*************************************************
* Name:        montgomery_reduce_newhope
*
* Description: Montgomery reduction; given a 32-bit integer a, computes
*              16-bit integer congruent to a * R^-1 mod q,
*              where R=2^18 (see value of rlog)
*
* Arguments:   - uint32_t a: input unsigned integer to be reduced; has to be in {0,...,1073491968}
*
* Returns:     unsigned integer in {0,...,2^14-1} congruent to a * R^-1 modulo q.
**************************************************/
uint64_t montgomery_reduce(uint64_t a)
{
    //TODO: check this
    // a < q < 2^32
    uint64_t u;

    a = a%RINGCT_Q;
    u = (a * qinv);
    u &= (((uint64_t) 1<<rlog)-1);
    u *= RINGCT_Q;
    a = a + u;
    a = a>>rlog;
    if (a < RINGCT_Q) {
        return a;
    }
    else {
        return a - RINGCT_Q;
    }
}
