#include <iostream>
#include <queue>
#include <vector>
using namespace std;
int main()
{
    int n, m;
    cin >> n >> m;
    priority_queue<int, vector<int>, greater<int>> heap;
    vector<int> k;
    int last = __INT_MAX__;
    int first = 0;
    for (int i = 0; i < n; i++)
    {
        int temp;
        cin >> temp;
        if (i < m)
        {
            heap.push(temp);
        }
        else
        {
            if (heap.empty())
            {
                for (auto t : k)
                    heap.push(t);
                k.clear();
                cout << endl;
                first = 0;
            }
            int min = heap.top();
            heap.pop();
            if (first == 0)
            {
                cout << min;
                first = 1;
            }
            else
                cout << " " << min;
            last = min;
            if (temp < last)
            {
                k.push_back(temp);
            }
            else
            {
                heap.push(temp);
            }
        }
    }
    if (n < m)
    {
        for (int i = 0; i < n; i++)
        {
            cout << heap.top() << ' ';
            heap.pop();
        }
    }
    else
    {
        for (int i = 0; i < m; i++)
        {
            if (heap.empty())
            {
                for (auto t : k)
                    heap.push(t);
                k.clear();
                cout << endl;
                first = 0;
            }
            int min = heap.top();
            heap.pop();
            if (first == 0)
            {
                cout << min;
                first = 1;
            }
            else
                cout << " " << min;
            last = min;
        }
    }
}