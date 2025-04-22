/**
 * \file ChildView.cpp
 *
 * \author Connor Mears
 */

// ChildView.cpp : implementation of the CChildView class
//

#include "pch.h"
#include "framework.h"
#include "DoubleBufferDC.h"
#include "Project1.h"
#include "ChildView.h"
#include "XmlNode.h"
#include "Tile.h"

#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace Gdiplus;
using namespace std;
using namespace xmlnode;

// CChildView
/// Frame duration in milliseconds
const int FrameDuration = 30;

/** Constructor */
CChildView::CChildView()
{
	wstring filename = L"levels/level1.xml";
	mGame.Load(filename);
}

/** Destructor */
CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_LEVEL_LEVEL0, &CChildView::OnLevelLevel0)
	ON_COMMAND(ID_LEVEL_LEVEL1, &CChildView::OnLevelLevel1)
	ON_COMMAND(ID_LEVEL_LEVEL2, &CChildView::OnLevelLevel2)
	ON_COMMAND(ID_LEVEL_LEVEL3, &CChildView::OnLevelLevel3)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

/**
* This function is called to draw in the window.
*
* This function is called in response to a drawing message
* whenever we need to redraw the window on the screen.
* It is responsible for painting the window.
*/
void CChildView::OnPaint() 
{
	if (mFirstDraw)
	{
		mFirstDraw = false;
		SetTimer(1, FrameDuration, nullptr);

		/*
		* Initialize the elapsed time system
		*/
		LARGE_INTEGER time, freq;
		QueryPerformanceCounter(&time);
		QueryPerformanceFrequency(&freq);

		mLastTime = time.QuadPart;
		mTimeFreq = double(freq.QuadPart);
	}

	// Compute the elapsed time since the last draw
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	long long diff = time.QuadPart - mLastTime;
	double elapsed = double(diff) / mTimeFreq;
	mLastTime = time.QuadPart;

	// Update
	mGame.Update(elapsed);

	CPaintDC paintDC(this);
	CDoubleBufferDC dc(&paintDC); // device context for painting
	Graphics graphics(dc.m_hDC);

	CRect rect;
	GetClientRect(&rect);

	// Then Draw
	mGame.OnDraw(&graphics, rect.Width(), rect.Height());


	Invalidate();
	
}

/**
 * Erase the background
 *
 * This is disabled to eliminate flicker
 * \param pDC Device context
 * \returns FALSE
 */
BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	return FALSE;
}

/**  Called when there is a left mouse button press
* \param nFlags Flags associated with the mouse button press
* \param point Where the button was pressed
*/
void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	mGame.OnLButtonDown(point.x, point.y);
}

/**
 * Called when the left mouse button is released
 * \param nFlags Flags associated with the mouse button release
 * \param point Where the button was pressed
 */
void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	OnMouseMove(nFlags, point);
}

/**
 * Called when the mouse is moved
 * \param nFlags Flags associated with the mouse movement
 * \param point Where the button was pressed
 */
void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	mGame.OnMouseMove(nFlags, point);
	Invalidate();
}

/**
 * This function is called when Level Level0 menu item is selected.
 *
 * It loads the level from a file.
 */
void CChildView::OnLevelLevel0()
{
	wstring filename = L"levels/level0a.xml";
	mGame.Load(filename);
	Invalidate();
}

/**
 * This function is called when Level Level1 menu item is selected.
 *
 * It loads the level from a file.
 */
void CChildView::OnLevelLevel1()
{
	wstring filename = L"levels/level1.xml";
	mGame.Load(filename);
	Invalidate();
}

/**
 * This function is called when Level Level2 menu item is selected.
 *
 * It loads the level from a file.
 */
void CChildView::OnLevelLevel2()
{
	wstring filename = L"levels/level2.xml";
	mGame.Load(filename);
	Invalidate();
}

/**
 * This function is called when Level Level3 menu item is selected.
 *
 * It loads the level from a file.
 */
void CChildView::OnLevelLevel3()
{
	wstring filename = L"levels/level3.xml";
	mGame.Load(filename);
	Invalidate();
}








