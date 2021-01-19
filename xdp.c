#include <linux/kernel.h>
#include <linux/netdevice.h>
#include <linux/errno.h>	

#include <linux/atomic.h>	// xchg()
#include <linux/filter.h>	// u32 bpf_prog_run_xdp(const struct bpf_prog *prog, 
				// 				struct xdp_buff *xdp) 
#include <linux/if_ether.h>	// Macros ETH_*

#include <linux/bpf.h>		// bpf_prog_put

#include "e1000.h"


#define DEBUG	1

int __xdp_setup_prog(struct net_device *dev, struct netdev_bpf *bpf) {
	struct e1000_adapter *adapter;
	struct bpf_prog *prev;

	adapter = netdev_priv(dev);

#if DEBUG == 1
	printk("[E1000E-XDP]: dev 0x%lx bpf->prog 0x%lx\n", (unsigned long)dev, 
							(unsigned long)bpf->prog);
#endif

	prev = xchg(&adapter->xdp_prog, bpf->prog);
	if (prev)
		bpf_prog_put(prev);

	return 0;
}

int e1000e_bpf(struct net_device *dev, struct netdev_bpf *bpf) {
	struct e1000_adapter *adapter;

	switch (bpf->command) {

	case XDP_SETUP_PROG:
		return __xdp_setup_prog(dev, bpf);

	case XDP_SETUP_XSK_UMEM:
		return 0;

	case XDP_QUERY_PROG:
		adapter = netdev_priv(dev);
		bpf->prog_id = adapter->xdp_prog ?
				adapter->xdp_prog->aux->id : 0;
		return 0;

	default:
		return -EINVAL;
	}

	return 0;
}

int e1000e_xsk_wakeup(struct net_device *dev, unsigned int qid,
			unsigned int flags) {
	return 0;
}

int e1000e_xdp_xmit(struct net_device *dev, int n, 
			struct xdp_frame **xdp) {

	return 0;
}
