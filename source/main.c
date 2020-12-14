


/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include "time.h"
#include "usart_1284.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

unsigned char temp;
enum MC1_States{MC1_Transmit, MC1_Wait, MC1_Receive} MC1_State;

void Micro1(){

    // Transition
    switch(MC1_State){
	case MC1_Transmit:
	    if(USART_IsSendReady(0)){
		MC1_State = MC1_Wait;
	    }else{
		MC1_State = MC1_Transmit;
	    } 
	    break;

	case MC1_Wait:
	    if(USART_HasTransmitted(0)){
		MC1_State = MC1_Receive;
	    } else { 
		MC1_State = MC1_Wait;
	    }
	    break;

	case MC1_Receive:
	    if(USART_HasReceived(0)){
		MC1_State = MC1_Transmit;
	    } else { 
		MC1_State = MC1_Receive;
	    }
	    break;
    }

    // Action
    switch(MC1_State){
	case MC1_Transmit:
	    USART_Send(temp, 0);
	    break;
	case MC1_Wait:
	    break;
	case MC1_Receive:
	    temp = USART_Receive(0);
	    PINA = 1;
	    USART_Flush(0);	    
	    break;

    }
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRD = 0xFF; PORTD = 0x00;
    temp = 0xFF;
  
    TimerSet(1000);
    TimerOn();
    MC1_State = MC1_Transmit;
    initUSART(0);
    /* Insert your solution below */
    while (1) {   	
  	Micro1();
    }
    return 1;
}
