#include <iostream>
#include <string>
#include <functional>

#include <omp.h>
#include <chrono>

using namespace std;


void s_sort(int *a, int n){
    int last;
    for (int x=0; x<n; x++){
        last = n;
        for (int y=0; y < last; y++){
            if(a[y] > a[y+1]){
                swap(a[y], a[y+1]);
            }
        }
        last = last -1;
    }

}

int main(){

    int *a,n;

    cout << "Enter Length Of Array\n";

    cin >> n;
    int no;
    for (int x=0; x<n; x++){
        cout << "Enter no " << x << "\n";
        cin >> no;
        a[x] = no;
    }


    for (int x=0; x<n; x++){
        cout << a[x] << " ,";
    }

    cout << "\n";

    cout << "After Sorting Array\n";

    s_sort(a,n);

    for (int x=0; x<n; x++){
        cout << a[x] << " ,";
    }

    cout << "\n";

    return 0;
}