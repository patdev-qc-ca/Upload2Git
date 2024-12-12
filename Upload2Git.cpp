// Upload2Git.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <Windows.h>
#include <shlwapi.h>
#include <iostream>
#pragma comment(lib,"shlwapi")
#pragma warning (disable: 4996)
char curdir[0x104] = { 0 };
char buffer[4096] = { 0 };
char buff[256];
int main()
{
    std::cout << "Upload2Git!\n";
    SetConsoleTitle("Upload2Git");
    GetCurrentDirectory(0xFF, curdir);
    char szTitle[0x64];
    strcpy(szTitle, PathFindFileName(curdir));
    std::cout << szTitle << std::endl;
    SYSTEMTIME st;
    GetSystemTime(&st);
    char timestamp[0x1F];
    sprintf(timestamp, "%4d%.2d%.2d %.2d:%.2d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute);
    std::cout << timestamp << std::endl;
    HANDLE hConsoleInput = GetStdHandle(STD_INPUT_HANDLE); 
    if (hConsoleInput == INVALID_HANDLE_VALUE) {
        std::cerr << "Erreur lors de l'obtention du handle de la console." << std::endl; return 1;
    }
    std::cout << "Depot existant sur Github : ";

    DWORD bytesRead;
    if (!ReadConsole(hConsoleInput, buff, sizeof(buff) - 1, &bytesRead, NULL)) {
        std::cerr << "Erreur lors de la lecture depuis la console." << std::endl; 
        return 1; 
    }
    buffer[bytesRead] = '\0'; 
    std::cout << "Chaine lue : " << buff << std::endl;
    sprintf(buffer,
    "echo \"# %s\" >> README.md\n \
    git init\n \
    git add *.*\n \
    git commit - m \"%s\"\n \
    git branch - M main \n \
    git remote add origin %s \n \
    git push - u origin main",szTitle,timestamp,szTitle,buff );
    std::cout << buffer << std::endl;

}
