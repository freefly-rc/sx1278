#!/usr/bin/env bash

apt-get update
apt-get upgrade
apt-get install -y git wget curl vim build-essential make cmake gdb zip swig libftdi-dev python-dev "linux-headers-$(uname -r)"


# install mpsse library
cd /tmp || exit
git clone https://github.com/devttys0/libmpsse.git
cd libmpsse/src || exit
./configure
make
make install
ln -sf /usr/local/lib/libmpsse.so /usr/lib/

# Cmake can't find and link when it's in /usr/local so make ln to /usr/lib instead. FIXME
ln -s /usr/local/lib/libmpsse.so /usr/lib/
# Setup root password and login
echo -e "vagrant\nvagrant" | passwd root
echo "PermitRootLogin yes" >> /etc/ssh/sshd_config
sed -in 's/PasswordAuthentication no/PasswordAuthentication yes/g' /etc/ssh/sshd_config
service ssh restart

