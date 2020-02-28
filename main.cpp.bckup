#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;


int* arr;
char** strings;
void quicksort(int start, int end);
bool check_string(const char* inp);


/* как показывает практика - так почему-то дольше чем 2 массива
 * полагаю из-за обращений к памяти, чтобы еще раз обратиться к памяти (arr[index].FIELD)
struct element {
    long value;
    char* string;
};*/

int main(int argc, char *argv[]) {
    if (argc != 3) {
        return 1;
    }
    int count;
    FILE *fp;
    fp = fopen(argv[1], "rb");
    if (fp == nullptr) {
        return 2;
    }
    _fseeki64(fp, 0, SEEK_END);
    size_t filesize = _ftelli64(fp);
    char *filecontent = new char[filesize + 1];
    filecontent[filesize] = '\0';
    _fseeki64(fp, 0, SEEK_SET);
    if (fread(filecontent, filesize, 1, fp) != 1) {
        return 2;
    }
    count = strtol(filecontent, nullptr, 10);
    if (count == 0){
        if (filecontent[0] == '0') {
            return 0;
        } else {
            return 3;
        }
    }
    arr = new int [count];
    strings = new char* [count];
    int index = 0;
    for (size_t i = 0; i < filesize; i++) {
        if (filecontent[i] == '\n') {
            filecontent[i] = '\0';
            if (index < count) {
                strings[index] = filecontent + i + 1;
                if (check_string(strings[index])) {
                    return 3;
                }
                arr[index] = (int)strtol(strings[index], nullptr, 10);
                if (arr[index] == 0 && strings[index][0] != '0') {
                    return 3;
                }
                index++;
            }
        }
    }
    if (index < count) {
        return 3;
    }
    quicksort(0, count - 1);
    FILE *fpw;
    fpw = fopen(argv[2], "wb");
    if (fpw == nullptr){
        return 2;
    }
    if (fprintf(fpw, "%i\n", count) < 0) {
        return 2;
    }
    for (int i = 0; i < count; i++) {
        if (fprintf(fpw, "%s\n", strings[i]) < 0) {
            return 2;
        }
    }
    return 0;
}


void quicksort(int start, int end) {
    int l = start;
    int r = end;
    int pivot = arr[(l + r) / 2];
    while (l <= r){
        while (arr[l] < pivot) {
            l-=-1;
        }
        while (arr[r] > pivot) {
            r+=-1;
        }
        if (l <= r){
            int tmp = arr[l];
            char *stmp = strings[l];
            arr[l] = arr[r];
            strings[l] = strings[r];
            arr[r] = tmp;
            strings[r] = stmp;
            l-=-1;
            r+=-1;
        }
    }
    if (r > start){
        quicksort(start, r);
    }
    if (l < end){
        quicksort(l, end);
    }
}


bool check_string(const char* inp) {
    unsigned char frst = inp[0];
    if ((frst < '0' || frst > '9') && frst != '-') {
        return true;
    }
    int i = 1;
    if (frst == '-' && inp[1] == ' '){
        return true;
    }
    while (inp[i] != '\n') {
        if (inp[i] != ' ') {
            if (inp[i] < 48 || inp[i] > 57) {
                return true;
            }
        } else {
            return false;
        }
        i++;
    }
    return false;
}