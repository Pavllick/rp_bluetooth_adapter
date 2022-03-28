export USER=dev

. /home/$USER/poky/oe-init-build-env /home/$USER/build

echo '====================================================='
echo 'bitbake cleaning all...'
bitbake core-image-base -c cleanall

echo '====================================================='
echo 'Copying new config...'
cp /home/$USER/src/conf/local.conf /home/$USER/build/conf
