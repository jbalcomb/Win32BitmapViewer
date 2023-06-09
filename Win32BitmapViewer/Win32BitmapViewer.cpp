// Win32BitmapViewer.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Win32BitmapViewer.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

//WCHAR szBmpFileName[MAX_PATH] = L"C:\\devel\\Win32BitmapViewer\\Win32BitmapViewer\\MAIN000.BMP";
WCHAR szBmpFileName[MAX_PATH] = L"C:\\devel\\Win32BitmapViewer\\Win32BitmapViewer\\MAIN000_24bpp.BMP";
HBITMAP g_hBitmap;
LPBYTE* g_ppaBmpFileData;
DWORD* g_pcbBmpFileData;
LPBYTE g_paBitmapData;
BITMAPINFO bmi;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
HRESULT LoadFile(LPCWSTR lpFileName, LPBYTE* ppaFileData, DWORD* pcbFileData);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    //g_hBitmap = (HBITMAP)LoadImage(NULL, szBmpFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    LPBYTE paBmpFileData;
    DWORD cbBmpFileData;
    LoadFile(szBmpFileName, &paBmpFileData, &cbBmpFileData);
    BITMAPFILEHEADER* pBitmapFileHeader;
    BITMAPINFOHEADER* pBitmapInfoHeader;
    pBitmapFileHeader = (BITMAPFILEHEADER*)paBmpFileData;
    pBitmapInfoHeader = (BITMAPINFOHEADER*)(((PBYTE)pBitmapFileHeader) + sizeof(BITMAPFILEHEADER));
    DWORD cbPixelDataOffset = pBitmapFileHeader->bfOffBits;
    LPBYTE paBitmapData;
    DWORD cbBitmapData;

    paBitmapData = ((LPBYTE)pBitmapFileHeader) + cbPixelDataOffset;
    cbBitmapData = cbBmpFileData - cbPixelDataOffset;

    g_paBitmapData = ((LPBYTE)pBitmapFileHeader) + cbPixelDataOffset;

    //BITMAPINFO bmi;
    bmi.bmiHeader.biSize = pBitmapInfoHeader->biSize;  // sizeof(BITMAPINFOHEADER)
    bmi.bmiHeader.biWidth = pBitmapInfoHeader->biWidth;
    bmi.bmiHeader.biHeight = pBitmapInfoHeader->biHeight;
    bmi.bmiHeader.biPlanes = pBitmapInfoHeader->biPlanes;
    bmi.bmiHeader.biBitCount = pBitmapInfoHeader->biBitCount;
    bmi.bmiHeader.biCompression = pBitmapInfoHeader->biCompression;
    bmi.bmiHeader.biSizeImage = pBitmapInfoHeader->biSizeImage;
    bmi.bmiHeader.biXPelsPerMeter = pBitmapInfoHeader->biXPelsPerMeter;
    bmi.bmiHeader.biYPelsPerMeter = pBitmapInfoHeader->biYPelsPerMeter;
    bmi.bmiHeader.biClrUsed = pBitmapInfoHeader->biClrUsed;
    bmi.bmiHeader.biClrImportant = pBitmapInfoHeader->biClrImportant;

    /*
    BITMAPFILEHEADER.bfSize     The size, in bytes, of the bitmap file.
    BITMAPFILEHEADER.bfOffBits  The offset, in bytes, from the beginning of the BITMAPFILEHEADER structure to the bitmap bits.
    BITMAPINFOHEADER.biSize     sizeof(BITMAPINFOHEADER)  ~== 40


    */

    wchar_t text_buffer[4096] = { 0 };  // temporary buffer

    swprintf(text_buffer, _countof(text_buffer), L"pBitmapFileHeader: 0x%016X\n", pBitmapFileHeader);
    OutputDebugStringW(text_buffer);
    swprintf(text_buffer, _countof(text_buffer), L"pBitmapInfoHeader: 0x%016X\n", pBitmapInfoHeader);
    OutputDebugStringW(text_buffer);
    swprintf(text_buffer, _countof(text_buffer), L"paBitmapData: 0x%016X\n", paBitmapData);
    OutputDebugStringW(text_buffer);
    //swprintf(text_buffer, _countof(text_buffer), L"(pBitmapInfoHeader - pBitmapFileHeader): %d\n", (pBitmapInfoHeader - pBitmapFileHeader));
    //OutputDebugStringW(text_buffer);
    //swprintf(text_buffer, _countof(text_buffer), L"(paBitmapData - pBitmapInfoHeader): %d\n", (paBitmapData - pBitmapInfoHeader));
    //OutputDebugStringW(text_buffer);
    /*
        e.g.,
            pBitmapFileHeader:  0x00000000AEF29FE0
            pBitmapInfoHeader:  0x00000000AEF29FEE
            paBitmapData:       0x00000000AEF2A016
            582BAFCE - 582BAFC0 =  Eh 14d
            582BAFF6 - 582BAFCE = 28h 40d
            582BAFF6 - 582BAFC0 = 36h 54d
    */
    swprintf(text_buffer, _countof(text_buffer), L"g_paBitmapData: 0x%016X\n", g_paBitmapData);
    OutputDebugStringW(text_buffer);
    /*
        e.g.,
            g_paBitmapData:  0x00000000AEF2A016
    */

    swprintf(text_buffer, _countof(text_buffer), L"pBitmapFileHeader->bfType: 0x%04X\n", pBitmapFileHeader->bfType);  // WORD
    OutputDebugStringW(text_buffer);
    swprintf(text_buffer, _countof(text_buffer), L"pBitmapFileHeader->bfSize: %d\n", pBitmapFileHeader->bfSize);  // DWORD
    OutputDebugStringW(text_buffer);
    swprintf(text_buffer, _countof(text_buffer), L"pBitmapFileHeader->bfReserved1: %d\n", pBitmapFileHeader->bfReserved1);  // WORD
    OutputDebugStringW(text_buffer);
    swprintf(text_buffer, _countof(text_buffer), L"pBitmapFileHeader->bfReserved2: %d\n", pBitmapFileHeader->bfReserved2);  // WORD
    OutputDebugStringW(text_buffer);
    swprintf(text_buffer, _countof(text_buffer), L"pBitmapFileHeader->bfOffBits: %d\n", pBitmapFileHeader->bfOffBits);  // DWORD
    OutputDebugStringW(text_buffer);

    swprintf(text_buffer, _countof(text_buffer), L"pBitmapInfoHeader->biSize: %d\n", pBitmapInfoHeader->biSize);  // DWORD
    OutputDebugStringW(text_buffer);
    swprintf(text_buffer, _countof(text_buffer), L"pBitmapInfoHeader->biWidth: %d\n", pBitmapInfoHeader->biWidth);  // LONG
    OutputDebugStringW(text_buffer);
    swprintf(text_buffer, _countof(text_buffer), L"pBitmapInfoHeader->biHeight: %d\n", pBitmapInfoHeader->biHeight);  // LONG
    OutputDebugStringW(text_buffer);
    swprintf(text_buffer, _countof(text_buffer), L"pBitmapInfoHeader->biPlanes: %d\n", pBitmapInfoHeader->biPlanes);  // WORD
    OutputDebugStringW(text_buffer);
    swprintf(text_buffer, _countof(text_buffer), L"pBitmapInfoHeader->biBitCount: %d\n", pBitmapInfoHeader->biBitCount);  // WORD
    OutputDebugStringW(text_buffer);
    swprintf(text_buffer, _countof(text_buffer), L"pBitmapInfoHeader->biCompression: %d\n", pBitmapInfoHeader->biCompression);  // DWORD
    OutputDebugStringW(text_buffer);
    swprintf(text_buffer, _countof(text_buffer), L"pBitmapInfoHeader->biSizeImage: %d\n", pBitmapInfoHeader->biSizeImage);  // DWORD  (320 * 200) = 64,000 * 3BPP = 192,000
    OutputDebugStringW(text_buffer);
    swprintf(text_buffer, _countof(text_buffer), L"pBitmapInfoHeader->biXPelsPerMeter: %d\n", pBitmapInfoHeader->biXPelsPerMeter);  // LONG
    OutputDebugStringW(text_buffer);
    swprintf(text_buffer, _countof(text_buffer), L"pBitmapInfoHeader->biYPelsPerMeter: %d\n", pBitmapInfoHeader->biYPelsPerMeter);  // LONG
    OutputDebugStringW(text_buffer);
    swprintf(text_buffer, _countof(text_buffer), L"pBitmapInfoHeader->biClrUsed: %d\n", pBitmapInfoHeader->biClrUsed);  // DWORD
    OutputDebugStringW(text_buffer);
    swprintf(text_buffer, _countof(text_buffer), L"pBitmapInfoHeader->biClrImportant: %d\n", pBitmapInfoHeader->biClrImportant);  // DWORD
    OutputDebugStringW(text_buffer);

    swprintf(text_buffer, _countof(text_buffer), L"bmi.bmiHeader.biSize: %d\n", bmi.bmiHeader.biSize);
    OutputDebugStringW(text_buffer);
    swprintf(text_buffer, _countof(text_buffer), L"bmi.bmiHeader.biWidth: %d\n", bmi.bmiHeader.biWidth);
    OutputDebugStringW(text_buffer);
    swprintf(text_buffer, _countof(text_buffer), L"bmi.bmiHeader.biHeight: %d\n", bmi.bmiHeader.biHeight);
    OutputDebugStringW(text_buffer);
    swprintf(text_buffer, _countof(text_buffer), L"bmi.bmiHeader.biPlanes: %d\n", bmi.bmiHeader.biPlanes);
    OutputDebugStringW(text_buffer);
    swprintf(text_buffer, _countof(text_buffer), L"bmi.bmiHeader.biBitCount: %d\n", bmi.bmiHeader.biBitCount);
    OutputDebugStringW(text_buffer);
    swprintf(text_buffer, _countof(text_buffer), L"bmi.bmiHeader.biCompression: %d\n", bmi.bmiHeader.biCompression);
    OutputDebugStringW(text_buffer);
    swprintf(text_buffer, _countof(text_buffer), L"bmi.bmiHeader.biSizeImage: %d\n", bmi.bmiHeader.biSizeImage);  // (320 * 200) = 64,000 * 3BPP = 192,000
    OutputDebugStringW(text_buffer);
    swprintf(text_buffer, _countof(text_buffer), L"bmi.bmiHeader.biXPelsPerMeter: %d\n", bmi.bmiHeader.biXPelsPerMeter);
    OutputDebugStringW(text_buffer);
    swprintf(text_buffer, _countof(text_buffer), L"bmi.bmiHeader.biYPelsPerMeter: %d\n", bmi.bmiHeader.biYPelsPerMeter);
    OutputDebugStringW(text_buffer);
    swprintf(text_buffer, _countof(text_buffer), L"bmi.bmiHeader.biClrUsed: %d\n", bmi.bmiHeader.biClrUsed);
    OutputDebugStringW(text_buffer);
    swprintf(text_buffer, _countof(text_buffer), L"bmi.bmiHeader.biClrImportant: %d\n", bmi.bmiHeader.biClrImportant);
    OutputDebugStringW(text_buffer);

    HDC hdc;
    hdc = CreateCompatibleDC(NULL);
    //g_hBitmap = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, (void**)&paBitmapData, NULL, 0);
    g_hBitmap = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, (void**)&g_paBitmapData, NULL, 0);
    //g_hBitmap = CreateDIBSection(hdc, (BITMAPINFO*)&bmi, DIB_RGB_COLORS, (void**)&paBitmapData, NULL, 0);
    //frame_bitmap = CreateDIBSection(NULL, &frame_bitmap_info, DIB_RGB_COLORS, &frame.pixels, 0, 0);
    pDC = CreateCompatibleDC(NULL);
    old = SelectObject(pDC, ourbitmap);
    DeleteDC(hDC);


    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WIN32BITMAPVIEWER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32BITMAPVIEWER));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDC_WIN32BITMAPVIEWER));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WIN32BITMAPVIEWER);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Store instance handle in our global variable

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Add any drawing code that uses hdc here...

        BITMAP bm;
        HDC hdcMem = CreateCompatibleDC(hdc);
        HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, g_hBitmap);
        GetObject(g_hBitmap, sizeof(bm), &bm);

        wchar_t text_buffer[4096] = { 0 };  // temporary buffer
        swprintf(text_buffer, _countof(text_buffer), L"bm.bmType: %d\n", bm.bmType);  // LONG
        OutputDebugStringW(text_buffer);
        swprintf(text_buffer, _countof(text_buffer), L"bm.bmWidth: %d\n", bm.bmWidth);  // LONG
        OutputDebugStringW(text_buffer);
        swprintf(text_buffer, _countof(text_buffer), L"bm.bmHeight: %d\n", bm.bmHeight);  // LONG
        OutputDebugStringW(text_buffer);
        swprintf(text_buffer, _countof(text_buffer), L"bm.bmWidthBytes: %d\n", bm.bmWidthBytes);  // LONG
        OutputDebugStringW(text_buffer);
        swprintf(text_buffer, _countof(text_buffer), L"bm.bmPlanes: %d\n", bm.bmPlanes);  // WORD
        OutputDebugStringW(text_buffer);
        swprintf(text_buffer, _countof(text_buffer), L"bm.bmBitsPixel: %d\n", bm.bmBitsPixel);  // WORD
        OutputDebugStringW(text_buffer);
        swprintf(text_buffer, _countof(text_buffer), L"bm.bmBits: 0x%016X\n", bm.bmBits);  // LPVOID
        OutputDebugStringW(text_buffer);
        /*
            e.g.,
                bm.bmType:            0
                bm.bmWidth:         320
                bm.bmHeight:        200
                bm.bmWidthBytes:    960
                bm.bmPlanes:          1
                bm.bmBitsPixel:      24
                bm.bmBits:          0x00000000AEEE0000

        */
        // bm.bmBits = g_paBitmapData;
        // swprintf(text_buffer, _countof(text_buffer), L"g_paBitmapData: 0x%016X\n", g_paBitmapData);  // LPVOID
        // OutputDebugStringW(text_buffer);
        // swprintf(text_buffer, _countof(text_buffer), L"bm.bmBits: 0x%016X\n", bm.bmBits);  // LPVOID
        // OutputDebugStringW(text_buffer);
        // /*
        //     e.g., 
        //         g_paBitmapData: 0x00000000AEF2A016
        //         bm.bmBits:      0x00000000AEF2A016
        // */

        BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);
        //StretchDIBits(hdc, 0, 0, 320, 200, 0, 0, 320, 200, g_paBitmapData, &bmi, 0, SRCCOPY);
        SelectObject(hdcMem, hbmOld);
        DeleteDC(hdcMem);

        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

HRESULT LoadFile
(
    __in LPCWSTR lpFileName,
    // wchar_t * FileName ... Why not LPCWSTR?
    __deref_out_bcount(*pcbFileData) LPBYTE* ppaFileData,
    // Will contain the pointer to the file data buffer
    __out DWORD* pcbFileData
    // Size of file data buffer returned
)
{

    HANDLE hFile;
    HRESULT hResult;
    DWORD dwBytesRead;

    hResult = S_OK;

    if (!ppaFileData || !pcbFileData)
    {
        return E_INVALIDARG;
    }

    hFile = CreateFile(lpFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hFile == INVALID_HANDLE_VALUE)
    {
        //DisplayError(TEXT("CreateFile"));
        wprintf(L"Terminal failure: unable to open file \"%s\" for read.\n", lpFileName);
        //return EXIT_FAILURE;
    }
    *pcbFileData = GetFileSize(hFile, NULL);
    *ppaFileData = new BYTE[*pcbFileData];
    dwBytesRead = 0;
    if (FALSE == ReadFile(hFile, *ppaFileData, *pcbFileData, &dwBytesRead, NULL)) {
        //DisplayError(TEXT("ReadFile"));
        _tprintf(TEXT("Terminal failure: Unable to read from file.\n GetLastError=%08x\n"), GetLastError());
        CloseHandle(hFile);
        //return EXIT_FAILURE;

    }
    if (dwBytesRead != *pcbFileData) {
        //DisplayError(TEXT("ReadFile"));
        _tprintf(TEXT("Terminal failure: Unable to read from file.\n GetLastError=%08x\n"), GetLastError());
        CloseHandle(hFile);
        //return EXIT_FAILURE;
    }

    //if (_msize(hFile) == 0) { CloseHandle(hFile); }
//#pragma warning disable
#pragma warning disable C6001 // Warning suppressed from here
    CloseHandle(hFile);
#pragma warning restore C6001 // Warning recognized from here
    //#pragma warning restore

    return hResult;
}
