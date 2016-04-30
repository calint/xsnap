#include</usr/include/X11/xpm.h>
#include<stdlib.h>
int main(int argc,char*argv[]){
	Display*d=XOpenDisplay(0);if(d==NULL)return-1;
	Window w=RootWindow(d,DefaultScreen(d));
	XWindowAttributes wa;XGetWindowAttributes(d,w,&wa);
	XImage*i=XGetImage(d,w,0,0,(unsigned)wa.width,(unsigned)wa.height,XAllPlanes(),ZPixmap);
	if(i==NULL){XCloseDisplay(d);return-2;}
	const int r=XpmWriteFileFromImage(d,"snap.xpm",i,0,NULL);
	XDestroyImage(i);
	XCloseDisplay(d);
	if(r!=XpmSuccess)return-3;
	if(system("convert snap.xpm snap.png"))return-4;//.uses imagemagick
	return 0;
}
