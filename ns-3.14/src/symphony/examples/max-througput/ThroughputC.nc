#include "Timer.h"
#include "ns3/calls-to-ns3.h"

#include "Timer.h"

typedef nx_struct radio_count_msg {
  nx_uint16_t counter;
  nx_uint32_t a;
  nx_uint32_t b;
  nx_uint32_t c;
  nx_uint32_t d;
} radio_count_msg_t;

module ThroughputC @safe() {
  uses {
    interface Boot;
    interface Receive;
    interface AMSend;
    interface Timer<TMilli> as MilliTimer;
    interface SplitControl as AMControl;
    interface Packet;
    interface AMPacket;
    interface RealTimeClock as RTC;

  }
}
implementation {
  
  void task send();

  uint32_t time_exec=0;
  uint64_t time_rt=0;
 
  
  message_t packet;
  uint8_t dest=1;
  bool locked;
  uint16_t counter = 0;
 
  event void Boot.booted() {
    call AMControl.start();

  }

  event void AMControl.startDone(error_t err) {
    //printf("AMControl.startDone: TOS_NODE_ID == %d\n", TOS_NODE_ID);
    if (err == SUCCESS) {
      if (TOS_NODE_ID == 0)
          post send();       
 
      ////printf("AMControl.startDone: TOS_NODE_ID == %d\n", TOS_NODE_ID);
    }else {
      call AMControl.start();
    }
  }
 
  void task send(){
    error_t sendErr;
 
    counter++;
    if (locked) {
      printf("LOCKED\n");
      return;
    }
    else {
      radio_count_msg_t* rcm = (radio_count_msg_t*)call Packet.getPayload(&packet, sizeof(radio_count_msg_t));
      if (rcm == NULL) {
        printf("rcm == NULL\n");
        return;
      }
      rcm->counter = counter;
      rcm->a = 178956970;
      rcm->b = 196852667;
      rcm->c = 214748364;
      rcm->d = 232644061;
      sendErr = call AMSend.send(dest, &packet, sizeof(radio_count_msg_t));
      if (sendErr == SUCCESS) {
        locked = TRUE;
        time_exec = call MilliTimer.getNow();
        time_rt = call RTC.getTime(MILLISECOND);
        printf("task send():: \t\tlocal %lu - sim %lu\n",time_exec, time_rt);
      } else {
        printf("call AMSend.send error: %u\n",sendErr);
      }
 
    }
  }
  event void AMSend.sendDone(message_t* bufPtr, error_t error) {
    if (&packet == bufPtr) {
      locked = FALSE;
      time_exec = call MilliTimer.getNow();
      time_rt = call RTC.getTime(MILLISECOND);
      printf("AMSend.sendDone:: \tlocal %lu - sim %lu\n",time_exec, time_rt);
      post send();
    } else {
      printf("ERROR: AMSend.sendDone &packet != bufPtr \n");
    }

  }
 
  event void MilliTimer.fired() {
    time_exec = call MilliTimer.getNow();
    time_rt = call RTC.getTime(MILLISECOND);
    dbg("Info", "Fired %u\n", time_exec);
    //printf("%lu\n", time_rt);
  }
    event message_t* Receive.receive(message_t* bufPtr, 
            void* payload, uint8_t len) {
              time_exec = call MilliTimer.getNow();
              time_rt = call RTC.getTime(MILLISECOND);
              printf("Receive.receive:: \t\tlocal %lu - sim %lu\n",time_exec, time_rt);
              return bufPtr;
            }

    event void AMControl.stopDone(error_t err) {
        // do nothing
    }

}




