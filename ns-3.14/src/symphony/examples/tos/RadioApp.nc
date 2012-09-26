
configuration RadioApp
{
}
implementation {
  components MainC, RadioTestC as App;
  components new AMSenderC(30);
  components new AMReceiverC(30);
  components new TimerMilliC();
  components ActiveMessageC;
  
  App.Boot -> MainC.Boot;
  
  App.Receive -> AMReceiverC;
  App.AMSend -> AMSenderC;
  App.AMControl -> ActiveMessageC;
  App.MilliTimer -> TimerMilliC;
  App.Packet -> AMSenderC;
}