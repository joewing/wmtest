
#ifndef TEST_UTIL_H
#define TEST_UTIL_H

#include <stdio.h>

void IgnoreEvents();
char AwaitEvent(int type);
char AwaitEvent2(int type, XEvent *event);
void ShowEvents();

void Minimize(Window w);
void Unminimize(Window w);
void Shade(Window w);
void Unshade(Window w);
void Maximize(Window w, char vert, char horiz);
void Unmaximize(Window w, char vert, char horiz);
long GetCardinal(Window w, Atom atom);
void SetCardinal(Window w, Atom atom, long value);
int GetDesktop(Window w);
void SetDesktop(Window w, int desktop);

int GetCurrentDesktop();
void SetCurrentDesktop(int desktop);

#endif
