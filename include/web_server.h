#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include <WebServer.h>

extern WebServer server;
extern bool ledState;

void serverStart();
void serverSetupRoutes();

void handleRoot();
void ledOn();
void ledOff();
void handleCaptivePortal();
void handleNotFound();

#endif
