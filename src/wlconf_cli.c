#include <stdio.h>
#include "wlconf.h"

int main (int argc, char **argv)
{
	/* alloc wlconf */
	struct wlconf *wlconf;
	wlconf = wlconf_alloc();

	/* Basic configuration */
	wlconf->set_ssid_hidden(wlconf, false);
	wlconf->set_ssid(wlconf, "testssid");
	wlconf->set_hwmode(wlconf, ONLY_N);
	wlconf->set_encryption(wlconf, WPA_WPA2_MIXED);
	wlconf->set_key(wlconf, "kkkkk");
	wlconf->set_channel(wlconf, "1");

	/* MAC Filter configuration */
	wlconf->set_macfilter(wlconf, MAC_FILTER_NONE);
	//wlconf->set_macfilter(wlconf, MAC_FILTER_ALLOW);
	//wlconf->add_macfilterlist(wlconf, "aa:aa:aa:aa:aa:aa");
	//wlconf->set_macfilter(wlconf, MAC_FILTER_DENY);

	/* Get Confuguration */
	printf("ssid:%s\n", wlconf->conf->ssid);
	printf("channel:%s\n", wlconf->conf->channel);
	printf("hwmode:%s\n", wlconf->conf->hwmode);
	printf("encryption:%s\n", wlconf->conf->encryption);
	printf("key:%s\n", wlconf->conf->key);
	printf("channel:%s\n", wlconf->conf->channel);
	printf("macfilter:%s\n", wlconf->conf->macfilter);

	/* Get MAC Filter List */
	struct maclist_node *node;
	mlist_foreach_element(wlconf->conf->macfilter_list, node)
	{
		printf("allow mac:%s\n", node->macaddr);
	}
	
	/* Commit your changes */
	wlconf->change_commit(wlconf);
	
	/* destroy wlconf */
	wlconf_free(wlconf);
}