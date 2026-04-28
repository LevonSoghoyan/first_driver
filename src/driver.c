#include <linux/module.h>
#include <linux/uaccess.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/cdev.h>
#include <linux/printk.h>
#include <linux/device.h>
#include <linux/moduleparam.h>
#define BUFFER_SIZE 1024
static dev_t dev_num;
static char *DEVICE_NAME = "My_device";
static struct cdev my_cdev;
static int major;
static struct class *pClass;
static struct device *pDevice;
MODULE_LICENSE("GPL");
module_param(DEVICE_NAME, charp, 0664);
MODULE_PARM_DESC(DEVICE_NAME,"cdev name");
/******************************************************************************
 * @brief Closes the file and releases all allocated memory.
 * @param pInode  Pointer to the file inode structure.
 * @param pFile   Pointer to the file object structure to be freed.
 *
 * @return int    Always returns 0.
 *****************************************************************************/
static int dev_release(struct inode *pInode, struct file *pFile)
{
    pr_info("%s: dev_release  called \n", DEVICE_NAME);
    kfree(pFile->private_data);
    return 0;
}
/******************************************************************************
 * @brief Reads a specified number of characters from the user buffer into the device buffer.
 *
 * @param pFile  Pointer to the file structure.
 * @param pBuf   Pointer to the source user buffer.
 * @param size   Number of bytes to copy from the user buffer.
 * @param pOffs  Pointer to the offset within the destination device buffer.
 *
 * @return size_t The actual number of bytes successfully copied.
 *****************************************************************************/
static ssize_t dev_read(struct file *pFile, char __user *pBuf, size_t size, loff_t *pOffs)
{
    char *temp = pFile->private_data;
    int len = BUFFER_SIZE;
    pr_info("%s: dev_read called \n", DEVICE_NAME);
    size ++;
    if (len <= *pOffs)
        return 0;

    if (size > len - *pOffs)
        size = len - *pOffs;

    if (copy_to_user(pBuf, temp + *pOffs, size))
        return -EFAULT;

    *pOffs += size;
    return size;
}
/******************************************************************************
 * @brief Writes a specified number of characters from the device buffer to the user buffer.
 *
 * @param pFile  Pointer to the file structure.
 * @param pBuf   Pointer to the destination user buffer.
 * @param size   Number of bytes to be transferred.
 * @param pOffs  Pointer to the current offset in the source device buffer.
 *
 * @return size_t The total number of bytes successfully written.
 *****************************************************************************/
static ssize_t dev_write(struct file *pFile, const char __user *pBuf, size_t size, loff_t *pOffs)
{

    char *temp = pFile->private_data;
    pr_info("%s: dev_write called \n", DEVICE_NAME);
    if (size > BUFFER_SIZE)
        size = BUFFER_SIZE;

    if (copy_from_user(temp, pBuf, size))
        return -EFAULT;
    temp[size] = '\0';
    return size;
}
/******************************************************************************
 * @brief Opens the file and allocates necessary memory resources.
 *
 * @param pInode  Pointer to the file inode structure.
 * @param pFile   Pointer to the file object structure.
 *
 * @return int    Always returns 0.
 *****************************************************************************/
static int dev_open(struct inode *pInode, struct file *pFile)
{

    pFile->private_data = kmalloc(BUFFER_SIZE + 1,GFP_KERNEL);
    pr_info("%s: dev_open called \n", DEVICE_NAME);
    return 0;
}

struct file_operations fops = {
    .open  = dev_open,
    .release = dev_release,
    .read = dev_read,
    .write = dev_write
};

char *command[256];

static char *devNode(struct device *dev, umode_t *mode)
{

    if (mode) {
        *mode = 0666;
    }
    return NULL;
}
static int  dev_init(void)
{
    alloc_chrdev_region(&dev_num, 0, 1, DEVICE_NAME);
    major = MAJOR(dev_num);
    cdev_init(&my_cdev, &fops);
    cdev_add(&my_cdev, dev_num, 1);
    pClass = class_create(THIS_MODULE,"driver_class");
    pClass->devnode = devNode;
    pDevice = device_create(pClass, NULL, dev_num, NULL, DEVICE_NAME);
    pr_info("%s: Registered with Major %d\n", DEVICE_NAME,  major);
    if (major < 0)
    {
        printk(KERN_CRIT "device registration error");
    }
    return 0;
}


static void dev_exit (void)
{
    device_destroy(pClass,dev_num);
    class_destroy(pClass);
    cdev_del(&my_cdev);
    unregister_chrdev_region(dev_num, 1);
    pr_info("%s: Unregistered \n", DEVICE_NAME);
}


module_init(dev_init);
module_exit(dev_exit);





