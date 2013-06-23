
#include "wmtest.h"

Display *display;
Window rootWindow;
int rootScreen;
int rootDepth;
unsigned int errorCount = 0;

static void ShowUsage(const char *name)
{
   printf("usage: %s [options]\n", name);
}

int main(int argc, char *argv[])
{
   const char *displayString = NULL;
   int i;

   for(i = 1; i < argc; i++) {
      if(!strcmp(argv[i], "-display") && i + 1 < argc) {
         i += 1;
         displayString = argv[i];
      } else {
         ShowUsage(argv[0]);
         exit(-1);
      }
   }

   display = XOpenDisplay(displayString);
   if(!display) {
      if(displayString) {
         printf("error: could not open display %s\n", displayString);
      } else {
         printf("error: could not open display\n");
      }
      exit(-1);
   }

   rootScreen = DefaultScreen(display);
   rootWindow = RootWindow(display, rootScreen);
   rootDepth = DefaultDepth(display, rootScreen);

   TestMap();
   TestGravity();
   TestDesktop();
   TestResize();

   XCloseDisplay(display);

   printf("Errors: %u\n", errorCount);

   return 0;

}
