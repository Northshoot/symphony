#include "ns3/event-id.h"
#include "ns3/nstime.h"
#include "ns3/simulator.h"
#include <iostream>

namespace ns3 {

  class Test : public Object{
  public:
    Test();
    ~Test();
    void Print(void);
    void Printer(int a);
    void DoStart (void);
  private:
    EventId m_evenId;
  };

  Test::Test() {}
  Test::~Test(){}

  void Test::DoStart(void) {
    m_evenId = Simulator::Schedule (MilliSeconds(1000), &Test::Print, this);
    Object::DoStart();
  }
  void Test::Print( void ){

    m_evenId = Simulator::Schedule (MilliSeconds(1000), &Test::Printer, this,1);
    std::cout<<"Test::Print "  << std::endl;
  }

  void Test::Printer( int a ){
    m_evenId.Cancel();
    std::cout<<"Test::Printer " << a << std::endl;
  }
}
using namespace ns3;

int main(void ){
  Test * t = new Test();
  t->Start();
  ns3::Simulator::Stop(ns3::Seconds(3.0));
  ns3::Simulator::Run();
  ns3::Simulator::Destroy ();
  return 0;
}
