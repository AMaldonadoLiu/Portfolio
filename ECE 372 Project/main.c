
#define HWREG(x) (*((volatile unsigned int *)(x)))

void wait_for_rdy(unsigned int y);
int send_data(unsigned int a,unsigned int b);
void turn_0();
void turn_45();
void turn_neg45();
void turn_90();
void turn_neg90();
void IntMasterIRQEnable();
void int_handler();
void turn_off_leds();
void turn_on_led1();
void turn_on_led2();
void turn_on_led3();
void turn_on_led4();

void timer5_int();
void wait_loop();
void return_from_int();

//GPIO defines
#define GPIO1BA 0x4804C000
#define GPIO_SET_DATA_OUT 0x194
#define GPIO_CLEAR_DATA_OUT 0x190

//INTC defines
#define INTCBA 0x48200000

//Timer 5 defines
#define TIMER5_BA 0x48046000

//other defines
#define CLKWKUPS 0x44E00000
#define LIGHT_BITS 0x01E00000

volatile unsigned int INT_STACK[100];
volatile unsigned int USR_STACK[100];
unsigned int readybit = 0;
unsigned int busybus = 0;
unsigned int maskedbus = 0;
unsigned int setting = 0;
unsigned int current_state = 0;
/**
 * main.c
 */
int main(void)
{

    asm("LDR R13, =USR_STACK");         // Set register 13 = to USR_STACK variables
    asm("ADD R13, R13, #0x100");        // Put 0x100 into R13 for our stack
    //**** init IRQ stack ****
    asm("CPS #0x12");
    asm("LDR R13, =INT_STACK");         // Set register 13 = to USR_STACK variables
    asm("ADD R13, R13, #0x100");      // Put 0x100 into R13 for our stack
    asm("CPS #0x13");                               // Write 0x13 to CPS
    //**** LED INIT ****
    HWREG(CLKWKUPS + 0xAC) = 0x2;               //GPIO1 initialization code
    HWREG(GPIO1BA + GPIO_CLEAR_DATA_OUT) = LIGHT_BITS;  //Set initial GPIO values
    HWREG(GPIO1BA + 0x134) &= 0xFE1FFFFF;                               // set output enable

    //**** TIMER 5 INIT ****
    HWREG(CLKWKUPS + 0xEC) = 0x2;                   //wakeup timer 5
    HWREG(CLKWKUPS + 0x518) = 0x2;              //set clock speed
    HWREG(TIMER5_BA + 0x10) = 0x1;              //software reset
    HWREG(TIMER5_BA + 0x28) = 0x7;              //clear irqs
    HWREG(TIMER5_BA + 0x2C) = 0x2;              //enable overflow IRQ

    //**** INTC INIT ****
    HWREG(INTCBA + 0x10) = 0x2;                     //reset INTC
    HWREG(INTCBA + 0xC8) = 0x20000000;      //unmast INTC_TINT5

    //**** ENABLE IRQ ****
    IntMasterIRQEnable();


    HWREG(0x44E00044) = 0x2;            // turn on clock for i2c
    HWREG(0x44E1097C) = 0x2B;           // setting i2c2_scl mode
    HWREG(0x44E10978) = 0x2B;           // setting i2c2_sda mode

    HWREG(0x4819C0B8) = 0xA;            // set SCLH
    HWREG(0x4819C0B4) = 0x8;            // set SCLL
    HWREG(0x4819C0B0) = 0x3;            // setting the PSC clock
    HWREG(0x4819C0A4) = 0x8600;         // set settings for i2c_con
    HWREG(0x4819C0AC) = 0x40;           // set SA

    send_data(0x00, 0x11);      // send data to turn off
    send_data(0xFE, 0x79);
    send_data(0x00, 0x81);

    HWREG(TIMER5_BA + 0x3C) = 0xFFFFFFFA;   //set timer for 250 ms
    HWREG(TIMER5_BA + 0x38) = 0x1;              //start timer

    wait_loop();

}

void wait_loop(void)
// The wait_loop function is a while loop with nothing in it.
// It is used for the system to wait for an interrupt to take action on.
{
    while(1)
    {
        //do nothing loop
    }
}

void turn_0()
{
    setting++;
    turn_on_led1();
    send_data(0x26, 0x00);     // send data to not have delay

    send_data(0x27, 0x0);     // send data to 0 on motor

    send_data(0x28, 0x33);     // send data to have delay here for 0 degrees

    send_data(0x29, 0x1);      // send data to have delay here for 0 degrees

    HWREG(TIMER5_BA + 0x3C) = 0xFFFF7FFF;   //set timer for 1 s
    HWREG(TIMER5_BA + 0x38) = 0x1;              //start timer
}

void turn_45()
{
    turn_on_led2();
    setting++;
    turn_on_led1();


    send_data(0x26, 0x00);      // send data to not have delay

    send_data(0x27, 0x0);   // send data to full on motor

    send_data(0x28, 0x66);       // send data to have delay here for 45 degrees

    send_data(0x29, 0x1);       // send data to have delay here for 45 degrees

    HWREG(TIMER5_BA + 0x3C) = 0xFFFFBFFF;   //set timer for 0.5 s
    HWREG(TIMER5_BA + 0x38) = 0x1;              //start timer
}

void turn_neg45()
{
    turn_on_led3();
    setting++;
    send_data(0x26, 0x00);      // send data to not have delay

    send_data(0x27, 0x0);      // send data to full on motor

    send_data(0x28, 0x00);      // send data to have delay here for -45 degrees

    send_data(0x29, 0x1);      // send data to have delay here for -45 degrees

    HWREG(TIMER5_BA + 0x3C) = 0xFFFF7FFF;   //set timer for 1 s
    HWREG(TIMER5_BA + 0x38) = 0x1;              //start timer
}

void turn_90()
{
    turn_on_led4();
    setting++;
    send_data(0x26, 0x00);      // send data to not have delay

    send_data(0x27, 0x0);      // send data to full on motor

    send_data(0x28, 0x9A);       // send data to have delay here for 90 degrees

    send_data(0x29, 0x1);       // send data to have delay here for 90 degrees

    HWREG(TIMER5_BA + 0x3C) = 0xFFFFBFFF;   //set timer for 0.5 s
    HWREG(TIMER5_BA + 0x38) = 0x1;              //start timer
}

void turn_neg90()
{
    turn_off_leds();
    setting++;
    send_data(0x26, 0x00);      // send data to not have delay

    send_data(0x27, 0x0);      // send data to full on motor

    send_data(0x28, 0xCD);      // send data to have delay here for -90 degrees

    send_data(0x29, 0x0);       // send data to have delay here for -90 degrees

    HWREG(TIMER5_BA + 0x3C) = 0xFFFF7FFF;   //set timer for 1 s
    HWREG(TIMER5_BA + 0x38) = 0x1;              //start timer
}

void wait_for_rdy(unsigned int y)
{
    maskedbus = 0;

    HWREG(0x4819C09C) = y;
}

int send_data(unsigned int a,unsigned int b)
{
    readybit = 0;
    busybus = HWREG(0x4819C024);
    maskedbus = busybus & 0x1000;
    while(maskedbus == 0x1000)
    {
        busybus = HWREG(0x4819C024);
        maskedbus = busybus & 0x1000;
    }
    HWREG(0x4819C098) = 0x2;

    HWREG(0x4819C0A4) = 0x8603;
    while(readybit != 0x10)
    {
        readybit = HWREG(0x4819C024);
        readybit = readybit & 0x10;
    }
    wait_for_rdy(a);
    for(int i = 0; i < 5000; i++)
    {
        a = b;
    }
    wait_for_rdy(b);

    return 0;
}

void int_handler(void)
{
    if(HWREG(0x482000D8) == 0x20000000 && setting != 26)
    {
        HWREG(TIMER5_BA + 0x28) = 0x7;                  //clear timer5 interrupts
        HWREG(INTCBA + 0x48) = 0x1;                         //clear NEWIRQ bit in INTC
        if(setting%5 == 0)
        {

            turn_0();
        }
        else if(setting%5 == 1)
        {
            turn_45();
        }
        else if(setting%5 == 2)
        {
            turn_neg45();
        }
        else if(setting%5 == 3)
        {
            turn_90();
        }
        else if(setting%5 == 4)
        {
            turn_neg90();
        }

    }

    asm("LDMFD SP!, {LR}");
    asm("LDMFD SP!, {LR}");
    asm("SUBS PC, LR, #0x4");
}


void turn_on_led1(void)
{
    HWREG(GPIO1BA + GPIO_SET_DATA_OUT) = 0x00200000;    //turn on leds
}
void turn_on_led2(void)
{
    HWREG(GPIO1BA + GPIO_SET_DATA_OUT) = 0x00400000;    //turn on leds
}
void turn_on_led3(void)
{
    HWREG(GPIO1BA + GPIO_SET_DATA_OUT) = 0x00800000;    //turn on leds
}
void turn_on_led4(void)
{
    HWREG(GPIO1BA + GPIO_SET_DATA_OUT) = 0x01000000;    //turn on leds
}

void turn_off_leds(void)
{
    HWREG(GPIO1BA + GPIO_CLEAR_DATA_OUT) = LIGHT_BITS;  //turn off leds
}


void IntMasterIRQEnable(void)
{
    asm("   mrs     r0, CPSR\n\t"
        "   bic     r0, r0, #0x80\n\t"
        "   msr     CPSR_c, R0");
}


//
//void timer5_int(void)
//{
//    HWREG(TIMER5_BA + 0x28) = 0x7;                  //clear timer5 interrupts
//    HWREG(INTCBA + 0x48) = 0x1;                         //clear NEWIRQ bit in INTC
//    if(current_state == 1)                                  //toggle current state
//    {
//        current_state = 0;
//        HWREG(TIMER5_BA + 0x3C) = 0xFFFF7FFF;      //set timer for 250 ms
//        HWREG(TIMER5_BA + 0x38) = 0x1;              //start timer
//        turn_off_leds();
//    }
//    else
//    {
//        current_state = 1;
//        HWREG(TIMER5_BA + 0x3C) = 0xFFFF7FFF;   //set timer for 250 ms
//        HWREG(TIMER5_BA + 0x38) = 0x1;              //start timer
//        turn_on_leds();
//
//
//    }       //toggle finished
//
//}
//

