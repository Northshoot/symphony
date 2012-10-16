module SensorAppC {
    uses {
        interface Boot;
        interface SplitControl as SensorControl;
        interface InterruptWithData as DataIn;
    }
}
implementation {

 
    event void Boot.booted() {
        printf("App: booted %d\n", TOS_NODE_ID);
       call SensorControl.start();
    }

    event void SensorControl.startDone(error_t err) {
        if (err == SUCCESS) {
          printf("SensorControl.startDone: TOS_NODE_ID == %d\n", TOS_NODE_ID);
          fflush(stdout);
        }else {
            call SensorControl.start();
        }
    }

    event void SensorControl.stopDone(error_t err) {
        // do nothing
    }
 


    async event void DataIn.interruptWithData(error_t result, uint16_t length, void * buffer) {
            printf("event void InterruptWithData.interruptWithData NODE_ID %d - data lenght %d\n",TOS_NODE_ID, length);
    }

}