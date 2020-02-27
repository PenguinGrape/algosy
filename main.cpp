#include <iostream>
using namespace std;


struct element {
    long value;
    char* string;
};


void heapify(element* arr, int count, int root);
void heapsort(element* arr, int count);


int main(int argc, char *argv[]) {
    if (argc != 3) {
        return 1;
    }
    int count;
    FILE *fp;
    fp = fopen("/media/veracrypt1/temp/algosy/shortest", "r");
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
    auto *arr = new element [count];
    int index = 0;
    for (size_t i = 0; i < filesize; i++) {
        if (filecontent[i] == '\n') {
            filecontent[i] = '\0';
            if (index < count) {
                arr[index].string = filecontent + i + 1;
                arr[index].value = strtol(arr[index].string, nullptr, 10);
                if (arr[index].value == 0 && arr[index].string[0] != '0') {
                    return 3;
                }
                index++;
            }
        }
    }
    if (index < count) {
        return 3;
    }
    heapify(arr, count, 0);

    // sort here
    heapsort(arr, count);
    FILE *fpw;
    fpw = fopen("/media/veracrypt1/temp/algosy/out-h", "w");
    if (fpw == nullptr){
        return 2;
    }
    if (fprintf(fpw, "%i\n", count) < 0) {
        return 2;
    }
    for (int i = 0; i < count; i++){
        if (fprintf(fpw, "%s\n", arr[i].string) < 0) {
            return 2;
        }
    }
    return 0;
}


void heapify(element* arr, int count, int root){
    int max = root;
    int l = 2*root + 1;
    int r = 2*root + 2;
    if (l < count && arr[l].value > arr[max].value) {
        max = l;
    }
    if (r < root && arr[r].value > arr[max].value) {
        max = r;
    }
    if (max != root){
        swap(arr[root], arr[max]);
        heapify(arr, count, root);
    }
}


void heapsort(element* arr, int count)
{
    for (int i = count / 2 - 1; i >= 0; i--) {
        heapify(arr, count, i);
    }
    for (int i=count-1; i>=0; i--)
    {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}
