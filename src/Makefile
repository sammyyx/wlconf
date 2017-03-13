wlconf:wlconf_cli.o wlconf.o
	$(CC) $(LDFLAGS) -luci wlconf_cli.o wlconf.o -o wlconf

wlconf.o:wlconf.c
	$(CC) $(CFLAGS) -c wlconf.c

wlconf_cli.o:wlconf_cli.c
	$(CC) $(CFLAGS) -c wlconf_cli.c

clean:
	rm *.o wlconf
