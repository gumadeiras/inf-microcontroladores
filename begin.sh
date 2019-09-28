#!/bin/bash

# create user 

ssh root@galileo51

useradd -c "Gustavo" -s /bin/bash -m gus
passwd gus
exit

ssh gus@galileo51
echo "export PATH=.:$PATH" >> .profile
exit

ssh-keygen -g ~/.ssh/id_galileo
scp ~/.ssh/id_galileo.pub gus@galileo51:

ssh gus@galileo51
mkdir .ssh
cat id_galileo.pub >> .ssh/authorized_keys
exit

/usr/bin/ssh-add -K ~/.ssh/id_galileo

# create gpio group and add user

groupadd -r gpio # -r = system account
groupmems -g gpio -a <login> # -g = group name, -a = username

chown :gpio -R /sys/class/gpio
chmod 770 -R /sys/class/gpio