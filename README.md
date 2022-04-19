# Raspberry Pi Zero W Bluetooth Speaker Adapter

Project is using Docker to download all the dependencies into Debian dock, as well volume for build directory is created.

## Usage Guide

To establish Bluetooth connection physical button could be installed between pins **7** and **9**. Once the button is clicked **bta** device become discoverable and could be connected.

By default HDMI is used as sound output.

## Development Guide

To ssh through usb use following command, password **pass**, (disabled in local.conf by default):
```
ssh root@bta.local
```
or
```
ssh pri@bta.local
```

To build container run:
```
docker-compose up --build
```

To run bash terminal in container execute:
```
docker-compose run --rm yocto
```
where **yocto** is Docker image name


### Inside Container

For initial configuration run:
```
~/scripts/init.sh
```

To apply latest updates and build the project run:
```
~/scripts/build.sh
```

### Flash SD Card

#### On Linux

Check connected drives using command:
```
lsblk
```

Lets suppose that our SD Card name is discovered as **sdb** if it has partitions mounted they will be names sdb1, sdb2 and so on, they might need to be unmounted prior flashing.

To unmount partition sdb1 use command:
```
umount /dev/sdb1
```

To flash image to SD Card cd to **build/tmp/deploy/images/raspberrypi0-wifi/** and execute command:
```
sudo bmaptool copy core-image-base-raspberrypi0-wifi.wic.bz2 /dev/sdb
```

Where **core-image-base-raspberrypi0-wifi.wic.bz2** is image name and **/dev/sdb** is SD Card path.

The flashing utility will partition SD Card and write system files on it.

#### On Mac

Use **balenaEtcher** for simple GUI or terminal:

Check connected drives using command:
```
diskutil list
```

Lets suppose that our SD Card name is discovered as **disk2** if it has partitions mounted they will be names disk2s1, disk2s2 and so on, they might need to be unmounted prior flashing.

To unmount partition disk2 use command:
```
sudo diskutil unmountDisk /dev/disk2
```

To flash image to SD Card cd to **build/tmp/deploy/images/raspberrypi0-wifi/** and execute command:
```
bzip2 -dkc "$(readlink ./core-image-base-raspberrypi0-wifi.wic.bz2)" | sudo dd bs=1m of=/dev/disk2
```

For progress bar install pv with **brew install pv** and use following command:
```
bzip2 -dkc "$(readlink ./core-image-base-raspberrypi0-wifi.wic.bz2)" | sudo dd bs=1m | pv | sudo dd bs=1m of=/dev/disk2
```

Where **core-image-base-raspberrypi0-wifi.wic.bz2** is image name and **/dev/disk2** is SD Card path.

The flashing utility will partition SD Card and write system files on it.
