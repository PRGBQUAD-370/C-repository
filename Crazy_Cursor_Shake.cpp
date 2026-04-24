#include <windows.h>
#include <cstdlib>
#include <ctime>

VOID WINAPI sound1() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 12000, 12000, 1, 8, 0 };

    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

    char buffer[12000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(2 * t & t >> 8 | 5 * t & t >> 7 | 9 * t & t >> 4 | 15 * t & t >> 4);

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };

    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));

    // ✅ WAIT for sound to finish
    Sleep(30000);

    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

int main() {
    // Hide console window
    HWND console = GetConsoleWindow();
    if (console) {
        ShowWindow(console, SW_HIDE);
    }
if (MessageBoxW(NULL, L"Do you want to shake the cursor crazy", L"Crazy_Cursor_Shake.exe", MB_YESNO) == IDNO)
{
    ExitProcess(0);
}
else
{
    if (MessageBoxW(NULL, L"Just press ESC if you want to stop it", L"Crazy_Cursor_Shake", MB_YESNO) == IDNO)
    {
        ExitProcess(0);
    }
    else
    {
        // Put your cursor shaking code here
    }
}

    POINT p;
    srand((unsigned int)time(nullptr));

    // Play sound at same time
    CreateThread(0, 0, (LPTHREAD_START_ROUTINE)sound1, 0, 0, 0);

    while (true) {
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            break;
        }

        GetCursorPos(&p);

        int dx = (rand() % 50) - 25;
        int dy = (rand() % 50) - 25;

        SetCursorPos(p.x + dx, p.y + dy);

        Sleep(10);
    }

    return 0;
}