#include <string.h>
#include "menu.h"

#define MENU_SELECTION_PLAYER1 0
#define MENU_SELECTION_PLAYER2 1
#define MENU_SELECTION_PLAYER3 2
#define MENU_SELECTION_PLAYER4 3
#define MENU_SELECTION_MUTATIONS 4
#define MENU_SELECTION_AIRVENTS 5
#define MENU_SELECTION_START 6
#define MENU_SELECTION_BACK 7

#define MENU_PLAYER_OFF 0
#define MENU_PLAYER_ON 1
#define MENU_PLAYER_AI 2

#define MENU_FLAG_MUTATIONS 0x01
#define MENU_FLAG_AIRVENTS 0x02

typedef struct
{
    u32 players[NU_CONT_MAXCONTROLLERS];
    u32 flags;
} Settings;

Settings settings;

s32 selection;

void init_menu()
{
    selection = MENU_SELECTION_PLAYER1;
    settings.players[0] = MENU_PLAYER_ON;
    settings.players[1] = MENU_PLAYER_ON;
    settings.players[2] = MENU_PLAYER_OFF;
    settings.players[3] = MENU_PLAYER_OFF;
    settings.flags = MENU_FLAG_MUTATIONS | MENU_FLAG_AIRVENTS;
}

void menu_up()
{
    if (selection == MENU_SELECTION_START || selection == MENU_SELECTION_BACK)
    {
        selection = MENU_SELECTION_AIRVENTS;
    }
    else if (selection > 0)
    {
        selection--;
    }
}

void menu_down()
{
    if (selection != MENU_SELECTION_START && selection != MENU_SELECTION_BACK)
    {
        selection++;
    }
}

void menu_change(s32 sel, s32 d)
{
    s32 value = 0;

    switch (sel)
    {
    case MENU_SELECTION_PLAYER1:
    case MENU_SELECTION_PLAYER2:
    case MENU_SELECTION_PLAYER3:
    case MENU_SELECTION_PLAYER4:
        value = (s32)settings.players[sel] + d;
        if (value > MENU_PLAYER_AI)
            value = MENU_PLAYER_OFF;
        else if (value < 0)
            value = MENU_PLAYER_AI;
        settings.players[sel] = value;
        break;

    case MENU_SELECTION_MUTATIONS:
        settings.flags ^= MENU_FLAG_MUTATIONS;
        break;

    case MENU_SELECTION_AIRVENTS:
        settings.flags ^= MENU_FLAG_AIRVENTS;
        break;
    }
}

void menu_left()
{
    if (selection == MENU_SELECTION_START)
    {
        selection = MENU_SELECTION_BACK;
    }
    else
    {
        menu_change(selection, -1);
    }
}

void menu_right()
{
    if (selection == MENU_SELECTION_BACK)
    {
        selection = MENU_SELECTION_START;
    }
    else
    {
        menu_change(selection, +1);
    }
}

s32 menu_action()
{
    switch (selection)
    {
    case MENU_SELECTION_START:
        return 1;

    case MENU_SELECTION_BACK:
        return -1;
    }

    return 0;
}

char *get_player_value_string(u32 value)
{
    switch (value)
    {
    case MENU_PLAYER_OFF:
        return "Off";

    case MENU_PLAYER_ON:
        return "On";

    case MENU_PLAYER_AI:
        return "AI";
    }
}

char *get_flags_value_string(u32 value)
{
    if (value)
    {
        return "On";
    }
    else
    {
        return "Off";
    }
}

void menu_to_gfx(char text[32][32])
{
    if (selection == MENU_SELECTION_PLAYER1)
    {
        strcpy(text[0], "\x06");
        strcpy(text[1], "\x06");
    }
    else
    {
        strcpy(text[0], "\x08");
        strcpy(text[1], "\x08");
    }
    strcat(text[0], "Player 1");
    strcat(text[1], get_player_value_string(settings.players[0]));

    if (selection == MENU_SELECTION_PLAYER2)
    {
        strcpy(text[2], "\x06");
        strcpy(text[3], "\x06");
    }
    else
    {
        strcpy(text[2], "\x08");
        strcpy(text[3], "\x08");
    }
    strcat(text[2], "Player 2");
    strcat(text[3], get_player_value_string(settings.players[1]));

    if (selection == MENU_SELECTION_PLAYER3)
    {
        strcpy(text[4], "\x06");
        strcpy(text[5], "\x06");
    }
    else
    {
        strcpy(text[4], "\x08");
        strcpy(text[5], "\x08");
    }
    strcat(text[4], "Player 3");
    strcat(text[5], get_player_value_string(settings.players[2]));

    if (selection == MENU_SELECTION_PLAYER4)
    {
        strcpy(text[6], "\x06");
        strcpy(text[7], "\x06");
    }
    else
    {
        strcpy(text[6], "\x08");
        strcpy(text[7], "\x08");
    }
    strcat(text[6], "Player 4");
    strcat(text[7], get_player_value_string(settings.players[3]));

    if (selection == MENU_SELECTION_MUTATIONS)
    {
        strcpy(text[8], "\x06");
        strcpy(text[9], "\x06");
    }
    else
    {
        strcpy(text[8], "\x08");
        strcpy(text[9], "\x08");
    }
    strcat(text[8], "Mutations");
    strcat(text[9], get_flags_value_string(settings.flags & MENU_FLAG_MUTATIONS));

    if (selection == MENU_SELECTION_AIRVENTS)
    {
        strcpy(text[10], "\x06");
        strcpy(text[11], "\x06");
    }
    else
    {
        strcpy(text[10], "\x08");
        strcpy(text[11], "\x08");
    }
    strcat(text[10], "Air vents");
    strcat(text[11], get_flags_value_string(settings.flags & MENU_FLAG_AIRVENTS));

    if (selection == MENU_SELECTION_BACK)
    {
        strcpy(text[12], "\x02""B""\x03""a""\x02""c""\x03""k");
    }
    else
    {
        strcpy(text[12], "\x08""Back");
    }

    if (selection == MENU_SELECTION_START)
    {
        strcpy(text[13], "\x04""S""\x05""t""\x04""a""\x05""r""\x04""t");
    }
    else
    {
        strcpy(text[13], "\x08Start");
    }
}
