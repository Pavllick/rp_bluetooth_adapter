export USER=dev

. /home/$USER/poky/oe-init-build-env /home/$USER/build

cp /home/$USER/src/conf/local.conf /home/$USER/build/conf

bitbake-layers add-layer /home/$USER/meta-openembedded/meta-oe
bitbake-layers add-layer /home/$USER/meta-openembedded/meta-python
bitbake-layers add-layer /home/$USER/meta-openembedded/meta-networking
bitbake-layers add-layer /home/$USER/meta-raspberrypi

bitbake-layers add-layer /home/$USER/src/meta-bttoaux_network

bitbake -k core-image-base
