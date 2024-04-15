#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <chrono>

using namespace std;

int cost()
{
    int cost=0;
    return cost;
}

int CMax(int n, int m, int** matrix,const int* order)
{
    /*for(int i = 0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }*/

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

    delete t;

    return CMax;
}

int main()
{
    ifstream data;
    data.open("../Lab3/data.txt", ifstream::in);

    int n,m;
    data >> n >> m;

    int** matrix;
    matrix =  new int*[n];

    int order[] = {0,3,2,1};

    for(int i = 0;i<n;i++)
    {
        matrix[i] = new int[m];
        for(int j=0;j<m;j++)
        {
            data >> matrix[i][j];
           // cout << matrix[i][j] << " ";
        }
      //cout << "\n";
    }

   //cout << "\n";

    cout << CMax(n,m,matrix,order) << "\n";

    delete matrix;
}