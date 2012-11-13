
configuration RadioApp
{
}
implementation {
  components MainC, RadioTestC as App;
  components new TimerMilliC();

  
  App.Boot -> MainC.Boot;
  App.MilliTimer -> TimerMilliC;


}