#ifndef __TYPES_H__
#define __TYPES_H__
#include <WString.h>
typedef unsigned char uint8_t;
struct AccessPoint {
  short power;
  short channel;
  String ssid;
  uint8_t *mac;
  bool secured;
};

struct arp_head
{   uint16_t htype;      /* Hardware Type           */
    uint16_t ptype;      /* Protocol Type           */
    uint8_t hlen;        /* Hardware Address Length */
    uint8_t plen;        /* Protocol Address Length */
    uint16_t oper;       /* Operation Code          */
    uint8_t sha[6];      /* Sender hardware address */
    uint8_t spa[4];      /* Sender IP address       */
    uint8_t tha[6];      /* Target hardware address */
    uint8_t tpa[4];      /* Target IP address       */

} __attribute__((packed));

struct eth_head{
  unsigned char  dest[6];
  unsigned char  src[6];
  unsigned short eth_type;
  arp_head       arp;
} __attribute__((packed));


#endif