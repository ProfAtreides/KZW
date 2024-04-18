#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <chrono>
#include <vector>
#include <algorithm>

using namespace std;

int cost()
{
    int cost=0;
    return cost;
}

int CMax(int n, int m, int** matrix,vector <int> order)
{
    int CMax=0;

    int *t = new int[m] {0};

    for(int i =0;i<n;i++)
    {
        int tempTime = t[0];
        for(int j=0;j<m;j++)
        {
            tempTime = max(tempTime,t[j]);
            tempTime += matrix[order[i]][j];
            //cout << t[j] << "|";
            t[j] = tempTime;
            //cout << t[j] << " ";
        }
        //cout <<"\n";
    }

    CMax = t[m-1];

    delete[] t;

    return CMax;
}

int* returnBigger(int a[2],int b[2]){
    if(a[1] < b[1])
    {
        return a;
    }
    else
    {
        return b;
    }
}

vector<int> sortByWeight(int n, int m, int** matrix)
{
    vector <pair<int,int>> order;

    for(int i = 0;i<n;i++)
    {
        int sum = 0;
        for(int j = 0;j<m;j++)
        {
            sum += matrix[i][j];
        }
        order.push_back(make_pair(i,sum));
    }

    sort(order.begin(), order.end(), [](pair<int, int> a, pair<int, int> b){
        return a.second > b.second;
    });

    vector <int> result;

    for (auto i : order)
    {
        result.push_back(i.first);
    }

    return result;
}

int main()
{
    ifstream data;
    data.open("../Lab3/data.txt", ifstream::in);

    int n,m;
    data >> n >> m;

    int** matrix;
    matrix =  new int*[n];

    for(int i = 0;i<n;i++)
    {
        matrix[i] = new int[m];
        for(int j=0;j<m;j++)
        {
            data >> matrix[i][j];
        }
    }

    vector <int> order;
    vector <int> weights = sortByWeight(n,m,matrix);

    order.push_back(weights[0]);

    for(int i =1;i<n;i++)
    {
        //order.push_back(weights[i]);
        int index = weights[i];
        int minCMax = 5000;
        vector <int> bestOrder;
        for(int j = 0;j<order.size() + 1;j++)
        {
            auto temp = order;
            temp.insert(temp.begin()+j,index);
            auto curCMax = CMax(i+1,m,matrix,temp);
            if(curCMax < minCMax)
            {
                minCMax = curCMax;
                bestOrder = temp;
            }
        }
        order = bestOrder;
    }

    for(int i = 0;i<n;i++)
    {
        cout << order[i] << " ";
    }

    cout << "\n" << CMax(n,m,matrix,order) << "\n";

    delete matrix;
}