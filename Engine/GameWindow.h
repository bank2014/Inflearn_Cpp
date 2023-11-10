#pragma once

class GameWindow
{
public:
    virtual ~GameWindow() = default;

    void MakeWindow(std::wstring title, HINSTANCE hInst, DWORD dwWindowWidth, DWORD dwWindowHeight);

protected:
    HINSTANCE   m_HInstance;
    HWND        m_hWnd;
    DWORD       m_WindowExStyle;
    DWORD       m_WindowStyle;
    DWORD       m_WindowPosX;
    DWORD       m_WindowPosY;
    DWORD       m_WindowWidth;
    DWORD       m_WindowHeight;
};

