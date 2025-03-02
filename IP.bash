#/usr/bin/bash

sudo ip addr add 192.168.96.55/24 dev lo
sudo ip link set lo up
sudo ip route add default via 192.168.96.1

 
