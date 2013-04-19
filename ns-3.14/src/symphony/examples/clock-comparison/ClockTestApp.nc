
configuration ClockTestApp
{
}
implementation {
  components MainC, LedsC, RealTimeClockC, ClockTestC as App;
  components new TimerMilliC();

  
  App.Boot -> MainC.Boot;
  App.MilliTimer -> TimerMilliC;
  App.Leds -> LedsC;
  App.RTC -> RealTimeClockC;

}
