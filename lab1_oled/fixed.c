// Filename: fixed.c
// Description: Fixed-point output routines for LM3S OLED
// Danny Salzman and Luke Trowbridge
// EE445L - Spring 2014 - Lab 1

#include <stdio.h>
#include "fixed.h"


void Fixed_uDecOut2s(unsigned long n,  char *string) {
	char *temp = string;
	unsigned int quotient;
	unsigned int divisor;
	if (n > 99999){										   //checks if input out of bounds
		string[0] = '*';                   //output error
		string[1] = '*';
		string[2] = '*';
		string[3] = '.';
		string[4] = '*';
		string[5] = '*';		
	}
	else {
		divisor = 10000;
		while (divisor > 0) {							 //recursively input largest int into string
			quotient = n/divisor;
			*string	= quotient + '0';
			string ++;

			if (divisor == 100) {					   //input decimal
			*string = '.';
			string++;
			}

			n = n%divisor;
			divisor = divisor/10;
		}
		*string = 0;
		string = temp;
	}
}

void Fixed_sDecOut3s(long n, char *string) {
	char *temp = string;
	unsigned int quotient;
	unsigned int divisor;
	if (n > 9999 || n < -9999) {
	  string[0] = ' ';
		string[1] = '*';
		string[2] = '.';
		string[3] = '*';
		string[4] = '*';
		string[5] = '*';
	}
	else {
		if (n < 0){
			*string = '-';
			string++;
			n *= -1;
		}
		else {
			*string = ' ';
			string++;
		}
		
		divisor = 1000;
		while (divisor > 0) {						    //recursively input largest int into string					    
			quotient = n/divisor;
			*string	= quotient + '0';
			string ++;

			if (divisor == 1000) {					  //input decimal
				*string = '.';
				string++;
			}

			n = n%divisor;
			divisor = divisor/10;
		}
		*string = 0;
		string = temp;
	}
				  
}

void Fixed_uBinOut8s(unsigned long n,  char *string) {
	char *temp = string;
	unsigned int quotient;
	unsigned int divisor;
	if (n >= 256000) {
	  string[0] = '*';
		string[1] = '*';
		string[2] = '*';
		string[3] = '.';
		string[4] = '*';
		string[5] = '*';
	}
	else {
		n = n*1000;
		n = n/256;
		divisor = 100000;
		while (divisor > 1) { 				     //recursively input largest int into string
			quotient = n/divisor;
			*string	= quotient + '0';
			string ++;

			if (divisor == 1000) {					 //input decimal
				*string = '.';
				string++;
			}

			n = n%divisor;
			divisor = divisor/10;
		}
		*string = 0;
		string = temp;
	}

}
