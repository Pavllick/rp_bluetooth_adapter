export USER=dev

echo '====================================================='
echo 'Cleaning previous build...'
bash /home/$USER/src/scripts/clear.sh

echo '====================================================='
echo 'Sourcing yocto tools...'
. /home/$USER/poky/oe-init-build-env /home/$USER/build

echo '====================================================='
echo 'Building...'
# -k is for --continue, means bitbake will proceed as far as possible after finding an error
bitbake -k core-image-base
