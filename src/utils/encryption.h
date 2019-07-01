#ifndef _ENCRYPTION_H
#define _ENCRYPTION_H

#include <stdint.h>
#include <stdlib.h>
#include <float.h>
#include <string.h>
#include <stdio.h>

#define ALPHA_SPACE 27

/*
Source: http://www.data-compression.com/english.html
*/
static double english_frequencies[] = {
    0.0651738, // a
    0.0124248, // b
    0.0217339, // c
    0.0349835, // d
    0.1041442, // e
    0.0197881, // f
    0.0158610, // g
    0.0158610, // h
    0.0558094, // i
    0.0009033, // j
    0.0050529, // k
    0.0331490, // l
    0.0202124, // m
    0.0564513, // n
    0.0596302, // o
    0.0137645, // p
    0.0008606, // q
    0.0497563, // r
    0.0515760, // s
    0.0729357, // t
    0.0225134, // u
    0.0082903, // v
    0.0171272, // w
    0.0013692, // x
    0.0145984, // y
    0.0007836, // z
    0.1918182, // space
};

/*
Return an array containing the frequency of each character
within the plaintext.
Counts Latin alphabet characters and space.
*/
double* analyse_frequencies(char* plaintext, uint64_t length);

/*
Measure a plaintext's 'distance' from English by computing
the normalised sum of the squared distances between its
character frequencies and those found in the English language.
*/
double score_english_frequency(char* plaintext, uint64_t length);

/*
XOR-combine two equal-length buffers.
*/
char* xor_buffers(char* buf1, char* buf2, uint64_t length);

/*
XOR-encrypt (or decrypt) a buffer with a given key.
*/
char* xor_encrypt(char* plaintext, unsigned char* key, uint64_t plaintext_length,
        uint64_t key_length);

/*
Decrypt ciphertext against every possible one-byte key
and return the plaintext with the best character frequencies,
i.e. the least distance from English frequencies.
Store the key that yielded this plaintext in `key`.
*/
char* frequency_decrypt(char* ciphertext, uint64_t ciphertext_length, unsigned char* key,
        double* score_ptr);

/*
Using `frequency_decrypt` and `score_english_frequency`,
find the `n` plaintexts which are most similar to English.
Store the keys that yielded them in `keys` and their
difference from English in `scores`, both of which must be
arrays of length `n`.
*/
char** get_n_best_plaintexts(char** ciphertexts, uint64_t ciphertext_length, unsigned char** keys,
        uint64_t n_ciphertexts, uint64_t n, double* scores);

/*
Find the maximum element in an array and store its index
in `idx`.
*/
double find_max(double arr[], uint64_t length, uint64_t* idx);

/*
Find the minimum element in an array and store its index
in `idx`.
*/
double find_min(double arr[], uint64_t length, uint64_t* idx);

#endif