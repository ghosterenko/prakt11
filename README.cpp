#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include <stdlib.h>

using namespace std;

#define MAX_LOGS 1000
#define MAX_TEXT 128

string messages[3] = {
    "Вошел в систему",
    "Вышел из системы",
    "Ошибка входа в систему"
};

struct LogRecord {
    DWORD IDT = 0;
    int priority = 0;
    DWORD tick = 0;

    char message[MAX_TEXT] = "";
};

struct LogBuffer {
    LogRecord records[MAX_LOGS];
    LONG index = 0;
};
DWORD Tid[4] = { 1, 2, 3, 4 };
HANDLE T[4];

LogBuffer buffer;

void Logger() {
    srand(time(NULL));
    int id = rand() % 3;
    LogRecord record;
    record.IDT = GetCurrentThreadId();
    record.priority = GetThreadPriority(GetCurrentThread());
    
    string mess = "[" + to_string(record.IDT) + ", " + to_string(record.priority) + "] - " + record.message[id] + " (" + to_string(record.tick) + "ms).";
    for (int i = 0; i < mess.size(); i++)
    {
        record.message[i] += mess[i];
    }
    buffer.records[buffer.index] = record;
    buffer.index++;

    int time = rand() % 100;
    Sleep(time < 10 ? 10 : time);
}
void Seeker() {
    int temp = 0;
    for (int i = buffer.index; i > buffer.index; i--)
    {
        temp++;
        if (temp == 5) {
            Sleep(100);
        }
        else {
            cout << buffer.records[i].message << endl;
        }
    }
}

int main()
{
    setlocale(LC_ALL, "ru");

    T[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Logger, NULL, NULL, &Tid[0]);
    if (T[0] == NULL) {
        cout << "Ошибка";
    }
    T[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Logger, NULL, NULL, &Tid[1]);
    if (T[1] == NULL) {
        cout << "Ошибка";
    }
    T[2] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Logger, NULL, NULL, &Tid[2]);
    if (T[2] == NULL) {
        cout << "Ошибка";
    }
    T[3] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Seeker, NULL, NULL, &Tid[3]);
    if (T[3] == NULL) {
        cout << "Ошибка";
    }

    if (!SetThreadPriority(T[0], THREAD_PRIORITY_HIGHEST)) {
        cout << "Ошибка";
    }
    if (!SetThreadPriority(T[1], THREAD_PRIORITY_NORMAL)) {
        cout << "Ошибка";
    }
    if (!SetThreadPriority(T[2], THREAD_PRIORITY_BELOW_NORMAL)) {
        cout << "Ошибка";
    }
    if (!SetThreadPriority(T[3], THREAD_PRIORITY_IDLE)) {
        cout << "Ошибка";
    }
    
    WaitForMultipleObjects(4, T, TRUE, INFINITE);
}
