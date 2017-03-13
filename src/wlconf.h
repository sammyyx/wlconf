#include <uci.h>
#include <stdbool.h>

#define ESSID_MAX_SIZE 32

#define WPA2_PSK "psk2"
#define WPA_PSK "psk"
#define WPA_WPA2_MIXED "psk-mixed"

#define ONLY_N	"11g"

#define MAC_FILTER_DENY "deny"
#define MAC_FILTER_ALLOW "allow"
#define MAC_FILTER_NONE "none"

#define mlist_foreach_element(_list, _node)\
		for (_node = _list->head;\
			_node != NULL;\
			_node = _node->next)

struct maclist_node
{
	char macaddr[20];
	struct maclist_node *next;
};

struct maclist
{
	int listsize;
	struct maclist_node *head;
	struct maclist_node *tail;
	int (*add_member)(struct maclist *, char *macaddr);
	int (*del_member)(struct maclist *, char *macaddr);
	void (*free_maclist)(struct maclist *);
};

struct uci_conf
{
	char ssid[ESSID_MAX_SIZE];
	char channel[2];
	char encryption[16];
	char key[64];
	char macfilter[5];
	bool hidden;
	char hwmode[5];
	struct maclist *macfilter_list;
};

struct wlconf
{
	struct uci_package *pkg;
	struct uci_context *ctx;
	
	struct uci_conf *conf;

	int (*set_ssid)(struct wlconf *, char *ssid);
	int (*set_channel)(struct wlconf *, char *channel);
	int (*set_hwmode)(struct wlconf *, char *hwmode);
	int (*set_ssid_hidden)(struct wlconf *, bool hidden);
	int (*set_encryption)(struct wlconf *, char *encryption);
	int (*set_key)(struct wlconf *, char *key);
	int (*set_macfilter)(struct wlconf *, char *macfilter);
	int (*add_macfilterlist)(struct wlconf *, char *macaddr);
	int (*del_macfilterlist)(struct wlconf *, char *macaddr);
};

struct wlconf *wlconf_alloc(void);
void wlconf_free(struct wlconf *);
int set_uci_conf(struct wlconf *);
struct maclist *maclist_alloc(void);