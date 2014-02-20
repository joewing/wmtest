
#include "wmtest.h"
#include "test-util.h"

#include <sys/time.h>

void IgnoreEvents()
{
   XEvent event;
   while(XPending(display)) {
      XNextEvent(display, &event);
   }
}

char AwaitEvent(int type)
{
   return AwaitEvent2(type, NULL);
}

char AwaitEvent2(int type, XEvent *event)
{
   XEvent temp;
   struct timeval timeout;
   fd_set fds;
   int fd;

   fd = ConnectionNumber(display);
   for(;;) {
      while(XPending(display) == 0) {
         FD_ZERO(&fds);
         FD_SET(fd, &fds);
         timeout.tv_sec = 5;
         timeout.tv_usec = 0;
         if(select(fd + 1, &fds, NULL, NULL, &timeout) <= 0) {
            return 0;
         }
      }
      XNextEvent(display, &temp);
      if(temp.type == type) {
         if(event) {
            *event = temp;
         }
         break;
      }
   }
   IgnoreEvents();
   return 1;
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

long GetCardinal(Window w, Atom atom)
{
   unsigned long count;
   unsigned long extra;
   Atom realType;
   int realFormat;  
   unsigned char *data;
   long result = 0;
   XGetWindowProperty(display, w, atom, 0, 32, False, XA_CARDINAL,
                      &realType, &realFormat, &count, &extra, &data);
   result = *(long*)data;
   XFree(data);
   return result;
}

void SetCardinal(Window w, Atom atom, long value)
{
   XChangeProperty(display, w, atom, XA_CARDINAL, 32,
                   PropModeReplace, (unsigned char*)&value, 1);
}

int GetDesktop(Window w)
{
   return GetCardinal(w, XInternAtom(display, "_NET_WM_DESKTOP", False));
}

void SetDesktop(Window w, int desktop)
{
   SetCardinal(w, XInternAtom(display, "_NET_WM_DESKTOP", False), desktop);
   XEvent event;
   event.xclient.type = ClientMessage;
   event.xclient.window = w;
   event.xclient.message_type
      = XInternAtom(display, "_NET_WM_DESKTOP", False);
   event.xclient.format = 32;
   event.xclient.data.l[0] = desktop;
   XSendEvent(display, rootWindow, False, SubstructureRedirectMask, &event);
   XSync(display, False);
   sleep(1);
}

void GetPosition(Window w, int *x, int *y)
{
   XWindowAttributes attr;
   Window child;
   XGetWindowAttributes(display, w, &attr);
   XTranslateCoordinates(display, w, attr.root,
                         -attr.border_width, -attr.border_width,
                         x, y, &child);
}

int GetCurrentDesktop()
{
   return GetCardinal(rootWindow,
                      XInternAtom(display, "_NET_CURRENT_DESKTOP", False));
}

void SetCurrentDesktop(int desktop)
{
   XEvent event;
   event.xclient.type = ClientMessage;
   event.xclient.window = rootWindow;
   event.xclient.message_type
      = XInternAtom(display, "_NET_CURRENT_DESKTOP", False);
   event.xclient.format = 32;
   event.xclient.data.l[0] = desktop;
   XSendEvent(display, rootWindow, False, SubstructureRedirectMask, &event);
   XSync(display, False);
   sleep(1);
}

