#include<linux/netfilter.h>
#include<linux/skbuff.h>
#include <linux/netfilter_ipv4.h>
#include<linux/ip.h>
#include<linux/module.h>
#include<net/net_namespace.h>
MODULE_LICENSE("GPL");
static struct nf_hook_ops local_in_nfho;

unsigned int local_in_hook_func(void *priv, struct sk_buff *skb,
				const struct nf_hook_state *state)
{
	/*struct sk_buff *sb = *skb;*/
	struct iphdr *iph = ip_hdr(skb);

	if (iph->protocol != IPPROTO_UDP) {
		//return NF_ACCEPT;
              return NF_DROP;
	}
	return NF_ACCEPT;
	//return handle_udp_packet(skb);
}


int  hello_module_init(void)
{
	local_in_nfho.hook = local_in_hook_func;
	local_in_nfho.hooknum = NF_INET_LOCAL_IN;
        local_in_nfho.pf = PF_INET;
	local_in_nfho.priority = NF_IP_PRI_FIRST;
	nf_register_net_hook(&init_net,&local_in_nfho);
       return 0;
}

void hello_module_exit(void)
{
    nf_unregister_net_hook(&init_net,&local_in_nfho);
}

module_init(hello_module_init);
module_exit(hello_module_exit);
