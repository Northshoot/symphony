configuration SensorApp
{
}
implementation {
  components MainC, SensorAppC as App;
  components MagnetomiterC;
  components new TimerMilliC() as Timer0;
  
  App.Boot -> MainC.Boot;
  App.Timer0 -> Timer0;
  App.SensorControl -> MagnetomiterC.SplitControl;
  App.DataIn -> MagnetomiterC.InterruptWithData;

}