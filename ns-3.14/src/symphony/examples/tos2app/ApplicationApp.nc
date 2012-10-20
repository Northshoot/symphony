
configuration ApplicationApp
{
}
implementation {
  components MainC, ApplicationAppC as App;
  components new TimerMilliC();
  components Ns3ApplicationC as ns;
  
  App.Boot -> MainC.Boot;
  

  App.AppControl -> ns;
  App.MilliTimer -> TimerMilliC;
  App.Ns3Application -> ns;
}