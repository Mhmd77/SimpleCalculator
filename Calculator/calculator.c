#include <io.h>
// Graphic Display functions
#include <glcd.h>
#include <stdlib.h> 
#include <stdio.h>
// on the graphic display
#include <font5x7.h>
#include <delay.h>
#define MAXSIZE 102

void config_LCD(){
    GLCDINIT_t glcd_init_data;
    glcd_init_data.font=font5x7;
    glcd_init(&glcd_init_data);   
}
void config_PORTS(){
    DDRC=0X0F;
    PORTC=0XF0;
}
int get_number_from_keboard(void)
{
    PORTC.0=0; PORTC.1=1; PORTC.2=1; PORTC.3=1;
    if(!PINC.4) return 1;
    if(!PINC.5) return 2;
    if(!PINC.6) return 3;
    if(!PINC.7) return 10;
    PORTC.0=1; PORTC.1=0; PORTC.2=1; PORTC.3=1;
    if(!PINC.4) return 4;
    if(!PINC.5) return 5;
    if(!PINC.6) return 6;
    if(!PINC.7) return 11;
    PORTC.0=1; PORTC.1=1; PORTC.2=0; PORTC.3=1;
    if(!PINC.4) return 7;
    if(!PINC.5) return 8;
    if(!PINC.6) return 9;
    if(!PINC.7) return 12;
    PORTC.0=1; PORTC.1=1; PORTC.2=1; PORTC.3=0;
    if(!PINC.4) return 15;
    if(!PINC.5) return 0;
    if(!PINC.6) return 14;
    if(!PINC.7) return 13;
    return 16;
}

void show_key(int key)
{    
    if(key==0)  glcd_outtextf("0");
    if(key==1)  glcd_outtextf("1");
    if(key==2)  glcd_outtextf("2");
    if(key==3)  glcd_outtextf("3");
    if(key==4)  glcd_outtextf("4");
    if(key==5)  glcd_outtextf("5");
    if(key==6)  glcd_outtextf("6");
    if(key==7)  glcd_outtextf("7");
    if(key==8)  glcd_outtextf("8");
    if(key==9)  glcd_outtextf("9");
    if(key==10) glcd_outtextf("/");
    if(key==11) glcd_outtextf("*");
    if(key==12) glcd_outtextf("+");
    if(key==13) glcd_outtextf("-");
    if(key==14) glcd_clear(); //=
    if(key==15) glcd_clear();
    delay_ms(150);
}
int perform(int a,int b,int op){
    if(op == 10)
        return a/b;
    else if(op == 11)
        return a*b;
    else if(op == 12)
        return a+b;
    else if(op == 13)
        return a-b;        
}

char a[100];
void print(int x){
    sprintf(a,"%d",x);
    glcd_clear();
    glcd_outtext(a);
    delay_ms(150);
}
int key = 16;
int flag = 0;
int in1 = 0,in2 = 0;
int op = 0;
int res = 0;
int error = 0;

void reset(){
    glcd_clear();
    in1 = 0;
    in2 = 0;
    flag = 0;
    op = 0;
    res = 0;
}

void main(void)
{
config_LCD();
config_PORTS();

while (1)
{      
    
    do{
        key = get_number_from_keboard();  
    } while(key==16);
    if(res > 0){
        res = 0;
        reset();    
    }
    if(error == 1){
        reset();
        error = 0;        
    }
    show_key(key);     
     if(key < 10){        
            if(flag == 0){
                in1 = in1 * 10 + key;                           
            }
            else{
                in2 = in2 * 10 + key;              
            }                                       
     }else {            
            if(flag == 0)
                flag = 1;
            else if(flag == 1 && key < 14){
                glcd_clear();
                glcd_outtextf("Only Two Numbers!");
                error = 1;                                                    
            }
            if(key == 15){
                reset();
            }            
            else if(key != 14){
                op = key;  
            }else{                       
                res = perform(in1,in2,op);
                print(res); 
            }
     }  
     delay_ms(500);       
}                     
    delay_ms(500);
}
