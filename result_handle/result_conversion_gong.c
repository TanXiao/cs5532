#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/errno.h>

#define DEBUG


float   fpADin2;

float data_result_2(unsigned int CS_data, char str_data[20])   //Ain2--32位浮点数据转换--Char函数  // CS_data=READ_AD
{
  unsigned int READ_AD_PN;        //判断接收数据的正P、负N----32位16进制数据变量
  float   READ_AD_DEC;       //CS5532-处理任务进程的最终数据----无符号AD浮点数据（32位浮点）
 
//-------------------------CS5532---Ain2格值表-------------------------------------------------------------------------//
//08II-001号机 Vref(+)=2.468    Vref(-)=-2.484   CS_GZp=2.468/4195925=5.8818973e-7 CS_GZn=2.484/4216320=5.8913934e-7;  
//08II-002号机 Vref(+)=3.033    Vref(-)=-3.077   CS_GZp=3.033/4165675=7.2809329e-7 CS_GZn=3.077/4221875=7.2882309e-7;；  
//08II-003号机 Vref(+)=2.478    Vref(-)=-2.480   CS_GZp=2.478/4207148=5.8899758e-7 CS_GZn=2.480/4205047=5.8976749e-7;  
//08II-004号机 Vref(+)=2.49533  Vref(-)=-2.48781  CS_GZp=2.49533/4211813=5.9245982e-7  CS_GZn=2.48781/4198417=5.9255905e-7;
//08II-005号机 Vref(+)=2.45867  Vref(-)=-2.48634  CS_GZp=2.45867/4159046=5.9116201e-7  CS_GZn=2.48634/4207900=5.9087430e-7; 
//---------------------------------------------------------------------------------------------------------------------//
  //float   CS_GZp=5.8818973e-7;  //08II-001号机 正数格值
  //float   CS_GZn=5.8913934e-7;  //08II-001号机 负数格值  
  //float   CS_GZp=7.2809329e-7;  //08II-002号机 正数格值
  //float   CS_GZn=7.2882309e-7;  //08II-002号机 负数格值
  //float   CS_GZp=5.8899758e-7;  //08II-003号机 正数格值
  //float   CS_GZn=5.8976749e-7;  //08II-003号机 负数格值
  //float   CS_GZp=5.9245982e-7;  //08II-004号机 正数格值
  //float   CS_GZn=5.9255905e-7;  //08II-004号机 负数格值 
  float   CS_GZp=5.9116201e-7;  //08II-005号机 正数格值
  float   CS_GZn=5.9087430e-7;  //08II-005号机 负数格值   
  
  char   str_data_P[50];
  char   str_data_N[50]; 
  char   str_fpADin2[10]; 
       
        READ_AD_PN=CS_data & 0x800000;                      //赋值READ_AD给READ_AD_PN
        
      //1）采样输入为正数    
        if(READ_AD_PN ==0x00000000)                         //如果=0x00000000，采样输入为正数
          {
           CS_data = CS_data-0x00000000;                    //
           READ_AD_DEC=(float)CS_data;                      //(float)-强制格式转换。*****见《C语言大全》-P36页
           READ_AD_DEC=READ_AD_DEC * CS_GZp; 
           //得出"有符号字符串数据",作为函数返数组            
           sprintf(str_data_P," %8.6f ",READ_AD_DEC);       //察看(显示)READ_AD_DEC的值 "  %8.6f "11char-取6位小数
           sprintf(str_data,str_data_P);                    //保存有符号结果// "_1.123456_" -- 共11Bytes
           //得出"有符号float数据",作为函数返回值
           fpADin2=READ_AD_DEC;
           memset (str_fpADin2,'\0',sizeof(str_fpADin2));
           sprintf(str_fpADin2,"%8.6f ",fpADin2); 
          }
          
      //2）采样输入为负数
        else if(READ_AD_PN ==0x00800000)                    //如果=0x00800000，采样输入为负数
          {
           CS_data=0xFFFFFF-CS_data;
           READ_AD_DEC=(float)CS_data;                      //***READ_AD_DEC永远为正数
           READ_AD_DEC=READ_AD_DEC *  CS_GZn; 
          
           //if(READ_AD_DEC >  2.63902124245702E-03)                   //---090804gf 考虑常数--C（实测为负数）  ---在无数入信号时检测，但是READ_AD_DEC永远为正数，所以这里还要用减法  
           //   READ_AD_DEC =(READ_AD_DEC - 2.63902124245702E-03);     //---090804gf 2 号电源    
           //else
           //   READ_AD_DEC =(2.63902124245702E-03 - READ_AD_DEC);           
           
         //得出"有符号字符串数据",作为函数返数组   
           sprintf(str_data_N,"-%8.6f ",READ_AD_DEC);       // 察看(显示)READ_AD_DEC的值 "%6.4f"-取4位小数
           sprintf(str_data,str_data_N);                    //保存有符号结果//"-1.123456_" -- 共11Bytes,=0x2D--"-"值
         //得出"有符号float数据",作为函数返回值
           fpADin2=(-1) * READ_AD_DEC;
           memset(str_fpADin2,'\0',sizeof(str_fpADin2));
           sprintf(str_fpADin2,"%8.6f ",fpADin2); 
          }

   READ_AD_PN=0x00000000;        
   return(fpADin2);                 
       
 }

int main(int argc, char *argv[]) {
	int input;
	float output;
	char data[20];

#ifndef DEBUG
	if (argc != 2) {
		fprintf(stderr, "ERROR, please give me an int!\n");
		exit(1);57116
	}
	input = atoi(argv[1]);
#else
	input = 4109592;//356710;
#endif
	printf("The input is %8.6f\n", (float)input);
	output = data_result_2(input, data);
	printf("The input is %f\n", input);
	printf("The result is %f\n", output);
	return 0;
}


