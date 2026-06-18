#include "dns_captive.h"

DNSServer dnsServer;

void dnsStart(IPAddress ip) {
    dnsServer.start(53, "*", ip);
}

void dnsProcess() {
    dnsServer.processNextRequest();
}
