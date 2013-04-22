
configuration ClockTestApp
{
}
implementation {
  components MainC, LedsC, ClockTestC as App;
  components new TimerMilliC();

  
  App.Boot -> MainC.Boot;
  App.MilliTimer -> TimerMilliC;
  App.Leds -> LedsC;

}
