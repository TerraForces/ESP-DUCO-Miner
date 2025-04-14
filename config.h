#ifndef CONFIG_H
#define CONFIG_H

///////////////////////////////////////////////////////////////////////
//                                                                   //
//             Important Settings (needed for operation)             //
//                                                                   //
///////////////////////////////////////////////////////////////////////

// change CoolUsername to your DuinoCoin username to receive mining rewards
#define DUCO_NAME "CoolUsername"

// insert your mining key between the quotes if you have set one
#define MINING_KEY ""

// change MyWiFiName to the name (SSID) of the WiFi network you want to use for mining
#define WIFI_SSID "MyWiFiName"

// insert your WiFi password between the quotes or leave empty if you have not set one
#define WIFI_KEY ""


///////////////////////////////////////////////////////////////////////
//                                                                   //
//   Optional Settings (purely cosmetical, not necessary to change)  //
//                                                                   //
///////////////////////////////////////////////////////////////////////

// miner name ("Identifier") shown in the miner list on your dashboard
#define MINER_NAME "Lightweight ESP Miner"

// software name shown in the miner details tab on your dashboard
#define SOFTWARE_NAME "Lightweight ESP DUCO Miner 1.1"


///////////////////////////////////////////////////////////////////////
//                                                                   //
//   Advanced Settings (change only if you know what you're doing)   //
//                                                                   //
///////////////////////////////////////////////////////////////////////

// starting difficulty ("ESP8266H" for ESP8266 and "ESP32" for ESP32 MCUs)
#ifdef ESP8266
	#define START_DIFFICULTY "ESP8266H"
#else
	#define START_DIFFICULTY "ESP32"
#endif

// mining core count (2 for ESP32 or ESP32-S3, 1 for any other ESP32/ESP8266)
#define CORE_COUNT SOC_CPU_CORES_NUM

// core 0 task delay to avoid watchdog (in ticks, normally equal to milliseconds)
#define TASK_DELAY_0 10

#endif