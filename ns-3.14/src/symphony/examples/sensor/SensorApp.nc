configuration SensorApp
{
}
implementation {
  components MainC, SensorAppC as App;
  components TemperatureSensorC;
  components new TimerMilliC() as Timer0;
  
  App.Boot -> MainC.Boot;
  App.Timer0 -> Timer0;
  App.SensorControl -> TemperatureSensorC.SplitControl;
  App.DataIn -> TemperatureSensorC.InterruptWithData;

}
