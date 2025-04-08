#pragma GCC optimize("-Ofast")

#include <Arduino.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include "config.h"

class DSHA1 {
public:
	
	DSHA1() {
		initialize(s);
	}

	DSHA1 &write(const uint8_t* data, size_t len) {
		size_t bufsize = bytes % 64;
		if (bufsize && bufsize + len >= 64) {
			memcpy(buf + bufsize, data, 64 - bufsize);
			bytes += 64 - bufsize;
			data += 64 - bufsize;
			transform(s, (uint32_t*)buf);
			bufsize = 0;
		}
		while (len >= 64) {
			transform(s, (uint32_t*)data);
			bytes += 64;
			data += 64;
			len -= 64;
		}
		if (len > 0) {
			memcpy(buf + bufsize, data, len);
			bytes += len;
		}
		return *this;
	}

	void finalize(uint32_t hash[5]) {
		const uint8_t pad[64] = { 0x80 };
		uint64_t sizedesc = __builtin_bswap64(bytes << 3);
		write(pad, 1 + ((119 - (bytes % 64)) % 64));
		write((uint8_t*)(&sizedesc), 8);
		hash[0] = __builtin_bswap32(s[0]);
		hash[1] = __builtin_bswap32(s[1]);
		hash[2] = __builtin_bswap32(s[2]);
		hash[3] = __builtin_bswap32(s[3]);
		hash[4] = __builtin_bswap32(s[4]);
	}

	DSHA1 &reset() {
		bytes = 0;
		initialize(s);
		return *this;
	}

	// IDK who invented this, but it does not work without it
	DSHA1& warmup() {
		uint32_t warmup[5];
		this->write((uint8_t *)"warmupwarmupwa", 20).finalize(warmup);
		return *this;
	}

private:
	uint32_t s[5];
	unsigned char buf[64];
	uint64_t bytes;

	const uint32_t k1 = 0x5A827999ul;
	const uint32_t k2 = 0x6ED9EBA1ul;
	const uint32_t k3 = 0x8F1BBCDCul;
	const uint32_t k4 = 0xCA62C1D6ul;

	uint32_t inline f1(uint32_t b, uint32_t c, uint32_t d) { return d ^ (b & (c ^ d)); }
	uint32_t inline f2(uint32_t b, uint32_t c, uint32_t d) { return b ^ c ^ d; }
	uint32_t inline f3(uint32_t b, uint32_t c, uint32_t d) { return (b & c) | (d & (b | c)); }

	uint32_t inline left(uint32_t x) { return (x << 1) | (x >> 31); }

	void inline Round(uint32_t a, uint32_t &b, uint32_t c, uint32_t d, uint32_t &e, uint32_t f, uint32_t k, uint32_t w) {
		e += ((a << 5) | (a >> 27)) + f + k + w;
		b = (b << 30) | (b >> 2);
	}

	void initialize(uint32_t s[5]) {
		s[0] = 0x67452301ul;
		s[1] = 0xEFCDAB89ul;
		s[2] = 0x98BADCFEul;
		s[3] = 0x10325476ul;
		s[4] = 0xC3D2E1F0ul;
	}

	void transform(uint32_t *s, const uint32_t* chunk) {
		uint32_t a = s[0], b = s[1], c = s[2], d = s[3], e = s[4];
		uint32_t w0, w1, w2, w3, w4, w5, w6, w7, w8, w9, w10, w11, w12, w13, w14, w15;

		Round(a, b, c, d, e, f1(b, c, d), k1, w0 = __builtin_bswap32(chunk[0]));
		Round(e, a, b, c, d, f1(a, b, c), k1, w1 = __builtin_bswap32(chunk[1]));
		Round(d, e, a, b, c, f1(e, a, b), k1, w2 = __builtin_bswap32(chunk[2]));
		Round(c, d, e, a, b, f1(d, e, a), k1, w3 = __builtin_bswap32(chunk[3]));
		Round(b, c, d, e, a, f1(c, d, e), k1, w4 = __builtin_bswap32(chunk[4]));
		Round(a, b, c, d, e, f1(b, c, d), k1, w5 = __builtin_bswap32(chunk[5]));
		Round(e, a, b, c, d, f1(a, b, c), k1, w6 = __builtin_bswap32(chunk[6]));
		Round(d, e, a, b, c, f1(e, a, b), k1, w7 = __builtin_bswap32(chunk[7]));
		Round(c, d, e, a, b, f1(d, e, a), k1, w8 = __builtin_bswap32(chunk[8]));
		Round(b, c, d, e, a, f1(c, d, e), k1, w9 = __builtin_bswap32(chunk[9]));
		Round(a, b, c, d, e, f1(b, c, d), k1, w10 = __builtin_bswap32(chunk[10]));
		Round(e, a, b, c, d, f1(a, b, c), k1, w11 = __builtin_bswap32(chunk[11]));
		Round(d, e, a, b, c, f1(e, a, b), k1, w12 = __builtin_bswap32(chunk[12]));
		Round(c, d, e, a, b, f1(d, e, a), k1, w13 = __builtin_bswap32(chunk[13]));
		Round(b, c, d, e, a, f1(c, d, e), k1, w14 = __builtin_bswap32(chunk[14]));
		Round(a, b, c, d, e, f1(b, c, d), k1, w15 = __builtin_bswap32(chunk[15]));

		Round(e, a, b, c, d, f1(a, b, c), k1, w0 = left(w0 ^ w13 ^ w8 ^ w2));
		Round(d, e, a, b, c, f1(e, a, b), k1, w1 = left(w1 ^ w14 ^ w9 ^ w3));
		Round(c, d, e, a, b, f1(d, e, a), k1, w2 = left(w2 ^ w15 ^ w10 ^ w4));
		Round(b, c, d, e, a, f1(c, d, e), k1, w3 = left(w3 ^ w0 ^ w11 ^ w5));
		Round(a, b, c, d, e, f2(b, c, d), k2, w4 = left(w4 ^ w1 ^ w12 ^ w6));
		Round(e, a, b, c, d, f2(a, b, c), k2, w5 = left(w5 ^ w2 ^ w13 ^ w7));
		Round(d, e, a, b, c, f2(e, a, b), k2, w6 = left(w6 ^ w3 ^ w14 ^ w8));
		Round(c, d, e, a, b, f2(d, e, a), k2, w7 = left(w7 ^ w4 ^ w15 ^ w9));
		Round(b, c, d, e, a, f2(c, d, e), k2, w8 = left(w8 ^ w5 ^ w0 ^ w10));
		Round(a, b, c, d, e, f2(b, c, d), k2, w9 = left(w9 ^ w6 ^ w1 ^ w11));
		Round(e, a, b, c, d, f2(a, b, c), k2, w10 = left(w10 ^ w7 ^ w2 ^ w12));
		Round(d, e, a, b, c, f2(e, a, b), k2, w11 = left(w11 ^ w8 ^ w3 ^ w13));
		Round(c, d, e, a, b, f2(d, e, a), k2, w12 = left(w12 ^ w9 ^ w4 ^ w14));
		Round(b, c, d, e, a, f2(c, d, e), k2, w13 = left(w13 ^ w10 ^ w5 ^ w15));
		Round(a, b, c, d, e, f2(b, c, d), k2, w14 = left(w14 ^ w11 ^ w6 ^ w0));
		Round(e, a, b, c, d, f2(a, b, c), k2, w15 = left(w15 ^ w12 ^ w7 ^ w1));

		Round(d, e, a, b, c, f2(e, a, b), k2, w0 = left(w0 ^ w13 ^ w8 ^ w2));
		Round(c, d, e, a, b, f2(d, e, a), k2, w1 = left(w1 ^ w14 ^ w9 ^ w3));
		Round(b, c, d, e, a, f2(c, d, e), k2, w2 = left(w2 ^ w15 ^ w10 ^ w4));
		Round(a, b, c, d, e, f2(b, c, d), k2, w3 = left(w3 ^ w0 ^ w11 ^ w5));
		Round(e, a, b, c, d, f2(a, b, c), k2, w4 = left(w4 ^ w1 ^ w12 ^ w6));
		Round(d, e, a, b, c, f2(e, a, b), k2, w5 = left(w5 ^ w2 ^ w13 ^ w7));
		Round(c, d, e, a, b, f2(d, e, a), k2, w6 = left(w6 ^ w3 ^ w14 ^ w8));
		Round(b, c, d, e, a, f2(c, d, e), k2, w7 = left(w7 ^ w4 ^ w15 ^ w9));
		Round(a, b, c, d, e, f3(b, c, d), k3, w8 = left(w8 ^ w5 ^ w0 ^ w10));
		Round(e, a, b, c, d, f3(a, b, c), k3, w9 = left(w9 ^ w6 ^ w1 ^ w11));
		Round(d, e, a, b, c, f3(e, a, b), k3, w10 = left(w10 ^ w7 ^ w2 ^ w12));
		Round(c, d, e, a, b, f3(d, e, a), k3, w11 = left(w11 ^ w8 ^ w3 ^ w13));
		Round(b, c, d, e, a, f3(c, d, e), k3, w12 = left(w12 ^ w9 ^ w4 ^ w14));
		Round(a, b, c, d, e, f3(b, c, d), k3, w13 = left(w13 ^ w10 ^ w5 ^ w15));
		Round(e, a, b, c, d, f3(a, b, c), k3, w14 = left(w14 ^ w11 ^ w6 ^ w0));
		Round(d, e, a, b, c, f3(e, a, b), k3, w15 = left(w15 ^ w12 ^ w7 ^ w1));

		Round(c, d, e, a, b, f3(d, e, a), k3, w0 = left(w0 ^ w13 ^ w8 ^ w2));
		Round(b, c, d, e, a, f3(c, d, e), k3, w1 = left(w1 ^ w14 ^ w9 ^ w3));
		Round(a, b, c, d, e, f3(b, c, d), k3, w2 = left(w2 ^ w15 ^ w10 ^ w4));
		Round(e, a, b, c, d, f3(a, b, c), k3, w3 = left(w3 ^ w0 ^ w11 ^ w5));
		Round(d, e, a, b, c, f3(e, a, b), k3, w4 = left(w4 ^ w1 ^ w12 ^ w6));
		Round(c, d, e, a, b, f3(d, e, a), k3, w5 = left(w5 ^ w2 ^ w13 ^ w7));
		Round(b, c, d, e, a, f3(c, d, e), k3, w6 = left(w6 ^ w3 ^ w14 ^ w8));
		Round(a, b, c, d, e, f3(b, c, d), k3, w7 = left(w7 ^ w4 ^ w15 ^ w9));
		Round(e, a, b, c, d, f3(a, b, c), k3, w8 = left(w8 ^ w5 ^ w0 ^ w10));
		Round(d, e, a, b, c, f3(e, a, b), k3, w9 = left(w9 ^ w6 ^ w1 ^ w11));
		Round(c, d, e, a, b, f3(d, e, a), k3, w10 = left(w10 ^ w7 ^ w2 ^ w12));
		Round(b, c, d, e, a, f3(c, d, e), k3, w11 = left(w11 ^ w8 ^ w3 ^ w13));
		Round(a, b, c, d, e, f2(b, c, d), k4, w12 = left(w12 ^ w9 ^ w4 ^ w14));
		Round(e, a, b, c, d, f2(a, b, c), k4, w13 = left(w13 ^ w10 ^ w5 ^ w15));
		Round(d, e, a, b, c, f2(e, a, b), k4, w14 = left(w14 ^ w11 ^ w6 ^ w0));
		Round(c, d, e, a, b, f2(d, e, a), k4, w15 = left(w15 ^ w12 ^ w7 ^ w1));

		Round(b, c, d, e, a, f2(c, d, e), k4, w0 = left(w0 ^ w13 ^ w8 ^ w2));
		Round(a, b, c, d, e, f2(b, c, d), k4, w1 = left(w1 ^ w14 ^ w9 ^ w3));
		Round(e, a, b, c, d, f2(a, b, c), k4, w2 = left(w2 ^ w15 ^ w10 ^ w4));
		Round(d, e, a, b, c, f2(e, a, b), k4, w3 = left(w3 ^ w0 ^ w11 ^ w5));
		Round(c, d, e, a, b, f2(d, e, a), k4, w4 = left(w4 ^ w1 ^ w12 ^ w6));
		Round(b, c, d, e, a, f2(c, d, e), k4, w5 = left(w5 ^ w2 ^ w13 ^ w7));
		Round(a, b, c, d, e, f2(b, c, d), k4, w6 = left(w6 ^ w3 ^ w14 ^ w8));
		Round(e, a, b, c, d, f2(a, b, c), k4, w7 = left(w7 ^ w4 ^ w15 ^ w9));
		Round(d, e, a, b, c, f2(e, a, b), k4, w8 = left(w8 ^ w5 ^ w0 ^ w10));
		Round(c, d, e, a, b, f2(d, e, a), k4, w9 = left(w9 ^ w6 ^ w1 ^ w11));
		Round(b, c, d, e, a, f2(c, d, e), k4, w10 = left(w10 ^ w7 ^ w2 ^ w12));
		Round(a, b, c, d, e, f2(b, c, d), k4, w11 = left(w11 ^ w8 ^ w3 ^ w13));
		Round(e, a, b, c, d, f2(a, b, c), k4, w12 = left(w12 ^ w9 ^ w4 ^ w14));
		Round(d, e, a, b, c, f2(e, a, b), k4, left(w13 ^ w10 ^ w5 ^ w15));
		Round(c, d, e, a, b, f2(d, e, a), k4, left(w14 ^ w11 ^ w6 ^ w0));
		Round(b, c, d, e, a, f2(c, d, e), k4, left(w15 ^ w12 ^ w7 ^ w1));

		s[0] += a;
		s[1] += b;
		s[2] += c;
		s[3] += d;
		s[4] += e;
	}
};

// not optimized yet
String readClientString(WiFiClient* client) {
    int64_t startTime = esp_timer_get_time();
    while(client->connected()) {
        if(client->available()) return client->readStringUntil('\n');
        if(esp_timer_get_time() - startTime > 60000000) esp_restart();
		if(xPortGetCoreID() == 0) vTaskDelay(10);
    }
    return "";
}

uint8_t incrementStr(char* str) {
    if(*str < '9') {
        (*str)++;
        return 1;
    }
    else {
        *str = '0';
        return incrementStr(str - 1) + 1;
    }
}

IPAddress nodeIP;
uint16_t nodePort;
uint16_t walletID;

inline void handleCore0Watchdog(int64_t& lastDelay) {
	if(esp_timer_get_time() > lastDelay + 100000) {
		vTaskDelay(10);
		lastDelay = esp_timer_get_time();
	}
}

void mine(void*) {
	int64_t lastDelay = esp_timer_get_time();
	uint8_t coreID = xPortGetCoreID();
    WiFiClient client;
    DSHA1 sha;
    sha.warmup();
	const char jobRequest[] = "JOB," DUCO_NAME "," START_DIFFICULTY "," MINING_KEY "\n";
	char resultMessageBase[200];
	uint64_t chip_id;
    esp_efuse_mac_get_default((uint8_t*)(&chip_id));
	snprintf(resultMessageBase, sizeof(resultMessageBase), "%%u,%%f," SOFTWARE_NAME "," MINER_NAME ",DUCOID%04X%08X,%u\n", (uint16_t)(chip_id >> 32), (uint32_t)chip_id, walletID);
    while(true) {
        if(!client.connected()) {
			int64_t startTime = esp_timer_get_time();
			while(!client.connect(nodeIP, nodePort)) {
				if(esp_timer_get_time() - startTime > 60000000) esp_restart();
				if(coreID == 0) handleCore0Watchdog(lastDelay);
			}
            readClientString(&client);
        }
		client.print(jobRequest);

		// not optimized yet
        String response = readClientString(&client);
        uint32_t idx1 = response.indexOf(',');
        String lastBlockHash = response.substring(0, idx1);
        uint32_t idx2 = response.indexOf(',', idx1 + 1);
        String expectedHashStr = response.substring(idx1 + 1, idx2);
        uint8_t expectedHash[20];
        for(uint8_t i = 0; i < 20; i++) expectedHash[i] = strtoul(expectedHashStr.substring(i * 2, (i * 2) + 2).c_str(), 0, 16);
        uint32_t difficulty = response.substring(idx2 + 1).toInt() * 100 + 1;

        uint32_t hash[5];
        sha.reset().write((const uint8_t*)lastBlockHash.c_str(), lastBlockHash.length());
        int64_t startTime = esp_timer_get_time();
		int64_t lastDelay = startTime;
        uint8_t iStrLen = 1;
        char iStr[11] = { '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 0 };
        for (uint32_t i = 0; i < difficulty; i++) {
            DSHA1 ctx = sha;
            ctx.write((const uint8_t*)(iStr + 10 - iStrLen), iStrLen).finalize(hash);
            iStrLen = max(incrementStr(iStr + 9), iStrLen);
			if(coreID == 0) handleCore0Watchdog(lastDelay);
            if (memcmp(expectedHash, hash, 20) == 0) {
				char resultMessage[200];
                snprintf(resultMessage, 200, resultMessageBase, i, i * 1000000.0f / (esp_timer_get_time() - startTime));
				client.write((const uint8_t*)resultMessage, 200);
				readClientString(&client);
                break;
            }
        }
    }
}

void setup() {

	// connect to WiFi network
	WiFi.mode(WIFI_STA);
	WiFi.setSleep(false);
	WiFi.begin(WIFI_SSID, WIFI_KEY);
    while(WiFi.status() != WL_CONNECTED) delay(100);
	while ((WiFi.status() != WL_CONNECTED) || (WiFi.localIP() == IPAddress(0, 0, 0, 0)) || (WiFi.localIP() == IPAddress(192, 168, 4, 2)) || (WiFi.localIP() == IPAddress(192, 168, 4, 3))) {
        WiFi.disconnect();
        delay(500);
        WiFi.reconnect();
        delay(500);
    }
    WiFi.config(WiFi.localIP(), WiFi.gatewayIP(), WiFi.subnetMask(), IPAddress(1, 1, 1, 1));

	// get node info
	WiFiClientSecure client;
    HTTPClient https;
    client.setInsecure();
    https.begin(client, "https://server.duinocoin.com/getPool");
    https.addHeader("Accept", "*/*");
    int httpCode = https.GET();
    if ((httpCode != HTTP_CODE_OK) && (httpCode != HTTP_CODE_MOVED_PERMANENTLY)) {
        https.end();
        esp_restart();
    }
	String result = https.getString();
    nodeIP.fromString(result.substring(7, result.indexOf('\"', 7)));
	int portIdx = result.indexOf("port\":");
	nodePort = result.substring(portIdx + 6, result.indexOf(',', portIdx + 6)).toInt();
    https.end();

	// start mining
	walletID = esp_random() % 2811u;
	if(CORE_COUNT > 1) xTaskCreatePinnedToCore(mine, "Mining Task", 15000, 0, 1, 0, 1 - xPortGetCoreID());
	mine(0);
}

void loop() {}