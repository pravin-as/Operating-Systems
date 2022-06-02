1. Firstly go to the folder 12041130_Pravin_Arjun_Shankhapal and open the terminal in that folder.
2. Run command "gcc partA.c". This will generate a.out file. To run that use command "./a.out".
	- Try following command in this shell:
		- ls will list files and directories in the current folder.
		- ps will give information about all running processes. 
		- mkdir "directory name" to make a new directory.
		- cd "another directory name" to change directory.
		- netstat -a to find all listening connections on pc. If it is not running firstly install sudo apt-get install net-tools.

3. Run command "gcc partB.c". This will generate a.out file. To run that use command "./a.out".
	- All the previous commands will run. Additional two commands are added.
		- ps -aux | grep bash
		- ps -aux | grep sh | grep bash
		- sudo apt-get update && sudo apt-get upgrade


4. Run command "gcc partC.c". This will generate a.out file. To run that use command "./a.out".
	- All the previous commands will run. Additional commands are added.
		- Firstly make empty file using "touch hello.txt" then add text into it using "echo "Hi" > hello.txt". 
