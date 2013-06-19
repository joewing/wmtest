
#include "wmtest.h"
#include "test-util.h"

void TestMap()
{

   Window w;

   /* Create the window. */
   w = XCreateSimpleWindow(display, rootWindow, 100, 100, 200, 100, 0, 0, 0);
   XSelectInput(display, w, StructureNotifyMask | PropertyNotify);

   /* Map the window and wait for it. */
   XMapWindow(display, w);
   AwaitEvent(MapNotify, NULL);

   /* Unmap the window and wait for it. */
   XUnmapWindow(display, w);
   AwaitEvent(UnmapNotify, NULL);

   /* Map the window and wait for it (again). */
   XMapWindow(display, w);
   AwaitEvent(MapNotify, NULL);

   /* Minimize and wait. */
   Minimize(w);
   AwaitEvent(UnmapNotify, NULL);

   /* Restore and wait. */
   Unminimize(w);
   AwaitEvent(MapNotify, NULL);

   /* Maximize and wait. */
   Maximize(w, 1, 1);
   AwaitEvent(ConfigureNotify, NULL);

   /* Unmaximize and wait. */
   Unmaximize(w, 0, 1);
   AwaitEvent(ConfigureNotify, NULL);

   /* Unmaximize and wait. */
   Unmaximize(w, 1, 0);
   AwaitEvent(ConfigureNotify, NULL);

   /* Shade and wait. */
   Shade(w);
   AwaitEvent(UnmapNotify, NULL);

   /* Maximize and wait. */
   Maximize(w, 0, 1);
   AwaitEvent(MapNotify, NULL);

   /* Shade and wait. */
   Shade(w);
   AwaitEvent(UnmapNotify, NULL);

   /* Shade and wait. */
   Unshade(w);
   AwaitEvent(MapNotify, NULL);

   /* Destroy the window. */
   XDestroyWindow(display, w);

}
