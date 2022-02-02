#ifndef RINGCT_PARAMS_H
#define RINGCT_PARAMS_H


//TODO: make params sets




//#define RINGCT_N 512
//#define RINGCT_N 1024
#define RINGCT_N 4
//#define RINGCT_M 6
#define RINGCT_M 2                          //we use M as m-1 in the paper, and M+1 as m in the paper
#define RINGCT_LAM 100
#define RINGCT_DELTA 1.007
//#define RINGCT_Q 3677394373
//#define RINGCT_2Q 7354788746
#define RINGCT_Q 1767374849
#define RINGCT_2Q 3534749698
#define RINGCT_KAPPA 17
#define RINGCT_ETA 1.1
#define RINGCT_ALPHA 0.1
#define RINGCT_CAP_M 1.0027
#define RINGCT_GAMMA 13.6
#define RINGCT_CEILGAMMA 14
#define RINGCT_GAMMAPOWER 16384                //2^ceil(gamma)
#define RINGCT_SIGMA 283754

#define RINGCT_SYMBYTES 32

/*# m = 6                                   # Polynomial ring size
m = 3                                       # Polynomial ring size
# n = 512                                   # Polynomial ring degree
n = 3                                       # Polynomial ring degree
lam = 100                                   # Security parameter
delta = 1.007                               # Hermite factor
# q = next_prime(randint(2^31-1, 2^32))     # Quotient,
q = 3677394373                              # log(q) = 31
kappa = 17                                  # Random Oracle weight
eta = 1.1                                   # Correctness
alpha = 0.1                                 # Rejection sampling
M = 1.0027                                  # Rejection sampling
gamma = 13.6                                # Private-key density ≈ log(2 * n * kappa)
# gamma = 4.2                               # Private-key density ≈ log(2 * n * kappa)
sigma = 283754                              # Gaussian standart diveation
# sigma = 3                                 # Gaussian standart diveation*/



//#define RINGCT_SYMBYTES 32 /* size of shared key, seeds/coins, and hashes */
//
//#define RINGCT_POLYBYTES ((14 * RINGCT_N) / 8)
//#define RINGCT_POLYCOMPRESSEDBYTES ((3 * RINGCT_N) / 8)
//
//#define RINGCT_CPAPKE_PUBLICKEYBYTES (RINGCT_POLYBYTES + RINGCT_SYMBYTES)
//#define RINGCT_CPAPKE_SECRETKEYBYTES (RINGCT_POLYBYTES)
//#define RINGCT_CPAPKE_CIPHERTEXTBYTES (RINGCT_POLYBYTES + RINGCT_POLYCOMPRESSEDBYTES)
//
//#define RINGCT_CPAKEM_PUBLICKEYBYTES RINGCT_CPAPKE_PUBLICKEYBYTES
//#define RINGCT_CPAKEM_SECRETKEYBYTES RINGCT_CPAPKE_SECRETKEYBYTES
//#define RINGCT_CPAKEM_CIPHERTEXTBYTES RINGCT_CPAPKE_CIPHERTEXTBYTES
//
//#define RINGCT_CCAKEM_PUBLICKEYBYTES RINGCT_CPAPKE_PUBLICKEYBYTES
//#define RINGCT_CCAKEM_SECRETKEYBYTES (RINGCT_CPAPKE_SECRETKEYBYTES + RINGCT_CPAPKE_PUBLICKEYBYTES + 2 * RINGCT_SYMBYTES)
//#define RINGCT_CCAKEM_CIPHERTEXTBYTES (RINGCT_CPAPKE_CIPHERTEXTBYTES + RINGCT_SYMBYTES) /* Second part is for Targhi-Unruh */

#endif
