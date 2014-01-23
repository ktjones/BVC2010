
#include < afxwin.h > // For the class library

class COurApp: public CWinApp
{
	public:
	virtual BOOL InitInstance();
};

class COurWnd: public CFrameWnd
{
	public:
	// Constructor
		COurWnd()
		{
			Create(0, L"Our Dumb MFC Application");
		}
};

BOOL COurApp::InitInstance(void)
{
	// Construct a window object in the free store
	m_pMainWnd = new COurWnd;
	m_pMainWnd-> ShowWindow(m_nCmdShow); // ...and display it
	return TRUE;
}

COurApp AnApplication; // Define an application object
