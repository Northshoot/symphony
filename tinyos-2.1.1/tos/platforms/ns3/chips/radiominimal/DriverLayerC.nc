/*
 * Minimal wrapper holding the chip specific driver.
 * @author: Robert Samuelsson <meeeeeep@gmail.com>
 */

configuration DriverLayerC
{
	provides
	{
		interface RadioState;
		interface RadioSend;
		interface RadioReceive;
		interface RadioCCA;
		interface RadioPacket;

		interface PacketField<uint8_t> as PacketTransmitPower;
		interface PacketField<uint8_t> as PacketRSSI;
		interface PacketField<uint8_t> as PacketTimeSyncOffset;
		interface PacketField<uint8_t> as PacketLinkQuality;

		interface LocalTime<TRadio> as LocalTimeRadio;
	}

	uses
	{
		interface PacketTimeStamp<TRadio, uint32_t>;
	}
}

implementation
{
	/*
	 * Want to use another driver?
	 * (1) Switch driver component in designated area below
	 * (2) Make sure it provides same interfaces as this component
	 */

	/*** 1 ***************************************/

	components RF230DriverLayerC as Driver;
	components RF230DriverConfigC as Config;

	// Driver specific configuration
	Driver -> Config.RF230DriverConfig;

	// Resolve config dependencies
	components Ieee154PacketLayerC;
	Config.Ieee154PacketLayer -> Ieee154PacketLayerC;


	/*** 2 ***************************************/

	// Uses
	// Satisfy extra dependencies above in step (1)
	// OR change uses of this file (DriverLayerC) and the wiring in RadioC
	Driver               = PacketTimeStamp;

	// Provides
	RadioState           = Driver;
	RadioSend            = Driver;
	RadioReceive         = Driver;
	RadioCCA             = Driver;
	RadioPacket          = Driver;

	PacketTransmitPower  = Driver.PacketTransmitPower;
	PacketRSSI           = Driver.PacketRSSI;
	PacketTimeSyncOffset = Driver.PacketTimeSyncOffset;
	PacketLinkQuality    = Driver.PacketLinkQuality;

	LocalTimeRadio       = Driver;
}
