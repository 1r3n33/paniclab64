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

u32 menu_to_gfx(String strings[32])
{
    sb_init(&strings[0]);
    sb_init(&strings[1]);
    sb_init(&strings[2]);
    sb_init(&strings[3]);
    sb_init(&strings[4]);
    sb_init(&strings[5]);
    sb_init(&strings[6]);
    sb_init(&strings[7]);
    sb_init(&strings[8]);
    sb_init(&strings[9]);
    sb_init(&strings[10]);
    sb_init(&strings[11]);
    sb_init(&strings[12]);
    sb_init(&strings[13]);

    if (menu_selection == MENU_SELECTION_PLAYER1)
    {
        sb_color(&strings[0], SB_COLOR_YELLOW);
        sb_color(&strings[1], SB_COLOR_YELLOW);
    }
    else
    {
        sb_color(&strings[0], SB_COLOR_WHITE);
        sb_color(&strings[1], SB_COLOR_WHITE);
    }
    sb_append(&strings[0], "Player 1");
    sb_halign(&strings[0], 0, -40);
    sb_valign(&strings[0], 1, 60);

    sb_append(&strings[1], get_settings_player_string(0));
    sb_halign(&strings[1], 0, 40);
    sb_valign(&strings[1], 1, 60);

    if (menu_selection == MENU_SELECTION_PLAYER2)
    {
        sb_color(&strings[2], SB_COLOR_YELLOW);
        sb_color(&strings[3], SB_COLOR_YELLOW);
    }
    else
    {
        sb_color(&strings[2], SB_COLOR_WHITE);
        sb_color(&strings[3], SB_COLOR_WHITE);
    }
    sb_append(&strings[2], "Player 2");
    sb_halign(&strings[2], 0, -40);
    sb_valign(&strings[2], 1, 80);

    sb_append(&strings[3], get_settings_player_string(1));
    sb_halign(&strings[3], 0, 40);
    sb_valign(&strings[3], 1, 80);

    if (menu_selection == MENU_SELECTION_PLAYER3)
    {
        sb_color(&strings[4], SB_COLOR_YELLOW);
        sb_color(&strings[5], SB_COLOR_YELLOW);
    }
    else
    {
        sb_color(&strings[4], SB_COLOR_WHITE);
        sb_color(&strings[5], SB_COLOR_WHITE);
    }
    sb_append(&strings[4], "Player 3");
    sb_halign(&strings[4], 0, -40);
    sb_valign(&strings[4], 1, 100);

    sb_append(&strings[5], get_settings_player_string(2));
    sb_halign(&strings[5], 0, 40);
    sb_valign(&strings[5], 1, 100);

    if (menu_selection == MENU_SELECTION_PLAYER4)
    {
        sb_color(&strings[6], SB_COLOR_YELLOW);
        sb_color(&strings[7], SB_COLOR_YELLOW);
    }
    else
    {
        sb_color(&strings[6], SB_COLOR_WHITE);
        sb_color(&strings[7], SB_COLOR_WHITE);
    }
    sb_append(&strings[6], "Player 4");
    sb_halign(&strings[6], 0, -40);
    sb_valign(&strings[6], 1, 120);

    sb_append(&strings[7], get_settings_player_string(3));
    sb_halign(&strings[7], 0, 40);
    sb_valign(&strings[7], 1, 120);

    if (menu_selection == MENU_SELECTION_MUTATIONS)
    {
        sb_color(&strings[8], SB_COLOR_YELLOW);
        sb_color(&strings[9], SB_COLOR_YELLOW);
    }
    else
    {
        sb_color(&strings[8], SB_COLOR_WHITE);
        sb_color(&strings[9], SB_COLOR_WHITE);
    }
    sb_append(&strings[8], "Mutations");
    sb_halign(&strings[8], 0, -40);
    sb_valign(&strings[8], 1, 140);

    sb_append(&strings[9], get_settings_flags_string(SETTINGS_FLAG_MUTATION_ALL));
    sb_halign(&strings[9], 0, 40);
    sb_valign(&strings[9], 1, 140);

    if (menu_selection == MENU_SELECTION_AIRVENTS)
    {
        sb_color(&strings[10], SB_COLOR_YELLOW);
        sb_color(&strings[11], SB_COLOR_YELLOW);
    }
    else
    {
        sb_color(&strings[10], SB_COLOR_WHITE);
        sb_color(&strings[11], SB_COLOR_WHITE);
    }
    sb_append(&strings[10], "Air vents");
    sb_halign(&strings[10], 0, -40);
    sb_valign(&strings[10], 1, 160);

    sb_append(&strings[11], get_settings_flags_string(SETTINGS_FLAG_AIRVENTS));
    sb_halign(&strings[11], 0, 40);
    sb_valign(&strings[11], 1, 160);

    if (menu_selection == MENU_SELECTION_BACK)
    {
        sb_color(&strings[12], SB_COLOR_BLUE);
        sb_append(&strings[12], "B");
        sb_color(&strings[12], SB_COLOR_PURPLE);
        sb_append(&strings[12], "a");
        sb_color(&strings[12], SB_COLOR_BLUE);
        sb_append(&strings[12], "c");
        sb_color(&strings[12], SB_COLOR_PURPLE);
        sb_append(&strings[12], "k");
    }
    else
    {
        sb_color(&strings[12], SB_COLOR_WHITE);
        sb_append(&strings[12], "Back");
    }

    sb_valign(&strings[12], -1, 40);
    sb_halign(&strings[12], -1, 40);

    if (menu_selection == MENU_SELECTION_START)
    {
        sb_color(&strings[13], SB_COLOR_ORANGE);
        sb_append(&strings[13], "S");
        sb_color(&strings[13], SB_COLOR_RED);
        sb_append(&strings[13], "t");
        sb_color(&strings[13], SB_COLOR_ORANGE);
        sb_append(&strings[13], "a");
        sb_color(&strings[13], SB_COLOR_RED);
        sb_append(&strings[13], "r");
        sb_color(&strings[13], SB_COLOR_ORANGE);
        sb_append(&strings[13], "t");
    }
    else
    {
        sb_color(&strings[13], SB_COLOR_WHITE);
        sb_append(&strings[13], "Start");
    }

    sb_valign(&strings[13], -1, 40);
    sb_halign(&strings[13], 1, 40);

    return menu_selection;
}
