#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include "gpio_ctrl.h"
#include <dlfcn.h>



typedef int(*Fun)(int);

int main(void)
{
	int a,b,c,d;
	char *error;
	Fun fun = NULL;

	a = 1;
	b = 2;
	c = a+b;	
	printf("c is %d\n",c);
	d = c +a;
	printf("d is %d\n",d);

	int (*led_red_control)(int);
	int (*led_green_control)(int);
	int (*led_blue_control)(int);
	int (*gpio_init)(int);
    void *handle = dlopen("libgpioctrl.so",RTLD_LAZY);

    if(!handle)
    {
		fprintf(stderr, "%s\n", dlerror());
		exit(EXIT_FAILURE);
    }
	gpio_init = dlsym(handle,"gpio_init");
	if ((error = dlerror()) != NULL)  {
		fprintf(stderr, "%s\n", error);
		exit(EXIT_FAILURE);
	}

	printf("dlsym success\n");
	gpio_init(1);
    led_red_control = dlsym(handle,"led_red_control");
	led_red_control(1);

    led_green_control = dlsym(handle,"led_green_control");
	led_green_control(1);

    led_blue_control = dlsym(handle,"led_blue_control");
	led_blue_control(1);
    dlclose(handle);

	return 0;
}
