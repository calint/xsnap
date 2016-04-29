/* 

 root2xpm v0.99 [c]2012 Topcat Software LLC.

 http://www.topcat.hypermart.net/index.html

 Permission  is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in  the Software without restriction, including without limitation the rights
 to  use,  copy,  modify,  merge, publish, distribute, sublicense, and/or sell
 copies  of  the  Software,  and  to  permit  persons  to whom the Software is
 furnished to do so, subject to the following conditions:

 The  above  copyright  notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE  SOFTWARE  IS  PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED,  INCLUDING  BUT  NOT  LIMITED  TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS  FOR  A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS  OR  COPYRIGHT  HOLDERS  BE  LIABLE  FOR  ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.

 compilation: gcc -Wall -Werror root2xpm.c -o root2xpm -lX11 -lXpm

 */

//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//#include <unistd.h>
//#include <X11/Xlib.h>
#include </usr/include/X11/xpm.h>

// --------------------------------------------------------------------------
//
//int exitmsg(int e){
//
//	char buf[256]; // buffer for error messages
//
//	switch(e){
//	case 1:
//		sprintf(buf,"value must be from 1 to 59");
//		break;
//	case 2:
//		sprintf(buf,"error opening display");
//		break;
//	case 3:
//		sprintf(buf,"error obtaining image");
//		break;
//	case 4:
//		sprintf(buf,"libxpm error");
//		break;
//	}
//
//	fprintf(stderr,"root2xpm: %s...\n",buf);
//
//	return 1;
//
//}
//
//// --------------------------------------------------------------------------
//
//int syntax(void){
//
//	system("clear");
//
//	printf("%s","\n\n\
//  root2xpm screen-shot tool v0.99 [c]2012 Topcat Software LLC.\n\n\
//  syntax: root2xpm [-s seconds] [-f file.xpm]\n\n\
//  where...\n\n\
//  -s specifies sleep in secs. (1 to 59)\n\n\
//  -f specifies filename\n\n");
//
//	return 0;
//
//}
//
//// --------------------------------------------------------------------------

int main(int argc,char *argv[]){

//    if (argc < 5 || argc > 5) return syntax(); // bad syntax return
//    int x = strcmp(argv[1], "-s");             // -s option
//    int y = strcmp(argv[3], "-f");             // -f option
//    if (x || y) return syntax();               // bad syntax return
//    int n = atoi(argv[2]);                     // number of seconds to sleep
//    if (n < 1 || n > 59) return exitmsg(1);    // out of range return error msg
//    sleep(n);                                  // zzz... n seconds

	Display *dpy=XOpenDisplay(0);            // attempt to open display
	if(dpy==NULL)return -2;
//	if(dpy==NULL)
//		return exitmsg(2);        // else return error

	Window root=RootWindow(dpy,DefaultScreen(dpy)); // get root window
	XWindowAttributes rootAttributes;                 // and then...
	XGetWindowAttributes(dpy,root,&rootAttributes); // acquire attributes

	XImage *img=XGetImage(dpy,root,0,0,rootAttributes.width,rootAttributes.height,XAllPlanes(),ZPixmap);          // nab XImage of root window

	if(img==NULL){                  // if XGetImage() failed
		XCloseDisplay(dpy);             // close display and
//		return exitmsg(3);              // return error
		return -3;
	}else{
		const int x=XpmWriteFileFromImage(dpy,"snap.xpm",img,0,NULL); // write xpm
		XDestroyImage(img);                                 // release memory
		if(x==XpmOpenFailed){       // if libxpm failed
			XCloseDisplay(dpy);         // close display and
//			return exitmsg(4);          // return error
			return -4;
		}
	}

	XCloseDisplay(dpy);                 // close display and
	return 0;                           // bring it on home

}

// eof
