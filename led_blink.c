#include <linux/module.h>
#include <linux/init.h>
#include <linux/gpio.h>
#include <linux/kthread.h>             
#include <linux/sched.h>               
#include <linux/delay.h>

/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ali Chlaifa");
MODULE_DESCRIPTION("Module blink 3 led using threads");

static struct task_struct *thread1;
static struct task_struct *thread2;
static struct task_struct *thread3;


int thread_function1(void *pv)
{
    while(!kthread_should_stop()) {
        static int led_state = 0;
        led_state = !led_state;
        gpio_set_value(2, led_state);
        msleep(1000);
    }
    return 0;
}

int thread_function2(void *pv)
{
    while(!kthread_should_stop()) {
        static int led_state = 0;
        led_state = !led_state;
        gpio_set_value(3, led_state);
        msleep(700);
    }
    return 0;
}

int thread_function3(void *pv)
{
    while(!kthread_should_stop()) {
        static int led_state = 0;
        led_state = !led_state;
        gpio_set_value(4, led_state);
        msleep(500);
    }
    return 0;
}


static int __init ModuleInit(void) {
    printk("Hello, Kernel!\n");
    /* GPIO 2 init */
    if(gpio_request(2, "rpi-gpio-2")) {
        printk("Can not allocate GPIO 2\n");
        return -1;
    }
    
    /* GPIO 3 init */
    if(gpio_request(3, "rpi-gpio-3")) {
        printk("Can not allocate GPIO 3\n");
        return -1;
    }
    
    /* GPIO 4 init */
    if(gpio_request(4, "rpi-gpio-4")) {
        printk("Can not allocate GPIO 4\n");
        return -1;
    }
	
    /* Set GPIO 2 direction */
    if(gpio_direction_output(2, 0)) {
        printk("Can not set GPIO 2 to output!\n");
        gpio_free(2);
        return -1;
    }
    
    /* Set GPIO 3 direction */
    if(gpio_direction_output(3, 0)) {
        printk("Can not set GPIO 3 to output!\n");
        gpio_free(3);
        return -1;
    }
    /* Set GPIO 4 direction */
    if(gpio_direction_output(4, 0)) {
        printk("Can not set GPIO 4 to output!\n");
        gpio_free(4);
        return -1;
    }

    thread1 = kthread_create(thread_function1,NULL,"thread1");
    if(thread1) 
	    wake_up_process(thread1);
    else 
    printk("Cannot create kthread\n");
    
    thread2 = kthread_create(thread_function2,NULL,"thread2");
    if(thread1) 
	    wake_up_process(thread2);
    else 
    printk("Cannot create kthread\n");
    
    thread3 = kthread_create(thread_function3,NULL,"thread3");
    if(thread3) 
	    wake_up_process(thread3);
    else 
    printk("Cannot create kthread\n");

    return 0;
}

static void __exit ModuleExit(void) {
    printk("Goodbye, Kernel\n");
    gpio_free(2);
    gpio_free(3);
    gpio_free(4);
    kthread_stop(thread1);
    kthread_stop(thread2);
    kthread_stop(thread3);
}

module_init(ModuleInit);
module_exit(ModuleExit);

