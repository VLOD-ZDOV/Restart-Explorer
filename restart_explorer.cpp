#include <cstdlib>  
#include <iostream> 
#include <Windows.h> 
#include <string> 
#include <direct.h>   // Для _wgetcwd
#include <Shlwapi.h>  // Для PathFileExistsW
#pragma comment(lib, "Shlwapi.lib") // Подключение библиотеки Shlwapi

using namespace std;

void restartExplorer() {
    // Kills and restarts the explorer process
    system("taskkill /F /IM explorer.exe");
    system("start explorer.exe");
}

void addToStartup() {
    wchar_t* currentDir = _wgetcwd(NULL, 0);      // Получаем текущую рабочую директорию (wide characters)
    wstring path = wstring(currentDir) + L"\\no"; // Преобразуем в широкую строку и добавляем L перед строкой
    delete[] currentDir;                          // Освобождаем выделенную память

    if (!PathFileExistsW(path.c_str())) {         // Используем PathFileExistsW для wide characters
        wcout << L"Adding program to startup..." << endl;
        // Код добавления в автозапуск
    }
    else {
        wcout << L"Skipping adding to startup because 'no' file exists." << endl;
    }
}

int main() {
    // Регистрируем горячую клавишу и функцию
    if (RegisterHotKey(NULL, 1, MOD_ALT | MOD_SHIFT, 0x45)) { // 0x45 - виртуальный код клавиши E
        MSG msg = { 0 };
        while (GetMessage(&msg, NULL, 0, 0) != 0) {
            if (msg.message == WM_HOTKEY)
                restartExplorer();
        }
    }
    addToStartup();
    // Бесконечный цикл для поддержания работы программы
    while (true) {
        Sleep(1000); // Уменьшение использования CPU с помощью задержки в 1 секунду
    }
}