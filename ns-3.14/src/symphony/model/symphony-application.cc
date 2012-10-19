/*
 * tos-application.cc
 *
 *  Created on: Oct 19, 2012
 *      Author: lauril
 */

#include "ns3/assert.h"
#include "ns3/log.h"
#include "symphony-application.h"

namespace ns3
{
  NS_LOG_COMPONENT_DEFINE ("SymphonyApplication");
  NS_OBJECT_ENSURE_REGISTERED (SymphonyApplication);

  SymphonyApplication::SymphonyApplication():m_started(false) { }

  TypeId
  SymphonyApplication::GetTypeId(void)
  {
    static TypeId tid = TypeId ("ns3::SymphonyApplication")
      .SetParent<Application> ()
      .AddConstructor<SymphonyApplication> ()
      .AddAttribute("StartDone","Callback for application start done event.",
          CallbackValue(),
          MakeCallbackAccessor(&SymphonyApplication::m_startDone),
          MakeCallbackChecker ())
       .AddAttribute("StopDone","Callback for sensor stop done event.",
                       CallbackValue(),
                       MakeCallbackAccessor(&SymphonyApplication::m_stopDone),
                       MakeCallbackChecker ())
       .AddAttribute("ReceiveDataFromApplication","Callback for application to forwarding data to TinyOS.",
                                    CallbackValue(),
                                    MakeCallbackAccessor(&SymphonyApplication::m_sendDataUp),
                                    MakeCallbackChecker ())
       ;
    return tid;
  }

  SymphonyApplication::~SymphonyApplication() {}

  void
  SymphonyApplication::StartNS3Application(void)
  {
    StartApplication();
    NS_ASSERT(m_startTime < Simulator::Now());
    NS_ASSERT(!m_startDone.IsNull());
    m_started = true;
    m_startDone(0);

  }

  void
  SymphonyApplication::StopNS3Application(void)
  {
    NS_ASSERT(m_started);
    NS_ASSERT(!m_stopDone.IsNull());
    m_started =false;
    m_stopDone(0);
  }

  uint8_t
  SymphonyApplication::SendData(void*)
  {
    NS_ASSERT(!m_started);
    //TODO: Do something with data
    //ex;
    typedef struct {
      uint32_t counter;
      uint32_t nodeTime;
    } NodePacket;

    NodePacket *npkt;
    npkt= (NodePacket*) malloc(sizeof(NodePacket));
    NS_LOG_UNCOND("Node sent counter " <<npkt->counter<<" at time "<<npkt->nodeTime);
    delete npkt;
    return 0;
  }

  void
  SymphonyApplication::StartApplication(void)
  {
    NS_LOG_FUNCTION (this);
    m_startTime = Simulator:: Now();
    m_started = true;
    Application::DoStart();

  }

  void
  SymphonyApplication::StopApplication(void)
  {
    m_started = false;
  }

  void
  SymphonyApplication::DoDispose(void)
  {
    NS_LOG_FUNCTION (this);
    Application::DoDispose ();
  }

  uint32_t
  SymphonyApplication::GetApplicationId(void) const
  {
    Ptr<Node> node = GetNode ();
    for (uint32_t i = 0; i < node->GetNApplications (); ++i)
      {
        if (node->GetApplication (i) == this)
          {
            return i;
          }
      }
    NS_ASSERT_MSG (false, "forgot to add application to node");
    return 0; // quiet compiler
  }

} /* namespace ns3 */
