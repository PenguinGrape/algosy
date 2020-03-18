#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>


struct file_string {
    char* string;
    int value;
    unsigned int length;
};

file_string* arr;

using namespace std;
bool check_string(const char* inp);
void quicksort(int start, int end);


int main(int argc, char* argv[]) {
    if (argc != 3) {
        return 1;
    }
    HANDLE rfile = CreateFileA(argv[1], GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (rfile == INVALID_HANDLE_VALUE) {
        return 2;
    }
    DWORD filesizeh;
    DWORD filesizel = GetFileSize(rfile, &filesizeh);
    if (filesizel == INVALID_FILE_SIZE) {
        CloseHandle(rfile);
        return 2;
    }
    size_t filesize = (size_t)filesizeh << sizeof(DWORD) * 8 | filesizel; // FUCK WINDOWS DATA TYPES
    if (filesize == 0) {
        return 3;
    }
    HANDLE mapped = CreateFileMapping(rfile, nullptr, PAGE_READONLY, 0, 0, nullptr);
    if (mapped == nullptr) {
        CloseHandle(rfile);
        return 2;
    }
    auto filecontent = (char*)MapViewOfFile(mapped, FILE_MAP_READ, 0, 0, filesize);
    if (filecontent == nullptr) {
        CloseHandle(mapped);
        CloseHandle(rfile);
        return 2;
    }
    long count = strtol(filecontent, nullptr, 0);
    if (count < 0) {
        return 3;
    }
    unsigned short cindex = 0;
    while (filecontent[cindex] != '\n' && filecontent[cindex] != '\r' && cindex < filesize) {
        if (filecontent[cindex] < '0' || filecontent[cindex] > '9') {
            return 3;
        }
        cindex++;
    }
    if (count == 0) {
        if (filecontent[0] != '0') {
            return 3;
        }
        else {
            FILE* fpw = fopen(argv[2], "wb");
            if (fpw == nullptr) {
                return 2;
            }
            if (fprintf(fpw, "%i\r\n", count) < 0) {
                return 2;
            }
            return 0;
        }
    }
    arr = new file_string[count];
    unsigned int index = 0;
    for (size_t i = 0; i < filesize; i++) {
        if (filecontent[i] == '\n') {
            if (index < count) {
                arr[index].string = filecontent + i + 1;
                if (check_string(arr[index].string)) {
                    return 3;
                }
                arr[index].value = strtol(arr[index].string, nullptr, 0);
                if (arr[index].value < 1 && arr[index].string[0] != '0') {
                    return 3;
                }
            }
            index++;
            if (index > 1 && index <= count) {
                arr[index - 2].length = arr[index - 1].string - arr[index - 2].string;
            }
        }
    }
    if (index < count) {
        return 3;
    }
    if (index > count) {
        if (index - count > 1) {
            return 3;
        }
        else {
            if (filecontent[filesize - 1] != '\n') {
                return 3;
            }
        }
    }
    size_t write_index = arr[0].string - filecontent;
    arr[count - 1].length = filecontent + filesize - arr[count - 1].string;
    if (arr[count - 1].string[arr[count - 1].length - 1] == '\n') {
        if (arr[count - 1].string[arr[count - 1].length - 2] == '\r') {
            arr[count - 1].length -= 2;
        }
        else {
            arr[count - 1].length -= 1;
        }
    }
    char* str_crlf = new char[arr[count - 1].length + 2];
    memcpy(str_crlf, arr[count - 1].string, arr[count - 1].length);
    memcpy(str_crlf + arr[count - 1].length, "\r\n", 2);
    arr[count - 1].string = str_crlf;
    arr[count - 1].length += 2;
    quicksort(0, count - 1);
    HANDLE wfile = CreateFileA(argv[2], GENERIC_READ | GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (wfile == INVALID_HANDLE_VALUE) {
        return 2;
    }
    HANDLE wmapped = CreateFileMapping(wfile, nullptr, PAGE_READWRITE, filesizeh, filesizel, nullptr);
    if (wmapped == nullptr) {
        CloseHandle(wfile);
        return 2;
    }
    auto write_to = (char*)MapViewOfFile(wmapped, FILE_MAP_WRITE, 0, 0, filesize);
    memcpy(write_to, filecontent, write_index);
    for (unsigned long i = 0; i < count; i++) {
        memcpy(write_to + write_index, arr[i].string, arr[i].length);
        write_index += arr[i].length;
    }
    return 0;
}


bool check_string(const char* inp) {
    unsigned char frst = inp[0];
    if (frst < '0' || frst > '9') {
        return true;
    }
    int i = 1;
    while (inp[i] != '\n') {
        if (inp[i] != ' ') {
            if (inp[i] < '0' || inp[i] > '9') {
                return true;
            }
        }
        else {
            return false;
        }
        i++;
    }
    return false;
}


void quicksort(int start, int end) {
    int l = start;
    int r = end;
    int pivot = arr[(l + r) / 2].value;
    while (l <= r) {
        while (arr[l].value < pivot) {
            l++;
        }
        while (arr[r].value > pivot) {
            r--;
        }
        if (l <= r) {
            file_string tmp = arr[l];
            arr[l] = arr[r];
            arr[r] = tmp;
            l++;
            r--;
        }
    }
    if (r > start) {
        quicksort(start, r);
    }
    if (l < end) {
        quicksort(l, end);
    }
}
