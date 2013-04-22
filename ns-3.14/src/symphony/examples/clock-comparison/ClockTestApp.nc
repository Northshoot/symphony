
configuration ClockTestApp
{
}
implementation {
  components MainC, LedsC, RealTimeClockC, ClockTestC as App;
  components new TimerMilliC();
  components NsTimerP;

  
  App.Boot -> MainC.Boot;
  App.MilliTimer -> TimerMilliC;
  App.Leds -> LedsC;
  App.RTC -> NsTimerP;

}
