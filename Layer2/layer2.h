#ifndef __LAYER2__
#define __LAYER2__

#include "../net.h"
#include "../gluethread/glthread.h"

// pragma: compiler not insert any padding bytes in between members of data
#pragma pack (push, 1)
typedef struct ethernet_hdr_ {
  // ethernet header
  mac_add_t dst_mac; // destination
  mac_add_t src_mac; // source
  short type;
  char payload[248]; // Max allowed 1500
  unsigned int FCS; // Frame Check Sequence
} ethernet_hdr_t;
#pragma pack(pop)

/* decide whether routing device should accept or reject the incoming packet
 * arrived on an interface operating in L3 mode */
static inline bool_t
l2_frame_recv_qualify_on_interface(interface_t *interface, ethernet_hdr_t *ethernet_hdr) {
  // if the interface is not working in L3 mode, return false;
  if (!IS_INTF_L3_MODE(interface)) return FALSE;
  // return true if receiving machine must accept the frame
  if (memcmp(IF_MAC(interface), ethernet_hdr->dst_mac.mac, sizeof(mac_add_t)) == 0) {
    // memcmp: compare first n bytes between two strings
    return TRUE;
  }
  // dst mac in ethernet header is BROADCAST MAC
  if (IS_MAC_BROADCAST_ADDR(ethernet_hdr->dst_mac.mac)) {
    return TRUE;
  }
  return FALSE;
}

#endif