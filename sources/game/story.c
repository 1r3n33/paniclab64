#include <string.h>
#include "story.h"

#define STORY_SELECTION_LEVEL 0
#define STORY_SELECTION_START 1
#define STORY_SELECTION_BACK 2

#define STORY_LEVEL_COUNT 8

u32 story_selection = 0;
u32 story_current_level = 0;
u32 story_level_count = 0;

char *story_title[STORY_LEVEL_COUNT] = {
    "Room 1",
    "Room 2",
    "Room 3",
    "Room 4",
    "Room 5",
    "Room 6",
    "Room 7",
    "Room 8",
};

char *story_subtitle[STORY_LEVEL_COUNT] = {
    "Meet Squiddy",
    "Introducing Sluggy",
    "Beware Of Mutations",
    "Even More Mutations",
    "Hide And Seek",
    "AI Battle Mode",
    "Subtitle 7",
    "Subtitle 8",
};

void story_init()
{
    story_selection = STORY_SELECTION_START;
    story_current_level = 0;
    story_level_count = STORY_LEVEL_COUNT;
}

u32 story_up()
{
    switch (story_selection)
    {
    case STORY_SELECTION_START:
        story_selection = STORY_SELECTION_LEVEL;
        return 1;

    case STORY_SELECTION_BACK:
        story_selection = STORY_SELECTION_LEVEL;
        return 1;
    }

    return 0;
}

u32 story_down()
{
    switch (story_selection)
    {
    case STORY_SELECTION_LEVEL:
        story_selection = STORY_SELECTION_START;
        return 1;
    }

    return 0;
}

u32 story_left()
{
    switch (story_selection)
    {
    case STORY_SELECTION_LEVEL:
        if (story_current_level > 0)
        {
            story_current_level--;
            return 1;
        }
        else
        {
            return 0;
        }

    case STORY_SELECTION_START:
        story_selection = STORY_SELECTION_BACK;
        return 1;
    }

    return 0;
}

u32 story_right()
{
    switch (story_selection)
    {
    case STORY_SELECTION_LEVEL:
        if (story_current_level < story_level_count - 1)
        {
            story_current_level++;
            return 1;
        }
        else
        {
            return 0;
        }

    case STORY_SELECTION_BACK:
        story_selection = STORY_SELECTION_START;
        return 1;
    }

    return 0;
}

// Return -1 if selection is BACK
// Return +1 if selection is START/RESUME
// else return 0
s32 story_action()
{
    switch (story_selection)
    {
    case STORY_SELECTION_START:
        return 1;

    case STORY_SELECTION_BACK:
        return -1;
    }

    return 0;
}

// Map to graphics data
u32 story_to_gfx(String strings[32])
{
    sb_init(&strings[0]);
    sb_init(&strings[1]);
    sb_init(&strings[2]);
    sb_init(&strings[3]);

    if (story_selection == STORY_SELECTION_LEVEL)
    {
        sb_color(&strings[0], SB_COLOR_YELLOW);
        sb_color(&strings[1], SB_COLOR_YELLOW);
    }
    else
    {
        sb_color(&strings[0], SB_COLOR_WHITE);
        sb_color(&strings[1], SB_COLOR_WHITE);
    }

    sb_append(&strings[0], story_title[story_current_level]);
    sb_append(&strings[1], story_subtitle[story_current_level]);

    sb_valign(&strings[0], 1, 40);
    sb_halign(&strings[0], 0, 0);

    sb_valign(&strings[1], 1, 60);
    sb_halign(&strings[1], 0, 0);

    if (story_selection == STORY_SELECTION_BACK)
    {
        sb_color(&strings[2], SB_COLOR_BLUE);
        sb_append(&strings[2], "B");
        sb_color(&strings[2], SB_COLOR_PURPLE);
        sb_append(&strings[2], "a");
        sb_color(&strings[2], SB_COLOR_BLUE);
        sb_append(&strings[2], "c");
        sb_color(&strings[2], SB_COLOR_PURPLE);
        sb_append(&strings[2], "k");
    }
    else
    {
        sb_color(&strings[2], SB_COLOR_WHITE);
        sb_append(&strings[2], "Back");
    }

    sb_valign(&strings[2], -1, 40);
    sb_halign(&strings[2], -1, 40);

    if (story_selection == STORY_SELECTION_START)
    {
        sb_color(&strings[3], SB_COLOR_ORANGE);
        sb_append(&strings[3], "S");
        sb_color(&strings[3], SB_COLOR_RED);
        sb_append(&strings[3], "t");
        sb_color(&strings[3], SB_COLOR_ORANGE);
        sb_append(&strings[3], "a");
        sb_color(&strings[3], SB_COLOR_RED);
        sb_append(&strings[3], "r");
        sb_color(&strings[3], SB_COLOR_ORANGE);
        sb_append(&strings[3], "t");
    }
    else
    {
        sb_color(&strings[3], SB_COLOR_WHITE);
        sb_append(&strings[3], "Start");
    }

    sb_valign(&strings[3], -1, 40);
    sb_halign(&strings[3], 1, 40);

    return story_selection;
}

u32 story_get_current_level()
{
    return story_current_level;
}
