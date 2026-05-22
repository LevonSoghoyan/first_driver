
             PROJECT: SIMPLE CHARACTER DEVICE DRIVER
             
1. DESCRIPTION
-----------------------------------------------------------------------------
This project implements a Linux Kernel Module (Character Device) and a 
User-Space utility. It allows data to be transferred between a file on disk, 
the kernel memory buffer, and the terminal.
The project is split into three main components:

- driver.c: Kernel-level functionality (open, read, write, release).
- user_program.c: Main entry point for the terminal interface.
- user_functions.c: Helper functions for help and device communication.

2. COMPILATION
-----------------------------------------------------------------------------
The project uses a custom Makefile with specific targets:


- To build the driver (Kernel Module):
  $ make device MODULE_NAME=<your_module_name>

- To build the user space program:
- 
  $ make user

- To remove all compiled files:
  $ make clean

3. INSTALLATION
-----------------------------------------------------------------------------
After building, insert the module into the kernel and set the device name:

$ sudo insmod <MODULE_NAME>.ko DEVICE_NAME=<new_device_name>

4. USAGE
-----------------------------------------------------------------------------
To run the user program and see help information:
$ ./user_program

To perform a test (Write from file to device and read it back):
$ ./user_program /dev/<DEVICE_NAME> <path_to_file> <length_to_read>

Example:
$ ./user_program /dev/my_device data.txt 15

5. MONITORING & DEBUGGING
-----------------------------------------------------------------------------
- Check if the device exists:
  $ ll /dev

- Check kernel logs for printk messages (open, read, write calls):
  $ dmesg

6. TECHNICAL SPECIFICATIONS
-----------------------------------------------------------------------------
- Buffer Size: 1024 bytes (plus safety null-terminator).
- Return Codes:
    * dev_read: Returns actual number of bytes read.
    * dev_write: Returns number of bytes written.
    * dev_open/release: Returns 0.
    * User program: Returns 0 on success, non-zero on error.

-----------------------------------------------------------------------------
