
#include "wmtest.h"
#include "test-util.h"

void TestDesktop()
{

   XWindowAttributes attr;
   Window w;

   /* This assumes we have at least 2 desktops. */
   /* Switch to desktop 0. */
   SetCurrentDesktop(0);
   Assert(GetCurrentDesktop() == 0);

   /* Create the window. */
   w = XCreateSimpleWindow(display, rootWindow, 100, 100, 200, 100, 0, 0, 0);
   XSelectInput(display, w, StructureNotifyMask | PropertyNotify);

   /* Map the window and wait for it. */
   XMapWindow(display, w);
   Assert(AwaitEvent(MapNotify));

   /* Make sure the window is on desktop 0. */
   Assert(GetDesktop(w) == 0);

   /* Switch to desktop 2. */
   SetCurrentDesktop(1);
   XSync(display, False);
   Assert(GetCurrentDesktop() == 1);
   XGetWindowAttributes(display, w, &attr);
   Assert(attr.map_state == IsUnviewable);
   Assert(AwaitEvent(ConfigureNotify));

   /* Switch back to desktop 0. */
   SetCurrentDesktop(0);
   Assert(GetDesktop(w) == 0);
   XGetWindowAttributes(display, w, &attr);
   Assert(attr.map_state == IsViewable);

   /* Move the window to the other desktop. */
   SetDesktop(w, 1);
   Assert(GetDesktop(w) == 1);
   XGetWindowAttributes(display, w, &attr);
   Assert(attr.map_state == IsUnviewable);

   /* Destroy the window. */
   XDestroyWindow(display, w);

}

