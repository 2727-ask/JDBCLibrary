#include <bits/stdc++.h>
#include <omp.h>

using namespace std;


void s_sort(int *a, int n){
    for (int i = 0; i<n; i++){
        for (int j=0; j<n-i; j++){
            if(a[j] > a[j+1]){
                swap(a[j],a[j+1]);
            }
        }
    }
}


void p_sort(int *a, int n){
    for (int i = 0; i<n; i++){
        int first = n - i; 
        #pragma omp parallel for shared(a,first) num_threads(2) 
        for (int j=0; j<n-i; j++){
            if(a[j] > a[j+1]){
                swap(a[j],a[j+1]);
            }
        }
    }
}



string time_calculator(int *a, int n, bool isParallel){
    auto start = chrono::high_resolution_clock::now();
    if(isParallel){
        p_sort(a,n);
    }else{
        s_sort(a,n);
    }  
    auto stop = chrono::high_resolution_clock::now();
    auto result = stop - start;
    auto duration = result;
    return to_string(duration.count());
}

int main(){

    int n;
    cout << "Enter Length Of Array\n";
    cin >> n;
    int *a = new int[n];

    for (int x = 0; x < n+1; x++){
        cout << "Enter no =" << x << " ";
        cin >> a[x];
    }

    cout << "Array Before Sorting \n";
    for (int x = 0; x < n+1; x++){
        cout << a[x] << " ";
    }

    cout << "\n";

    omp_set_num_threads(2);
    cout << "Time Required for Execution " << time_calculator(a, n, true) << " ms/n\n";

    cout << "Array After Sorting \n";
    for (int x = 0; x < n+1; x++){
        cout << a[x] << " ";
    }

    cout << "\n";



    return 0;
}