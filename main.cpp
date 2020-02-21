#include <ctime>
#include <iostream>
using namespace std;


struct element {
    long value;
    char* string;
};


element* mergesort(element *buf1, element *buf2, int l, int r) {
    if (l == r){
        buf2[l] = buf1[l];
        return buf2;
    }
    int m = (r + l) / 2;
    element *lb = mergesort(buf1, buf2, l, m);
    element *rb = mergesort(buf1, buf2, m + 1, r);
    element *to;
    if (lb == buf2) {
        to = buf1;
    } else {
        to = buf2;
    }
    int curl = l;
    int curr = m + 1;
    for (int i = l; i < r; i++) {
        if (curr > r) {
            to[i] = lb[curl];
            curl++;
            continue;
        }
        if (curl > m) {
            to[i] = rb[curr];
            curr++;
            continue;
        }
        if (lb[curl].value < rb[curr].value) {
            to[i] = lb[curl];
            curl++;
        } else {
            to[i] = rb[curr];
            curr++;
        }
    }
    if (rb[r].value > lb[m].value){
        to[r] = rb[r];
    } else {
        to[r] = lb[m];
    }
    return to;
}


int main(int argc, char *argv[]) {
    cout << "program started at: " << time(nullptr) << endl;
    if (argc != 3 && false){
        return 1;
    }
    int count;
    FILE *fp;
    fp = fopen("/media/veracrypt1/temp/algosy/short-numbers", "r");
    if (fp == nullptr) {
        return 2;
    }
    fseeko64(fp, 0, SEEK_END);
    size_t filesize = ftello64(fp);
    char *filecontent = new char[filesize];
    fseeko64(fp, 0, SEEK_SET);
    if (fread(filecontent, filesize, 1, fp) != 1) {
        return 2;
    }
    count = (int)strtol(filecontent, nullptr, 10);
    auto *arr = new element [count];
    int index = 0;
    for (size_t i = 0; i < filesize; i++) {
        if (filecontent[i] == '\n' && index < count) {
            filecontent[i] = '\0';
            arr[index].string = filecontent + i +1;
            arr[index].value = strtol(arr[index].string, nullptr, 10);
            if (arr[index].value == 0 && arr[index].string[0] != '0') {
                cout << arr[index].string << endl;
                return 3;
            }
            index++;
        }
    }
    cout << "reading finished at: " << time(nullptr) << endl;
    if (index < count) {
        return 3;
    }
    auto *barr = new element [count];
    element *result = mergesort(arr, barr, 0, count-1);
    cout << "sorting finished at: " << time(nullptr) << endl;
    FILE *fpw;
    try {
        fpw = fopen("out", "w");
        if (fpw == nullptr){
            return 2;
        }
        for (int i = 0; i < count; i++){
            fprintf(fpw, "%s\n", result[i].string);
        }
    } catch (int exception) {
        return 2;
    }
    cout << "writing finished at: " << time(nullptr) << endl;
    return 0;
}
