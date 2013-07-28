/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#ifndef HvBaseStation_H
#define HvBaseStation_H

#include "ns3/application.h"
#include "ns3/traced-callback.h"
#include "ns3/nstime.h"
#include "ns3/average.h"
#include "ns3/simulator.h"
#include "ns3/tos-node-container.h"
#include <map>

namespace ns3 {

static const int a = 1000; //dimensionality of hypervectors

// Initialize structure init1 for initialization memory that consists of role hypervectors and id of devices
struct init1{
    int id, role_hv[a]; // a - dimensionality of hypervector
};
// Initialize structure init2 for item memory that consists of current shift, previous shift, current role vector id,
//previous vector id and two hypervectors one for sensor and one for actuator
struct init2{
    int cur_role, cur_shift, prev_role, prev_shift, hp_sen[a], hp_act[a];// a - dimensionality of hypervector
};
// Initialize structure init3 for sensors state table that consists of current shift, and current sensor id (current role vector id)
struct init3{
    int sen_id, cur_shift;
};

typedef struct {
	  uint32_t nodeId;
      int vector[a];
} NodePacket;


/**
 *
 */
class HvBaseStation : public Application
{
public:
	static TypeId GetTypeId (void);

	/**
	 *
	 */
	HvBaseStation (TosNodeContainer nodes);
	virtual ~HvBaseStation ();

	void ReceiveHyperVector(uint16_t length, void* buffer);
	void InitializeNodes(TosNodeContainer container );

private:

  // inherited from Application base class.
  virtual void StartApplication (void);
  virtual void StopApplication (void);
  virtual void DoDispose (void);
  uint32_t GetApplicationId (void) const;

  int m_dimension;
  TosNodeContainer m_nodes;
  int m_P [a];

  init1 *init_mem;
  init2 *item_mem;
  init2 *item_pending;
  init3 *sen_state;

  int item_len, k_shift, n;
  int check_vec1[a], check_vec2[a],
      shift_vec1[a], pres_sum, count_adr, count_shift ,
      subs_vec[a], input_id , input_shift, cur_state_num ;
  double check_sum, sum_adres, sum_shift;
  int* item_pres;
  double* item_check;

  int buff_int[a], buff_bin[a], input_vector[a], output_vec[a];

  void Xor(int *arr0, int *arr1, int *arr2, int n);
  void Or(int *arr0, int *arr1, int *arr2, int n);
  double Sum(int *arr0, int n);
  void Shift(int *arr1, int *arr2, int n, int k);
  void Buff_int_to_bin(int *buff_int, int *buff_bin, int n);


  /**
   * Sends data to the device as an interruption from
   * the simulator
   */
  Callback<int, uint8_t, uint16_t ,void * > m_InitializationVectorInterrupt;
  Callback<int, uint8_t, uint16_t, void * > m_RandomVectorInterrupt;
};

} // namespace ns3

#endif /* IOProxyServer_H */
