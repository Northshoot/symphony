
configuration ThroughputApp
{
}
implementation {
  components MainC, RealTimeClockC, ThroughputC as App;
   components new AMSenderC(12);
  components new AMReceiverC(12);
  components new TimerMilliC();
  components ActiveMessageC;
  components NsTimerP;
  
  App.Boot -> MainC.Boot;
  
  App.Receive -> AMReceiverC;
  App.AMSend -> AMSenderC;
  App.AMControl -> ActiveMessageC;
  App.MilliTimer -> TimerMilliC;
  App.Packet -> AMSenderC;
  App.RTC -> NsTimerP;

}
