#include <string.h>
#include "menu.h"
#include "settings.h"

#define MENU_SELECTION_PLAYER1 0
#define MENU_SELECTION_PLAYER2 1
#define MENU_SELECTION_PLAYER3 2
#define MENU_SELECTION_PLAYER4 3
#define MENU_SELECTION_MUTATIONS 4
#define MENU_SELECTION_AIRVENTS 5
#define MENU_SELECTION_START 6
#define MENU_SELECTION_BACK 7

s32 menu_selection;

void init_menu()
{
    menu_selection = MENU_SELECTION_PLAYER1;
    init_settings();
}

u32 menu_up()
{
    if (menu_selection == MENU_SELECTION_START || menu_selection == MENU_SELECTION_BACK)
    {
        menu_selection = MENU_SELECTION_AIRVENTS;
        return 1;
    }
    else if (menu_selection > 0)
    {
        menu_selection--;
        return 1;
    }

    return 0;
}

u32 menu_down()
{
    if (menu_selection != MENU_SELECTION_START && menu_selection != MENU_SELECTION_BACK)
    {
        menu_selection++;
        return 1;
    }

    return 0;
}

u32 menu_change(s32 sel, s32 d)
{
    s32 value = 0;

    switch (sel)
    {
    case MENU_SELECTION_PLAYER1:
    case MENU_SELECTION_PLAYER2:
    case MENU_SELECTION_PLAYER3:
    case MENU_SELECTION_PLAYER4:
        change_settings_player(sel, d);
        return 1;

    case MENU_SELECTION_MUTATIONS:
        change_settings_flags(SETTINGS_FLAG_MUTATION_ALL);
        return 1;

    case MENU_SELECTION_AIRVENTS:
        change_settings_flags(SETTINGS_FLAG_AIRVENTS);
        return 1;
    }

    return 0;
}

u32 menu_left()
{
    if (menu_selection == MENU_SELECTION_START)
    {
        menu_selection = MENU_SELECTION_BACK;
        return 1;
    }
    else
    {
        return menu_change(menu_selection, -1);
    }

    return 0;
}

u32 menu_right()
{
    if (menu_selection == MENU_SELECTION_BACK)
    {
        menu_selection = MENU_SELECTION_START;
        return 1;
    }
    else
    {
        return menu_change(menu_selection, +1);
    }

    return 0;
}

s32 menu_action()
{
    switch (menu_selection)
    {
    case MENU_SELECTION_START:
        return 1;

    case MENU_SELECTION_BACK:
        return -1;
    }

    return 0;
}

u32 menu_to_gfx(char text[32][32])
{
    if (menu_selection == MENU_SELECTION_PLAYER1)
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
    strcat(text[1], get_settings_player_string(0));

    if (menu_selection == MENU_SELECTION_PLAYER2)
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
    strcat(text[3], get_settings_player_string(1));

    if (menu_selection == MENU_SELECTION_PLAYER3)
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
    strcat(text[5], get_settings_player_string(2));

    if (menu_selection == MENU_SELECTION_PLAYER4)
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
    strcat(text[7], get_settings_player_string(3));

    if (menu_selection == MENU_SELECTION_MUTATIONS)
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
    strcat(text[9], get_settings_flags_string(SETTINGS_FLAG_MUTATION_ALL));

    if (menu_selection == MENU_SELECTION_AIRVENTS)
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
    strcat(text[11], get_settings_flags_string(SETTINGS_FLAG_AIRVENTS));

    if (menu_selection == MENU_SELECTION_BACK)
    {
        strcpy(text[12], "\x02"
                         "B"
                         "\x03"
                         "a"
                         "\x02"
                         "c"
                         "\x03"
                         "k");
    }
    else
    {
        strcpy(text[12], "\x08"
                         "Back");
    }

    if (menu_selection == MENU_SELECTION_START)
    {
        strcpy(text[13], "\x04"
                         "S"
                         "\x05"
                         "t"
                         "\x04"
                         "a"
                         "\x05"
                         "r"
                         "\x04"
                         "t");
    }
    else
    {
        strcpy(text[13], "\x08Start");
    }

    return menu_selection;
}
