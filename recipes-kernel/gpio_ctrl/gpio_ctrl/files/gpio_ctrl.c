#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include "gpio_ctrl.h"

int init_flag = 0;
/****************************************************************
 * gpio_export
 ****************************************************************/
int gpio_export(unsigned int gpio)
{
	int fd, len;
	char buf[MAX_BUF];

	fd = open(SYSFS_GPIO_DIR "/export", O_WRONLY);
	if (fd < 0) {
		perror("gpio/export");
		return fd;
	}

	len = snprintf(buf, sizeof(buf),"%d", gpio);
	write(fd, buf, len);
	close(fd);

	return 0;
}

/****************************************************************
 * gpio_unexport
 ****************************************************************/
int gpio_unexport(unsigned int gpio)
{
	int fd, len;
	char buf[MAX_BUF];

	fd = open(SYSFS_GPIO_DIR "/unexport", O_WRONLY);
	if (fd < 0) {
		perror("gpio/export");
		return fd;
	}

	len = snprintf(buf, sizeof(buf), "%d",gpio);
	write(fd, buf, len);
	close(fd);
	return 0;
}

/****************************************************************
 * gpio_set_dir
 ****************************************************************/
int gpio_set_dir(unsigned int gpio, unsigned int out_flag)
{
	int fd, len;
	char buf[MAX_BUF];

	len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR  "/gpio%d/direction", gpio);

	fd = open(buf, O_WRONLY);
	if (fd < 0) {
		//perror("gpio/direction");
		return fd;
	}

	if (out_flag)
		write(fd, "out", 3);
	else
		write(fd, "in", 2);

	close(fd);
	return 0;
}

/****************************************************************
 * gpio_set_value
 ****************************************************************/
int gpio_set_value(unsigned int gpio, unsigned int value)
{
	int fd, len;
	char buf[MAX_BUF];

	len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio);

	fd = open(buf, O_WRONLY);
	if (fd < 0) {
		perror("gpio/set-value");
		return fd;
	}

	if (value)
		write(fd, "1", 1);
	else
		write(fd, "0", 1);

	close(fd);
	return 0;
}

/****************************************************************
 * gpio_get_value
 ****************************************************************/
int gpio_get_value(unsigned int gpio, unsigned int *value)
{
	int fd, len;
	char buf[MAX_BUF];
	char ch;

	len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio);

	fd = open(buf, O_RDONLY);
	if (fd < 0) {
		perror("gpio/get-value");
		return fd;
	}

	read(fd, &ch, 1);

	if (ch != '0') {
		*value = 1;
	} else {
		*value = 0;
	}

	close(fd);
	return 0;
}



/****************************************************************
 * gpio_fd_open  for value
 ****************************************************************/

int gpio_fd_open(unsigned int gpio)
{
	int fd, len;
	char buf[MAX_BUF];

	len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio);

	fd = open(buf, O_RDONLY | O_WRONLY| O_NONBLOCK );
	if (fd < 0) {
		perror("gpio/fd_open");
	}
	return fd;
}

/****************************************************************
 * gpio_fd_open_read  for value
 ****************************************************************/

int gpio_fd_open_read(unsigned int gpio)
{
	int fd, len;
	char buf[MAX_BUF];

	len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio);

	fd = open(buf, O_RDONLY | O_NONBLOCK );
	if (fd < 0) {
		perror("gpio/fd_open");
	}
	return fd;
}


/****************************************************************
 * gpio_fd_close
 ****************************************************************/

int gpio_fd_close(int fd)
{
	return close(fd);
}



/****************************************************************
 * multiplex the gpio pins
 ****************************************************************/

int mux_gpio_set(unsigned int gpio, unsigned int value)
{
	gpio_export(gpio);
	gpio_set_dir(gpio, 1);
	gpio_set_value(gpio, value);

	return 0;
}

int reset_imx6ull(void)
{
	int ret,fd;
	unsigned int value;
	fd=ret=value=0;

	fd = gpio_fd_open(RESET_IMX6ULL_GPIO);
	if (fd < 0){
		printf("gpio RESET_IMX6ULL_GPIO is not present!\n");
		return -1;
	}
	
	gpio_set_value(RESET_IMX6ULL_GPIO, 0);
	usleep(1000);
	gpio_set_value(RESET_IMX6ULL_GPIO, 1);
	usleep(1000);
	ret = gpio_get_value(RESET_IMX6ULL_GPIO, &value);
    if (ret < 0) {
        printf("---get RESET_IMX6ULL_GPIO failed\n");
        return -1;
    }
	printf("gpio state RESET_IMX6ULL_GPIO is %d\n", RESET_IMX6ULL_GPIO);
	gpio_fd_close(fd);

	return 0;
}

int reset_zigbee(void)
{
	int ret,fd;
	unsigned int value;
	fd=ret=value=0;

	fd = gpio_fd_open(RESET_ZIGBEE_GPIO);
	if (ret < 0){
		printf("gpio RESET_IMX6ULL_GPIO is not present!\n");
		return -1;
	}
	
	gpio_set_value(RESET_ZIGBEE_GPIO, 0);
	usleep(1000);
	gpio_set_value(RESET_ZIGBEE_GPIO, 1);
	usleep(1000);
	ret = gpio_get_value(RESET_ZIGBEE_GPIO, &value);
    if (ret < 0) {
        printf("----get RESET_ZIGBEE_GPIO failed\n");
        return -1;
    }
	printf("gpio state RESET_ZIGBEE_GPIO is %d\n", RESET_ZIGBEE_GPIO);

	gpio_fd_close(fd);
	return 0;
}

int reset_rgm(void)
{
	int ret,fd;
	unsigned int value;
	fd=ret=value=0;

	fd = gpio_fd_open(RESET_RGM_GPIO);
	if (fd < 0){
		printf("gpio RESET_RGM_GPIO is not present!\n");
		return -1;
	}
	
	gpio_set_value(RESET_RGM_GPIO, 0);
	usleep(1000);
	gpio_set_value(RESET_RGM_GPIO, 1);
	usleep(1000);
	ret = gpio_get_value(RESET_RGM_GPIO, &value);
    if (ret < 0) {
        printf("----get RESET_RGM_GPIO failed\n");
        return -1;
    }
	printf("gpio state RESET_RGM_GPIO is %d\n", RESET_RGM_GPIO);
	gpio_fd_close(fd);
	return 0;
}

int enable_buttom(void)
{
	int ret,fd;
	unsigned int temp;
	ret=fd=0;

	fd = gpio_fd_open(BUTTOM_CONTROL_GPIO);
	if (fd < 0){
		printf("gpio BUTTOM_CONTROL_GPIO is not present!\n");
		return -1;
	}
	
	gpio_set_value(BUTTOM_CONTROL_GPIO, 0);
	usleep(1000);
	gpio_set_value(BUTTOM_CONTROL_GPIO, 1);
	usleep(1000);
	ret = gpio_get_value(BUTTOM_CONTROL_GPIO, &temp);
    if (ret < 0) {
        printf("---get RBUTTOM_CONTROL_GPIO, failed\n");
        return -1;
    }
	printf("gpio state BUTTOM_CONTROL_GPIO, is %d\n", temp);

	gpio_fd_close(fd);
	return 0;
}

#if 0
int custom_key(void)
{
	int ret;
	unsigned int value;
	ret=value=0;

	ret = gpio_fd_open(BUTTOM_CONTROL_GPIO);
	if (ret < 0){
		printf("gpio BUTTOM_CONTROL_GPIO is not present!\n");
		return -1;
	}
	
	gpio_set_value(BUTTOM_CONTROL_GPIO, 0);
	usleep(1000);
	gpio_set_value(BUTTOM_CONTROL_GPIO,RESET_RGM_GPIO, 1);
	usleep(1000);
	ret = gpio_get_value(BUTTOM_CONTROL_GPIO, &value);
    if (ret < 0) {
        printf("---get RBUTTOM_CONTROL_GPIO, failed\n");
        return -1;
    }
	printf("gpio state BUTTOM_CONTROL_GPIO, is %d\n", BUTTOM_CONTROL_GPIO);

	return 0;
}
#endif

int led_red_control(int value)
{
	int ret,fd;
	unsigned int temp;
	fd=ret=temp=0;

	fd = gpio_fd_open(LED_R_GPIO);
	if (fd < 0){
		printf("gpio LED_R_GPIO is not present!\n");
		return -1;
	}
	if (value == 0)	{
		gpio_set_value(LED_R_GPIO, 0);
		printf("turn off the red led!\n");
	}else if (value == 1) {
		gpio_set_value(LED_R_GPIO, 1);
		printf("turn on the red led!\n");
	}else {
		printf("the value is not accept!\n");
	}
	ret = gpio_get_value(LED_R_GPIO, &temp);
    if (ret < 0) {
        printf("---get RLED_R_GPIO, failed\n");
        return -1;
    }
	printf("gpio state LED_R_GPIO, is %d\n", temp);

	gpio_fd_close(fd);
	return 0;
}

int led_green_control(int value)
{
	int ret,fd;
	unsigned int temp;
	fd=ret=temp=0;

	ret = gpio_fd_open(LED_G_GPIO);
	if (ret < 0){
		printf("gpio LED_G_GPIO is not present!\n");
		return -1;
	}
	if (value == 0)	{
		gpio_set_value(LED_G_GPIO, 0);
		printf("turn off the green led!\n");
	}else if (value == 1) {
		gpio_set_value(LED_G_GPIO, 1);
		printf("turn on the geen led!\n");
	}else {
		printf("the value is not accept!\n");
	}
	ret = gpio_get_value(LED_G_GPIO, &temp);
    if (ret < 0) {
        printf("---get RLED_G_GPIO, failed\n");
        return -1;
    }
	printf("gpio state LED_G_GPIO, is %d\n", temp);

	gpio_fd_close(fd);
	return 0;
}

int led_blue_control(int value)
{
	int ret,fd;
	unsigned int temp;
	fd=ret=temp=0;

	ret = gpio_fd_open(LED_B_GPIO);
	if (ret < 0){
		printf("gpio LED_B_GPIO is not present!\n");
		return -1;
	}
	if (value == 0)	{
		gpio_set_value(LED_B_GPIO, 0);
		printf("turn off the blue led!\n");
	}else if (value == 1) {
		gpio_set_value(LED_B_GPIO, 1);
		printf("turn on the blue led!\n");
	}else {
		printf("the value is not accept!\n");
	}
	ret = gpio_get_value(LED_B_GPIO, &temp);
    if (ret < 0) {
        printf("---get RLED_B_GPIO, failed\n");
        return -1;
    }
	printf("gpio state LED_B_GPIO, is %d\n", temp);

	gpio_fd_close(fd);
	return 0;
}


/****************************************************************
 * Retrive the corresponding GPIO pins for the given IO pins
   and multiplex them
 ****************************************************************/

int gpio_init(int value)
{
	 mux_gpio_set(RESET_ZIGBEE_GPIO,0); //zigbee reset
	 mux_gpio_set(RESET_IMX6ULL_GPIO,0); // reset nxp
	 mux_gpio_set(RESET_RGM_GPIO,0); //reset rgm
	 mux_gpio_set(BUTTOM_CONTROL_GPIO,0); //buttom
	 mux_gpio_set(COSTOM_CONTROL_GPIO,0); //gpio0 reserved
	 mux_gpio_set(LED_R_GPIO,0); //Led R
	 mux_gpio_set(LED_G_GPIO,0); //Led G
	 mux_gpio_set(LED_B_GPIO,0); //Led B

	return 0;
}


