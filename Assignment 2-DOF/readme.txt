1. Command to make the Object file:  
	$ make all
2. Push the KO to the kernel 
	$ sudo insmod main.ko
3.Checkout the automatically created block device files, dof1 and dof2 are the primary partions.
	$ ls -l /dev/dof*
4.To display the created partions(dof1 and dof2)
	$ $ fdisk -l /dev/dof
5.	$ sudo dd if=/dev/dof of=dof
6.	$ sudo dd if=/dev/zero of=/dev/dof count=1
7.Modify permissions for write.
	$ sudo chmod 777 /dev/dof1
8.	$ sudo cat > /dev/dof1
    	/* Text to be written to disk on file */
9.Display the initial contents of the first partition (/dev/dof1) using the xxd utility
	$ sudo xxd /dev/dof1 | less
10.Copy the contents from first partion to sample.txt
	$ sudo dd if=/dev/dof1 of=/etc/sample.txt count=1
11.Modify the contents in sample.txt 
12.To copy the contents from sample.txt to Disk 
	$ sudo dd if=/etc/sample.txt of=/dev/dof1 count=1
13.Display the initial contents of the first partition (/dev/dof1) using the xxd utility
	$ sudo xxd /dev/dof1 | less
