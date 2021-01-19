#ifndef __E1000E_XDP_H__
#define __E1000E_XDP_H__
#include <linux/netdevice.h>
extern int e1000e_bpf(struct net_device *dev, struct netdev_bpf *bpf);
extern int e1000e_xsk_wakeup(struct net_device *dev, unsigned int qid, 
				unsigned int flags);
extern int e1000e_xdp_xmit(struct net_device *dev, int n,
				struct xdp_frame **xdp, unsigned int flags);
#endif
