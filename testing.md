# ESP-DUCO-Miner Performance Testing

## General testing conditions
- 2 boards of the same type, activated at the same time at the same place
- Flash and RAM usage measurements made using PlatformIO build output
- hashrate and share measurements made using DuinoCoin dashboard
- share rate calculated with total mined shares divided by operation time
- official code unchanged, only Serial printing deactivated

## Testing results

### ESP32 Dev Kit C V4

| Category | ESP DUCO Miner | Official ESP32 Miner 4.3 |
| --- | --- | --- |
| Flash usage | 899 kB (68.6%) | 959 kB (73.2%) |
| RAM usage | 46 kB (14.1%) | 49 kB (15%) |
| Hashrate | &asymp; 151.7 kH/s | &asymp; 145.6 kH/s |
| Sharerate | 22.1 Shares/min | 21.1 Shares/min |

### ESP32-S3 Dev Kit 1

| Category | ESP DUCO Miner | Official ESP32 Miner 4.3 |
| --- | --- | --- |
| Flash usage | 851 kB (25.5%) | 917 kB (27.4%) |
| RAM usage | 45 kB (13.7%) | 48 kB (14.7%) |
| Hashrate | &asymp; 132.2 kH/s | &asymp; 126.9 kH/s |
| Sharerate | 19.8 Shares/min | 18.3 Shares/min |