﻿#include <Windows.h>
#include <iostream>
#include <string>
#include <thread>
#include <libloaderapi.h>

using namespace std;

void get_proc_id(const char* window_title, DWORD& process_id)
{
    GetWindowThreadProcessId(FindWindow(NULL, window_title), &process_id);
}

void error(const char* error_title, const char* error_message)
{
    MessageBox(NULL, error_message, error_title, NULL);
    exit(-1);
}

bool file_exists(string file_name)
{
    struct stat buffer;
    return (stat(file_name.c_str(), &buffer) == 0);
}

int main()
{
    {
        DWORD proc_id = NULL;
        char dll_path[MAX_PATH];
        const char* dll_name = "Your.Dll"; // name of the dll/cheat that the injects in process below ⤵
        const char* window_title = "Game Name"; // open your game and hover over it in ur taskbar and you will see the window title,

        if (!file_exists(dll_name))
        {
            error(":(", "DLL Does Not Exist!"); // add your dll in \x64\Debug then
        }

        if (!GetFullPathName(dll_name, MAX_PATH, dll_path, nullptr))
        {
            error(":(", "Failed To Get Path:("); //delete everything in \x64\Debug and build (make sure its on debug)
        }
        get_proc_id(window_title, proc_id);
        if (proc_id == NULL)
        {
            error(":(", "Failed To Find Process"); // make sure "window_title" is the name of the window
        }

        HANDLE h_process = OpenProcess(PROCESS_ALL_ACCESS, NULL, proc_id);
        if (!h_process)
        {
            error(":(", "Failed To Inject!");
        }

        void* allocated_memory = VirtualAllocEx(h_process, nullptr, MAX_PATH, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
        if (!allocated_memory)
        {
            error(":(", "Failed to allocate memory");
        }

        if (!WriteProcessMemory(h_process, allocated_memory, dll_path, MAX_PATH, nullptr))
        {
            error(":(", "Failed to process memory");
        }

        HANDLE h_thread = CreateRemoteThread(h_process, nullptr, NULL, LPTHREAD_START_ROUTINE(LoadLibraryA), allocated_memory, NULL, nullptr);
        if (!h_thread)
        {
            error(":(", "Failed To Create Remote Thread");
        }


        CloseHandle(h_process);
        VirtualFreeEx(h_process, allocated_memory, NULL, MEM_RELEASE);
        MessageBox(0, "successfully Injected With Saturn!\n", ":)", 0);
    }
}