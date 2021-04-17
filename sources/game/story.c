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
    "Subtitle 6",
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
u32 story_to_gfx(char text[32][32])
{
    if (story_selection == STORY_SELECTION_LEVEL)
    {
        strcpy(text[0], "\x06");
        strcpy(text[1], "\x06");
    }
    else
    {
        strcpy(text[0], "\x08");
        strcpy(text[1], "\x08");
    }
    strcat(text[0], story_title[story_current_level]);
    strcat(text[1], story_subtitle[story_current_level]);

    if (story_selection == STORY_SELECTION_BACK)
    {
        strcpy(text[2], "\x02"
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
        strcpy(text[2], "\x08"
                        "Back");
    }

    if (story_selection == STORY_SELECTION_START)
    {
        strcpy(text[3], "\x04"
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
        strcpy(text[3], "\x08Start");
    }

    return story_selection;
}
