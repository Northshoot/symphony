
#ifndef RADIO_COUNT_TO_LEDS_H
#define RADIO_COUNT_TO_LEDS_H

#ifndef TOSH_DATA_LENGTH
#define TOSH_DATA_LENGTH 121
#else
#undef TOSH_DATA_LENGTH
#define TOSH_DATA_LENGTH 121
#endif


typedef nx_struct radio_count_msg {
  nx_uint8_t counter[121];
} radio_count_msg_t;

enum {
  AM_RADIO_COUNT_MSG = 6,
};

#endif
