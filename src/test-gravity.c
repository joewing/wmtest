
#include "wmtest.h"
#include "test-util.h"

static void DoTestGravity(int gravity)
{
   XEvent event;
   Window w;
   XSizeHints *hints;
   int left, right, top, bottom;
   int expectedx, expectedy;
   int deltax, deltay;
   Atom extents_atom;
   XWindowAttributes attr;
   Window child;
   int x, y;

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
      char rc = AwaitEvent2(PropertyNotify, &event);
      if(!rc) {
         Assert(0);
         printf("could not get frame extents\n");
         left     = 0;
         right    = 0;
         top      = 0;
         bottom   = 0;
         break;
      }
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
         break;
      }
   }

   /* Determine where the window should be mapped. */
   deltax = 0;
   deltay = 0;
   switch(gravity) {
   case NorthGravity:
      printf("North\n");
      deltay = top;
      break;
   case SouthGravity:
      printf("South\n");
      deltay = -bottom;
      break;
   case EastGravity:
      printf("East\n");
      deltax = -left;
      break;
   case WestGravity:
      printf("West\n");
      deltax = right;
      break;
   case NorthEastGravity:
      printf("NorthEast\n");
      deltax = -left;
      deltay = top;
      break;
   case NorthWestGravity:
      printf("NorthWest\n");
      deltax = right;
      deltay = top;
      break;
   case SouthEastGravity:
      printf("SouthEast\n");
      deltax = -left;
      deltay = -bottom;
      break;
   case SouthWestGravity:
      printf("SouthWest\n");
      deltax = right;
      deltay = -bottom;
      break;
   case CenterGravity:
      printf("Center\n");
      deltax = (right - left) / 2;
      deltay = (bottom - top) / 2;
      break;
   default:
      printf("Static\n");
      break;
   }
   expectedx = 100 + deltax;
   expectedy = 100 + deltay;
   
   /* Map the window. */
   XMapWindow(display, w);
   Assert(AwaitEvent(MapNotify));

   /* Check the position. */
   XGetWindowAttributes(display, w, &attr);
   XTranslateCoordinates(display, w, attr.root,
                         -attr.border_width, -attr.border_width,
                         &x, &y, &child);
   if(expectedx != x || expectedy != y) {
      Assert(0);
      printf("expected (%d, %d) got (%d, %d)\n", expectedx, expectedy, x, y);
   }

   XUnmapWindow(display, w);
   Assert(AwaitEvent(UnmapNotify));
   XMapWindow(display, w);
   Assert(AwaitEvent(MapNotify));

   XGetWindowAttributes(display, w, &attr);
   XTranslateCoordinates(display, w, attr.root,
                         -attr.border_width, -attr.border_width,
                         &x, &y, &child);
   if(expectedx != x || expectedy != y) {
      Assert(0);
      printf("expected (%d, %d) got (%d, %d)\n", expectedx, expectedy, x, y);
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
   DoTestGravity(CenterGravity);
   DoTestGravity(StaticGravity);

}

