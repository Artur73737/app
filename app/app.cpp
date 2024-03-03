#include "framework.h" // Includi il file header "framework.h"
#include "app.h" // Includi il file header "app.h"

#define MAX_LOADSTRING 100 // Definisci una costante chiamata MAX_LOADSTRING con valore 100

HINSTANCE hInst; // Definisci una variabile globale HINSTANCE chiamata hInst
WCHAR szTitle[MAX_LOADSTRING]; // Definisci un array di caratteri wide chiamato szTitle con dimensione MAX_LOADSTRING
WCHAR szWindowClass[MAX_LOADSTRING]; // Definisci un array di caratteri wide chiamato szWindowClass con dimensione MAX_LOADSTRING

// Prototipi delle funzioni
ATOM MyRegisterClass(HINSTANCE hInstance); // Dichiarazione del prototipo della funzione MyRegisterClass
BOOL InitInstance(HINSTANCE, int); // Dichiarazione del prototipo della funzione InitInstance
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); // Dichiarazione del prototipo della funzione WndProc
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM); // Dichiarazione del prototipo della funzione About

// Funzione principale dell'applicazione Windows
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance); // Ignora il parametro hPrevInstance
    UNREFERENCED_PARAMETER(lpCmdLine); // Ignora il parametro lpCmdLine

    // Carica le stringhe di testo dal file di risorse
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_APP, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance); // Registra la classe della finestra

    // Inizializza l'istanza dell'applicazione
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    // Carica e mostra l'acceleratore
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_APP));

    MSG msg;

    // Ciclo principale di messaggi
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

// Registra la classe della finestra
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APP));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = CreateSolidBrush(RGB(33, 33, 33)); // Colore di sfondo scuro
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_APP);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex); // Registra la classe della finestra
}

// Inizializza l'istanza dell'applicazione
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance;

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

// Gestore del messaggio principale della finestra
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
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
        SetTextColor(hdc, RGB(255, 255, 255)); // Imposta il colore del testo su bianco
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

// Gestore del messaggio della finestra di dialogo "About"
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
