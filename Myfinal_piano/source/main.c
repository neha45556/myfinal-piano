/*	Author: ngupt009
 *  Partner(s) Name: none
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "/Users/nehagupta/Downloads/simavr-master/simavr/sim/avr/avr_mcu_section.h"
#endif

void set_PWM(double frequency){
    static double current_frequency;
    if(frequency != current_frequency){
        if(!frequency){ TCCR3B &= 0x08; }
        else{ TCCR3B |= 0x03; }
        if(frequency < .954){ OCR3A = 0xFFFF;}
        else if(frequency > 31250) { OCR3A = 0x0000; }
        else { OCR3A = (short)(8000000 / (128* frequency)) -1; }
        TCNT3 = 0;
        current_frequency = frequency;
    }
}

void PWM_on(){
    TCCR3A = (1 << COM3A0);
    TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
    set_PWM(0);
}

void PWM_off(){
    TCCR3A = 0x00;
    TCCR3B = 0x00;
}


#define buttons (~PINA & 0x07)

enum states {init, C, D, E, F, G, A, B} state;
void sound(){
	switch(state){
		case init:
			if(buttons == 0x01){
				state = C;
			}
			else if(buttons == 0x02){
				state = D;
			}
			else if(buttons == 0x04){
				state = E;
			}
			else if(buttons == 0x08){
				state = F;
			}
			else if(buttons == 0x0F){
				state = G;
			}
// 			else if(buttons == 0x20){
// 				state = A;
// 			}
// 			else if(buttons == 0x40){
// 				state = B;
			//}
			else{
				state = init; 
			}	
		break;
		case C:
			if(buttons == 0x01){
				state = C;
			}
			else if(buttons == 0x02){
				state = D;
			}
			else if(buttons == 0x04){
				state = E;
			}
			else if(buttons == 0x08){
				state = F;
			}
			else if(buttons == 0x0F){
				state = G;
			}
			else{
				state = init;
			}
		break;
		case D:
			if(buttons == 0x01){
				state = C;
			}
			else if(buttons == 0x02){
				state = D;
			}
			else if(buttons == 0x04){
				state = E;
			}
			else if(buttons == 0x08){
				state = F;
			}
			else if(buttons == 0x0F){
				state = G;
			}
			else{
				state = init;
			}
		break;
		case E:
			if(buttons == 0x01){
				state = C;
			}
			else if(buttons == 0x02){
				state = D;
			}
			else if(buttons == 0x04){
				state = E;
			}
			else if(buttons == 0x08){
				state = F;
			}
			else if(buttons == 0x0F){
				state = G;
			}
			else{
				state = init;
			}
		break;
		case F:
			if(buttons == 0x01){
				state = C;
			}
			else if(buttons == 0x02){
				state = D;
			}
			else if(buttons == 0x04){
				state = E;
			}
			else if(buttons == 0x08){
				state = F;
			}
			else if(buttons == 0x0F){
				state = G;
			}
			else{
				state = init;
			}
		break;
		case G:
			if(buttons == 0x01){
				state = C;
			}
			else if(buttons == 0x02){
				state = D;
			}
			else if(buttons == 0x04){
				state = E;
			}
			else if(buttons == 0x08){
				state = F;
			}
			else if(buttons == 0x0F){
				state = G;
			}
			else{
				state = init;
			}
		break;
	
		default:
			state = init;
			break;
	}
	switch(state){
		case init:
			set_PWM(0);
			break;
		case C:
			set_PWM(261.63);
			break;
		case D:
			set_PWM(293.66);
			break;
		case E:
			set_PWM(329.63);
			break;
		case F:
			set_PWM(349.23);
			break;
		case G:
			set_PWM(392.00);
			break;
		default:
			break;
	}
				
			
}


int main(void){
  	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	PWM_on();
	state = init;
	while(1) {
		sound();
	}
	return 1;
}



