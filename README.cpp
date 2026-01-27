# #include <iostream>
#include <Windows.h>

#define MAX_LOGS 1000
#define MAX_TEXT 128

struct LogRecord {
    DWORD threadId = 0;
    int priority = 0;
    DWORD tick = 0;
    char message[MAX_TEXT];
};

struct LogBuffer {
    LogRecord records[MAX_LOGS];
    LONG index = 0;
};

HANDLE T[4];
LogBuffer buffer;
char t1[] = "Пользователь вошел ";
char t2[] = "Ошибка входа ";
char t3[] = "Пользователь вышел ";

void logger() {
    srand(time(NULL));
    LogRecord lr;
    int time = rand() % 100;

    char res[MAX_TEXT];
    strcpy_s(res, t1);
    strcpy_s(lr.message, res);

    buffer.records[buffer.index] = lr;

    buffer.index++;
    Sleep(time < 10 ? 10 : time);
}

void sekeer() {
    if (buffer.index != 0) {
        for (int i = buffer.index; i > 5; i--)
        {
            std::cout << buffer.records[i].message;
            Sleep(100);
        }
    }
}



int main()
{
    T[0] = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(logger), NULL, 0, NULL);
    T[1] = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(logger), NULL, 0, NULL);
    T[2] = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(logger), NULL, 0, NULL);
    T[3] = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(sekeer), NULL, 0, NULL);

    if(!SetThreadPriority(T[0], THREAD_PRIORITY_HIGHEST))
        std::cout << "Ошибка";
    if (!SetThreadPriority(T[1], THREAD_PRIORITY_NORMAL))
        std::cout << "Ошибка";
    if (!SetThreadPriority(T[2], THREAD_PRIORITY_BELOW_NORMAL))
        std::cout << "Ошибка";
    if (!SetThreadPriority(T[3], THREAD_PRIORITY_LOWEST))
        std::cout << "Ошибка";

    WaitForMultipleObjects(4, T, TRUE, INFINITE);
}
