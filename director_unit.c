#include<reg51.h>
#include<string.h>
#define lcdport P2
// Defining specific pins of the ports
sbit rs = P1^0;	   
sbit rw = P1^1;
sbit en = P1^2;
			  
//sbit zig_veh_rx = P3^0;

void delay(int time){           //When time = 1, delay = 5m
	int i,j;
	for(i=0;i<time;i++)
		for(j=0;j<1275;j++);
}
//setting up LCD

void cmd()	//0010
{
rs = 0;
rw = 0;
en = 1;
delay(5);
en = 0;
}

void dataen()  //1010
{
rs = 1; 
rw = 0;
en = 1; 
delay(5);
en = 0;
}
/*
void lcddataint(int a){
lcdport = a;
dataen();
}*/

void lcdstring(char *ptr){  //Prints a string on the LCD
	while(*ptr){
		 lcdport = *ptr;
		 dataen();
		 ptr++;
	}
}

void lcdcmd(char c)		 //Directly write a command into LCD
{
	lcdport = c;
	cmd();	

}
void lcdinit()			//Initialize LCD
{  
	lcdcmd(0x38);
	lcdcmd(0x0e);
	lcdcmd(0x80);
}

//Serial communication
void serial_setup()	   {
 IE= 0x90;			   //EnableInterrupt bit=1, EnableSerialIntBit=1//10010000
 SCON = 0x50;		  //SM1=1,REN=1//01010000
 TMOD = 0x20;	      //Timer1 mode1 for serial communication
 TH1 = -3;			  //baud rate=9600
 TR1=1;				   //Start Timer 1
}	
 
void lcddata(char c){	 //Directly write a data character into LCD{
	lcdport = c;
	dataen();	

}
void disp_num(int numb)            //displays number on LCD
{	
	unsigned char UnitDigit  = 0;  //It will contain unit digit of numb
	unsigned char TenthDigit = 0;  //It will contain 10th position digit of numb
	unsigned char HundredthDigit = 0;
	if(numb<0){
		numb = -1*numb;  // Make number positive
		lcddata('-');	 // Display a negative sign on LCD
	}
	 
	 HundredthDigit = (numb/100);
	 
	 if(HundredthDigit != 0)	          // If it is zero, then don't display
		lcddata(HundredthDigit+0x30);
	
	
	TenthDigit = (numb -  HundredthDigit*100)/10;	          // Findout Tenth Digit

	if(TenthDigit != 0)	         // If it is zero, then don't display
	//	lcdstring("Not zero");
		lcddata(TenthDigit+0x30);	  // Make Char of TenthDigit and then display it on LCD

	UnitDigit = numb - HundredthDigit*100 - TenthDigit*10;

	lcddata(UnitDigit+0x30);	  // Make Char of UnitDigit and then display it on LCD
}	
/* Serial Interrupt service routine 
 * The other zigbee will either send a 1 or a zero
 * Receive data completely at SBUF
 */
 
 int num = 30;
 int balance_one = 1000;
 int balance_three = 100;
 int balance=0;
 int min = 30;
 void txstring(char *str)
{				  
	while(*str)
	{
		SBUF = *str;
		while(TI==0);
		TI=0;
		str++;
	}
}
void rx_isr() interrupt 4{	   //Serial Interrupt service routine  

	while(RI==0);					//recieve completely
	if(RI)
	//show on lcd
	if(SBUF == '1'){
		balance_one = balance_one - num;  // Balance
		balance = balance_one; 												  
	}
		else if(SBUF == '3'){
			balance_three = 	balance_three-num;
			balance = balance_three;
		}
			lcdcmd(0x80);
			lcdstring("Avl bal: ");
			disp_num(balance);
			lcdstring(" INR  ");
			lcdcmd(0xc0);
		if(balance>min){
			lcdstring("Take tag  lane");
			SBUF = '1';			   	//load 1 into sbuf
		}else {
		   lcdstring("Take cash lane");
		   SBUF = '2';
		}
			while(TI == 0);
			TI = 0;						//transmit complete
			RI=0;						//rcv next only when current process is complete
}

void main(){
	lcdinit();
	lcdstring("welcome!");
	lcdcmd(0xc0);
	serial_setup();
	while(1);
}	
