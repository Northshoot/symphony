#ifndef SKYNET_TOS_H
#define SKYNET_TOS_H

enum {
  DIMENSION = 1000
};


typedef struct init1{
    int id, role_hv[DIMENSION]; // a - dimensionality of hypervector
} init1;

  
void Xor(int *arr0, int *arr1, int *arr2, int n);
void Or(int *arr0, int *arr1, int *arr2, int n);
void Shift(int *arr1, int *arr2, int n, int k);
void printFiller();

typedef struct {
			uint32_t nodeId;
      int vector[DIMENSION];
} NodePacket;
  


#endif



