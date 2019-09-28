# export target things
export DEVKIT=/opt/iot-devkit/devkit-x86 
export PATH=$PATH:$DEVKIT/sysroots/x86_64-pokysdk-linux/usr/bin/i586-poky-linux 
export CROSS_COMPILE=i586-poky-
linuxexport ARCH=x86

# compiling stuff
source iss_setup.sh

# navite to dir
make

scp blink gus@galileo51:

# running init scripts
scp eng10032lab03_1 gus@galileo51:

ssh gus@galileo51
cp ~/eng10032lab03_1 /etc/init.d
chmod +x /etc/init.d/eng10032lab03_1 # +x make executable
update-rc.d eng10032lab03_1 defaults # add to defaults on boot up
reboot

# remove init script
update-rc.d -f eng10032lab03_1 remove # -f force