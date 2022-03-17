# 2022_DKU_OS


This is a place for studying Operaing System in Dankook University.
- Professor : Jongmoo Choi
- Assistant : Hojin Shin (Email : ghwls03s@gmail.com)
- 2022 DKU Operating System Course Information [link]()


## Download Environment
Virtual Machine Platform: VirtualBox 6.1.32

[VirtualBox Download Link](https://www.virtualbox.org/wiki/Downloads)

Windows Subsystem for Linux Install Guide (WSL)

[WSL Install Guide Link](https://docs.microsoft.com/ko-KR/windows/wsl/install-win10#step-4---download-the-linux-kernel-update-package)

Operating System: Ubuntu 20.04

This environment is based on VirtualBox 6.1.32
If image execution is not possible, we recommend reinstalling VirtualBox 6.0 version.

[Virtual Box 6.0 Link](https://www.virtualbox.org/wiki/Download_Old_Builds_6_0)

## Clone Git Repository
git clone https://github.com/DKU-EmbeddedSystem-Lab/2022_DKU_OS.git

If you get an error there are no commands, install git with following command :

    sudo apt-get install git

## Lab0

lab0 contains information about installing a virtual machine and Ubuntu.

Set the environment according to the documentation.

The documentation for lab0 is at the link below.

The OS image to use for preferences is also on the link below.

Documentation for conducting the assignment can be found at following link :

[Lab0 Document Link](https://drive.google.com/file/d/1pBeBZlKkimcdILv7AwA26p1IwYQKCPUZ/view?usp=sharing)

DKU OS Image Download Link [Link](https://drive.google.com/file/d/19qontuOYiDqqQVj312CjC2TqFWc5XDPS/view?usp=sharing)

Root password : 1234

### If you have an error, you must check VirtualBox version check(6.1.18). If not, you reinstall VirtualBox.


## Lab1
If you want to proceed to Lab1, go to command below :

    cd lab1_sched

    make

    ./lab1_sched

Documentation for conducting the assignment can be found at following link :

[Lab1 Document Link](https://drive.google.com/file/d/1QVdx0xEbYv6G-fm2p_5tAsZ4MQEwzezK/view?usp=sharing)

## Lab2

See the documentation for details.

Documentation for conducting the assignment can be found at following link :

[Lab2 Document Link]()

## Lab3

### You must be use VirtualBox(Ubuntu Linux Env), not WSL!!

VirtualBox image is upload at above.

If you want for proceed to Lab3, go to command below :

    cd lab3_filesystem
    
    sudo apt-get update

    make

    insmod ramdisk.ko

    mkfs.ext2 /dev/ramdisk
  
    mkdir mnt

    mount /dev/ramdisk ./mnt

    ./create.sh
  
    ./apd mnt/A/BC 13 A/BC-13        //A, B, C is your last 3 digit of you student ID : 32XXXABC

Then you can proceed Lab3

If you want to proceed to Lab3-Bounus, go to command below:

    umount /dev/ramdisk
  
    rmmod ramdisk
  
    insmod ramdisk.ko
  
    cd os_ext2        //Change the source code
  
    make
  
    insmod os_ext2.ko
  
    mkfs.ext2 /dev/ramdisk
  
    mount -t os_ext2 /dev/ramdisk ../mnt
  
    dmesg | grep [YOUR_NAME]

See the documentation for details.

[Lab3 Document Link]()
