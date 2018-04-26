/*
 *  Main.cpp
 *  glass
 *
 *  Created by sunjun on 11-6-14.
 *  Copyright 2011 sunstdio. All rights reserved.
 *
 */

//////////////////////////////////////////////////////////////////////////

#include <Glass.h>
#include "Window.h"

//////////////////////////////////////////////////////////////////////////

extern VOID GInitGame();
extern VOID GRunGame(F64 delta_time);
extern VOID GDrawGame(GGraph& graph);
extern VOID GExitGame();

//////////////////////////////////////////////////////////////////////////

static WindowPtr gWndPtr;
static U32 gWndWidth = 1024;
static U32 gWndHeight = 768;
static GImagePtr gBackground;

//////////////////////////////////////////////////////////////////////////

static VOID appInit();
static VOID appRun();
static VOID appExit();

//////////////////////////////////////////////////////////////////////////

/*
====================
main
====================
*/ 
I32 main(I32 argc, CHAR** argv)
{
	// register the window class
	WNDCLASSEX wcex;	
	wcex.cbSize			= sizeof(WNDCLASSEX);
	wcex.style			= 0;
	wcex.lpfnWndProc	= (WNDPROC)Window::wndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= ::GetModuleHandle(NULL);
	wcex.hIcon			= NULL;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)WHITE_BRUSH;
	wcex.lpszMenuName	= 0;
	wcex.lpszClassName	= "GWindow";
	wcex.hIconSm		= 0;
	CHECK(::RegisterClassEx(&wcex));

	appInit();

	// the message loop
	MSG msg; ::memset(&msg,0,sizeof(msg));
	while(msg.message != WM_QUIT) 
	{
		if(::PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) 
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		} 
		else 
		{
			appRun();

			// sleep it
      GSleep(0.001f);
		}
	}

	appExit();	

	// unregister the window class
	::UnregisterClass("GWindow", ::GetModuleHandle(NULL));

	return 0;
}

//////////////////////////////////////////////////////////////////////////
/*
====================
appInit
====================
*/
static VOID appInit()
{ 
	// create the window
	gWndPtr = GNEW(Window); CHECK(gWndPtr);
	gWndPtr->SetText("glass");
	gWndPtr->move(gWndWidth, gWndHeight);

  // init the game
	GInitGame();
}

/*
====================
appRun
====================
*/
static VOID appRun()
{
  // get the frame time
  static F64 system_time = GSeconds();
  F64 current_time = GSeconds();
  F64 frame_time = current_time - system_time;
  if(frame_time == 0) return;
  system_time = current_time;

  // run the game
	GRunGame(frame_time);

  // update the window
  RECT rc_wnd;
  ::GetClientRect(gWndPtr->handle(), &rc_wnd);
  ::InvalidateRect(gWndPtr->handle(), &rc_wnd, FALSE);
}

/*
====================
appDraw
====================
*/
VOID appDraw()
{
	if(gWndPtr == NULL) return;

  // draw the game
  PAINTSTRUCT paint;
  HDC dc = ::BeginPaint(gWndPtr->handle(), &paint);  
  
  I32 x = paint.rcPaint.left;
  I32 y = paint.rcPaint.top;
  I32 w = paint.rcPaint.right - x;
  I32 h = paint.rcPaint.bottom - y;
  if(w == 0 || h == 0) return;
  if(gBackground == NULL || gBackground->Width() != w || gBackground->Height() != h)
  {
    gBackground = GImage::Create(w, h, PF_R8G8B8); CHECK(gBackground);
  }
  
  GGraph graph(gBackground.Get());
  GDrawGame(graph);

  // convert the pixel format from rgb to bgr
  {
    I32 width = gBackground->Width();
    I32 height = gBackground->Height();
    U8* pixels = (U8*)gBackground->Pixels();
    for(I32 j = 0; j < height; j++)
    {
      for(I32 i = 0; i < width; i++)
      {
        U8& r = pixels[j*width*3 + (i*3+0)];
        U8& b = pixels[j*width*3 + (i*3+2)];
        std::swap(r, b);
      }
    }
  }

  BITMAPINFO bi;
  bi.bmiHeader.biSize	= sizeof(BITMAPINFOHEADER);   
  bi.bmiHeader.biWidth = w;   
  bi.bmiHeader.biHeight = -h;
  bi.bmiHeader.biPlanes = 1;   
  bi.bmiHeader.biBitCount = 24;
  bi.bmiHeader.biCompression = BI_RGB;
  bi.bmiHeader.biSizeImage = 0;   
  bi.bmiHeader.biXPelsPerMeter = 0;   
  bi.bmiHeader.biYPelsPerMeter = 0;   
  bi.bmiHeader.biClrUsed = 0;   
  bi.bmiHeader.biClrImportant = 0;
  ::StretchDIBits(dc, x, y, w, h, 0, 0, gBackground->Width(), gBackground->Height(), gBackground->Pixels(), (const BITMAPINFO*)&bi, DIB_RGB_COLORS, SRCCOPY);
  ::EndPaint(gWndPtr->handle(), &paint);
}

/*
====================
appExit
====================
*/
static VOID appExit()
{
	// exit the game
	GExitGame();  

	// release the window
	if(gWndPtr) gWndPtr.Release();
}

//////////////////////////////////////////////////////////////////////////

/*
====================
GLoad
====================
*/
const GData* GLoad(const CHAR* path)
{
	GFile file;
	file.Open(path);
	U32 pos = file.Seek(0,FS_CUR);
	U32 size = file.Seek(0,FS_END);	
	file.Seek(pos,FS_SET);
	GData* data = GNEW(GData(size+1,0)); CHECK(data);
	CHECK(file.Read(data->Get(),data->Size())==size);
	file.Close();
	return data;
}

//////////////////////////////////////////////////////////////////////////