//#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#define _fseeki64 fseeko64
#define _ftelli64 ftello64
using namespace std;


struct element {
    long value;
    char* string;
};


bool check_string(const char* inp);
void heapify(element* arr, int count, int root);


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
    count = (int)strtol(filecontent, nullptr, 10);
    if (count == 0){
        if (filecontent[0] == '0') {
            return 0;
        } else {
            return 3;
        }
    }
    auto *arr = new element [count];
    int index = 0;
    for (size_t i = 0; i < filesize; i++) {
        if (filecontent[i] == '\n') {
            filecontent[i] = '\0';
            if (index < count) {
                arr[index].string = filecontent + i + 1;
                if (check_string(arr[index].string)) {
                    return 3;
                }
                arr[index].value = (int)strtol(arr[index].string, nullptr, 10);
                if (arr[index].value < 1 && arr[index].string[0] != '0') {
                    return 3;
                }
                index++;
            }
        }
    }
    if (index < count) {
        return 3;
    }


    for (int i = count / 2 - 1; i >= 0; i--) {
        heapify(arr, count, i);
    }
    for (int i= count - 1; i >= 0; i--)
    {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
    for (int i = 0; i < count; i++) {
        cout << arr[i].value << endl;
    }
    FILE *fpw;
    fpw = fopen(argv[2], "wb");
    if (fpw == nullptr){
        return 2;
    }
    if (fprintf(fpw, "%i\n", count) < 0) {
        return 2;
    }
    for (int i = 0; i < count; i++) {
        if (fprintf(fpw, "%s\n", arr[i].string) < 0) {
            return 2;
        }
    }
    return 0;
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


void heapify(element* arr, int count, int root) {
    int max = root;
    int l = 2 * root + 1;
    int r = 2 * root + 2;
    if (l < count && arr[l].value > arr[max].value)
        max = l;
    if (r < count && arr[r].value > arr[max].value)
        max = r;
    if (max != root)
    {
        swap(arr[root], arr[max]);
        heapify(arr, count, max);
    }
}