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


#define buttons (~PINA & 0xFF)

enum states {init, sound1, sound2} state;
void sound(){
	switch(state){
		case init:
			if(buttons == 0x01){
				state = sound1;
			}
// 			if(buttons == 0x02){
// 				state = sound2;
			//}
			state = init; 
			
		break;
		case sound1:
			if(buttons == 0x01){
				state = sound1;
			}
			else{
				state = init;
			}
		break;
// 		case sound2:
// 			if(PA0){
// 				state = sound1;
// 			}
// 			state = sound2;
// 			break;
	}
	switch(state){
		case init:
			set_PWM(523.25);
			break;
		case sound1:
			set_PWM(261.63);
			break;
		case sound2:
			set_PWM(293.66);
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
