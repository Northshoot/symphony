/*
 * tos-application.h
 *
 *  Created on: Oct 19, 2012
 *      Author: lauril
 */

#ifndef TOS_APPLICATION_H_
#define TOS_APPLICATION_H_

#include "ns3/application.h"
#include "ns3/simulator.h"
#include "ns3/callback.h"

namespace ns3
{

  class SymphonyApplication : public ns3::Application

  {
    /**
     * Notification when the application is started
     */
    typedef Callback<void, int> StartDone;
    /**
     * Notification when application is stopped
     */
    typedef Callback<void, int> StopDone;
    /**
     * Call for sending data to the application.
     * Only buffer is accepted right now.
     */
    typedef Callback<uint8_t, void *> SendDataToApplication;
    typedef Callback<void *, uint8_t, void *> ReceiveDataFromApplication;

  public:
    static TypeId GetTypeId (void);
    SymphonyApplication();
    virtual
    ~SymphonyApplication();
    /**
     * Start the application
     */
    void
    StartNS3Application(void);
    /**
     * Stop the application
     */
    void
    StopNS3Application(void);
    /**
     * Call for sending data to the application.
     * Only buffer is accepted right now.
     * Override it for other usage.
     */
    virtual uint8_t
    SendData(void *);



  private:
    virtual void StartApplication (void);
    virtual void StopApplication (void);
    virtual void DoDispose (void);
    uint32_t GetApplicationId (void) const;
    Time m_startTime;
    bool m_started;

    StartDone m_startDone;
    StopDone m_stopDone;
    ReceiveDataFromApplication m_sendDataUp;

  };

} /* namespace ns3 */
#endif /* TOS_APPLICATION_H_ */
