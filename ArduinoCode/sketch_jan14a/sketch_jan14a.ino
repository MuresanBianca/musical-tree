#include <avr/io.h>
#include <avr/interrupt.h>

float C4 =  261.63;        
float Db4 = 277.18;   
float D4 =  293.66;       
float Eb4 = 311.13;  
float E4 =  329.63;        
float F4 =  349.23;     
float Gb4=  369.99;   
float G4 =  392.00;        
float Ab4=  415.30;            
float musicalNoteA4 = 440.00;     
float Bb4 = 466.16;            
float B4 = 493.88;           
float C5 = 523.25;        
float D5 = 587.33; 
float Eb5 = 622.25;
float E5 =  659.25; 
float F5 = 698.46; 
float G5 = 783.99; 
float Gb5 = 739.99;
float musicalNoteA5 = 880.00;
float Ab5  = 830.61;
float B5 = 987.77;  
float Bb5 = 932.33;
float C6 = 1046.50; 
float Db6 =  1108.73; 
float D6 = 1174.66 ;  
float Eb6 = 1244.51 ;
float E6 = 1318.51 ; 
float F6 = 1396.91 ; 
float Gb6 = 1479.98 ;
float G6 = 1567.98 ; 
int pouse=0;        

int sec=500;
int counter=-1;
long int i=0,ms=0,TOP;

float HarryPotter_Notes[]={B4,E5,G5,F5,Eb5,B5,musicalNoteA5,F5,E5,G5,F5,Eb5,B5,B4,pouse,B4,E5,G5,F5,Eb5,B5,D6,Db6,C6,Ab5,C6,B5,Bb5,Bb4,F5,E5,pouse};//32
long int HarryPotter_Duration[]={0,sec,sec*1.5,sec/2,sec,sec*2,sec,sec*3,sec*3,sec*1.5,sec/2,sec,sec*2,sec,sec*3,sec*2,sec,sec*1.5,sec/2,sec,sec*2,sec,sec*2,sec,sec*2,sec,sec*1.5,sec/2,sec,sec*2,sec,sec*2,sec/2};//32

int sec2 = 500;
float FurElise_Notes[]={ E5, Eb5, E5,Eb5,E5,B4,D5,C5, musicalNoteA4,0,C4,E4,musicalNoteA4, B4,0,E4,Ab4,B4, C5,0,E4,E5,Eb5, E5,Eb5,E5,B4,D5,C5, musicalNoteA4,0,C4,E4, B4,0,E4,C4,B4, musicalNoteA4,0,E5,Eb5, E5,Eb5,B4,D5,C5,  B4,0,E4,C5,B4, musicalNoteA4,0,B4,C5,D5, E5,0,G4,F5,E5, D5,0,F4,E5,D5, C5,0,E4,D5,C5, B4,0,E4,C5,B4, musicalNoteA4,0,B4,C5,D5, E5,0,G4,F5,E5, D5,0,F4,D5,E5, C5,0,E4,D5,C5 ,F4, 0 };
long int FurElise_Duration[]={ sec2/2,sec2/2,sec2/2,sec2/2,sec2/2,sec2/2,sec2/2,sec2/2,sec2,sec2/2,sec2/2,sec2/2,sec2/2,sec2,sec2/2,sec2/2,sec2/2,sec2/2, sec2, sec2/2, sec2,sec2,sec2, sec2/2,sec2/2,sec2/2,sec2/2,sec2/2,sec2/2, sec2,sec2/2,sec2/2,sec2/2,sec2/2, sec2,sec2/2,sec2/2,sec2/2,sec2/2, sec2,sec2,sec2/2,sec2/2, sec2/2,sec2/2,sec2/2,sec2/2,sec2/2,sec2/2, sec2,sec2/2,sec2/2,sec2/2,sec2/2,sec2,sec2/2,sec2/2,sec2/2,sec2/2,sec2,sec2/2,sec2/2,sec2/2,sec2/2,sec2/2,sec2/2,sec2/2,sec2/2,sec2/2,sec2/2,sec2,sec2/2,sec2/2,sec2/2,sec2/2, sec2,sec2/2,sec2/2,sec2/2,sec2/2, sec2,sec2/2,sec2/2,sec2/2,sec2/2, sec2,sec2/2,sec2/2,sec2/2,sec2/2, sec2,sec2/2,sec2/2,sec2/2,sec2/2, sec2,sec2/2,sec2/2,sec2/2,sec2/2, sec*2, sec*4};

int sec3 = 300;
float Spiderman_Notes[]={E4,G4,B4,musicalNoteA4,musicalNoteA4,G4,E4,E4,G4,B4,musicalNoteA4,G4,E4,musicalNoteA4,C5,E5,D5,C5,musicalNoteA4,musicalNoteA4,E4,G4,B4,musicalNoteA4,G4,E4,C5,B4,G4,musicalNoteA4,musicalNoteA4,G4,musicalNoteA4,G4,E4,G4,B4,musicalNoteA4,G4,E4,0};
int Spiderman_Duration[]={sec,sec3/2,sec3*2,sec3/2,sec3/2,sec3/2,sec3*2,sec3,sec3/2,sec3*2.5,sec3,sec3/2,sec3*2,sec3,sec3/2,sec3*2,sec3,sec3/2,sec3/2,sec3,sec3,sec3/2,sec3*2,sec3,sec3/2,sec3*2,sec3/2,sec3*1.5,sec3/2,sec3,sec3,sec3/2,sec3,sec3/2,sec3*4,sec3/2,sec3*2,sec3,sec3/2,sec3,sec3*3};

void timer0_init() 
{
SREG = 1<<7; // Global Interrupt Enable
//normal port operation, OC0A si OC0B disconnect, CTC with OCRA,64 prescaler
TCCR0A = 0b00000010; 
TCCR0B = 0b00000011;
TCNT0 = 0;
OCR0A = 250;
TIMSK0 |= 0b00000010; 
}

void interrupt_init()
{
  EIMSK=0b00000011;//acvtivate the external interrupts
  SREG = 1<<7; // Global Interrupt Enable
  EICRA=0b00001010;//positive edge INT0 and INT1
}

void buzzer_init()
{
  DDRB |= 0b00000010;  //PB1 is set as an output for the buzzer's PWM signal
  //the setings for the timer as CTC, clk/8 prescaler,toogle OC1A compare match :
  TCCR1A =  0b01000000;
  TCCR1B =  0b00001010;
  TCCR1C =  0b00000000;
}

void button_int()
{
    DDRD &=~ 0b00000100;//PD2 - switch the melody
}

void LEDs_init()
{
  DDRC |= 0b00000111;//yellow output
  DDRC |= 0b00111000;//green output
  DDRB |= 0b00111101;//red output
  DDRD |= 0b11100000;//blue output
}

void LED(int freq)
{
  if(freq<400)
    PORTB |= 0b00111101;//red
  else 
    PORTB &=~ 0b00111101;//not red
  if(freq>300&&freq<500)
    PORTC |= 0b00000111;//yellow
  else 
    PORTC &=~ 0b00000111;//not yellow
  if(freq>500&&freq<700)
    PORTD |= 0b11100000;//blue
  else
    PORTD &=~ 0b11100000;//not blue
  if(freq>700)
    PORTC |= 0b00111000;//green
  else
     PORTC &=~ 0b00111000;//not green
}


ISR(TIMER0_COMPA_vect)
{
  switch(counter)
    {
    case 0:
         {
          if(ms>=HarryPotter_Duration[i])
          {
            TOP = 1000000/HarryPotter_Notes[i]-1;
            OCR1AH = ((TOP+1)/2)>>8;
            OCR1AL = (TOP+1)/2;
            LED(HarryPotter_Notes[i]);
            ms=0;
            i++;
            if(i==32)
              i=0;
          }
          else
            ms++;
        }break;
    case 1:
        {
          if(ms>=FurElise_Duration[i])
          {
            TOP = 1000000/FurElise_Notes[i]-1;
            OCR1AH = ((TOP+1)/2)>>8;
            OCR1AL = (TOP+1)/2;
            LED(FurElise_Notes[i]);
            ms=0;
            i++;
            if(i==102)
              i=0;
          }
          else
            ms++;
        }break;
    case 2:
        {
          if(ms>=Spiderman_Duration[i])
          {
            TOP = 1000000/Spiderman_Notes[i]-1;
            OCR1AH = ((TOP+1)/2)>>8;
            OCR1AL = (TOP+1)/2;
            LED(Spiderman_Notes[i]);
            ms=0;
            i++;
            if(i==41)
              i=0;
          }
          else
            ms++;
        }break;
    }
}

ISR(INT0_vect)//PD2
{
  counter++;
  i=0;
  ms=0;
  if(counter==3)
      counter=0;
      
}                                                                    
                                                                                                                                          
int main()
{
  timer0_init();
  buzzer_init();
  button_int();
  LEDs_init();
  interrupt_init();
  while(1)
  {

  }
}
