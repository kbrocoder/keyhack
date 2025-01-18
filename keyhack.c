#include <windows.h>
#include <shlobj.h>  // For SHGetFolderPath
#include <stdio.h>
#include <tchar.h>

#define HOTKEY_MODIFIER (MOD_CONTROL | MOD_ALT)
#define HOTKEY_ID 1
// 
// Program to use Control + Alt + Zero (0) to open Desktop folder
// 

// Function declarations
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
void ShowDesktopContents();

// Global variables
HHOOK hook = NULL;
HINSTANCE hInstance;

// Entry point for the application
int main() {
    // Set up a hook to listen for keyboard events
    hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, hInstance, 0);
    if (hook == NULL) {
        MessageBox(NULL, _T("Failed to install hook!"), _T("Error"), MB_ICONERROR);
        return 1;
    }

    // Message loop to keep the program running in the background
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Clean up hook before exiting
    UnhookWindowsHookEx(hook);
    return 0;
}

// Keyboard hook procedure to monitor key presses
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT *p = (KBDLLHOOKSTRUCT *)lParam;

        // Check if Ctrl + Alt + 0 is pressed
        if ((GetAsyncKeyState(VK_CONTROL) & 0x8000) && 
            (GetAsyncKeyState(VK_MENU) & 0x8000) && 
            p->vkCode == '0') {
            // Call the function to show the desktop contents
            ShowDesktopContents();
        }
    }

    return CallNextHookEx(hook, nCode, wParam, lParam);
}

// Function to display contents of the Desktop directory
void ShowDesktopContents() {
    char desktopPath[MAX_PATH];
    TCHAR buffer[MAX_PATH];
    
    // Get the path to the Desktop directory
    if (SHGetFolderPath(NULL, CSIDL_DESKTOPDIRECTORY, NULL, 0, buffer) == S_OK) {
        // Open the Desktop directory using File Explorer
        ShellExecute(NULL, _T("explore"), buffer, NULL, NULL, SW_SHOW);
    } else {
        MessageBox(NULL, _T("Failed to access Desktop folder!"), _T("Error"), MB_ICONERROR);
    }
}
