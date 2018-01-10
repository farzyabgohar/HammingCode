
/*

File receive.c


Purpose: simulate the receiveing end of a message over the network.  

The program converts a message encodded as an array of short integers into characters.
The input message uses 1-bit error correction code.
As part of the simulation, the program also corrects any 1-bit errors in the receiving message.


Revision:
a. Initial code - Doron Nussbaum
b. Revision - Farzyab Gohar

*/


/************************************************************************/

// INCLUDE FILES

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "assert.h"
#include "bit_manipulation.h"


/************************************************************************/
//MACROS  / DEFINES



#define XSTR(A) STR(A)
#define STR(A) #A
#define MAX_INPUT_LENGTH 8192
#define MAX_MSG_LENGTH 2048
#define P1_MASK 0xaa8   // 0b0101010101000
#define P2_MASK 0xcc8	// 0b0110011001000
#define P4_MASK 0x10e0	// 0b1000011100000
#define P8_MASK 0x1e00  // 0b1111000000000


/************************************************************************/
// FUNCTION PROTOTYPES


void short2Char(short encodedChar, char *c);
void correctCode(short *num);
void readEncodedMessage(short *buf, int len, int *numRead);




/**************************************************************************/

int main(int argc, char *argv[])

{
	int rc = 0;		// return code

	char s[MAX_MSG_LENGTH] = { '\0' };  // message
	short encodedMsg[MAX_MSG_LENGTH];
	int numRead = 0;  // number of characters in the message
	int i;

	// read the message
	printf("Please enter the transmitted message: ");
	readEncodedMessage(encodedMsg, MAX_MSG_LENGTH, &numRead);



	// print the corrected message
	printf("\n\n Transmitted Message:\n");
	for (i = 0; i < numRead; i++) {
		char c;
		short2Char(encodedMsg[i], &c);
		printf("%c", c);
    }
    printf("\n");

    // correct the message
	for (i = 0; i < numRead; i++) {
		correctCode(&encodedMsg[i]);
	}



	// print the corrected message
	printf("\n\n Corrected Transmitted Message:\n");
	for (i = 0; i < numRead; i++) {
		char c;
		short2Char(encodedMsg[i], &c);
		printf("%c", c);
	}
	printf("\n");

	return(0);
}


/***********************************************************************************/
/* reads a message from the user

input
len - maximum length of mesage that should be read

output
receivedMsg - contains the message
numRead - the number of characters in the message

*/


void readEncodedMessage(short *receivedMsg, int len, int *numRead)
{
	int i;
	int rc;
	char s[MAX_INPUT_LENGTH+1];
	char *token = NULL;
	*numRead = 0;

	s[MAX_INPUT_LENGTH] = '\0';
	scanf("%"XSTR(MAX_INPUT_LENGTH)"[^\n]s", s);
	token = strtok(s, " ");

	for (i = 0; token != NULL  &&  i < len;token = strtok(NULL, " "), i++) {
		rc = sscanf(token, "%hd", &receivedMsg[i]);
	}

	*numRead = i; // set the number of read integers

    // empty the input buffer
    for( ; getchar() != '\n'; );


}




/*************************************************************************/
/* collect of a short bits 3,5,6,7,9,10,11,12  to bits 0-7 of a char

input
encodedNum - a short with the bits of c

output
c - the char that is embedded in encodedNum

*/


void short2Char(short encodedNum, char *c)

{
	int i;


//checks if we are at the required bit positions (3, 5, 6, 7...), and if the bit value at those positions is 1, then it sets the corresponding bit value of char (0, 1, 2, 3...) to 1. I had trouble understanding what I needed to use mask and bitSet for, so I worked around a different solution which also works.
	*c = 0;
	for (i = 0; i < 8; i++) {
		
		if ((i+3 == 3) && isShortBitSet(encodedNum, 3)) {
			setCharBit(i, c);
		}
		if ((i+4 == 5) && isShortBitSet(encodedNum, 5)) {
			setCharBit(i, c);
		}
		if ((i+4 == 6) && isShortBitSet(encodedNum, 6)) {
			setCharBit(i, c);
		}
		if ((i+4 == 7) && isShortBitSet(encodedNum, 7)) {
			setCharBit(i, c);
		}
		if ((i+5 == 9) && isShortBitSet(encodedNum, 9)) {
			setCharBit(i, c);
		}
		if ((i+5 == 10) && isShortBitSet(encodedNum, 10)) {
			setCharBit(i, c);
		}
		if ((i+5 == 11) && isShortBitSet(encodedNum, 11)) {
			setCharBit(i, c);
		}
		if ((i+5 == 12) && isShortBitSet(encodedNum, 12)) {
			setCharBit(i, c);
		}
		
	}
}


/*************************************************************************************/


/* purpose:
performs error corrrections, if needed on the short integer

The function first checks the parity bits for error.  
If there is an error then it fixes it.

input
num - the address of the short number 
*/


void correctCode(short *num)

{
	int mask;
	int sum;
	int bitNumber = 0; //  bit number with the error bit
	int parity;		// a parity bit either 0 or 1
	int storedParity; // the parity bit in the encoded char

	
	mask = *num & P1_MASK;
	//parity bit check for P1. If mismatch is found, 2^0 is added to bitnumber
	sum = countBits(mask);
	storedParity = isShortBitSet(*num, 1);


	if(!((sum % 2) == storedParity)) {
		bitNumber = bitNumber + 1;
	}
	
	//parity bit check for P2. If mismatch is found, 2^1 is added to bitnumber

	mask = *num & P2_MASK;
	
	sum = countBits(mask);
	storedParity = isShortBitSet(*num, 2);
	
	if(!((sum % 2) == storedParity)) {
		bitNumber = bitNumber + 2;
	}

	//parity bit check for P4. If mismatch is found, 2^2 is added to bitnumber
	
	mask = *num & P4_MASK;
	
	sum = countBits(mask);
	storedParity=isShortBitSet(*num,4);
	// if the two parities are different add 2^2 to bitNumber
	if(!((sum % 2) == storedParity)) {
		bitNumber = bitNumber + 4;
	}
	
	//parity bit check for P8. If mismatch is found, 2^3 is added to bitnumber
	
	// check parity bit p8
    // calculate the parity for P8
	// compare the calculated parity with the stored parity
	mask = *num & P8_MASK;
	
	sum=countBits(mask);
	storedParity = isShortBitSet(*num, 8);
    // if the two parities are different add 2^3 to bitNumber
	if(!((sum%2) == storedParity)) {
		bitNumber = bitNumber + 8;
	}


    // if necessary flip the bit at position bitNumber 
	if(bitNumber!=0) {
		flipBitShort(bitNumber, num);
	}
}

