#ifndef DNS_CAPTIVE_H
#define DNS_CAPTIVE_H

#include <DNSServer.h>

extern DNSServer dnsServer;

void dnsStart(IPAddress ip);
void dnsProcess();

#endif
