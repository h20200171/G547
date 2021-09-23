#include <linux/kernel.h>       
#include <linux/module.h>
#include<linux/version.h>       
#include <linux/fs.h>
#include <linux/errno.h>
#include<linux/init.h>
#include<linux/types.h>
#include<linux/kdev_t.h>
#include <linux/uaccess.h>        
#include <linux/time.h>
#include <linux/random.h>
#include<linux/device.h>
#include<linux/cdev.h>
#include "header.h"


#ifndef IMUDEV_H
#define IMUDEV_H

#include <linux/ioctl.h>

#define MAJOR_NUM 250


#define IOCTL_GET_PRESSURE _IOR(MAJOR_NUM, 0, char *)
#define IOCTL_GET_XACC _IOR(MAJOR_NUM, 1, char *)
#define IOCTL_GET_YACC _IOR(MAJOR_NUM, 3, char *)
#define IOCTL_GET_ZACC _IOR(MAJOR_NUM, 4, char *)
#define IOCTL_GET_XGYRO _IOR(MAJOR_NUM, 5, char *)
#define IOCTL_GET_YGYRO _IOR(MAJOR_NUM, 6, char *)
#define IOCTL_GET_ZGYRO _IOR(MAJOR_NUM, 7, char *)
#define IOCTL_GET_XMAG _IOR(MAJOR_NUM, 8, char *)
#define IOCTL_GET_YMAG _IOR(MAJOR_NUM, 9, char *)
#define IOCTL_GET_ZMAG _IOR(MAJOR_NUM, 2, char *)


#define DEVICE_FILE_NAME "/dev/imu_char"

#endif



#define SUCCESS 0
#define DEVICE_NAME "imu_char"

static dev_t first;
static struct cdev c_dev;
static struct class *cls;


static int Device_Open = 0;

static int device_open(struct inode *inode, struct file *file)
{

    /*
     * We don't want to talk to two processes at the same time
     */
    if (Device_Open)
        return -EBUSY;

    Device_Open++;
    try_module_get(THIS_MODULE);
    return SUCCESS;
}

static int device_release(struct inode *inode, struct file *file)
{


    /*
     * We're now ready for our next caller
     */
    Device_Open--;

    module_put(THIS_MODULE);
    return SUCCESS;
}

static ssize_t device_read(struct file *file,   /* see include/linux/fs.h   */
                           char __user * buffer,        /* buffer to be
                                                         * filled with data */
                           size_t length,       /* length of the buffer     */
                           loff_t * offset)
{

    	uint16_t random;
    	
	
	char *temp;
	char temp2[8];
	
	
	get_random_bytes(&random, 2);
	random=random&0x7FFF;  // generate 16 bit random variable and make it positive number
	
	sprintf(temp2,"%d\n",random);  // to copy the random generated int to string(Char type)
	temp = temp2;
	copy_to_user(buffer, temp, sizeof(temp));
         

    return (sizeof(buffer));
}

static ssize_t device_write(struct file *file,
             const char __user * buffer, size_t length, loff_t * offset)
{

	
	return SUCCESS;
}


long device_ioctl(struct file *file,            
                  unsigned int ioctl_num,        
                  unsigned long ioctl_param)
{
    int i;
    switch(ioctl_num){
    
    
    case IOCTL_GET_XMAG:
	
            i = device_read(file, (char *)ioctl_param, 99, 0);

            /*
            * IOCTL read for Magnetometer data
            */
            put_user('\0', (char *)ioctl_param + i);
	    break;
	
	case IOCTL_GET_YMAG:
	
            i = device_read(file, (char *)ioctl_param, 99, 0);

           /*
            * IOCTL read for Magnetometer data
            */
            put_user('\0', (char *)ioctl_param + i);
	    break;

	case IOCTL_GET_ZMAG:
	
            i = device_read(file, (char *)ioctl_param, 99, 0);

            /*
            * IOCTL read for Magnetometer data
            */
            put_user('\0', (char *)ioctl_param + i);
	    break;
	    
	    

        case IOCTL_GET_XACC:
            i = device_read(file, (char *)ioctl_param, 99, 0);

            /*
            * IOCTL read for Accelerometer data
            */
            put_user('\0', (char *)ioctl_param + i);
 	    break;

        case IOCTL_GET_YACC:
	
            i = device_read(file, (char *)ioctl_param, 99, 0);

             /*
            * IOCTL read for Accelerometer data
            */
            put_user('\0', (char *)ioctl_param + i);
	    break;

	case IOCTL_GET_ZACC:
	
            i = device_read(file, (char *)ioctl_param, 99, 0);
	    
             /*
            * IOCTL read for Accelerometer data
            */
            put_user('\0', (char *)ioctl_param + i);
	    break;

	case IOCTL_GET_XGYRO:
	
            i = device_read(file, (char *)ioctl_param, 99, 0);
 	    /*
            * IOCTL read for Gyroscope data
            */
            put_user('\0', (char *)ioctl_param + i);
	    break;

	case IOCTL_GET_YGYRO:
	
            i = device_read(file, (char *)ioctl_param, 99, 0);

            /*
            * IOCTL read for Gyroscope data
            */
            put_user('\0', (char *)ioctl_param + i);
	    break;

	case IOCTL_GET_ZGYRO:
	
            i = device_read(file, (char *)ioctl_param, 99, 0);

            /*
            * IOCTL read for Gyroscope data
            */
            put_user('\0', (char *)ioctl_param + i);
	    break;

	

	case IOCTL_GET_PRESSURE:
	
            i = device_read(file, (char *)ioctl_param, 99, 0);
	    
            /*
            * IOCTL read for Barometer data
            */
            put_user('\0', (char *)ioctl_param + i);
	    break;
    }

    return SUCCESS; 
}

struct file_operations fops = {
        .read = device_read,
        .write = device_write,
        .unlocked_ioctl = device_ioctl,
        .open = device_open,
        .release = device_release,     
};


static int __init mychar_init(void)
{

	printk(KERN_INFO "Mychar driver registered \n");
	if (alloc_chrdev_region(&first,0,1,"Bits_Pilani") < 0)
	{
		return -1;
	}
	
	if((cls = class_create(THIS_MODULE,"imu_dev")) == NULL)
	{
		unregister_chrdev_region(first,1);
		return -1;
	}
	if(device_create(cls,NULL,first,NULL,DEVICE_NAME) == NULL)
	{
		class_destroy(cls);
		unregister_chrdev_region(first,1);
		return -1;
	}

	cdev_init(&c_dev,&fops);
	if(cdev_add(&c_dev,first,1) == -1)
	{
		device_destroy(cls,first);
		class_destroy(cls);
		unregister_chrdev_region(first,1);
		return -1;
	}
	
	printk(KERN_INFO " First assignment <Major,Minor> : <%d, %d>\n",MAJOR(first),MINOR(first));
	return 0;
}

static void __exit mychar_exit(void)
{
	cdev_del(&c_dev);
	unregister_chrdev_region(first,1);
	device_destroy(cls,first);
	class_destroy(cls);
	printk(KERN_INFO "mychar driver unregistered \n");
	
}

module_init(mychar_init);
module_exit(mychar_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anuj Sanathanan 2020H1400171P");
MODULE_DESCRIPTION("First Assignment, EEE G547");



