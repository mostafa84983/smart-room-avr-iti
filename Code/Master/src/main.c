#include "../include/STD_TYPES.h"
#include "../include/BIT_MATH.h"
#include "../lib/MCAL/DIO/DIO_interface.h"
#include "../lib/HAL/LCD/LCD_interface.h"
#include "../lib/HAL/KEYPAD/KPD_interface.h"
#include "../lib/MCAL/TWI/TWI_interface.h"
#include "../lib/MCAL/EXIT_EEPROM/EEPROM_interface.h"
#include "../lib/MCAL/UART/UART_interface.h"
#include "main_config.h"
#include <util/delay.h>

#define LED_PORT Port_B
#define LED_BLOCK Pin0
#define LED_OPEN_DOOR Pin1
#define LED_CLOSE_DOOR Pin2

void WaitForKey(u8 *PtrKeyPressed);

int main()
{
    // inti
    TWI_init();
    KPD_VidInit();
    LCD_VidInit();
    UART_VidInit();

    DIO_VidSetPinDirection(LED_PORT, LED_BLOCK, Output);      // Led Block
    DIO_VidSetPinDirection(LED_PORT, LED_OPEN_DOOR, Output);  // Led Open Door
    DIO_VidSetPinDirection(LED_PORT, LED_CLOSE_DOOR, Output); // Led Close Door
    // Clear Leds
    DIO_VidSetPinValue(LED_PORT, LED_BLOCK, PinLow);
    DIO_VidSetPinValue(LED_PORT, LED_OPEN_DOOR, PinLow);
    // Close Door
    DIO_VidSetPinValue(LED_PORT, LED_CLOSE_DOOR, PinHigh);

    u8 Local_u8ShowMenu = MAIN_MENU;       // Menu to be displayed
    u8 Local_u8KeyPressed = NOT_PRESSED;   // Pressed key holder
    u8 Local_u8Response = DEMAND_RESPONSE; // Response from slave
    u8 Local_u8Chooser = ROOM1;            // Peripheral chooser
    u8 Local_u8Tens = 0;                   // Temp value
    u8 Local_u8Ones = 0;                   // Temp value
    u8 Local_u8Temperature = 0;            // Temp holder

    u8 Pass[PASS_SIZE] = {NOT_STORED, NOT_STORED, NOT_STORED, NOT_STORED};
    u8 Entered_Pass[PASS_SIZE] = {NOT_STORED, NOT_STORED, NOT_STORED, NOT_STORED};
    u8 Pass_Match = TRUE;
    u8 Pass_Counter;
    u8 Block_Mode_Flag = FALSE;
    u8 User_Status = 0;
    u8 pass_tries_count = 0;

    // Welcome Screen
    LCD_VidSendString_XY("Welcome To", 0, 3);
    LCD_VidSendString_XY("Smart Home", 1, 3);
    _delay_ms(DEFUALT_DELAY_TIME * 5);
    LCD_VidClearScreen();

    // // Set Pass
    EEPROM_readByte(USER_PASS_STATUS_ADDRESS, &User_Status);
    if (User_Status != PASS_SET)
    {
        LCD_VidSendString_XY("Login To System", 0, 0);
        LCD_VidSendString_XY("For First Time", 1, 0);
        _delay_ms(DEFUALT_DELAY_TIME * 4);
        LCD_VidClearScreen();
        LCD_VidSendString_XY("Set Admin Pass", 0, 0);
        LCD_VidSendString_XY("Admin Pass:", 1, 0);

        Pass_Counter = 0;
        while (Pass_Counter < 4)
        {
            WaitForKey(&Local_u8KeyPressed);
            if (Local_u8KeyPressed >= '0' && Local_u8KeyPressed <= '9')
            {
                Pass[Pass_Counter] = Local_u8KeyPressed;
                LCD_VidSendChar_XY(Local_u8KeyPressed, 1, 11 + Pass_Counter);
                _delay_ms(CHARACTER_PREVIEW_TIME);
                LCD_VidSendChar_XY(PASSWORD_SYMBOL, 1, 11 + Pass_Counter);
                Pass_Counter++;
            }
        }

        EEPROM_WriteBlock(EEPROM_USER_ADDRESS, Pass, 4);
        EEPROM_writeByte(USER_PASS_STATUS_ADDRESS, PASS_SET);
        LCD_VidClearScreen();
        LCD_VidSendString_XY("Pass Saved", 0, 3);
        _delay_ms(DEFUALT_DELAY_TIME * 4);
        LCD_VidClearScreen();
        EEPROM_writeByte(LOGIN_BLOCKED_ADDRESS, FALSE);
    }
    else
    {
        EEPROM_readByte(LOGIN_BLOCKED_ADDRESS, &Block_Mode_Flag);
    }
    /////////////////////////////////////////////////////////////////////////////
    // Login
    while (1)
    {
        if (Block_Mode_Flag == TRUE)
        {
            LCD_VidSendString_XY("Login Blocked", 0, 0);
            LCD_VidSendString_XY("Wait 10 Seconds", 1, 0);
            DIO_VidSetPinValue(Port_B, Pin0, PinHigh);
            _delay_ms(BLOCK_MODE_TIME);
            DIO_VidSetPinValue(Port_B, Pin0, PinLow);
            pass_tries_count = 0;
            Block_Mode_Flag = FALSE;
            EEPROM_writeByte(LOGIN_BLOCKED_ADDRESS, FALSE);
            LCD_VidClearScreen();
        }
        // Get Pass
        Pass_Counter = 0;
        LCD_VidSendString_XY("Enter Password ", 0, 0);
        LCD_VidSendString_XY("____", 1, 0);
        LCD_VidMoveCursor(1, 0);
        while (Pass_Counter < 4)
        {
            WaitForKey(&Local_u8KeyPressed);
            if (Local_u8KeyPressed >= '0' && Local_u8KeyPressed <= '9')
            {
                Entered_Pass[Pass_Counter] = Local_u8KeyPressed;
                LCD_VidSendChar_XY(Local_u8KeyPressed, 1, Pass_Counter);
                _delay_ms(CHARACTER_PREVIEW_TIME);
                LCD_VidSendChar_XY(PASSWORD_SYMBOL, 1, Pass_Counter);
                Pass_Counter++;
            }
        }
        LCD_VidClearScreen();

        // check Pass
        Pass_Match = TRUE;
        for (Pass_Counter = 0; Pass_Counter < PASS_SIZE; Pass_Counter++)
        {
            u8 temp = 0;
            EEPROM_readByte(EEPROM_USER_ADDRESS + Pass_Counter, &temp); // Stored Pass
            if (Entered_Pass[Pass_Counter] != temp)
            {
                Pass_Match = FALSE;
                break;
            }
            else
                continue;
        }
        if (Pass_Match == TRUE)
        {
            LCD_VidSendString_XY("Right Pass!!", 0, 3);
            _delay_ms(DEFUALT_DELAY_TIME * 4);
            LCD_VidClearScreen();
            // Send Order to open door
            LCD_VidSendString_XY("DOOR is OPENING", 0, 0);
            DIO_VidSetPinValue(Port_B, LED_CLOSE_DOOR, PinLow);
            DIO_VidSetPinValue(Port_B, LED_OPEN_DOOR, PinHigh);
            UART_VidSendByte(DOOR_OPEN);
            _delay_ms(DOOR_TIME);
            LCD_VidClearScreen();
            // Send Order to close door
            LCD_VidSendString_XY("DOOR is CLOSING", 0, 0);
            DIO_VidSetPinValue(Port_B, LED_OPEN_DOOR, PinLow);
            DIO_VidSetPinValue(Port_B, LED_CLOSE_DOOR, PinHigh);
            UART_VidSendByte(DOOR_CLOSE);
            _delay_ms(DOOR_TIME);
            LCD_VidClearScreen();

            break;
        }
        else
        {
            pass_tries_count++;
            LCD_VidSendString_XY("Wrong Pass!!", 0, 2);
            LCD_VidSendString_XY("Tries Left:", 1, 0);
            LCD_VidIntegerToString((TRIES_ALLOWED - pass_tries_count));
            _delay_ms(DEFUALT_DELAY_TIME * 4);
            LCD_VidClearScreen();
            if (pass_tries_count >= TRIES_ALLOWED)
            {
                EEPROM_writeByte(LOGIN_BLOCKED_ADDRESS, TRUE);
                Block_Mode_Flag = TRUE;
            }
        }
    }

    while (1)
    {
        switch (Local_u8ShowMenu)
        {
        case MAIN_MENU:
            LCD_VidClearScreen();

            LCD_VidSendString_XY("1.Door    2.Fan", 0, 0);
            LCD_VidSendString_XY("3.Rooms", 1, 4);
            WaitForKey(&Local_u8KeyPressed);

            if (SELECT_DOOR == Local_u8KeyPressed)
            {
                LCD_VidClearScreen();
                LCD_VidSendString("Door");
                _delay_ms(DEFUALT_DELAY_TIME);

                Local_u8ShowMenu = DOOR_MAIN_MENU;
            }

            else if (SELECT_FAN == Local_u8KeyPressed)
            {
                LCD_VidClearScreen();
                LCD_VidSendString("Fan");
                _delay_ms(DEFUALT_DELAY_TIME);

                Local_u8ShowMenu = AUTO_MANUAL_MENU;
                Local_u8Chooser = FAN;
            }

            else if (SELECT_ROOMS == Local_u8KeyPressed)
            {
                LCD_VidClearScreen();
                LCD_VidSendString("Rooms");
                _delay_ms(DEFUALT_DELAY_TIME);

                Local_u8ShowMenu = ROOM_CHOOSER_MENU;
            }
            else
            {
                LCD_VidClearScreen();
                LCD_VidSendString("Wrong Input");
                LCD_VidSendString_XY("Try Again", 1, 0);
                _delay_ms(DEFUALT_DELAY_TIME);
            }

            break;

        case DOOR_MAIN_MENU:
            LCD_VidClearScreen();

            LCD_VidSendString_XY("1.AUTO  2.Manual", 0, 0);
            LCD_VidSendString_XY("0.Return", 1, 3);
            WaitForKey(&Local_u8KeyPressed);

            if (SELECT_AUTO == Local_u8KeyPressed)
            {
                LCD_VidClearScreen();
                LCD_VidSendString("AUTO");
                _delay_ms(DEFUALT_DELAY_TIME);
                DIO_VidSetPinValue(Port_B, LED_CLOSE_DOOR, PinLow);
                DIO_VidSetPinValue(Port_B, LED_OPEN_DOOR, PinHigh);
                // _delay_ms(DOOR_TIME);
                UART_VidSendByte(DOOR_SET_AUTO);
                _delay_ms(DOOR_TIME * 2);
                DIO_VidSetPinValue(Port_B, LED_CLOSE_DOOR, PinHigh);
                DIO_VidSetPinValue(Port_B, LED_OPEN_DOOR, PinLow);
            }
            else if (SELECT_MANUAL == Local_u8KeyPressed)
            {
                LCD_VidClearScreen();
                LCD_VidSendString("Manual");
                _delay_ms(DEFUALT_DELAY_TIME);
                Local_u8ShowMenu = DOOR_MANUAL_MENU;
            }
            else if (SELECT_RETURN == Local_u8KeyPressed)
            {
                LCD_VidClearScreen();
                LCD_VidSendString("Return");
                _delay_ms(DEFUALT_DELAY_TIME);

                Local_u8ShowMenu = MAIN_MENU;
            }
            else
            {
                LCD_VidClearScreen();
                LCD_VidSendString("Wrong Input");
                LCD_VidSendString_XY("Try Again", 1, 0);
                _delay_ms(DEFUALT_DELAY_TIME);
            }

            break;

        case DOOR_MANUAL_MENU:
            LCD_VidClearScreen();

            LCD_VidSendString("Door S: ");

            UART_VidSendByte(DOOR_STATUS);
            Local_u8Response = UART_u8ReceiveData();

            if (OPEN_STATUS == Local_u8Response)
                LCD_VidSendString("Open");
            else if (CLOSED_STATUS == Local_u8Response)
                LCD_VidSendString("Closed");
            else
                LCD_VidSendString("ERROR");

            LCD_VidSendString_XY("1.Open   2.Close", 1, 0);
            WaitForKey(&Local_u8KeyPressed);

            if (SELECT_OPEN == Local_u8KeyPressed)
            {
                LCD_VidClearScreen();
                LCD_VidSendString("Open");
                _delay_ms(DEFUALT_DELAY_TIME);

                UART_VidSendByte(DOOR_OPEN);

                LCD_VidSendString_XY("DOOR is OPENING", 0, 0);
                _delay_ms(DOOR_TIME);
                DIO_VidSetPinValue(Port_B, LED_CLOSE_DOOR, PinLow);
                DIO_VidSetPinValue(Port_B, LED_OPEN_DOOR, PinHigh);
            }
            else if (SELECT_CLOSE == Local_u8KeyPressed)
            {
                LCD_VidClearScreen();
                LCD_VidSendString("Close");
                _delay_ms(DEFUALT_DELAY_TIME);

                Local_u8ShowMenu = DOOR_MANUAL_MENU;

                UART_VidSendByte(DOOR_CLOSE);

                LCD_VidSendString_XY("DOOR is CLOSING", 0, 0);
                _delay_ms(DOOR_TIME);
                DIO_VidSetPinValue(Port_B, LED_OPEN_DOOR, PinLow);
                DIO_VidSetPinValue(Port_B, LED_CLOSE_DOOR, PinHigh);
            }
            else if (SELECT_RETURN == Local_u8KeyPressed)
            {
                LCD_VidClearScreen();
                LCD_VidSendString("Return");
                _delay_ms(DEFUALT_DELAY_TIME);

                Local_u8ShowMenu = DOOR_MAIN_MENU;
            }
            else
            {
                LCD_VidClearScreen();
                LCD_VidSendString("Wrong Input");
                LCD_VidSendString_XY("Try Again", 1, 0);
                _delay_ms(DEFUALT_DELAY_TIME);
            }

            break;

        case FAN_AUTO_MENU:
            LCD_VidSendString_XY("Set Temperature", 0, 0);
            LCD_VidSendString_XY("__", 1, 0);
            LCD_VidMoveCursor(1, 0);

            WaitForKey(&Local_u8KeyPressed);
            LCD_VidSendChar(Local_u8KeyPressed);
            Local_u8Tens = Local_u8KeyPressed - ASCII_ZERO;

            WaitForKey(&Local_u8KeyPressed);
            LCD_VidSendChar(Local_u8KeyPressed);
            Local_u8Ones = Local_u8KeyPressed - ASCII_ZERO;

            Local_u8Temperature = Local_u8Tens * 10 + Local_u8Ones;

            LCD_VidClearScreen();
            LCD_VidSendString("Temp Set to: ");
            LCD_VidIntegerToString(Local_u8Temperature);
            _delay_ms(DEFUALT_DELAY_TIME * 4);

            UART_VidSendByte(SET_TEMPERATURE);
            UART_VidSendByte(Local_u8Temperature);

            Local_u8ShowMenu = AUTO_MANUAL_MENU;

            break;

        case ROOM_CHOOSER_MENU:
            LCD_VidClearScreen();

            LCD_VidSendString_XY("1.Room1  2.Room2", 0, 0);
            LCD_VidSendString_XY("3.Room3  4.Room4", 1, 0);
            WaitForKey(&Local_u8KeyPressed);

            if (SELECT_RETURN == Local_u8KeyPressed)
            {
                LCD_VidClearScreen();
                LCD_VidSendString("Return");
                _delay_ms(DEFUALT_DELAY_TIME);

                Local_u8ShowMenu = MAIN_MENU;
            }
            else if (Local_u8KeyPressed >= SELECT_ROOM1 && Local_u8KeyPressed <= SELECT_ROOM4)
            {
                LCD_VidClearScreen();
                LCD_VidSendString("Room");
                LCD_VidSendChar(Local_u8KeyPressed);
                _delay_ms(DEFUALT_DELAY_TIME);

                Local_u8Chooser = Local_u8KeyPressed - SELECT_ROOM1;
                Local_u8ShowMenu = AUTO_MANUAL_MENU;
            }
            else
            {
                LCD_VidClearScreen();
                LCD_VidSendString("Wrong Input");
                LCD_VidSendString_XY("Try Again", 1, 0);
                _delay_ms(DEFUALT_DELAY_TIME);
            }

            break;

        case AUTO_MANUAL_MENU:
            LCD_VidClearScreen();

            LCD_VidSendString_XY("1.AUTO  2.Manual", 0, 0);
            LCD_VidSendString_XY("0.Return", 1, 3);
            WaitForKey(&Local_u8KeyPressed);

            if (SELECT_AUTO == Local_u8KeyPressed)
            {
                LCD_VidClearScreen();
                LCD_VidSendString("AUTO");
                _delay_ms(DEFUALT_DELAY_TIME);

                if (Local_u8Chooser == FAN)
                    Local_u8ShowMenu = FAN_AUTO_MENU;
                else
                    UART_VidSendByte(ROOM1_SET_AUTO + Local_u8Chooser);
            }
            else if (SELECT_MANUAL == Local_u8KeyPressed)
            {
                LCD_VidClearScreen();
                LCD_VidSendString("Manual");
                _delay_ms(DEFUALT_DELAY_TIME);
                Local_u8ShowMenu = MANUAL_MENU;
            }
            else if (SELECT_RETURN == Local_u8KeyPressed)
            {
                LCD_VidClearScreen();
                LCD_VidSendString("Return");
                _delay_ms(DEFUALT_DELAY_TIME);

                if (Local_u8Chooser == FAN)
                    Local_u8ShowMenu = MAIN_MENU;
                else
                    Local_u8ShowMenu = ROOM_CHOOSER_MENU;
            }
            else
            {
                LCD_VidClearScreen();
                LCD_VidSendString("Wrong Input");
                LCD_VidSendString_XY("Try Again", 1, 0);
                _delay_ms(DEFUALT_DELAY_TIME);
            }

            break;

        case MANUAL_MENU:
            LCD_VidClearScreen();
            if (Local_u8Chooser == FAN)
            {
                LCD_VidSendString("Fan");
            }
            else
            {
                LCD_VidSendString("Room");
                LCD_VidIntegerToString(Local_u8Chooser + 1);
            }
            LCD_VidSendString(" S: ");

            UART_VidSendByte(ROOM1_STATUS + Local_u8Chooser);
            Local_u8Response = UART_u8ReceiveData();

            if (ON_STATUS == Local_u8Response)
                LCD_VidSendString("On");
            else if (OFF_STATUS == Local_u8Response)
                LCD_VidSendString("Off");
            else
                LCD_VidSendString("ERROR");

            LCD_VidSendString_XY("1.On   2.Off", 1, 0);
            WaitForKey(&Local_u8KeyPressed);

            if (SELECT_ON == Local_u8KeyPressed)
            {
                LCD_VidClearScreen();
                LCD_VidSendString("On");
                UART_VidSendByte(ROOM1_TURN_ON + Local_u8Chooser);

                _delay_ms(DEFUALT_DELAY_TIME);
            }
            else if (SELECT_OFF == Local_u8KeyPressed)
            {
                LCD_VidClearScreen();
                LCD_VidSendString("Off");
                UART_VidSendByte(ROOM1_TURN_OFF + Local_u8Chooser);

                _delay_ms(DEFUALT_DELAY_TIME);
            }
            else if (SELECT_RETURN == Local_u8KeyPressed)
            {
                LCD_VidClearScreen();
                LCD_VidSendString("Return");
                _delay_ms(DEFUALT_DELAY_TIME);

                Local_u8ShowMenu = AUTO_MANUAL_MENU;
            }
            else
            {
                LCD_VidClearScreen();
                LCD_VidSendString("Wrong Input");
                LCD_VidSendString_XY("Try Again", 1, 0);
                _delay_ms(DEFUALT_DELAY_TIME);
            }

            break;
        default:
            LCD_VidClearScreen();
            LCD_VidSendString("Wrong Input");
            LCD_VidSendString_XY("Try Again", 1, 0);
            _delay_ms(DEFUALT_DELAY_TIME);
            Local_u8ShowMenu = MAIN_MENU;
            break;
        }
    }
}

void WaitForKey(u8 *PtrKeyPressed)
{
    u8 Local_u8KeyPressed = NOT_PRESSED;

    while (Local_u8KeyPressed == NOT_PRESSED) // repeat till the user press any key
    {
        Local_u8KeyPressed = Kpd_U8GetPressedKey(); // if the user pressed any button in keypad save the value in Local_u8KeyPressed
    }

    *PtrKeyPressed = Local_u8KeyPressed;
}
