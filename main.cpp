/*
 * PhaseAngleControl.cpp
 *
 * Created: 18-09-2019 18:13:39
 * Author : Rushad
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int ADC_read(unsigned char chnl)
{
	chnl= chnl & 0b00000111;
	ADMUX = 0x40;
	ADCSRA|=(1<<ADSC);
	while(!(ADCSRA & (1<<ADIF)));
	ADCSRA|=(1<<ADIF);
	return (ADC);
}

unsigned int map(int input, float input_start, float input_end, float output_start, float output_end)
{
	double slope = 1.0 * (output_end - output_start) / (input_end - input_start);
	unsigned int output = output_start + slope * (input - input_start);
	return output;
}

int main(void)
{
	DDRB = 0b00000001;
	ADMUX=(1<<REFS0);
	ADCSRA=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	
	EICRA |= (1 << ISC00);
	EIMSK |= (1 << INT0);
	
	sei();
	
	while (1)
	{
		
	}
}

ISR (INT0_vect)
{
	int pot = ADC_read(0);
	int on_time = map(pot, 0, 1023, 0, 1000);
	PORTB |= (1 << PB0);
	_delay_ms(on_time);
	PORTB &= ~(1 << PB0);
	_delay_ms(100);

}

