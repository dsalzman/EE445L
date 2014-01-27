// filename lab1.c
// Description: Testing routines for fixed.c
#include <stdio.h>
#include "fixed.h"
#include "Output.h"
// const will place these structures in ROM
const struct outTestCase{       // used to test routines for unsigned inputs
  unsigned long InNumber;       // test input number
  char OutBuffer[10];           // Output String  
};
typedef const struct outTestCase outTestCaseType;

const struct signedOutTestCase{       // used to test routines for signed inputs
  long InNumber;                // test input number
  char OutBuffer[10];           // Output String  
};
typedef const struct signedOutTestCase signedOutTestCaseType;

outTestCaseType outTests1[10]={ 
{     0,  "000.00" }, 
{     1,  "000.01" }, 
{    99,  "000.99" }, 
{   100,  "001.00" }, 
{   999,  "009.99" }, 
{  1000,  "010.00" }, 
{  9999,  "099.99" }, 
{ 10000,  "100.00" }, 
{ 99999,  "999.99" }, 
{100000,  "***.**" }  // error
};

signedOutTestCaseType signedOutTests1[10]={
{ -100000, " *.***" },
{  -10000, " *.***" },
{   -9999, "-9.999" },
{    -999, "-0.999" },
{      -1, "-0.001" },
{       0, " 0.000" }, 
{     123, " 0.123" },
{    1234, " 1.234" },
{    9999, " 9.999" },
{   10000, " *.***" }
};

outTestCaseType outTests3[16]={ 
{     0,  "000.00" }, //      0/256 = 0.00  
{     4,  "000.01" }, //      4/256 = 0.01  
{    10,  "000.03" }, //     10/256 = 0.03
{   200,  "000.78" }, //    200/256 = 0.78
{   254,  "000.99" }, //    254/256 = 0.99
{   505,  "001.97" }, //    505/256 = 1.97
{  1070,  "004.17" }, //   1070/256 = 4.17
{  5120,  "020.00" }, //   5120/256 = 20.00
{ 12184,  "047.59" }, //  12184/256 = 47.59
{ 26000,  "101.56" }, //  26000/256 = 101.56
{ 32767,  "127.99" }, //  32767/256 = 127.99
{ 32768,  "128.00" }, //  32768/256 = 128
{ 34567,  "135.02" }, //  34567/256 = 135.02
{123456,  "482.25" }, // 123456/256 = 482.25
{255998,  "999.99" }, // 255998/256 = 999.99
{256000,  "***.**" }  // error
};

unsigned int Errors1,AnError1;
unsigned int Errors2,AnError2;
unsigned int Errors3,AnError3;
unsigned int TotalErrors;
int delayTime;

char Buffer[10];
volatile unsigned long ulLoop;

void delay(unsigned int time){
	for(ulLoop = 0; ulLoop < time*100000; ulLoop++)
        {
        }

}
void main(void){ 
unsigned int i;	
   Errors1 = 0;

  Output_Init();
  Output_Color(15);
	delayTime = 3;
  for(i=0; i<10; i++){
    Fixed_uDecOut2s(outTests1[i].InNumber,Buffer); // Send test cases 
		printf(Buffer);
		delay(delayTime);
		Output_Clear();
		if(strcmp(Buffer, outTests1[i].OutBuffer)){    // Compare returned result with expected result
      Errors1++;     // Count errors
      AnError1 = i;
    }
  }

	  Errors2 = 0;
  for(i=0; i<10; i++){
    Fixed_sDecOut3s(signedOutTests1[i].InNumber,Buffer);
		printf(Buffer);
		delay(delayTime);
		Output_Clear();
    if(strcmp(Buffer, signedOutTests1[i].OutBuffer)){
      Errors2++;
      AnError2 = i;
			
    }
  }

	  Errors3 = 0;
  for(i=0; i<16; i++){
    Fixed_uBinOut8s(outTests3[i].InNumber,Buffer);
		printf(Buffer);
		delay(delayTime);
		Output_Clear();
    if(strcmp(Buffer, outTests3[i].OutBuffer)){
      Errors3++;
      AnError3 = i;
    }
  }
	
	TotalErrors = Errors1 + Errors2 + Errors3;
	if(TotalErrors > 0){
		printf("Errors: %d ",TotalErrors);
	}
	else{
		printf("Test Complete, No errors!");
	}


  for(;;) {} /* wait forever */
}

