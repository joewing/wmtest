
#ifndef TEST_UTIL_H
#define TEST_UTIL_H

void IgnoreEvents();
void AwaitEvent(int type, XEvent *event);
void ShowEvents();

void Minimize(Window w);
void Unminimize(Window w);
void Shade(Window w);
void Unshade(Window w);
void Maximize(Window w, char vert, char horiz);
void Unmaximize(Window w, char vert, char horiz);

#endif
