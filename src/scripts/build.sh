export USER=dev

echo '====================================================='
echo 'Cleaning previous build...'
bash /home/$USER/src/scripts/clear.sh

# echo '====================================================='
# echo 'Copying new config...'
# cp /home/$USER/src/conf/local.conf /home/$USER/build/conf

echo '====================================================='
echo 'Sourcing yocto tools...'
. /home/$USER/poky/oe-init-build-env /home/$USER/build

# echo '====================================================='
# echo 'Adding bt_daemon recipe...'
# devtool add --no-same-dir /home/$USER/src/meta-bt_daemon

# echo '====================================================='
# echo 'bitbake bt-daemon'
# bitbake bt-daemon

# echo '====================================================='
# echo 'Adding bt-daemon to local.conf...'
# echo $'\nCORE_IMAGE_EXTRA_INSTALL += "bt-daemon"' >> /home/$USER/build/conf/local.conf

echo '====================================================='
echo 'Building...'
# -k is for --continue, means bitbake will proceed as far as possible after finding an error
bitbake -k core-image-base
