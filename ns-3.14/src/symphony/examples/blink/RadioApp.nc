
configuration RadioApp
{
}
implementation {
  components MainC, LedsC, RadioTestC as App;
  components new TimerMilliC();

  
  App.Boot -> MainC.Boot;
  App.MilliTimer -> TimerMilliC;
  App.Leds -> LedsC;

}