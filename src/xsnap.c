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


 modified by github.com/calint
 */
#include</usr/include/X11/xpm.h>
int main(int argc,char*argv[]){
	Display*dpy=XOpenDisplay(0);
	if(dpy==NULL)return-1;
	Window root=RootWindow(dpy,DefaultScreen(dpy));
	XWindowAttributes rootAttributes;
	XGetWindowAttributes(dpy,root,&rootAttributes);
	XImage*img=XGetImage(dpy,root,0,0,(unsigned)rootAttributes.width,(unsigned)rootAttributes.height,XAllPlanes(),ZPixmap);
	if(img==NULL){XCloseDisplay(dpy);return-2;}
	const int x=XpmWriteFileFromImage(dpy,"snap.xpm",img,0,NULL);
	XDestroyImage(img);
	if(x==XpmOpenFailed){XCloseDisplay(dpy);return-3;}
	XCloseDisplay(dpy);
	return 0;
}
