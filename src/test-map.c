
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
   Assert(AwaitEvent(MapNotify));

   /* Unmap the window and wait for it. */
   XUnmapWindow(display, w);
   Assert(AwaitEvent(UnmapNotify));

   /* Map the window and wait for it (again). */
   XMapWindow(display, w);
   Assert(AwaitEvent(MapNotify));

   /* Minimize and wait. */
   Minimize(w);
   Assert(AwaitEvent(UnmapNotify));

   /* Restore and wait. */
   Unminimize(w);
   Assert(AwaitEvent(MapNotify));

   /* Maximize and wait. */
   Maximize(w, 1, 1);
   Assert(AwaitEvent(ConfigureNotify));

   /* Unmaximize and wait. */
   Unmaximize(w, 0, 1);
   Assert(AwaitEvent(ConfigureNotify));

   /* Unmaximize and wait. */
   Unmaximize(w, 1, 0);
   Assert(AwaitEvent(ConfigureNotify));

   /* Shade and wait. */
   Shade(w);
   Assert(AwaitEvent(UnmapNotify));

   /* Maximize and wait. */
   Maximize(w, 0, 1);
   Assert(AwaitEvent(MapNotify));

   /* Shade and wait. */
   Shade(w);
   Assert(AwaitEvent(UnmapNotify));

   /* Shade and wait. */
   Unshade(w);
   Assert(AwaitEvent(MapNotify));

   /* Destroy the window. */
   XDestroyWindow(display, w);

}
