#include "Timer.h"

module BlinkC @safe()
{
  uses interface Boot;
  uses interface Random;
}

implementation
{
  event void Boot.booted()
  {
  		uint16_t dimension = 64;
  		uint16_t i = 0;
  
  		//Hypervector 1
  		uint16_t hv1[dimension];
  		//Hypervector 2
  		uint16_t hv2[dimension];
  		//Hypervector result
  		uint16_t hvres[dimension];
  		
  		//Random values
  		for(i = 0; i < dimension; i++ ){
  			hv1[i] = call Random.rand16();
  			hv2[i] = call Random.rand16();
  			
  		}
  		
  		for(i = 0; i < dimension; i++ ){
  			hvres[i] =  hv1[i] ^ hv2[i];
  			dbg("Boot", "hvres[%d] = %x <- hv1[%d] = %x - hv2[%d] = %x \n", i, hvres[i], i, hv1[i], i, hv2[i]);
  		}
  		
  		
  }
}

