/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/02/2017 20:05:55
 *       Revision:  none
 *       Compiler:  arm-none-eabi-gcc
 *
 * =====================================================================================
 */

#include "gpio.h"

int flag;

/*****************************************************************************
**                INTERNAL MACRO DEFINITIONS
*****************************************************************************/
#define TIME /*2000000*/ 2000
#define TIME_2 20000
#define TOGGLE (0x01u)
#define BIT_WIDTH 8 /* Largura de 1 byte do número */

/*****************************************************************************
**                INTERNAL FUNCTION PROTOTYPES
*****************************************************************************/
static void delay();
//static void toggle(gpioPort port, ucPinNumber pin);

void init_zero(){

	/* PINOS DE CONTROLE */

	gpioSetPinValue(GPIO1, 16, LOW); // Define RS em 0
	gpioSetPinValue(GPIO2, 4, LOW); // Define E em 0

	/* PINOS DE DADOS */

	gpioSetPinValue(GPIO1, 28, LOW); // D0 - PIN12 - P9
	gpioSetPinValue(GPIO1, 12, LOW); // D1 - PIN12 - P8
	gpioSetPinValue(GPIO0, 26, LOW); // D2 - PIN14 - P8
	gpioSetPinValue(GPIO1, 14, LOW); // D3 - PIN16 - P8
	gpioSetPinValue(GPIO2, 1, LOW);  // D4 - PIN18 - P8
	gpioSetPinValue(GPIO1, 29, LOW); // D5 - PIN26 - P8
	gpioSetPinValue(GPIO1, 13, LOW); // D6 - PIN11 - P8 
	gpioSetPinValue(GPIO1, 15, LOW); // D7 - PIN15 - P8
}

void init_zero_others(){ // função que coloca o RS em 1 para enviar caracteres

	/* PINOS DE CONTROLE */

	gpioSetPinValue(GPIO1, 16, HIGH); // Define RS em 0
	gpioSetPinValue(GPIO2, 4, LOW); // Define E em 0

	/* PINOS DE DADOS */

	gpioSetPinValue(GPIO1, 28, LOW); // D0 - PIN12 - P9
	gpioSetPinValue(GPIO1, 12, LOW); // D1 - PIN12 - P8
	gpioSetPinValue(GPIO0, 26, LOW); // D2 - PIN14 - P8
	gpioSetPinValue(GPIO1, 14, LOW); // D3 - PIN16 - P8
	gpioSetPinValue(GPIO2, 1, LOW);  // D4 - PIN18 - P8
	gpioSetPinValue(GPIO1, 29, LOW); // D5 - PIN26 - P8
	gpioSetPinValue(GPIO1, 13, LOW); // D6 - PIN11 - P8 
	gpioSetPinValue(GPIO1, 15, LOW); // D7 - PIN15 - P8
}

void send_data(int number) {

	int i = 0;
	int pin_value[10];
	int mod_number[10];

	// MAPEAMENTO DE PINOS DE DADOS DENTRO DE UM VETOR

	pin_value[0] = 28;
	pin_value[1] = 12;
	pin_value[2] = 26;
	pin_value[3] = 14;
	pin_value[4] = 1;
	pin_value[5] = 29;
	pin_value[6] = 13;
	pin_value[7] = 15;
	pin_value[8] = 4;  // Posição do vetor referente ao pino do E
	pin_value[9] = 16; // Posição do vetor referente ao pino do RS

	// MAPEAMENTO DOS MÓDULOS DENTRO DE UM VETOR

	mod_number[0] = GPIO1;
	mod_number[1] = GPIO1;
	mod_number[2] = GPIO0;
	mod_number[3] = GPIO1;
	mod_number[4] = GPIO2;
	mod_number[5] = GPIO1;
	mod_number[6] = GPIO1;
	mod_number[7] = GPIO1;
	mod_number[8] = GPIO2; // Posição do vetor referente ao Módulo do E
	mod_number[9] = GPIO1; // Posição do vetor referente ao Módulo do RS

int cont = 8;

while(cont > 0){


	for(i = 0; i < BIT_WIDTH; ++i){
		if(number & (1 << i)){
			gpioSetPinValue(mod_number[i], pin_value[i], HIGH);
			//delay();
		}
	}
	delay();
 	cont--;
 }

 	//gpioSetPinValue(mod_number[8], pin_value[8], HIGH); // Define E em 1
	//delay();
	//gpioSetPinValue(mod_number[8], pin_value[8], LOW); // Define E em 0
	//delay();
	gpioSetPinValue(mod_number[8], pin_value[8], HIGH); // Pulso Enable
	delay();
	gpioSetPinValue(mod_number[8], pin_value[8], LOW); // Pulso Enable
	delay();
	//gpioSetPinValue(mod_number[9], pin_value[9], HIGH); // Define E em 0
}

int asciiToInt (char ascii){
	if (ascii < '0' || ascii > '9') {
		return -1; //error
	}else{
		return (int)(ascii - '0'); // This works because '0' has the int value 48 in Ascii and '1' 49 and so on.
	}
}

void intToAscii (int dec, int c_op){

register int i;
int cont = 0;

char str[c_op];
char aux[c_op];

for (i = 0; i < c_op; i++){
	if(dec == 0) 
		break;
	str[i] = (dec % 10) + 48;
	dec /= 10;
}

str[i] = 0x0;

for(i = 0; i < c_op; i++){
	aux[c_op-i-1] = str[i];
}

aux[c_op] = '\0';

while(aux[cont] != '\0'){
	init_zero_others();
	send_data(aux[cont]);
	delay();
	cont++;
}

//return str;

}

int count_op(int op){

int count = 0;

	while(op > 0){
		op = op / 10;
    	count = count + 1;  
  	}

  	return count;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */

int main(void){

	flag=0x0;	
	/*-----------------------------------------------------------------------------
	 *  initialize GPIO module
	 *-----------------------------------------------------------------------------*/
	
	//gpioInitModule(GPIO0);
	//gpioInitModule(GPIO1);
	//gpioInitModule(GPIO2);

	/*-----------------------------------------------------------------------------
	 *  initialize pin of mudule
	 *-----------------------------------------------------------------------------*/
	
	/* PINOS DE CONTROLE */

	gpioInitModule(GPIO1);
	gpioInitPin(GPIO1, 16); // RS - PIN15 - P9
	gpioInitModule(GPIO2);
	gpioInitPin(GPIO2, 4); // E  - PIN10 - P8

	/* PINOS DE DADOS */

	gpioInitModule(GPIO1);
	gpioInitPin(GPIO1, 28);	// D0 - PIN12 - P9
	gpioInitModule(GPIO1);
	gpioInitPin(GPIO1, 12);	// D1 - PIN12 - P8
	gpioInitModule(GPIO0);
	gpioInitPin(GPIO0, 26); // D2 - PIN14 - P8
	gpioInitModule(GPIO1);
	gpioInitPin(GPIO1, 14); // D3 - PIN16 - P8
	gpioInitModule(GPIO2);
	gpioInitPin(GPIO2, 1);  // D4 - PIN18 - P8
	gpioInitModule(GPIO1);
	gpioInitPin(GPIO1, 29); // D5 - PIN26 - P8
	gpioInitModule(GPIO1);
	gpioInitPin(GPIO1, 13); // D6 - PIN11 - P8
	gpioInitModule(GPIO1); 
	gpioInitPin(GPIO1, 15); // D7 - PIN15 - P8 

	/*-----------------------------------------------------------------------------
	 *  set pin direction 
	 *-----------------------------------------------------------------------------*/

	/* PINOS DE CONTROLE */

	gpioSetDirection(GPIO1, 16, OUTPUT); // RS - PIN15 - P9
	gpioSetDirection(GPIO2, 4, OUTPUT); // E  - PIN10 - P8

	/* PINOS DE DADOS */

	gpioSetDirection(GPIO1, 28, OUTPUT); // D0 - PIN12 - P9
	gpioSetDirection(GPIO1, 12, OUTPUT); // D1 - PIN12 - P8
	gpioSetDirection(GPIO0, 26, OUTPUT); // D2 - PIN14 - P8
	gpioSetDirection(GPIO1, 14, OUTPUT); // D3 - PIN16 - P8
	gpioSetDirection(GPIO2, 1, OUTPUT);  // D4 - PIN18 - P8
	gpioSetDirection(GPIO1, 29, OUTPUT); // D5 - PIN26 - P8
	gpioSetDirection(GPIO1, 13, OUTPUT); // D6 - PIN11 - P8 
	gpioSetDirection(GPIO1, 15, OUTPUT); // D7 - PIN15 - P8

	init_zero();

	send_data(0x80); // inicia a 1ª linha

	//char letter[20] = "#RobertMelhorMonitor";

	//send_data(0x0E); // inicia a 1ª linha
	delay();
	init_zero();
	send_data(0x30);
	delay();
	init_zero();
	send_data(0x38);
	delay();
	init_zero();
	send_data(0xF);
	delay();
	init_zero_others();
	//gpioSetPinValue(GPIO1, 16, HIGH);
	//send_data('I');
	//delay();
	//init_zero_others();
	//gpioSetPinValue(GPIO1, 16, HIGH);
	//send_data('a');
	//delay();
	//init_zero();
	//send_data(0xF);
	//init_zero();
	//gpioSetPinValue(GPIO1, 16, HIGH); // Define RS em 1
	//send_data('a');
	//delay();

int cont1 = 0;	
int cont2 = 0;	

int a, b;
int i = 0;
int j = 0;
char latitude[6] = "128";
char teste[6] = "54";

while(latitude[cont1] != '\0'){
		init_zero_others();
		send_data(latitude[cont1]);
		delay();
		cont1++;
	}

init_zero_others();
send_data('-');
delay();

while(teste[cont2] != '\0'){
		init_zero_others();
		send_data(teste[cont2]);
		delay();
		cont2++;
	}

init_zero_others();
send_data('=');
delay();

while(latitude[i] != '\0'){
	i++;
}

while(teste[j] != '\0'){
	j++;
}

if(i == 1){
	a = asciiToInt(latitude[0]);
}
if(i == 2){
	a = asciiToInt(latitude[1]);
	a += asciiToInt(latitude[0])*10;
}
if(i == 3){
	a = asciiToInt(latitude[2]);
	a += asciiToInt(latitude[1])*10;
	a += asciiToInt(latitude[0])*100;
}
if(i == 4){
	a = asciiToInt(latitude[3]);
	a += asciiToInt(latitude[2])*10;
	a += asciiToInt(latitude[1])*100;
	a += asciiToInt(latitude[0])*1000;
}
if(i == 5){
	a = asciiToInt(latitude[4]);
	a += asciiToInt(latitude[3])*10;
	a += asciiToInt(latitude[2])*100;
	a += asciiToInt(latitude[1])*1000;
	a += asciiToInt(latitude[0])*10000;
}
if(j == 1){
	b = asciiToInt(teste[0]);
}
if(j == 2){
	b = asciiToInt(teste[1]);
	b += asciiToInt(teste[0])*10;
}
if(j == 3){
	b = asciiToInt(teste[2]);
	b += asciiToInt(teste[1])*10;
	b += asciiToInt(teste[0])*100;
}
if(j == 4){
	b = asciiToInt(teste[3]);
	b += asciiToInt(teste[2])*10;
	b += asciiToInt(teste[1])*100;
	b += asciiToInt(teste[0])*1000;
}
if(j == 5){
	b = asciiToInt(teste[4]);
	b += asciiToInt(teste[3])*10;
	b += asciiToInt(teste[2])*100;
	b += asciiToInt(teste[1])*1000;
	b += asciiToInt(teste[0])*10000;
}

//int c_sum;
int c_sub;
//int c_mult;
//int c_div;

//int soma = a + b;
int sub = a - b;
//int mult = a * b;
//int div = a / b;

//c_sum = count_op(soma);
c_sub = count_op(sub);
//c_mult = count_op(mult);
//c_div = count_op(div);

//intToAscii(soma, c_sum);

intToAscii(sub, c_sub);

//intToAscii(mult, c_mult);

//intToAscii(div, c_div);

return(0);

} /* ----------  end of function main  ---------- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  toggle
 *  Description:  				
 * =====================================================================================
 */

//void toggle(gpioPort port, ucPinNumber pin){
//	flag^=TOGGLE;

//	if(flag)
//		gpioSetPinValue(port, pin, HIGH);
//	else
//		gpioSetPinValue(port, pin, LOW);	
//}		/* -----  end of function GPIO_toggle  ----- */

/*FUNCTION*-------------------------------------------------------
*
* Function Name : Delay
* Comments      :
*END*-----------------------------------------------------------*/

static void delay(){
	volatile unsigned int ra;
	for(ra = 0; ra < TIME; ra ++);
}

