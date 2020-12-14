




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
#include "usart.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

unsigned char temp;


enum MC1_States{MC1_Transmit, MC1_Wait, MC1_Receive} MC1_State;

void Micro1(){

    // Transition
    switch(MC1_State){
	case MC1_Transmit:
	    if(USART_IsSendReady()){
		MC1_State = MC1_Wait;
	    }else{
		MC1_State = MC1_Transmit;
	    } 
	    break;

	case MC1_Wait:
	    if(USART_HasTransmitted()){
		MC1_State = MC1_Receive;
	    } else { 
		MC1_State = MC1_Wait;
	    }
	    break;

	case MC1_Receive:
	    if(USART_HasReceived()){
		MC1_State = MC1_Transmit;
	    } else { 
		MC1_State = MC1_Receive;
	    }
	    break;
    }

    // Action
    switch(MC1_State){
	case MC1_Transmit:
	    USART_Send(temp);
	    break;
	
	case MC1_Receive:
	    temp = USART_Received();
	    PINA = temp;
	    USART_Flush();	    
	    break;

    }
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRD = 0xFF; PORTD = 0xFF;
    temp = 0xFF;
  
    MC1_State = MC1_Transmit;
    initUSART(0);
    /* Insert your solution below */
    while (1) {
   	
   	Micro1();
    }
    return 1;
}
