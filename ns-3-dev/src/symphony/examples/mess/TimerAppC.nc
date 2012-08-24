
configuration TimerAppC
{
}
implementation
{
  components MainC, Ns3TimerUser;
  //components NsTimerP as NsTimer;
  components new TimerMilliC() as Timer0;
  components new TimerMilliC() as Timer1;  
  Ns3TimerUser -> MainC.Boot;

  Ns3TimerUser.Timer0->Timer0;
  Ns3TimerUser.Timer1->Timer1;
//  Ns3TimerUser.Timer1 -> NsTimer;
 
  
//  Ns3TimerUser.Timer2 -> NsTimer;
//  Ns3TimerUser.Timer3 -> NsTimer;

}

