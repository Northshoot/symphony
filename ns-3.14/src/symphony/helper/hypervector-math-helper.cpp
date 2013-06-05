/*
 * hypervector-math-helper.cpp
 *
 *  Created on: May 18, 2013
 *      Author: onir
 */

#include <iostream>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#include "hypervector-math-helper.h"

namespace ns3 {

/**
 * XOR operation over vectors of size equals to dimension parameter.
 *
 * @param result a pointer to store the the result of firstVector XOR secondVector
 * @param firstVector a pointer to the first xor operand
 * @param secondVector a pointer to the second xor operand
 * @param dimension size of the vectors used
 */
void Xor(int *result, int *firstVector, int *secondVector, int dimension)
{
    for(int i=0; i < dimension; i++) {
        result[i] = firstVector[i] ^ secondVector[i];
    }
}

/**
 * OR operation over vectors of size equals to dimension parameter.
 *
 * @param result a pointer to store the the result of firstVector XOR secondVector
 * @param firstVector a pointer to the first xor operand
 * @param secondVector a pointer to the second xor operand
 * @param dimension size of the vectors
 */
void Or(int *result, int *firstVector, int *secondVector, int dimension)
{
    for(int i=0; i < dimension; i++) {
        result[i] = firstVector[i] | secondVector[i];
    }
}

/**
 * Reduced sum of a vector with size equal to dimension
 *
 * @param vector a pointer to the vector
 * @param dimension size of the vector
 */
double Sum(int *vector, int dimension)
{
    int res = 0;
    for(int i=0; i < dimension; i++) {
        res += vector[i];
    }
    return res/n;
}

/**
 * Shifts a vectors of size dimension the number of places indicated by shift value.
 *
 * @param result a pointer to store the shifted vector
 * @param vector a pointer to the vector to shift
 * @param dimension size of the vector to shift
 * @param shitValue number of bit positions to shift
 */
void Shift(int *result, int *vector, int dimension, int shiftValue)
{
    for(int i = 0; i < dimension; i++) {
        if (i + shiftValue < dimension)
        {
        	result[i+shiftValue] = (vector[i]);
        }
        else
        {
        	result[i + shiftValue - dimension] = vector[i];
        }
    }
}

/**
 * Get the binary buffer from a integer buffer
 *
 * @param buff_int integer buffer
 * @param buff_bin binary buffer
 * @paran dimension size of the buffers
 */
void Buff_int_to_bin(int *buff_int, int *buff_bin, int dimension)
{
    double max = 0; // max maximun number in integer buffer

    for(int i=0; i < dimension; i++) // cycle for finding maximum number
    {
    	if(max<buff_int[i])
        {
          	max = buff_int[i];
        }
    }
    srand((unsigned)time(NULL)); // seeds generation for rand function
    for(int i = 0; i < dimension; i++)
    {
    	if (buff_int[i] > max/2)
        { // if i'th position in integer buffer more than max/2 put 1 in binary buffer vector
             buff_bin[i] = 1;
        }
        else if (buff_int[i] < max/2)
        { //if i'th position in integer buffer less than max/2 put 0 in binary buffer vector
            buff_bin[i] = 0;
        }
        else
        { //if i'th position in integer buffer equal to max/2 put uniform random number (1 or 0) in binary buffer vector
            if (((double)rand() / RAND_MAX) < 0.5)
            {
            	buff_bin[i] = 0;
            }
            else
            {
            	buff_bin[i] = 1;
            }
        }
    }
}

} /* namespace ns3 */
