#include <EspMQTTClient.h>
#include <ArduinoJson.h>
#include <TimerMs.h>
#include <GyverPortal.h>
#include <EEManager.h>
#include <ESPRelay.h>
#include <Button.h>

String version = "2.1.3";
#define LIGHT_THEME 0
#define DARK_THEME 1
#define RELAY_PIN 12
#define BUTTON_PIN 0

struct Data {
  //Data
  char label[32] = "Sonoff";
  char device_name[32] = "sonoff";
  bool relayInvertMode = false;
  bool factoryReset = true;
  byte wifiConnectTry = 0;
  bool wifiAP;
  bool relaySaveStatus = false;
  bool state;
  int  theme = LIGHT_THEME;
  // WiFi
  char ssid[32];
  char password[32];
  //MQTT
  char mqttServerIp[32];
  short mqttServerPort = 1883;
  char mqttUsername[32];
  char mqttPassword[32];
  //Delay before send message in seconds
  int status_delay = 10;
  int avaible_delay = 60;
  //MQTT Topic
  char discoveryTopic[100] = "homeassistant/switch/sonoff/config";
  char commandTopic[100]   = "homeassistant/switch/sonoff/set";
  char avaibleTopic[100]   = "homeassistant/switch/sonoff/avaible";
  char stateTopic[100]     = "homeassistant/switch/sonoff/state";
};

#define WIFIAPTIMER 180000
Data data;
GyverPortal portal;
EEManager memory(data);
GPlog glog("log");
WiFiEventHandler onSoftAPModeStationConnected, onSoftAPModeStationDisconnected, onStationModeConnected;

struct Form{
  const char* root = "/";
  const char* log = "/log";
  const char* config = "/config";
  const char* preferences = "/config/preferences";
  const char* WiFiConfig ="/config/wifi_config";
  const char* mqttConfig = "/config/mqtt_config";
  const char* factoryReset = "/config/factory_reset";
  const char* firmwareUpgrade = "/ota_update";
};

Form form;
TimerMs MessageTimer, ServiceMessageTimer, WiFiApTimer, wifiApStaTimer;
EspMQTTClient mqttClient;
ESPRelay Relay1;
bool resetAllow;
Button button;

void publishRelay();
void SendDiscoveryMessage();
void SendAvailableMessage(const String &mode );
void wifiAp();
void wifiConnect();
void mqttPublish();
void factoryReset();
void changeRelayState();
void mqttStart();
void restart();


#include <webface.h>
#include <function.h>
#include <mqtt.h>

void setup() {
  startup();
}

void loop(){
  mqttClient.loop();
  mqttPublish();
  portal.tick();
  WiFiApTimer.tick(); 
  wifiApStaTimer.tick();
  button.tick();
}