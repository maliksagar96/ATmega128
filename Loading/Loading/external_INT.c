#include "external_INT.h"
void setInterrupt(int interruptNum,int edgemode) {
		/* interrupt 0,1,2,3 can call only rising and falling edge...interrupt 4,5,6,7 can trigger rising,falling.level change.
void setInterrupt(int ,int );
*/
	
	switch(interruptNum) {
		case 0:
				EIMSK |= (1<<INT0);
				switch(edgemode) {
					case 0:				
					EICRA |= (1<<ISC00)|(1<<ISC01);  //rising edge ,interrupt 0
					break;
					case 1:
					EICRA |= (1<<ISC01);           //falling edge, interrupt 0
					EICRA &= ~(1<<ISC00);
					break;
					}
					break;
		case 1:
				EIMSK |= (1<<INT0);
				switch(edgemode) {
					case 0:
					EICRA |= (1<<ISC10)|(1<<ISC11);  //rising edge, interrupt 1
					break;
							
					case 1:
					EICRA |= (1<<ISC11);           //falling edge, interrupt 1
					EICRA &= ~(1<<ISC10);
					break;
					}
					break;
		case 2:
				EIMSK |= (1<<INT2);
				switch(edgemode){
					case 0:
					EICRA |= (1<<ISC20)|(1<<ISC21);  //rising edge, interrupt 2
					break;
					case 1:
					EICRA |= (1<<ISC21);           //falling edge, interrupt 2
					EICRA &= ~(1<<ISC20);
					break;
					}
				break;
		case 3:
				EIMSK |= (1<<INT3);
				switch(edgemode){
					case 0:
					EICRA |= (1<<ISC30)|(1<<ISC31);  //rising edge, interrupt 3
					break;
					case 1:
					EICRA |= (1<<ISC31);           //falling edge, interrupt 3
					EICRA &= ~(1<<ISC30);
					break;
					}
				break;
		case 4:
				EIMSK |= (1<<INT4);
				switch(edgemode){
					case 0: 
					EICRA |= (1<<ISC40)|(1<<ISC41);  //rising edge, interrupt 4
					break;
					case 1:
					EICRA |= (1<<ISC41);           //falling edge, interrupt 4
					EICRA &= ~(1<<ISC40);
					break;
					case 2:
					EICRA |= (1<<ISC40);           //any level change edge, interrupt 4
					EICRA &= ~(1<<ISC41);	
					break;
				}
				break;
		case 5:
				EIMSK |= (1<<INT5);
				switch(edgemode){
					case 0:
					EICRA |= (1<<ISC50)|(1<<ISC51);  //rising edge, interrupt 5
					break;
					case 1:
					EICRA |= (1<<ISC51);           //falling edge, interrupt 5
					EICRA &= ~(1<<ISC50);
					break;
					case 2:
					EICRA |= (1<<ISC50);           //any level change edge, interrupt 5
					EICRA &= ~(1<<ISC51);	
					break;
				}
				break;
		case 6:
				EIMSK |= (1<<INT6);
				
				switch(edgemode){
					case 0:
					EICRA |= (1<<ISC60)|(1<<ISC61);  //rising edge, interrupt 6
					break;
					case 1:
					EICRA |= (1<<ISC61);           //falling edge, interrupt 6
					EICRA &= ~(1<<ISC60);
					break;
					case 2:
					EICRA |= (1<<ISC60);           //any level change edge, interrupt 6
					EICRA &= ~(1<<ISC61);
					break;
				}
				break;
		case 7:
				EIMSK |= (1<<INT7);
				switch(edgemode){
					case 0:
					EICRA |= (1<<ISC70)|(1<<ISC71);  //rising edge, interrupt 6
					break;
					case 1:
					EICRA |= (1<<ISC71);           //falling edge, interrupt 6
					EICRA &= ~(1<<ISC70);
					break;
					case 2:
					EICRA |= (1<<ISC70);           //any level change edge, interrupt 6
					EICRA &= ~(1<<ISC71);
					break;
				}
				break;	
	}
}

