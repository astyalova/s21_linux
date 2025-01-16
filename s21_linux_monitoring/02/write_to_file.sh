#!/bin/bash

file=$(date "+%d_%m_%y_%H_%M_%S").status  

echo HOSTNAME = $HOSTNAME >> $file
echo TIMEZONE = $(timedatectl show --property=Timezone --value) $(date +%z | cut -c 1-3) >> $file
echo USER = $USER >> $file
echo OS = $OSTYPE >> $file
echo DATE = $(date +%d) $(date +%b) $(date +%Y) $(date +%H:%M:%S) >> $file
echo UPTAME = $(uptime -p) >> $file
echo UPTAME_SEC = $(awk '{print $1}' /proc/uptime) >> $file
echo IP = $(hostname -I | awk '{print $1}') >> $file
echo MASK = $(ip addr show | grep -E 'inet ' | awk '{print $2}' | sed 's#/.*##' | head -n 1) >> $file
echo GATEWAY = $(ip route | grep default | awk '{print $3}') >> $file
echo RAM_TOTAL = $(free | grep Mem | awk '{kbyte =$2 /1024/1024; printf("%.3f GB", kbyte)}') >> $file
echo RAM_USED = $(free | grep Mem | awk '{kbyte =$3 /1024/1024; printf("%.3f GB", kbyte)}') >> $file
echo RAM_FREE = $(free | grep Mem | awk '{kbyte =$4 /1024/1024; printf("%.3f GB", kbyte)}') >> $file
echo SPACE_ROOT = $(df -h /root | grep "/dev/" | awk '{mb=$2*1024; printf("%.2f MB", mb)}') >> $file
echo SPACE_ROOT_USED  = $(df -h /root | grep "/dev/" | awk '{mb=$3*1024; printf("%.2f MB", mb)}') >> $file
echo SPACE_ROOT_FREE = $(df -h /root | grep "/dev/" | awk '{mb=$4*1024; printf("%.2f MB", mb)}') >> $file