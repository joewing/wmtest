
#include "wmtest.h"

static void DoTestGravity(int gravity)
{
   XEvent event;
   Window w;
   XSizeHints *hints;
   int first;
   int left, right, top, bottom;
   int expectedx, expectedy;
   int deltax, deltay;
   Atom extents_atom;

   extents_atom = XInternAtom(display, "_NET_FRAME_EXTENTS", False);

   /* Create the window. */
   w = XCreateSimpleWindow(display, rootWindow, 100, 100, 200, 100, 0, 0, 0);
   hints = XAllocSizeHints();
   hints->flags = PWinGravity | PPosition;
   hints->win_gravity = gravity;
   XSetWMNormalHints(display, w, hints);
   XFree(hints);
   XSelectInput(display, w, StructureNotifyMask | PropertyChangeMask);

   /* Determine the size of the border. */
   event.xclient.type = ClientMessage;
   event.xclient.window = w;
   event.xclient.message_type =
      XInternAtom(display, "_NET_REQUEST_FRAME_EXTENTS", False);
   event.xclient.format = 32;
   XSendEvent(display, rootWindow, False, SubstructureRedirectMask, &event);
   for(;;) {
      XNextEvent(display, &event);
      if(event.type == PropertyNotify && event.xproperty.atom == extents_atom) {
         Atom actual_type;
         int actual_format;
         unsigned long bytes;
         unsigned long nitems;
         long *props;
         XGetWindowProperty(display, w, extents_atom,
                            0, 4, False, XA_CARDINAL, &actual_type,
                            &actual_format, &nitems, &bytes,
                            (unsigned char**)&props);
         if(nitems == 4) {
            left     = props[0];
            right    = props[1];
            top      = props[2];
            bottom   = props[3];
            break;
         }
         XFree(props);
      }
   }

   /* Determine where the window should be mapped. */
   deltax = 0;
   deltay = 0;
   switch(gravity) {
   case NorthGravity:
      deltay = top;
      break;
   case SouthGravity:
      deltay = -bottom;
      break;
   case EastGravity:
      deltax = -left;
      break;
   case WestGravity:
      deltax = right;
      break;
   case NorthEastGravity:
      deltax = -left;
      deltay = top;
      break;
   case NorthWestGravity:
      deltax = right;
      deltay = top;
      break;
   case SouthEastGravity:
      deltax = -left;
      deltay = -bottom;
      break;
   case SouthWestGravity:
      deltax = right;
      deltay = -bottom;
      break;
   default:
      break;
   }
   expectedx = 100 + deltax;
   expectedy = 100 + deltay;
   
   /* Map the window. */
   XMapWindow(display, w);

   first = 1;
   for(;;) {
      XNextEvent(display, &event);
      if(event.type == MapNotify) {
         XWindowAttributes attr;
         Window child;
         int x, y;
         XGetWindowAttributes(display, w, &attr);
         XTranslateCoordinates(display, w, attr.root,
                               -attr.border_width, -attr.border_width,
                               &x, &y, &child);
         if(expectedx != x || expectedy != y) {
            printf("FAILED\n");
            printf("mapped at %d, %d\n", x, y);
            printf("expected position: %d, %d\n", expectedx, expectedy);
         }
         if(first) {
            XUnmapWindow(display, w);
            XMapWindow(display, w);
            first = 0;
         } else {
            break;
         }
      }
   }

   XDestroyWindow(display, w);
}

void TestGravity()
{

   DoTestGravity(NorthGravity);
   DoTestGravity(SouthGravity);
   DoTestGravity(EastGravity);
   DoTestGravity(WestGravity);
   DoTestGravity(NorthEastGravity);
   DoTestGravity(NorthWestGravity);
   DoTestGravity(SouthEastGravity);
   DoTestGravity(SouthWestGravity);
   DoTestGravity(StaticGravity);

}

