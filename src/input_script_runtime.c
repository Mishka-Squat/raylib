#include "input_script_runtime.h"

#include <stdlib.h>
#include <string.h>

typedef struct InputScriptRuntimeState {
    InputScriptEvent *events;
    int eventCount;
    int nextEvent;
    bool enabled;
    InputScriptMode mode;
    int currentFrame;

    bool keyDown[MAX_KEYBOARD_KEYS];
    bool keyPressed[MAX_KEYBOARD_KEYS];
    bool keyReleased[MAX_KEYBOARD_KEYS];
} InputScriptRuntimeState;

static InputScriptRuntimeState INPUT_SCRIPT = {
    .events = NULL,
    .eventCount = 0,
    .nextEvent = 0,
    .enabled = false,
    .mode = INPUT_SCRIPT_MODE_MERGE,
    .currentFrame = -1,
};

static bool InputScriptRuntimeIsValidKey(int key)
{
    return ((key > 0) && (key < MAX_KEYBOARD_KEYS));
}

static void InputScriptRuntimeClearFrameState(void)
{
    memset(INPUT_SCRIPT.keyPressed, 0, sizeof(INPUT_SCRIPT.keyPressed));
    memset(INPUT_SCRIPT.keyReleased, 0, sizeof(INPUT_SCRIPT.keyReleased));
}

static int InputScriptRuntimeCompareEvents(const void *left, const void *right)
{
    const InputScriptEvent *a = (const InputScriptEvent *)left;
    const InputScriptEvent *b = (const InputScriptEvent *)right;

    if (a->frame < b->frame) return -1;
    if (a->frame > b->frame) return 1;
    return 0;
}

void InputScriptRuntimeReset(void)
{
    if (INPUT_SCRIPT.events != NULL)
    {
        free(INPUT_SCRIPT.events);
        INPUT_SCRIPT.events = NULL;
    }

    INPUT_SCRIPT.eventCount = 0;
    INPUT_SCRIPT.nextEvent = 0;
    INPUT_SCRIPT.enabled = false;
    INPUT_SCRIPT.mode = INPUT_SCRIPT_MODE_MERGE;
    INPUT_SCRIPT.currentFrame = -1;

    memset(INPUT_SCRIPT.keyDown, 0, sizeof(INPUT_SCRIPT.keyDown));
    InputScriptRuntimeClearFrameState();
}

void InputScriptRuntimeLoadEvents(const InputScriptEvent *events, int count)
{
    if (INPUT_SCRIPT.events != NULL)
    {
        free(INPUT_SCRIPT.events);
        INPUT_SCRIPT.events = NULL;
    }

    INPUT_SCRIPT.eventCount = 0;
    INPUT_SCRIPT.nextEvent = 0;
    INPUT_SCRIPT.currentFrame = -1;
    memset(INPUT_SCRIPT.keyDown, 0, sizeof(INPUT_SCRIPT.keyDown));
    InputScriptRuntimeClearFrameState();

    if ((events == NULL) || (count <= 0)) return;

    INPUT_SCRIPT.events = (InputScriptEvent *)malloc((size_t)count*sizeof(InputScriptEvent));
    if (INPUT_SCRIPT.events == NULL) return;

    memcpy(INPUT_SCRIPT.events, events, (size_t)count*sizeof(InputScriptEvent));
    qsort(INPUT_SCRIPT.events, (size_t)count, sizeof(InputScriptEvent), InputScriptRuntimeCompareEvents);

    INPUT_SCRIPT.eventCount = count;
}

void InputScriptRuntimeSetEnabled(bool enabled)
{
    INPUT_SCRIPT.enabled = enabled;
}

void InputScriptRuntimeSetMode(InputScriptMode mode)
{
    INPUT_SCRIPT.mode = mode;
}

bool InputScriptRuntimeEnabled(void)
{
    return INPUT_SCRIPT.enabled;
}

InputScriptMode InputScriptRuntimeMode(void)
{
    return INPUT_SCRIPT.mode;
}

void InputScriptRuntimeAdvanceFrame(int frame)
{
    if (!INPUT_SCRIPT.enabled || (INPUT_SCRIPT.currentFrame == frame)) return;

    INPUT_SCRIPT.currentFrame = frame;
    InputScriptRuntimeClearFrameState();

    while ((INPUT_SCRIPT.nextEvent < INPUT_SCRIPT.eventCount) && (INPUT_SCRIPT.events[INPUT_SCRIPT.nextEvent].frame == frame))
    {
        InputScriptEvent e = INPUT_SCRIPT.events[INPUT_SCRIPT.nextEvent];

        if (!InputScriptRuntimeIsValidKey(e.key))
        {
            INPUT_SCRIPT.nextEvent++;
            continue;
        }

        switch (e.type)
        {
            case INPUT_SCRIPT_EVENT_KEY_DOWN:
            {
                if (!INPUT_SCRIPT.keyDown[e.key])
                {
                    INPUT_SCRIPT.keyDown[e.key] = true;
                    INPUT_SCRIPT.keyPressed[e.key] = true;
                }
            } break;
            case INPUT_SCRIPT_EVENT_KEY_UP:
            {
                if (INPUT_SCRIPT.keyDown[e.key])
                {
                    INPUT_SCRIPT.keyDown[e.key] = false;
                    INPUT_SCRIPT.keyReleased[e.key] = true;
                }
            } break;
            case INPUT_SCRIPT_EVENT_KEY_PRESS:
            {
                INPUT_SCRIPT.keyPressed[e.key] = true;
            } break;
            default: break;
        }

        INPUT_SCRIPT.nextEvent++;
    }
}

bool InputScriptRuntimeIsKeyPressed(int key)
{
    return InputScriptRuntimeIsValidKey(key) && INPUT_SCRIPT.keyPressed[key];
}

bool InputScriptRuntimeIsKeyDown(int key)
{
    return InputScriptRuntimeIsValidKey(key) && INPUT_SCRIPT.keyDown[key];
}

bool InputScriptRuntimeIsKeyReleased(int key)
{
    return InputScriptRuntimeIsValidKey(key) && INPUT_SCRIPT.keyReleased[key];
}

bool InputScriptRuntimeIsKeyUp(int key)
{
    if (!InputScriptRuntimeIsValidKey(key)) return true;
    return !INPUT_SCRIPT.keyDown[key];
}

int InputScriptRuntimeGetKeyDownCount(void)
{
    int count = 0;

    for (int key = 0; key < MAX_KEYBOARD_KEYS; key++)
    {
        if (INPUT_SCRIPT.keyDown[key]) count++;
    }

    return count;
}
