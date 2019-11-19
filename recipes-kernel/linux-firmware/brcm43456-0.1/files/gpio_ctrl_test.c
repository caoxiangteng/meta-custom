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
	int a,b,c;
	char *error;
	Fun fun = NULL;

	a = 1;
	b = 2;
	c = a+b;	
	printf("c is %d\n",c);

	int (*led_red_control)(int);
	int (*gpio_init)(int);
    void *handle = dlopen("libgpioctrl.so",RTLD_LAZY);
    if(!handle)
    {
        printf("dlopen error\n");
        return -1;
    }
	printf("handle is not NULL!\n");
//	gpio_init = dlsym(handle,"gpio_init");

	fun = (Fun)dlsym(handle, "gpio_init");
	if ((error = dlerror()) != NULL)
	{
		printf("dlsym error\n");
		exit(EXIT_FAILURE);
	}
	printf("dlsym success\n");
/*
	if (gpio_init == NULL){
		printf("gpio_init is NULL!\n");
		return -1;
	}
	printf("gpio_init is not NULL!\n");
	gpio_init(1);
    led_red_control = dlsym(handle,"led_red_control");
	led_red_control(1);
*/
    dlclose(handle);

	return 0;
}
