# Bluetooth Speaker Box

[Public Reference](https://community.fablab-cottbus.de/t/draft-bluetoothbox-selber-bauen/671)
[Origin](https://community.fablab-cottbus.de/t/osz-workshop-sommer-2025/618)

## Compiling the firmware

We are using Platform IO.

Install PlatformIO-Core (see [here](https://docs.platformio.org/en/latest/core/installation/index.html)).

Then run `pio project init`. Your might want to add  `--ide vim` for your IDE of choice.

Finally run `make` to build. This will also download missing dependencies if possible.

To upload, you might need to install the udev-rules. [See here](https://docs.platformio.org/en/latest/core/installation/udev-rules.html).
