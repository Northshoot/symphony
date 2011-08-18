/*
 * wifi-wsn.h
 *
 *  Created on: Aug 16, 2011
 *      Author: lauril
 */

#ifndef WIFIWSN_H_
#define WIFIWSN_H_
#include "ns3/wifi-phy.h"
namespace ns3 {
	

class PhyMyListener : public WifiPhyListener
{
public:
  PhyMyListener ();
   ~PhyMyListener ();
   void NotifyRxStart (Time duration);
   void NotifyRxEndOk (void);
   void NotifyRxEndError (void);
   void NotifyTxStart (Time duration);
   void NotifyMaybeCcaBusyStart (Time duration);
   void NotifySwitchingStart (Time duration);

  
};
}
#endif /* WIFIWSN_H_ */
