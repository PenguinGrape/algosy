#include <iostream>
using namespace std;

int* arr;
char** strings;
void quicksort(int start, int end);


/* как показывает практика - так почему-то дольше чем 2 массива
struct element {
    long value;
    char* string
 */

int main(int argc, char *argv[]) {
    if (argc != 3) {
        return 1;
    }
    int count;
    FILE *fp;
    fp = fopen(argv[1], "r");
    if (fp == nullptr) {
        return 2;
    }
    fseeko64(fp, 0, SEEK_END);
    size_t filesize = ftello64(fp);
    char *filecontent = new char[filesize + 1];
    filecontent[filesize] = '\0';
    fseeko64(fp, 0, SEEK_SET);
    if (fread(filecontent, filesize, 1, fp) != 1) {
        return 2;
    }
    count = (int)strtol(filecontent, nullptr, 10);
    arr = new int [count];
    strings = new char* [count];
    int index = 0;
    for (size_t i = 0; i < filesize; i++) {
        if (filecontent[i] == '\n') {
            filecontent[i] = '\0';
            if (index < count) {
                strings[index] = filecontent + i + 1;
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
    quicksort(0, count);
    FILE *fpw;
    fpw = fopen(argv[2], "w");
    if (fpw == nullptr){
        return 2;
    }
    if (fprintf(fpw, "%i\n", count) < 0) {
        return 2;
    }
    for (int i = 0; i < count; i++){
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
