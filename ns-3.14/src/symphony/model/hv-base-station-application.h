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
    int sen_id, cur_shift, init_flag;
};

typedef struct {
	  uint32_t nodeId;
      int vector[a];
} NodePacket;


/**
 * NS-3 application for a base station using a cognitive code based on
 * binary spatter codes with hypervectors of a specific dimension
 */
class HvBaseStation : public Application
{
public:
	static TypeId GetTypeId (void);

	/**
	 * Creates a new application wita collection of TinyOS nodes
	 */
	HvBaseStation (TosNodeContainer nodes);
	virtual ~HvBaseStation ();

	/**
	 * Provides the TinyOS nodes with the initialization hypervectors
	 * to build the communication code between them and the base station.
	 */
	void InitializeNodes(TosNodeContainer container );

	/**
	 * Processes the hypervectors messages received from the TinyOS nodes
	 */
	void ReceiveHyperVector(uint16_t length, void* buffer);


private:

  // Inherited from Application base class.
  virtual void StartApplication (void);
  virtual void StopApplication (void);
  virtual void DoDispose (void);
  uint32_t GetApplicationId (void) const;

  // Collection of TinyOS nodes inside the simulation
  TosNodeContainer m_nodes;
  // Initial random hypervector used to build the codewords
  init1 m_P;
  // Memory to store the initialization hypervectors of the nodes (SRx and ARx)
  init1 *init_mem;
  // Memory to store the hypervectors patterns from the interaction between sensor and actuatros
  init2 *item_mem;
  // Information from sensors not stored yet in the item memory
  init2 *item_pending;
  // Status of all the sensors
  init3 *sen_state;

  // Algorithm variables
  int item_len, k_shift, n, check_vec1[a], check_vec2[a], shift_vec1[a],
  	  count_adr, count_shift, subs_vec[a], input_id , input_shift, cur_state_num,
  	  buff_int[a], buff_bin[a], input_vector[a], output_vec[a], node_pairs_number;
  int* item_pres;
  double check_sum, sum_adres, sum_shift, pres_sum;
  double* item_check;

  /**
  * Send the ouput hypervector of the algorithm to the actuators.
  * Also updates the I/O Clients interacting with the simulation
  */
  void SendOutputVector(int *output_vector);


  /**
   * Callback to send data to the device as an interruption from
   * the simulator
   */
  Callback<int, uint8_t, uint16_t ,void * > m_InitializationVectorInterrupt;
  Callback<int, uint8_t, uint16_t, void * > m_RandomVectorInterrupt;
  Callback<int, uint8_t, uint16_t ,void * > m_ActuatorInterrupt;
  Callback<int, uint8_t, uint16_t, void * > m_ActuatorHvVectorInterrupt;

  /**
   * XOR Operation. Input parameters are two interacting vectors (arr1, arr2),
   * result vector (arr0) and dimension (n)
   */
  void Xor(int *arr0, int *arr1, int *arr2, int n);

  /**
   * OR Operation. Input parameters are two interacting vectors (arr1, arr2),
   * result vector (arr0) and dimension (n)
   */
  void Or(int *arr0, int *arr1, int *arr2, int n);

  /**
   * Reduced Sum of a vector operation.
   * Input parameters are input vector (arr0) and dimensionality (n)
   */
  double Sum(int *arr0, int n);

  /**
   * Shifting operation. Obtains a new vector from shifting another.
   * Input parameters are input vector (arr2), dimensionality (n), shifting vector arr1 and shift value in bits (k)
   */
  void Shift(int *arr1, int *arr2, int n, int k);

  /**
   * Thresholds an integer buffer to obtain its binary version.
   * Input parameters are integer buffer (buff_int), binary buffer (buff_bin), dimensionality (n).
   */
  void Buff_int_to_bin(int *buff_int, int *buff_bin, int n);
};

} // namespace ns3

#endif /* IOProxyServer_H */
