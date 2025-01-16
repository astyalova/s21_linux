#!/bin/bash

echo HOSTNAME = $HOSTNAME
echo TIMEZONE = $(timedatectl show --property=Timezone --value) $(date +%z | cut -c 1-3)
echo USER = $USER
echo OS = $OSTYPE
echo DATE = $(date +%d) $(date +%b) $(date +%Y) $(date +%H:%M:%S)
echo UPTAME = $(uptime -p)
echo UPTAME_SEC = $(awk '{print $1}' /proc/uptime)
echo IP = $(hostname -I | awk '{print $1}')
echo MASK = $(ip addr show | grep -E 'inet ' | awk '{print $2}' | sed 's#/.*##' | head -n 1)
echo GATEWAY = $(ip route | grep default | awk '{print $3}')
echo RAM_TOTAL = $(free | grep Mem | awk '{kbyte =$2 /1024/1024; printf("%.3f GB", kbyte)}')
echo RAM_USED = $(free | grep Mem | awk '{kbyte =$3 /1024/1024; printf("%.3f GB", kbyte)}')
echo RAM_FREE = $(free | grep Mem | awk '{kbyte =$4 /1024/1024; printf("%.3f GB", kbyte)}')
echo SPACE_ROOT = $(df -h /root | grep "/dev/" | awk '{mb=$2*1024; printf("%.2f MB", mb)}')
echo SPACE_ROOT_USED  = $(df -h /root | grep "/dev/" | awk '{mb=$3*1024; printf("%.2f MB", mb)}')
echo SPACE_ROOT_FREE = $(df -h /root | grep "/dev/" | awk '{mb=$4*1024; printf("%.2f MB", mb)}')