export USER=dev

. /home/$USER/poky/oe-init-build-env /home/$USER/build

echo '====================================================='
echo 'bitbake cleaning core-image-base...'
bitbake core-image-base -c cleanall

echo '====================================================='
echo 'bitbake cleaning meta-bt-connect...'
bitbake bt-connect -c cleanall

echo '====================================================='
echo 'Copying new config...'
cp /home/$USER/src/conf/local.conf /home/$USER/build/conf
