
#include "wmtest.h"
#include "test-util.h"

void IgnoreEvents()
{
   XEvent event;
   while(XPending(display)) {
      XNextEvent(display, &event);
   }
}

void AwaitEvent(int type, XEvent *event)
{
   XEvent temp;
   for(;;) {
      XNextEvent(display, &temp);
      if(temp.type == type) {
         if(event) {
            *event = temp;
         }
         break;
      }
   }
   IgnoreEvents();
}

void ShowEvents()
{
   XEvent event;
   while(XPending(display)) {
      XNextEvent(display, &event);
      printf("event %d\n", event.type);
   }   
}

void Minimize(Window w)
{
   XEvent event;
   event.xclient.type = ClientMessage;
   event.xclient.window = w;
   event.xclient.message_type = XInternAtom(display, "_NET_WM_STATE", False);
   event.xclient.format = 32;
   event.xclient.data.l[0] = 1;  /* Add */
   event.xclient.data.l[1] =
      XInternAtom(display, "_NET_WM_STATE_HIDDEN", False);
   event.xclient.data.l[2] = 0;
   XSendEvent(display, rootWindow, False, SubstructureRedirectMask, &event);
}

void Unminimize(Window w)
{
   XEvent event;
   event.xclient.type = ClientMessage;
   event.xclient.window = w;
   event.xclient.message_type = XInternAtom(display, "_NET_WM_STATE", False);
   event.xclient.format = 32;
   event.xclient.data.l[0] = 0;  /* Remove */
   event.xclient.data.l[1] =
      XInternAtom(display, "_NET_WM_STATE_HIDDEN", False);
   event.xclient.data.l[2] = 0;
   XSendEvent(display, rootWindow, False, SubstructureRedirectMask, &event);
}

void Shade(Window w)
{
   XEvent event;
   event.xclient.type = ClientMessage;
   event.xclient.window = w;
   event.xclient.message_type = XInternAtom(display, "_NET_WM_STATE", False);
   event.xclient.format = 32;
   event.xclient.data.l[0] = 1;  /* Add */
   event.xclient.data.l[1] =
      XInternAtom(display, "_NET_WM_STATE_SHADED", False);
   event.xclient.data.l[2] = 0;
   XSendEvent(display, rootWindow, False, SubstructureRedirectMask, &event);
}

void Unshade(Window w)
{
   XEvent event;
   event.xclient.type = ClientMessage;
   event.xclient.window = w;
   event.xclient.message_type = XInternAtom(display, "_NET_WM_STATE", False);
   event.xclient.format = 32;
   event.xclient.data.l[0] = 0;  /* Remove */
   event.xclient.data.l[1] =
      XInternAtom(display, "_NET_WM_STATE_SHADED", False);
   event.xclient.data.l[2] = 0;
   XSendEvent(display, rootWindow, False, SubstructureRedirectMask, &event);
}

void Maximize(Window w, char vert, char horiz)
{
   XEvent event;
   int i = 1;
   event.xclient.type = ClientMessage;
   event.xclient.window = w;
   event.xclient.message_type = XInternAtom(display, "_NET_WM_STATE", False);
   event.xclient.format = 32;
   event.xclient.data.l[0] = 1;  /* Add */
   event.xclient.data.l[1] = 0;
   event.xclient.data.l[2] = 0;
   if(vert) {
      event.xclient.data.l[i++] =
         XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_VERT", False);
   }
   if(horiz) {
      event.xclient.data.l[i++] =
         XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_HORZ", False);
   }
   XSendEvent(display, rootWindow, False, SubstructureRedirectMask, &event);
}

void Unmaximize(Window w, char vert, char horiz)
{
   XEvent event;
   int i = 1;
   event.xclient.type = ClientMessage;
   event.xclient.window = w;
   event.xclient.message_type = XInternAtom(display, "_NET_WM_STATE", False);
   event.xclient.format = 32;
   event.xclient.data.l[0] = 0;  /* Remove */
   event.xclient.data.l[1] = 0;
   event.xclient.data.l[2] = 0;
   if(vert) {
      event.xclient.data.l[i++] =
         XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_VERT", False);
   }
   if(horiz) {
      event.xclient.data.l[i++] =
         XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_HORZ", False);
   }
   XSendEvent(display, rootWindow, False, SubstructureRedirectMask, &event);
}

