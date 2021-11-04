
#include <stdio.h>
#include <stdint.h>
#include <bcm2835.h>

#define I2C_BAUDRATE 100000
#define SLAVE_ADDRESS 0x52
#define DELAY_READ 100
#define BUFF_SIZE 6
#define ACTVAL_1 0x40
#define ACTVAL_2 0x00
#define X_AXIS 0
#define Y_AXIS 1
#define BUTTONS 5
void NunchukInit();
void NunchukRead(char *pLect);

int32_t main(int32_t argc, char **argv)
{
	char Lectura[BUFF_SIZE];
	NunchukInit();
	while(1)
	{
		NunchukRead(Lectura);
		printf("X: %x\t", Lectura[X_AXIS]);
		printf("Y: %x\t", Lectura[Y_AXIS]);
		printf("Botones: %x - %x\n", (Lectura[BUTTONS]&2)>>1, Lectura[BUTTONS]&1);
		delay(500);
	}
	bcm2835_i2c_end();
	bcm2835_close();
	return 0;
}

void NunchukInit()
{
	if(!bcm2835_init())
	{
		printf("I2C Init error\n");
		return;
	}
	bcm2835_i2c_begin();
	bcm2835_i2c_setSlaveAddress(SLAVE_ADDRESS);
	bcm2835_i2c_set_baudrate(I2C_BAUDRATE);
}

void NunchukRead(char *pLect)
{
	char Buf_Init_1[2]= {ACTVAL_1, ACTVAL_2},Buf_Init_2[1]={ACTVAL_2};
	bcm2835_i2c_write(Buf_Init_1, 2);
	delay(DELAY_READ);
	bcm2835_i2c_write(Buf_Init_2, 1);
	delay(DELAY_READ);
	bcm2835_i2c_read(pLect, BUFF_SIZE);
//	delay(100);
}
