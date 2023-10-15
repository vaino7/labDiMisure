/*Versione 1
#include <stm32f303xc.h>
static int i;
int main(void){
	RCC->AHBENR=(1<<21);
	GPIOE->MODER=(1<<16);
	while(1){
		GPIOE->ODR = (1<<8);
		for(i=0;i<100000;i++);
		GPIOE->ODR = 0;
		for(i=0;i<100000;i++);
	}
	return 0;
}
*/

/*---------------------------------------------------------*/

/*Versione 2 - ACCENSIONE 2 LED
#include <stm32f303xc.h>
static int i;
int main(void){
	RCC->AHBENR=(1<<21);
	GPIOE->MODER=0x00050000;                //Alziamo sia led blu che rosso
	while(1){
		GPIOE->ODR = (1<<8);                //Alzo linea 8
		GPIOE->ODR |= (1<<9);               //Alzo linea 9
		for(i=0;i<100000;i++);
		GPIOE->ODR = 0;
		for(i=0;i<100000;i++);
	}
	return 0;
}
*/
/*---------------------------------------------------------*/

/*Versione 3 -- ACCENSIONE 2 LED
#include <stm32f303xc.h>
static int i;
int main(void){
	RCC->AHBENR=(1<<21);
	GPIOE->MODER=0x00050000;                         //Alziamo sia led blu che rosso
	while(1){
		GPIOE->ODR = (1<<8) | (1<<9);                //Alzo linea 8 e 9
		for(i=0;i<100000;i++);
		GPIOE->ODR = 0;
		for(i=0;i<100000;i++);
	}
	return 0;
}
*/
/*---------------------------------------------------------*/

/*Versione 4 -- SPEGNIMENTO 1 DEI DUE LED
#include <stm32f303xc.h>
static int i;
int main(void){
	RCC->AHBENR=(1<<21);
	GPIOE->MODER=0x00050000;                         
	while(1){
		GPIOE->ODR = (1<<8) | (1<<9);                
		for(i=0;i<100000;i++);
		GPIOE->ODR &= 0xfffffeff;                         //& tutti 0 e 1 solo al LED che voglio spegnere
		for(i=0;i<100000;i++);
	}
	return 0;
}
*/


//Versione 5 -- SPEGNIMENTO 1 DEI DUE LED
#include <stm32f303xc.h>
static int i;
int main(void){
	RCC->AHBENR=(1<<21);
	GPIOE->MODER=0x00050000;                         
	while(1){
		GPIOE->ODR = (1<<8) | (1<<9);                
		for(i=0;i<100000;i++);
		GPIOE->ODR &= ~(1<<8);                         //& tutti 0 e 1 solo al LED che voglio spegnere
		for(i=0;i<100000;i++);
	}
	return 0;
}
