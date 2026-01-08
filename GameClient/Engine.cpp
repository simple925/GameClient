#include "pch.h"
LRESULT CALLBACK  WndProc(HWND, UINT, WPARAM, LPARAM);

Engine::Engine()
    : m_hInst(nullptr)
    , m_hWnd(nullptr)
    , m_Resolution{}
{
}

Engine::~Engine()
{
}
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
int Engine::Init(HINSTANCE _hInst, UINT _Width, UINT _Height)
{
    m_hInst = _hInst;
    m_Resolution.x = _Width;
    m_Resolution.y = _Height;


    WNDCLASSEXW wcex;

    //wcex.lpszClassName = szWindowClass;
    wcex.lpszClassName = L"MyGame";
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc; // 함수 포인터 등록
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = _hInst;
    wcex.hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_GAMECLIENT));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(1);
    //wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_GAMECLIENT); // 사용안할경우 null
    wcex.lpszMenuName = nullptr;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    RegisterClassExW(&wcex);

    m_hWnd = CreateWindowW(L"MyGame", L"MyGame", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_hInst, nullptr);


    // 윈도우 생성 실패 시 프로그램 종료
    if (!m_hWnd)
    {
        return E_FAIL;
    }

    // 생성한 윈도우를 화면에 보이도록 설정
    ShowWindow(m_hWnd, true);
    UpdateWindow(m_hWnd);


    // 내 모니터 해상도 얻어옴
    //UINT width = GetSystemMetrics(SM_CXSCREEN);
    //UINT hegit = GetSystemMetrics(SM_CYSCREEN);
    // 윈도우 크기 및 위치 변경
    //SetWindowPos(hWnd, nullptr, 0, 0, xsize, ysize, 0);
    SetWindowPos(m_hWnd, nullptr, 0, 0, m_Resolution.x, m_Resolution.y, 0);

    // 검은색으로 모든 pixel 채우기 cpu 방식
    HDC dc = GetDC(m_hWnd); // 입력으로 넣어준 윈도우에 그림을 그릴수 있게 해주는 도구
    HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0)); // 검은색 브러쉬 생성
    SelectObject(dc, hBrush); // dc 에 검은색 Brush 를 전달
    Rectangle(dc, 0, 0, 1600, 900); // dc 를 이용해서 윈도우에 검은색 사각형 그리기

    return 0;
}

void Engine::Progres()
{
	// 화면을 검은색으로 색칠한다.
	// 화면에 랜더링
	// 1600*900=144만개 의 픽셀을 0,0,0,0

	// CPU를 이용
	// Window 에서 제공하는 GDI 함수를 사용
	// 

	// GPU를 이용
	// Directx API(함수) 를 이용해서 GPU를 컨트롤하고 명령해야함

	// Pixel 1개당 4byte RGBA  r256 * g256 * b256 = 16,777,216


	
}

