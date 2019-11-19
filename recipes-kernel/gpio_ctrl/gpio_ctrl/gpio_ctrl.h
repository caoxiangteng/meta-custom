#ifndef __GPIO_FUNC_H__


 /****************************************************************
 * Constants
 ****************************************************************/
#define MAX_BUF 64
#define SYSFS_GPIO_DIR "/sys/class/gpio"

#define LED_R_GPIO                  1   
#define LED_G_GPIO                  2   
#define LED_B_GPIO                  4   
#define RESET_ZIGBEE_GPIO           128
#define RESET_IMX6ULL_GPIO          131
#define BUTTOM_CONTROL_GPIO         135 
#define COSTOM_CONTROL_GPIO         136 
#define RESET_RGM_GPIO              137 


/****************************************************************
 * Functions
 ****************************************************************/

int gpio_export(unsigned int gpio);
int gpio_unexport(unsigned int gpio);
int gpio_set_dir(unsigned int gpio, unsigned int out_flag);
int gpio_set_value(unsigned int gpio, unsigned int value);
int gpio_get_value(unsigned int gpio, unsigned int *value);
int gpio_set_edge(unsigned int gpio, char *edge);
int gpio_fd_open(unsigned int gpio);
int gpio_fd_open_read(unsigned int gpio);
int gpio_fd_open_edge(unsigned int gpio);
int gpio_fd_close(int fd);
int mux_gpio_set(unsigned int gpio, unsigned int value);
int gpio_pins(int io);
int reset_imx6ull(void);
int reset_zigbee(void);
int reset_rgm(void);
int enable_buttom(void);
int custom_key(void);
int led_red_control(int value);
int led_green_control(int value);
int led_blue_control(int value);
int gpio_init(int);

#endif /* __GPIO_FUNC_H__ */
