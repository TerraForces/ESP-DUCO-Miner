# ESP-DUCO-Miner (Version 1.1)
Just a fast, optimized, lightweight ESP32/8266 DUCO mining software (over WiFi), nothing more

## Performance
Compared to the Official ESP32 Miner 4.3
- up to 10.5% lower Flash usage
- up to 9.4% lower RAM usage
- up to 1.6% higher hashrate
- <b>up to 18.3% higher sharerate</b>

For more information about the testing conditions, see [testing.md](testing.md)

## Setup
1. Set your Duinocoin username and mining key (if set) in the [config.h](config.h) file
2. Set your WiFi name and passwort (if set) in the [config.h](config.h) file
3. If you want to adjust other settings check out the optional and the advanced section of the [config.h](config.h) file
4. Upload the [ESP-DUCO-Miner.ino](ESP-DUCO-Miner.ino) file to your ESP

## Additions
I won't provide support for any displays, RTCs or other functionalities, since this code focuses exclusively at speed and memory efficiency.
If you want to add functionalities to the code, I recommend creating a task [here](ESP-DUCO-Miner.ino#L314) in void setup().
Consider reducing the mining functionality to single core if your other functionality (e.g. web server) requires large CPU usage.<br>
<b>Please be aware that adding functionalities will always reduce mining performance!</b>

## Contact
In case of receiving warnings on your dashboard or other problems you can do one the following:
- open an issue in this repository containing a detailed description of your setup and the problem
- look for Terra (terraforces) on the [DuinoCoin Discord Server](https://discord.gg/duino-coin-677615191793467402)

## Donations
This mining software and other following DuinoCoin mining codes made by me are completely free and open source.<br>
If you enjoy working with my code, you can send some DUCOs to <b>Terra</b>.<br>
Thanks for your support!