#include <iostream>
#include <array>
#include <string>
#include <functional>

#include <omp.h>
#include <chrono>

using namespace std;


int s_sort(int *a, int n)
{
    int last = n;
    for (int j = 0; j < n; j++)
    {   
        for (int t = 0; t < last; t++)
        {
            if (a[t] > a[t + 1])
            {
                swap(a[t], a[t + 1]);
            }
        }
        last = last - 1;
    }

    return 0;
}

string executionTime(function<void()> sort_fn){
    auto start = chrono::high_resolution_clock::now();
    sort_fn();
    auto stop = chrono::high_resolution_clock::now();

    auto result = chrono::duration_cast<chrono::milliseconds>(start - stop);

    return to_string(result.count());
}


int main()
{
    int *a, n;
    cout << "Enter Number of Elements in Array\n";
    cin >> n;
    a = new int[n];

    for (int k = 0; k < n + 1; k++)
    {
        cout << "Enter no " << k << " ";
        cin >> a[k];
    }

    for (int l = 0; l < n + 1; l++)
    {
        cout << a[l] << ", ";
    }

    cout << "Total Time Required is" << executionTime([&]{s_sort(a,n);}) << "\n";

    cout << "\nAfter Sorting \n";
    for (int j = 0; j < n + 1; j++)
    {
        cout << a[j] << ", ";
    }

    cout << "\n";

    return 0;
}
