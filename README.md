# `cfs-rpi3`

## Building for rpi3

This builds for a 64-bit `aarch64` Ubuntu image Raspberry Pi 3+.

```
docker-compose run rpi3
make
make install
```

To copy to your Raspberry Pi:

```
export RASPBERRY_PI_HOSTNAME=<raspberry_pi_hostname>

scp -r build-rpi3/exe/rpi/ ${RASPBERRY_PI_HOSTNAME}:~
```

To run on your Raspberry Pi:

```
cd ~/rpi
sudo ./core-rpi
```