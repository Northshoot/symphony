/*
 * Create a NS-3 Application to represent a base station that
 * has support for hyper vector based communications.
 *
 * @author Jose Angel Fernandez
 */
#include "ns3/icmpv4.h"
#include "ns3/assert.h"
#include "ns3/log.h"
#include "ns3/ipv4-address.h"
#include "ns3/socket.h"
#include "ns3/integer.h"
#include "ns3/boolean.h"
#include "ns3/inet-socket-address.h"
#include "ns3/packet.h"
#include "ns3/trace-source-accessor.h"
#include "ns3/config.h"
#include "ns3/tos-device.h"
#include "ns3/names.h"
#include "ns3/string.h"
#include "ns3/object.h"
#include "ns3/tos-to-ns3-proxy.h"

#include "hv-base-station-application.h"

#include <stdio.h>

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("HvBaseStation");
NS_OBJECT_ENSURE_REGISTERED (HvBaseStation);

HvBaseStation::HvBaseStation (TosNodeContainer nodes)
{
	m_nodes = nodes;
	init_mem = new init1[nodes.GetN()];
	item_len = 0;
	item_pres = new int[item_len];
	item_check = new double[item_len];
	pres_sum = 0;
	count_adr = 0;
	count_shift = 0;
	input_id = 1000;
	input_shift = 0;
	cur_state_num = 0;
	sum_adres = 1;
	sum_shift = 1;
	k_shift = 1;
	n = 10;
    item_mem = new init2[100];
    item_pending = new init2[1];
    sen_state = new init3[n];

    for(int i = 0; i< item_len; i++){
        item_pres[i] = 0;
        item_check[i] = 0;
    }

    for(unsigned int i = 0 ; i < nodes.GetN(); i++){
    	init_mem[i].id = 0;
    	for (int j = 0; j < a; j++){
    		init_mem[i].role_hv[j] = 0;
    	}
    }

    for(int i = 0 ; i < n; i++){
    	sen_state[i].cur_shift = 0;
    	sen_state[i].sen_id = 0;
    }

    srand(1);

}

TypeId HvBaseStation::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::HvBaseStation")
    .SetParent<Application> ()
    .AddAttribute("InitializationVectorInterrupt","Callback for device interrupt with data event.",
           CallbackValue(),
           MakeCallbackAccessor(&HvBaseStation::m_InitializationVectorInterrupt),
           MakeCallbackChecker ())
    .AddAttribute("RandomVectorInterrupt","Callback for device interrupt with data event.",
           CallbackValue(),
           MakeCallbackAccessor(&HvBaseStation::m_RandomVectorInterrupt),
           MakeCallbackChecker ())
    .AddAttribute("ActuatorVectorInterrupt","Callback for device interrupt with data event.",
           CallbackValue(),
           MakeCallbackAccessor(&HvBaseStation::m_ActuatorHvVectorInterrupt),
           MakeCallbackChecker ())
    .AddAttribute("ActuatorInterrupt","Callback for device interrupt with data event.",
    	   CallbackValue(),
           MakeCallbackAccessor(&HvBaseStation::m_ActuatorInterrupt),
           MakeCallbackChecker ())
    .AddAttribute("Dimension", "Dimension of the hypervectors used",
    	   IntegerValue(10000),
    	   MakeIntegerAccessor(&HvBaseStation::m_dimension),
    	   MakeIntegerChecker<int16_t>());
  return tid;
}


void HvBaseStation::StartApplication (void)
{
  NS_LOG_FUNCTION (this);

  m_P.id = 0;
  //Generates the random hypervector used by the all nodes
  for (int j = 0; j < a;j++) {
	  m_P.role_hv[j] = rand() % 2;
  	  //  std::cout << m_P[j];
  }
  //std::cout << " -- \n";
  InitializeNodes(m_nodes);
}

void HvBaseStation::StopApplication (void)
{
  NS_LOG_FUNCTION (this);
}

void printFiller(int * array){
	int i = 0;
	printf("\n");
	for (i = 0 ; i < a; i++){
		printf("%d", array[i] );
	}
	printf("\n");

}

void HvBaseStation::ReceiveHyperVector(uint16_t size, void * buffer)
{
	NS_LOG_FUNCTION(this);

	//Extract the message from the sensor
	NodePacket* packet = (NodePacket*) buffer;
	//Store the vector locally
	memcpy(input_vector, packet->vector, sizeof(int[a]));

	//Check if the vector is on binary buffer
	Xor(check_vec1, input_vector, buff_bin, a);

	check_sum = Sum(check_vec1, a);

	//check for vector presence in binary buffer
    if (check_sum < 0.47) {//if condition is true exit from main (discard input vector)
        for (int i=0;i<a;i++) input_vector[i]=0; // return 0;
    } else { // new vector
        if (item_len != 0) { // if item memory is not empty
        	std::cout << "\t\tItem memory has elements... \n";
            for (int i=0; i<item_len; i++) {
                Xor(check_vec1, input_vector,item_mem[i].hp_sen, a); // check for vector presence in item memory
                item_check[i] = Sum(check_vec1, a);
                std::cout << "\t\t\tCheck entry " << i << " of item memory -> Sum " << item_check[i] << "\n";
                if (item_check[i] < 0.3) {
                    item_pres[i] = 1; //if yes put 1 in presence variable vector
                    std::cout << "\t\t\t\tPresence on position " << i << "\n";
                } else {
                    item_pres[i]= 0;
                }
            }
        }
        // Sum of presence vector
        pres_sum = Sum(item_pres, item_len);
        std::cout << "\t\tSum of presence vector is " << pres_sum << "\n";
        //if presence sum non zero check for prev_shift and sensor cur_shift coincidence
        if (pres_sum != 0) {
            for (int i=0;i<item_len;i++) {
            	std::cout << "\t\t\tChecking entity " << i << "\n";
                if (item_pres[i] == 1) {
                	std::cout << "\t\t\t\t Flag set to 1 on item presence \n";
                    if (item_mem[i].prev_shift == sen_state[item_mem[i].prev_role].cur_shift) {
                    	for (int j=0;j<a;j++) {
                            output_vec[j] = item_mem[i].hp_act[j]; // send corresponding hypervector to actuator
                        }
                        std::cout << "\t\t\t---> Update actuator status \n";
                    }
                }
            }
        }
        // If there is no item memory yet or input vector does not present in it, we decode input vector
        if ((pres_sum == 0) || (item_len == 0)) {
            std::cout << "\t\tLooking for input vector... \n";
        	//release input vector from randomization vector (init_mem[0].role_hv)  by xoring
            Xor(check_vec1, input_vector, m_P.role_hv, a);
           // check in init memory till we find correspond role vector
            std::cout << "\t\t\tInit memory... \n";
            while (sum_adres > 0.3) {
                Xor(check_vec2, check_vec1, init_mem[count_adr].role_hv, a);
                sum_adres = Sum(check_vec2, a);
                input_id = init_mem[count_adr].id;
                count_adr++;

            }
            std::cout << "\t\t\t\t[i,input_id, sum_adres] = " << count_adr << " " << input_id << " " << sum_adres << "\n";

           // check for shift of correspond role vector
            std::cout << "\t\t\tShifting vector... \n";
            while (sum_shift > 0.3) {
                Shift(shift_vec1, init_mem[input_id].role_hv, a, k_shift);
                Xor(check_vec2, check_vec1, shift_vec1, a);
                sum_shift = Sum(check_vec2, a);
                input_shift = k_shift;
                 count_shift++;
                k_shift++;
            }
            std::cout << "\t\t\t\t[i,input_shift, sum_shift] = " << count_shift << " " << input_shift << " " << sum_shift << "\n";

        }
        //If it is sensor
        /////
        ///// TODO:VALUE FOUR ONLY VALID FOR THIS SPECIFIC SCENARIO!
        /////         |v|
        if (input_id < 3) { //  sensors id less than 100 , actuators id > 100
            // find sensor in sensors state table
        	std::cout << "\t\tMessage from sensor " << input_id << " detected \n";
            for (int j=0; j<n;j++) {
                if (sen_state[j].sen_id == input_id) {
                    cur_state_num = j; //fix position of sensor in the table
                }
            }
            std::cout << "\t\t\tSensor position in table " << cur_state_num << "\n";
            //Form previous measurement vector for current sensor
            Shift(subs_vec, init_mem[cur_state_num].role_hv, a, sen_state[cur_state_num].cur_shift);
            Or(subs_vec, subs_vec, init_mem[cur_state_num].role_hv, a);
            Xor(subs_vec, subs_vec, init_mem[0].role_hv, a);

            for (int i=0; i<a;i++) {
                buff_int[i] = buff_int[i] + input_vector[i]; //add new vector to the integer buffer
                buff_int[i] = buff_int[i] - subs_vec[i]; //substitute old vector from the integer buffer
            }
            Buff_int_to_bin(buff_int, buff_bin, a); //update binary buffer

            // Open pending record for item memory
            item_pending[0].cur_role = input_id;
            item_pending[0].cur_shift = input_shift;
            item_pending[0].prev_role = input_id;
            item_pending[0].prev_shift = sen_state[cur_state_num].cur_shift;
            sen_state[cur_state_num].cur_shift = input_shift; // change sensor state in the table
            for (int i=0; i<a;i++) {
                item_pending[0].hp_sen[i] = input_vector[i];
            }
            std::cout << "\t\tInteger and binary buffer updated. Item pending configured \n";
            std::cout << "\t\t\tCurrent Role " << item_pending[0].cur_role << "\n";
            std::cout << "\t\t\tCurrent Shift " << item_pending[0].cur_shift << "\n";
            std::cout << "\t\t\tPrevious Role " << item_pending[0].prev_role << "\n";
            std::cout << "\t\t\tPrevious Shift " << item_pending[0].prev_shift << "\n";

            input_id = 0;
            input_shift = 0;
            sum_adres = 1;
            sum_shift = 1;
            count_adr = 0;
            count_shift = 0;
            k_shift = 1;
         // if vector from actuator
        } else if (input_id == 3) {
        	std::cout << "\t\tMessage from actuator detected \n";
            if (item_pending[0].cur_role != -1) { //if pending record exists
                for (int i=0; i<a;i++) {
                    item_pending[0].hp_act[i] = input_vector[i];
                }
                item_mem[item_len] = item_pending[0]; //add record to the item memory
                item_pending[0].cur_role = -1;
                item_pending[0].cur_shift = 0;
                item_pending[0].prev_role = 0;
                item_pending[0].prev_shift = 0;
                item_len++; // increase item memory length
                std::cout << "\t\tNew entry included in the item memory \n";
            }
            input_id = 0;
            input_shift = 0;
            sum_adres = 1;
            sum_shift = 1;
            count_adr = 0;
            count_shift = 0;
            k_shift = 1;
        }



    }
}

void HvBaseStation::InitializeNodes(TosNodeContainer container)
{
	NS_LOG_FUNCTION(this);
	for (TosNodeContainer::Iterator i = container.Begin(); i != container.End(); i++)
	{
		Ptr<TosNode> node = *i;

		//Configure the two callbacks to send the initialization and
		//random hypervector

	    Callback<int, uint8_t,uint16_t,void *> tmp1=
	              MakeCallback(&Ns3ToTosProxy::InitializationVectorInterrupt,(node->GetNs3ToTosProxy()));
	    this->SetAttribute("InitializationVectorInterrupt", CallbackValue(tmp1));

	    Callback<int, uint8_t,uint16_t,void *> tmp2=
	              MakeCallback(&Ns3ToTosProxy::RandomVectorInterrupt,(node->GetNs3ToTosProxy()));
	    this->SetAttribute("RandomVectorInterrupt", CallbackValue(tmp2));

	    Callback<int, uint8_t,uint16_t,void *> tmp3=
	              MakeCallback(&Ns3ToTosProxy::actuatorInterrupt,(node->GetNs3ToTosProxy()));
	    this->SetAttribute("ActuatorVectorInterrupt", CallbackValue(tmp3));

	    Callback<int, uint8_t,uint16_t,void *> tmp4=
	              MakeCallback(&Ns3ToTosProxy::actuatorHvInterrupt,(node->GetNs3ToTosProxy()));
	    this->SetAttribute("ActuatorInterrupt", CallbackValue(tmp4));

	    // Prepare the initialization vector for each node
	    init1 initial;

	    //srand(node->GetId());
	    initial.id = node->GetId();
	    for (int j = 0; j < a; j++) {
	        initial.role_hv[j] = rand() % 2;
	        //std::cout << initial.role_hv[j];
	    }
	    init_mem[initial.id] = initial;
	    //std::cout << "\n";

	    // Send the information to the sensor
	    m_InitializationVectorInterrupt(0, sizeof(initial), &initial);
	    m_RandomVectorInterrupt(0, sizeof(m_P), &m_P);
	}
}

HvBaseStation::~HvBaseStation ()
{

}

void HvBaseStation::DoDispose (void)
{
  NS_LOG_FUNCTION (this);
  delete[] item_pres;
  delete[] item_check;

  Application::DoDispose ();
}

void HvBaseStation::SendOutputVector(int *output_vector)
{
	 init1* initial;

     initial->id = 3;

     memcpy(initial->role_hv, output_vector, a);

	 m_ActuatorHvVectorInterrupt(0, sizeof(initial), &initial);

}

// Function for Xor operation. Input parameters are two interacting vectors (arr1, arr2), result vector (arr0) and dimensionality (n)
void HvBaseStation::Xor(int *arr0, int *arr1, int *arr2, int n)
{
    for(int i=0;i<n;i++) {
        arr0[i] = arr1[i] ^ arr2[i];
    }
}

// Function for Or operation. Input parameters are two interacting vectors (arr1, arr2), result vector (arr0) and dimensionality (n)
void HvBaseStation::Or(int *arr0, int *arr1, int *arr2, int n)
{
    for(int i=0;i<n;i++) {
        arr0[i] = arr1[i] | arr2[i];
    }
}

// Function for reduced sum calculation of a vector. Input parameters are input vector (arr0) and dimensionality (n)
double HvBaseStation::Sum(int *arr0, int n)
{
	if (n == 0)
	{
	  return 0;
	}
    double res = 0;
    for(int i=0;i<n;i++) {
        res = res + arr0[i];
    }
    res = res / n;
    return res;
}

//Function for obtaining new vector from old one by shifting its. Input parameters are input vector (arr2), dimensionality (n), shifting vector arr1 and shift value in bits (k)
void HvBaseStation::Shift(int *arr1, int *arr2, int n, int k)
{
    for(int i=0;i<n;i++) {
        if (i+k < n) {
        arr1[i+k] = (arr2[i]);
        } else arr1[i + k - n] = arr2[i];
    }
}

//Function for obtaining binary buffer vector from integer one. Input parameters are integer buffer (buff_int), binary buffer (buff_bin), dimensionality (n).
void HvBaseStation::Buff_int_to_bin(int *buff_int, int *buff_bin, int n)
// Convert integer vector to binary
{
    double max = 0; // max maximun number in integer buffer
    for(int i=0;i<n;i++) // cycle for finding maximum number
        {
            if(max<buff_int[i]){
                    max = buff_int[i];
            }
        }
     srand((unsigned)time(NULL)); // seeds generation for rand function
     for(int i=0;i<n;i++) {
         if (buff_int[i] > max/2) { // if i'th position in integer buffer more than max/2 put 1 in binary buffer vector
             buff_bin[i] = 1;
         } else if (buff_int[i] < max/2) { //if i'th position in integer buffer less than max/2 put 0 in binary buffer vector
             buff_bin[i] = 0;
         }else{ //if i'th position in integer buffer equal to max/2 put uniform random number (1 or 0) in binary buffer vector
             if (((double)rand() / RAND_MAX) < 0.5) buff_bin[i] = 0;
             else buff_bin[i] = 1;
         }
     }
}

} // namespace ns3
