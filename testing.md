# ESP-DUCO-Miner Performance Testing

## General testing conditions
- 2 boards of the same type, activated at the same time at the same place
- Flash and RAM usage measurements made using build output (rounded to nearest full kB)
- hashrate and share measurements made using DuinoCoin dashboard
- share rate calculated with total mined shares divided by operation time (>6h)
- official code unchanged from [duinocoin.com](https://duinocoin.com/getting-started.html)
- using preset rig identifier (same for both codes)
- difficulty constantly 8.2k during measurements

## Testing results (Arduino IDE)

### Arduino Nano ESP32

| Category | ESP DUCO Miner 1.1 | Official ESP32 Miner 4.3 |
| --- | --- | --- |
| Flash usage | 1034 kB (32%) | 1114 kB (35%) |
| RAM usage | 66 kB (20%) | 70 kB (21%) |
| Hashrate | &asymp; 161 kH/s | &asymp; 159 kH/s |
| Sharerate | 23.9 Shares/min | 22.9 Shares/min |

### ESP32 Dev Kit C V4

| Category | ESP DUCO Miner 1.1 | Official ESP32 Miner 4.3 |
| --- | --- | --- |
| Flash usage | 1013 kB (77%) | 1111 kB (84%) |
| RAM usage | 48 kB (14%) | 53 kB (16%) |
| Hashrate | &asymp; 191 kH/s | &asymp; 188 kH/s |
| Sharerate | 31.7 Shares/min | 26.8 Shares/min |

### ESP32-S3 Dev Kit 1

| Category | ESP DUCO Miner 1.1 | Official ESP32 Miner 4.3 |
| --- | --- | --- |
| Flash usage | 976 kB (74%) | 1091 kB (83%) |
| RAM usage | 46 kB (13%) | 51 kB (15%) |
| Hashrate | &asymp; 161 kH/s | &asymp; 159 kH/s |
| Sharerate | 23.5 Shares/min | 23.0 Shares/min |