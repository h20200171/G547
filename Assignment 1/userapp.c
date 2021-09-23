#include "header.h"

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>              /* open */
#include <unistd.h>             /* exit */
#include <sys/ioctl.h>          /* ioctl */

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



int ioctl_get_prsr(int file_desc)
{
    int ret_val;
    char message[8];

    ret_val = ioctl(file_desc,IOCTL_GET_PRESSURE,message);
    if (ret_val < 0) {
        printf("Failed BMP280 : %d\n", ret_val);
        exit(-1);
    }

    printf("Pressure :%s\n", message);
    return 0;
}

int ioctl_get_xa(int file_desc)
{
    int ret_val;
    char message[8];

    ret_val = ioctl(file_desc,IOCTL_GET_XACC,message);
    if (ret_val < 0) {
        printf("MPU9255 failed to read: %d\n", ret_val);
        exit(-1);
    }

    printf("Acceleration_x:%s\n", message);
    return 0;
}

int ioctl_get_ya(int file_desc)
{
    int ret_val;
    char message[64];


    ret_val = ioctl(file_desc,IOCTL_GET_YACC,message);

    if (ret_val < 0) {
        printf("MPU9255 failed to read: %d\n", ret_val);
        exit(-1);
    }

    printf("Acceleration_y:%s\n", message);
    return 0;
}

int ioctl_get_za(int file_desc)
{
    int ret_val;
    char message[8];

    ret_val = ioctl(file_desc,IOCTL_GET_ZACC,message);
    if (ret_val < 0) {
        printf("MPU9255 failed to read: %d\n", ret_val);
        exit(-1);
    }

    printf("Acceleration_z:%s\n", message);
    return 0;
}

int ioctl_get_xg(int file_desc)
{
    int ret_val;
    char message[8];

    ret_val = ioctl(file_desc,IOCTL_GET_XGYRO,message);
    if (ret_val < 0) {
        printf("MPU9255 failed to read: %d\n", ret_val);
        exit(-1);
    }

    printf("Gyroscope_x:%s\n", message);
    return 0;
}

int ioctl_get_yg(int file_desc)
{
    int ret_val;
    char message[8];

    ret_val = ioctl(file_desc,IOCTL_GET_YGYRO,message);
    if (ret_val < 0) {
        printf("MPU9255 failed to read: %d\n", ret_val);
        exit(-1);
    }

    printf("Gyroscope__y:%s\n", message);
    return 0;
}

int ioctl_get_zg(int file_desc)
{
    int ret_val;
    char message[8];

    ret_val = ioctl(file_desc,IOCTL_GET_ZGYRO,message);
    if (ret_val < 0) {
        printf("MPU9255 failed to read: %d\n", ret_val);
        exit(-1);
    }

    printf("Gyroscope__z:%s\n", message);
    return 0;
}

int ioctl_get_xm(int file_desc)
{
    int ret_val;
    char message[8];

    ret_val = ioctl(file_desc,IOCTL_GET_XMAG,message);
    if (ret_val < 0) {
        printf("MPU9255 failed to read : %d\n", ret_val);
        exit(-1);
    }

    printf("Magnetometer_x:%s\n", message);
    return 0;
}

int ioctl_get_ym(int file_desc)
{
    int ret_val;
    char message[8];

    ret_val = ioctl(file_desc,IOCTL_GET_YMAG,message);
    if (ret_val < 0) {
        printf("MPU9255 failed to read: %d\n", ret_val);
        exit(-1);
    }

    printf("Magnetometer_y:%s\n", message);
    return 0;
}

int ioctl_get_zm(int file_desc)
{
    int ret_val;
    char message[8];

    ret_val = ioctl(file_desc,IOCTL_GET_ZMAG,message);
    if (ret_val < 0) {
        printf("MPU9255 failed to read : %d\n", ret_val);
        exit(-1);
    }

    printf("Magnetometer_z:%s\n", message);
    return 0;
}



int main()
{
    int file_desc, ret_val;
    char *msg = "Message passed by ioctl\n";

    file_desc = open(DEVICE_FILE_NAME, 0);
    if (file_desc < 0) {
        printf("Can't open device file: %s\n", DEVICE_FILE_NAME);
        exit(-1);
    }


   ioctl_get_prsr(file_desc);			// Pressure data from BMP280
   
   
    ioctl_get_xa(file_desc);                   // Acceleration data from MPU9255
    ioctl_get_ya(file_desc);
    ioctl_get_za(file_desc);
    
    
    ioctl_get_xg(file_desc);			// Gyroscope data from MPU9255
    ioctl_get_yg(file_desc);
    ioctl_get_zg(file_desc);
    
    
    ioctl_get_xm(file_desc);			// Marnetometer data from MPU9255
    ioctl_get_ym(file_desc);
    ioctl_get_zm(file_desc);
 

    close(file_desc);
    return 0;
}
