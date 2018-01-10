#include "bit_manipulation.h"
/*

File bit_manipulation.c

Purpose :
contains helper functions for manipulating bits


//Initial code: Doron Nussbaum
//revisions : Farzyab Gohar

/*************************************************************************************/
/* purpose: checks if bit i is set

input:
c - the character to be checked
bitNum - the bit number to be checked

return:
1 if the bit is set to 1
0 if the bit is not set (bit is 0)

*/

int isCharBitSet(char c, int bitNum)

{
    return (c & (1 << bitNum)) >> bitNum;  // checks bit at position bitNum and returns its 											value
}




/*************************************************************************************/

/* purpose: checks if bit i is set

input: 
num - the number to be checked
bitNum - the bit number to be checked 

return:
1 if the bit is set to 1
0 if the bit is not set (bit is 0)

*/
int isShortBitSet(short num, int bitNum)

{
    if (((num>>bitNum) & 1) == 1) {
    	return 1;
    }
    return 0;
}

/*************************************************************************************/
/* purpose: sets bit bitNum to 1 

input:
num - the address of the short integer
bitNum - the bit number to be checked



*/

void setShortBit(int bitNum, short *num)

{
    *num = *num | (1<<bitNum); //sets bit at position bitNum to 1 
}

/*************************************************************************************/


/* purpose: sets bit bitNum to 1

input:
c - address of character 
bitNum - the bit number to be checked

return:
1 if the bit is set to 1
0 if the bit is not set (bit is 0)

*/
void setCharBit(int bitNum, char *c)

{

    *c = *c | (1<<bitNum); //sets bit at bitNum position of char to 1
}

/*************************************************************************************/


/*  count the number of bits in a short

input: 
num - a short interger

return
the numer of bits that are set to 1 in num



*/
int countBits(short num)

{
	int totalCount = 0;

    for (int i=0; i<=15; i++) {
    	if (isShortBitSet(num, i) == 1) {
    		totalCount = totalCount + 1;
    	}
    
    }
    return totalCount;
    
}






/*************************************************************************************/

/* purpose:
flips bit i in num (set bit i to 1 if the bit is 0 or set bit i to 0 if the bit is 1)

input:
bitNum - the bit number to be flipped
num - address of the short integer

*/
void flipBitShort(int bitNum, short *num)

{

    if (isShortBitSet(*num, bitNum)) { //checks if bit at position bitNum is 1, if yes then 										flips bit from 1 to 0 at position bitNum by clearing it
    	*num = *num & (~(1<<bitNum));
    } else {
    	*num = *num | (1<<bitNum);	//if first check returns false, then bit at bitNum must be 							0, hence to flip we must add 1 at that position using bitwise operators
    }
}


