#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include <WebServer.h>

extern WebServer server;
extern bool ledDurum;

void serverBaslat();
void serverRotalariEkle();

void anaSayfa();
void ledAc();
void ledKapat();
void handleCaptivePortal();
void handleNotFound();

#endif
