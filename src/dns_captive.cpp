#include "dns_captive.h"

DNSServer dnsServer;

void dnsBaslat(IPAddress ip) {
    dnsServer.start(53, "*", ip);
}

void dnsIsle() {
    dnsServer.processNextRequest();
}
