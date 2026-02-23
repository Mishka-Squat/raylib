#ifndef INPUT_SCRIPT_RUNTIME_H
#define INPUT_SCRIPT_RUNTIME_H

void InputScriptRuntimeReset(void);
void InputScriptRuntimeLoadEvents(const InputScriptEvent *events, int count);
void InputScriptRuntimeSetEnabled(bool enabled);
void InputScriptRuntimeSetMode(InputScriptMode mode);
bool InputScriptRuntimeEnabled(void);
InputScriptMode InputScriptRuntimeMode(void);
void InputScriptRuntimeAdvanceFrame(int frame);
bool InputScriptRuntimeIsKeyPressed(int key);
bool InputScriptRuntimeIsKeyDown(int key);
bool InputScriptRuntimeIsKeyReleased(int key);
bool InputScriptRuntimeIsKeyUp(int key);
int InputScriptRuntimeGetKeyDownCount(void);

#endif
