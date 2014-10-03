#include <stdio.h>
#include <windows.h>

int
hello(void) {
    puts("hello world");
}

BOOL WINAPI
DllMain(HINSTANCE hinstDLL, DWORD reason, LPVOID reserved) {
    switch(reason) {
    case DLL_PROCESS_ATTACH:
        puts("Openlf2.dll loading ...");
        break;
    case DLL_PROCESS_DETACH:
        puts("Openlf2.dll unloading ...");
        break;
    }
    return TRUE;
}
