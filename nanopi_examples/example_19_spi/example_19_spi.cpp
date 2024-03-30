/*
* Sample application that makes use of the SPIDEV interface
* to access an SPI slave device. Specifically, this sample
* reads a Device ID of a JEDEC-compliant SPI Flash device.
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <iostream>

int main(int argc, char **argv)
{
int fd;
struct spi_ioc_transfer xfer[2];
unsigned char buf[32], buf_rx[32], *bp;
int len, status;

fd = open("/dev/spidev0.0", O_RDWR);
if (fd < 0) {
  perror("open");
  return 1;
}

memset(xfer, 0, sizeof xfer);
memset(buf, 0, sizeof buf);
len = sizeof buf;

	unsigned int speed = 1000000;
	/*
	 * max speed hz
	 */
	int ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
	if (ret == -1)
		printf("can't set max speed hz");

	ret = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
	if (ret == -1)
		printf("can't get max speed hz");


/*
* Send a GetID command
*/
buf[0] = 0x01;
len = 1;
xfer[0].tx_buf = (unsigned long)buf;
xfer[0].len = 1;
status = ioctl(fd, SPI_IOC_MESSAGE(1), xfer);
std::cout << "LED ON" << std::endl;
sleep(1);
 
buf[0] = 0x00;
len = 1;
xfer[0].tx_buf = (unsigned long)buf;
xfer[0].len = 1;
status = ioctl(fd, SPI_IOC_MESSAGE(1), xfer);
std::cout << "LED OFF" << std::endl;

	return 0;
}
