export USER=dev

. /home/$USER/poky/oe-init-build-env /home/$USER/build

runqemu qemuarm nographic slirp
