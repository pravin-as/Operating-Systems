echo "System Name, IP Adress and Date "
uname -s
hostname -I
date
echo "System uptime"
uptime
echo "Operating system"
uname
echo "CPU type and Number of cores"
cat /proc/cpuinfo | grep "model name\|cpu cores"
echo "Main Memory size"
cat /proc/meminfo |grep "MemTotal"
echo "Total number of partition and their size, disk used, free spacec of disk"
df
echo "Instaneous RAM and CPU usages and loads"
htop
echo "Number of jobs running in kernel space, number of jobs running in user space"
ps | wc -l
sudo cat /proc/slabinfo | wc -l
echo "List of user accounts and list of users currently logged in"
w


