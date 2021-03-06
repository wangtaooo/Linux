#include <linux/device.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/string.h>


/**
 * ls /sys/bus/my_bus/
 *      devices     drivers_autoprobe   uevent
 *      drivers     drivers_probe       version
 *
 * ls /sys/devices/
 *      my_bus0     platform     system    virtual
 *  TODO 设备驱动分类一般两种方式
 *      1.功能分类
 *          字符设备
 *          块设备
 *          网络设备驱动
 *      2.总线分类
 *          pci
 *          usb
 *          i2c
 *          i2s
 *          platform
 */
MODULE_AUTHOR("Melvin");
MODULE_LICENSE("Dual BSD/GPL");
//TODO 输出my_bus 和 my_bus_type
EXPORT_SYMBOL(my_bus);
EXPORT_SYMBOL(my_bus_type);
static char*version="$ reversion :1.9$";

static void my_bus_release(struct device*dev){
	printk(KERN_DEBUG"my bus release\n");
}
static int my_match(struct device*dev,struct device_driver*driver){
	return !strncmp(dev->bus_id,driver->name,strlen(driver->name));
}
//export a simple attribute
static ssize_t show_bus_version(struct bus_type*bus,char*buf){
	return snprintf(buf,PAGE_SIZE,"%s\n",version);
}

//建立 /sys/bus/my_bus/version被创建
//cat /sys/bus/my_bus/version
//  $reversion : 1.9 $
static BUS_ATTR(version,S_IRUGO,show_bus_version,NULL);

struct device my_bus={
	.bus_id="my_bus0",
	.release=my_bus_release,
};

//建立/sys/bus/my_bus
struct bus_type my_bus_type={
	.name="my_bus",
	.match=my_match,
};
static int __init my_bus_init(void){
	int ret;
	//注册总线: 目录/sys/bus/my_bus
	ret=bus_register(&my_bus_type);
	if(ret){
		return ret;
	}
	//创建属性文件
	if(bus_create_file(&my_bus_type,&bus_attr_version)){
		printk(KERN_NOTICE"Fail to create version attribute\n");
	}
	//注册总线设备 TODO  一条总线也是一个设备,也必须按设备注册
    // 总线设备 /sys/devices/my_bus0 被注册
	ret=device_register(&my_bus);
	if(ret)
		printk(KERN_NOTICE"fail to register device:my_bus\n");
	return ret;
}
static void my_bus_exit(void){
	device_unregister(&my_bus);
	bus_unregister(&my_bus_type);
}
module_init(my_bus_init);
module_init(my_bus_exit);
