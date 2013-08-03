#ifndef SKYNET_TOS_H
#define SKYNET_TOS_H

enum {
  DIMENSION = 1000
};


typedef struct init1{
    int id, role_hv[DIMENSION]; // a - dimensionality of hypervector
} init1;

  


typedef struct {
			uint32_t nodeId;
      int vector[DIMENSION];
} NodePacket;
  


#endif



