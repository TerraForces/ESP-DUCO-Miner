# ESP-DUCO-Miner
Just a fast, optimized, lightweight ESP32/8266 DUCO mining software (over WiFi), nothing more

## Performance
Compared to the Official ESP32 Miner 4.3
- <b>6.3% - 7.2% lower Flash usage</b>
- <b>6.2% lower RAM usage</b>
- <b>4.2% higher hashrate</b>
- <b>4.7% - 7.7% higher sharerate</b>

For more information about the testing conditions, see [testing.md](testing.md)

## Setup
1. Set your Duinocoin username and mining key (if set) in the [config.h](config.h) file
2. Set your WiFi name and passwort (if set) in the [config.h](config.h) file
3. If you want to adjust other settings check out the optional and the advanced section of the [config.h](config.h) file
4. Upload the [ESP-DUCO-Miner.ino](ESP-DUCO-Miner.ino) file to your ESP

## Contact
In case of receiving warnings on your dashboard or other problems you can do one the following:
- open an issue in this repository containing a detailed description of your setup and the problem
- look for Terra (terraforces) on the [DuinoCoin Discord Server](https://discord.gg/duino-coin-677615191793467402)