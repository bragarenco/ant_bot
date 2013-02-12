/*
 * resources.c
 *
 *  Created on: Jan 13, 2011
 *      Author: Andrey
 */

#include "resources.h"

void intToStr(int nr, char* str){
	unsigned char pos = 0;
	unsigned char sign = 0;
	if(nr<0){
		nr*=-1;
		sign = 1;
	}
	while(nr){
		str[pos++] = nr%10+'0';
		nr/=10;
	}
	if(pos==0){
		str[pos++]='0';
	}
	if(sign){
		str[pos++] = '-';
	}
	str[pos] = 0;


    unsigned char i = 0;
	while(--pos>i){
		char tmp = str[pos];
		str[pos] = str[i];
		str[i++] = tmp;
	}

}

char StringSize(char* str){
	char pos=0;
	while(str[pos]!=0){
		pos++;
		if(!pos){
			pos = -1;
			break;
		}
	}
	return pos;
}
void StringPushBack(char* str, char ch){
	char pos=StringSize(str);
	if(pos>0){
		str[pos++]=ch;
		str[pos]=0;
	}
}
void StringAssign(char* str, char* str1){
	char pos=0;
	do{
		str[pos]= str1[pos];
	}while(str1[pos++]!=0);

}

void FloatToStr(float float_nr, char* float_str, char accuracy) {

	int intNr = float_nr;
	float_nr -= intNr;

	intToStr(intNr, float_str);

	int pointPos = StringSize(float_str);
	if (pointPos > 0) {
		float_str[pointPos++] = '.';

		while (accuracy--) {
			float_nr *= 10;
			char restNr = float_nr;
			float_str[pointPos++] = restNr + '0';
			float_nr -= restNr;
		}

		float_str[pointPos] = 0;

//		while (float_str[--pointPos] == '0') {
//			float_str[pointPos] = 0;
//		}
	}
}
