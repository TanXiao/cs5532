#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "cs5532.h"


int fd = 0;
FILE* pFile;

#undef DEBUG

u8 save_data(u8 *pdata){
	pFile=fopen("testresult","a+");
	fprintf(pFile,"%f\n ", *pdata);
	fclose(pFile);
	return 1;
}

int cs5532_init(void) {
	if (!fd) {
		fd = open("/dev/spi/1", O_RDWR);
		if (fd < 0) {
			printf("[APP INFO] : Open error.\n");
			return 0;
		}
	}

	int i = 0;
	u8 init_seq[16];

	for (i = 0; i < 15; i++)
		init_seq[i] = SYNC1;
	init_seq[15] = SYNC0;

	if (write(fd, init_seq, sizeof(char) * 16) != 0) {
		printf("write error.\n");
		return 0;
	}

	return 1;
}

u8 cs5532_reset(void) {

	u8 reset_result[4];

	write_to_cs5532(CMD_WRITE_CFG_REG, RS);

	int waste_time = 0;
	for(waste_time = RESET_TIME; waste_time > 0; waste_time--);

	write_to_cs5532(CMD_WRITE_CFG_REG, 0);
	read_from_cs5532(CMD_READ_CFG_REG, reset_result);

	if(reset_result[0] == 0x10)
		printf("CS5532 reset completed!\n");
	else{
		printf("CS5532 reset fails.\nThe configuration register is: ");
		int i = 0;
		for(i = 0; i < 4; i++)
			printf("%x ", reset_result[i]);
		printf("\n");
		return 0;
	}
	return 1;
}

u8 cmd_cs5532(u8 cmd)
{
	if (!fd) {
		fd = open("/dev/spi/1", O_RDWR);
		if (fd < 0) {
			printf("[APP INFO] : Open error.\n");
			return 0;
		}
	}

#ifdef DEBUG
	printf("put to cs5532: 0x%x\n",cmd);
#endif /* DEBUG */

	if (write(fd, &cmd, sizeof(char)) != 0) {
		printf("write error.\n");
		return 0;
	}
	return 1;
}

u8 write_to_cs5532(u8 cmd, int reg)
{
	u8 cmd_data[5];
	cmd_data[0] = cmd;

	if (!fd) {
			fd = open("/dev/spi/1", O_RDWR);
			if (fd < 0) {
				printf("[APP INFO] : Open error.\n");
				return 0;
			}
		}

		int i = 0;
		for(i = 0; i < 4; i++)
			cmd_data[i+1] = (u8)( (reg >> (8*(3-i))) & 0xff);

#ifdef DEBUG
		printf("put to cs5532: ");
		for (i = 0; i < 5; i++)
			printf("%x ",cmd_data[i]);
		printf("\n");
#endif /* DEBUG */

		if (write(fd, cmd_data, sizeof(char) * 5) != 0) {
				printf("write error.\n");
				return 0;
		}

	return 1;
}

u8 read_from_cs5532(u8 cmd, u8 *pdata)
{
	if (!fd) {
			fd = open("/dev/spi/1", O_RDWR);
			if (fd < 0) {
				printf("[APP INFO] : Open error.\n");
				return 0;
			}
		}

#ifdef DEBUG
	printf("put to cs5532: 0x%x\n",cmd);
#endif /* DEBUG */

	if (write(fd, &cmd, sizeof(char)) != 0) {
			printf("write error.\n");
			return 0;
		}
	if (read(fd, pdata, sizeof(char) * 4) != 0) {
			printf("read error.\n");
			return 0;
		}
	return 1;
}


u8 read_byte(u8 *pdata, int byte_count)
{
	if (!fd) {
			fd = open("/dev/spi/1", O_RDWR);
			if (fd < 0) {
				printf("[APP INFO] : Open error.\n");
				return 0;
			}
		}
	if (read(fd, pdata, sizeof(char) * byte_count) != 0) {
			printf("read error.\n");
			return 0;
		}
	return *pdata;
}


u8 calibrate(u8 calibrate_type, int cfg_reg, int setup_reg) {
	u8 calibrate_result[4];
	int waste_time, i;
	cfg_reg = (int)((calibrate_type % 2 == 1) ? (cfg_reg|IS):(cfg_reg));
	u8 cmd,read_reg;

	switch (calibrate_type)
	{
	case SELF_OFFSET: 	cmd = CMD_SELF_OFFSET_CAL_SETUP1;
						read_reg = CMD_READ_OFFSET_REG1;
						break;
	case SELF_GAIN: 	cmd = CMD_SELF_GAIN_CAL_SETUP1;
						read_reg = CMD_READ_GAIN_REG1;
						break;
	case SYSTEM_OFFSET: cmd = CMD_SYSTEM_OFFSET_CAL_SETUP1;
						read_reg = CMD_READ_OFFSET_REG1;
						break;
	case SYSTEM_GAIN: 	cmd = CMD_SYSTEM_GAIN_CAL_SETUP1;
						read_reg = CMD_READ_GAIN_REG1;
						break;
	}

	write_to_cs5532(CMD_WRITE_SETUP_REG1, setup_reg);
	write_to_cs5532(CMD_WRITE_CFG_REG, cfg_reg);
	cmd_cs5532(cmd);

	for(waste_time = WASTE_TIME; waste_time > 0; waste_time--)
		;

	read_from_cs5532(read_reg, calibrate_result);

	printf("The calibration result is: ");
	for(i = 0; i < 4; i++)
		printf("%x ", calibrate_result[i]);
	printf("\n");

	return 1;
}

int two_complement(int n)
{
	const int negative = (n & (1 << 23)) != 0;
	int native_int;

	if (negative)
	  native_int = n | ~((1 << 24) - 1);
	else
	  native_int = n;
	return native_int;
}



u8 convert(u8 convert_type, u8 setup_reg_no, u8 reg_no, int word_rate) {
	printf("Prepare for conversion.\n");
	u8 convert_result[4];
	int waste_time, i;
	int cfg_reg =  (int)VRS;
	int setup_reg = ((setup_reg_no % 2 == 1) ? ((word_rate) << 16) : word_rate);
	u8 cmd;

	switch (convert_type)
	{
	case SINGLE_CONVERSION: cmd = CMD_SINGLE_CONV_SETUP1; break;
	case CONTINUED_CONVERSION: cmd = CMD_CONTINUE_CONV_SETUP1; break;
	}
	write_to_cs5532(CMD_WRITE_SETUP_REG1, setup_reg);
	write_to_cs5532(CMD_WRITE_CFG_REG, cfg_reg);
	cmd_cs5532(cmd);
	printf("Conversion begins...\n");

	sleep(10);
	u8 test = 0;
	read_byte(&test, 1);
	read_byte(convert_result, 4);

	printf("\nThe conversion result is: ");
	for(i = 0; i < 4; i++)
		printf("%2x ", convert_result[i]);
	printf("\n");

	int final_result = 0;
	for (i = 0; i < 3; i++)
		final_result = (final_result << 8) + convert_result[i];
	printf("The raw result is: 0x%x\n", final_result);
	printf("The raw result is: %d\n", final_result);

	final_result = two_complement(final_result);
	printf("The final result is: 0x%x\n", final_result);
	printf("The final result is: %d\n", final_result);

	final_result = final_result * 500 / 0x7fffff;
	printf("The final result is: %d\n", final_result);


	return 1;
}
