#!/system/bin/sh
sleep 60

PPID=$(pidof wayfoo.wayfoo)
echo "-17" > /proc/$PPID/oom_adj
echo "hey there"
