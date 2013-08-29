configuration BlinkAppC
{
}

implementation
{
  components MainC, BlinkC, RandomC;

  BlinkC -> MainC.Boot;
  BlinkC -> RandomC.Random;
}

