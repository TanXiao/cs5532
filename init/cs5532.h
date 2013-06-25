#ifndef _CS5532_H_  
#define _CS5532_H_ 
 
/*
 * Alias of Basic Types
**/
#define i32 long int
#define i16 int
#define i8  char
#define u32 unsigned long int
#define u16 unsigned int
#define u8  unsigned char

#define RESET_TIME 1200000
#define WASTE_TIME 90000000

#define SELF_OFFSET 1
#define SELF_GAIN	2
#define SYSTEM_OFFSET	3
#define SYSTEM_GAIN	4

#define SINGLE_CONVERSION	1
#define CONTINUED_CONVERSION	2

/*
 * Alias of Basic Results
**/
//#define NULL              0x0
#define PASS              0x0        
#define FAIL              0xff
#define TRUE              1
#define FALSE             0
 
#define NOTHING 0

#define CS5532_READ_DATA_TIMEOUT 2000000
 
/* CS5532 command */
#define SYNC1 0xFF
#define SYNC0 0xFE

/* init sequence */

#define FIFTEEN(a) \
	(a, a, a, a, a,\
	 a, a, a, a, a,\
	 a, a, a, a, a, a, a)

#define INIT_SEQUENCE (FIFTEEN(SYNC1), SYNC0)
  
#define CMD_WRITE_CFG_REG 0x3
#define CMD_READ_CFG_REG 0xB
  
#define CMD_READ_ALL_OFFSET_CAL 0x49
#define CMD_WRITE_ALL_OFFSET_CAL 0x41
 
#define CMD_READ_ALL_GAIN_CAL 0x4A
#define CMD_WRITE_ALL_GAIN_CAL 0x42
  
#define CMD_READ_ALL_SETUP_REG 0x4D
#define CMD_WRITE_ALL_SETUP_REG 0x45
  
#define CMD_READ_OFFSET_REG1 0x9
#define CMD_WRITE_OFFSET_REG1 0x1
#define CMD_READ_OFFSET_REG2 0x19
#define CMD_WRITE_OFFSET_REG2 0x11
  
#define CMD_READ_GAIN_REG1 0xA
#define CMD_WRITE_GAIN_REG1 0x2
#define CMD_READ_GAIN_REG2 0x1A
#define CMD_WRITE_GAIN_REG2 0x12
 
#define CMD_READ_SETUP_REG1 0xD 
#define CMD_WRITE_SETUP_REG1 0x5
#define CMD_READ_SETUP_REG2 0x1D 
#define CMD_WRITE_SETUP_REG2 0x15
#define CMD_READ_SETUP_REG3 0x2D
#define CMD_WRITE_SETUP_REG3 0x25
#define CMD_READ_SETUP_REG4 0x3D
#define CMD_WRITE_SETUP_REG4 0x35
 
#define CMD_SINGLE_CONV_SETUP1 0x80
#define CMD_SINGLE_CONV_SETUP2 0x88
#define CMD_SINGLE_CONV_SETUP3 0x90
#define CMD_SINGLE_CONV_SETUP4 0x98
#define CMD_SINGLE_CONV_SETUP5 0xA0
#define CMD_SINGLE_CONV_SETUP6 0xA8
#define CMD_SINGLE_CONV_SETUP7 0xB0
#define CMD_SINGLE_CONV_SETUP8 0xB8

#define CMD_CONTINUE_CONV_SETUP1 0xC0 
#define CMD_CONTINUE_CONV_SETUP2 0xC8
#define CMD_CONTINUE_CONV_SETUP3 0xD0
#define CMD_CONTINUE_CONV_SETUP4 0xD8
#define CMD_CONTINUE_CONV_SETUP5 0xE0
#define CMD_CONTINUE_CONV_SETUP6 0xE8
#define CMD_CONTINUE_CONV_SETUP7 0xF0
#define CMD_CONTINUE_CONV_SETUP8 0xF8

#define CMD_SELF_OFFSET_CAL_SETUP1 0x81 
#define CMD_SELF_OFFSET_CAL_SETUP2 0x89
#define CMD_SELF_OFFSET_CAL_SETUP3 0x91
#define CMD_SELF_OFFSET_CAL_SETUP4 0x99
#define CMD_SELF_OFFSET_CAL_SETUP5 0xA1
#define CMD_SELF_OFFSET_CAL_SETUP6 0xA9
#define CMD_SELF_OFFSET_CAL_SETUP7 0xB1
#define CMD_SELF_OFFSET_CAL_SETUP8 0xB9
  
#define CMD_SELF_GAIN_CAL_SETUP1 0x82
#define CMD_SELF_GAIN_CAL_SETUP2 0x8A
#define CMD_SELF_GAIN_CAL_SETUP3 0x92
#define CMD_SELF_GAIN_CAL_SETUP4 0x9A
#define CMD_SELF_GAIN_CAL_SETUP5 0xA2
#define CMD_SELF_GAIN_CAL_SETUP6 0xAA
#define CMD_SELF_GAIN_CAL_SETUP7 0xB2
#define CMD_SELF_GAIN_CAL_SETUP8 0xBA
 
#define CMD_SYSTEM_OFFSET_CAL_SETUP1 0x85 
#define CMD_SYSTEM_OFFSET_CAL_SETUP2 0x8D
#define CMD_SYSTEM_OFFSET_CAL_SETUP3 0x95
#define CMD_SYSTEM_OFFSET_CAL_SETUP4 0x9D
#define CMD_SYSTEM_OFFSET_CAL_SETUP5 0xA5
#define CMD_SYSTEM_OFFSET_CAL_SETUP6 0xAD
#define CMD_SYSTEM_OFFSET_CAL_SETUP7 0xB5
#define CMD_SYSTEM_OFFSET_CAL_SETUP8 0xBD
 
#define CMD_SYSTEM_GAIN_CAL_SETUP1 0x86 
#define CMD_SYSTEM_GAIN_CAL_SETUP2 0x8E
#define CMD_SYSTEM_GAIN_CAL_SETUP3 0x96
#define CMD_SYSTEM_GAIN_CAL_SETUP4 0x9E
#define CMD_SYSTEM_GAIN_CAL_SETUP5 0xA6
#define CMD_SYSTEM_GAIN_CAL_SETUP6 0xAE
#define CMD_SYSTEM_GAIN_CAL_SETUP7 0xB6
#define CMD_SYSTEM_GAIN_CAL_SETUP8 0xBE
 
#define CMD_STOP_CONT_CONV 0xFF
  
#define TIMEOUTERR 0xff
 
#define SUCCESSFUL 0x0  
 
#define CAL_TIMEOUT_LIMIT 4000

#define READ_CONV_RESULT 0x00


  
#define DATA_VALID 0
 
#define ERR_AD_BUSY 1 
 
#define ERR_AD_OVER_FLOW 2
 
#define ERR_FILTER_ONGOING 3


/* Configuration Register */
#define PSS	1<<31
#define PDW 1<<30
#define RS	1<<29
#define RV 	1<<28
#define IS	1<<27
#define GB 	1<<26
#define VRS	1<<25
#define OLB 1<<23
#define OLS	1<<22
#define OGS 1<<20
#define FRS 1<<19

/* Setup Register */
#define CS1 0<<14
#define CS2 1<<14

/* CS5532 Gain settings */
#define GAINX1 0<<11
#define GAINX2 1<<11
#define GAINX4 2<<11
#define GAINX8 3<<11
#define GAINX16 4<<11
#define GAINX32 5<<11
#define GAINX64 6<<11

/* CS5532 Word rate settings */
#define WORD_RATE_100SPS 0x0<<7
#define WORD_RATE_50SPS 0x1<<7
#define WORD_RATE_25SPS 0x2<<7
#define WORD_RATE_12P5SPS 0x3<<7
#define WORD_RATE_6P25SPS 0x4<<7
#define WORD_RATE_3200SPS 0x8<<7
#define WORD_RATE_1600SPS 0x9<<7
#define WORD_RATE_800SPS 0xA<<7
#define WORD_RATE_400SPS 0xB<<7
#define WORD_RATE_200SPS 0xC<<7

#define UNIPOLAR 1<<6
#define OL 1<<4
#define DT 1<<3
#define OCD 1<<2
#define OG1 0
#define OG2 1


#define CMD_STOP_CONT_CONV 0xFF
 



  
/* CS5532 subroutines */
int cs5532_init(void);
u8 cs5532_reset(void);

u8 cmd_cs5532(u8 cmd);
u8 write_to_cs5532(u8 cmd, int reg);
u8 read_from_cs5532(u8 cmd, u8 *pdata);
u8 read_byte(u8 *pdata, int byte_count);

u8 calibrate(u8 calibrate_type, int cfg_reg, int setup_reg);
u8 convert(u8 convert_type, u8 setup_reg_no, u8 reg_no, int word_rate);

//void cs5532_config(unsigned int cfg_hw);
//extern u8 CS5532_Setup(void);  
//u8 CS5532_Setup_CH1(u8, u8);
//void cs5532_cont_conversion(char setup_no);
//extern void cs5532_single_conversion(char setup_no);
//extern u8 CS5532_Set_Offset_Gain(u8 *, char);
//u8 cs5532_readADC(u8 *ConvDataBuf);
//u8 CS5532_SysGainCal(void); 
//void cs5532_manual_offset_gain_cal(u8 *, u8, char reg_no);
//u8 CS5532_SysOffsetCal(void);
//extern u8 CS5532_SelfOffsetCal(void);
//extern void CS5532_ReadCal(unsigned int);
//void CS5532_Test(void);
void CS5532_Poise2Result(void);
u8 CS5532_PoiseWeight(void); 
u8 cs5532_cont_conv_stop();  
u8 load_mfg_calibration();
u8 save_mfg_calibration();
u8 valid_user_calibration();
void flush_data_buffer();
 
#ifdef _DEBUG_WEIGHT_ 
void enable_data_printing();
void disable_data_printing();
#endif
 
#endif /* _CS5532_H_ */ 
