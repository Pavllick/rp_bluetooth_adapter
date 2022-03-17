export USER=dev

. /home/$USER/poky/oe-init-build-env /home/$USER/build

# echo '====================================================='
# echo 'Reseting bt_daemon...'
# devtool reset bt-daemon

echo '====================================================='
echo 'bitbake cleaning all...'
bitbake core-image-base -c cleanall

echo '====================================================='
echo 'Copying new config...'
cp /home/$USER/src/conf/local.conf /home/$USER/build/conf
# sed -i '/CORE_IMAGE_EXTRA_INSTALL += "bt-daemon"/d' /home/$USER/build/conf/local.conf
