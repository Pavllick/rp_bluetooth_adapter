# Raspberry Pi Zero W Bluetooth Speaker Adapter

Project uses Docker to build Raspberry Pi file system

## Development Guide

To ssh through usb use following command:
```
ssh root@bta.local
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

Menuconfig
```
bitbake linux-raspberrypi -c menuconfig
```

For initial configuration run:
```
~/scripts/init.sh
```

To apply latest updates and build the project run:
```
~/scripts/build.sh
```

### Flash SD Card

Under Linux check connected drives using command:
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
