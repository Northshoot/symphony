configuration SensorApp
{
}
implementation {
  components MainC, SensorAppC as App;
  components MagnetomiterC;
  
  App.Boot -> MainC.Boot;
  
  App.SensorControl -> MagnetomiterC.SplitControl;
  App.DataIn -> MagnetomiterC.InterruptWithData;

}