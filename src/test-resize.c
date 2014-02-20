
#include "wmtest.h"
#include "test-util.h"

static Window CreateWindow(XSizeHints *hints)
{
   Window w;
   w = XCreateSimpleWindow(display, rootWindow, 100, 100, 200, 100, 0, 0, 0);
   XSetWMNormalHints(display, w, hints);
   XSelectInput(display, w, StructureNotifyMask | PropertyChangeMask);
   XMapWindow(display, w);
   Assert(AwaitEvent(MapNotify));
   return w;
}

static void TestResize1()
{
   /* no hints */

   Window w;
   XSizeHints hints;
   XWindowAttributes attr;

   hints.flags = 0;
   w = CreateWindow(&hints);

   XGetWindowAttributes(display, w, &attr);
   Assert(attr.width == 200);
   Assert(attr.height == 100);

   IgnoreEvents();
   XResizeWindow(display, w, 50, 150);
   Assert(AwaitEvent(ConfigureNotify));
   XSync(display, True);
   XGetWindowAttributes(display, w, &attr);
   Assert(attr.width == 50);
   Assert(attr.height == 150);

   XDestroyWindow(display, w);

}

static void TestResize2()
{
   /* xinc and yinc set */

   Window w;
   XSizeHints hints;

   hints.flags = 0;
   w = CreateWindow(&hints);


   XDestroyWindow(display, w);
}

static void TestResize3()
{
   /* min aspect ratio set */
}

static void TestResize4()
{
   /* max aspect ratio set */
}

void TestResize()
{
   TestResize1();
   TestResize2();
   TestResize3();
   TestResize4();
}

