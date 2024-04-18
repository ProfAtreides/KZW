#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <chrono>
#include <vector>
#include <algorithm>

using namespace std;

int cost() {
    int cost = 0;
    return cost;
}

int iter = 0;

int CMax(int n, int m, int **matrix, vector<int> order) {
    int CMax = 0;

    int *t = new int[m]{0};

    for (int i = 0; i < n; i++) {
        int tempTime = t[0];
        for (int j = 0; j < m; j++) {
            tempTime = max(tempTime, t[j]);
            tempTime += matrix[order[i]][j];
            //cout << t[j] << "|";
            t[j] = tempTime;
            //cout << t[j] << " ";
        }
        //cout <<"\n";
    }

    CMax = t[m - 1];

    delete[] t;

    return CMax;
}

vector<int> sortByWeight(int n, int m, int **matrix) {
    vector<pair<int, int>> order;

    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = 0; j < m; j++) {
            sum += matrix[i][j];
        }
        order.push_back(make_pair(i, sum));
    }

    sort(order.begin(), order.end(), [](pair<int, int> a, pair<int, int> b) {
        if(a.second == b.second)
        {
            return a.first < b.first;
        }
        return a.second > b.second;
    });

    vector<int> result;

    for (auto i: order) {
        result.push_back(i.first);
    }

    return result;
}

int main() {
    ifstream data;
    ofstream log;

    data.open("../Lab3/data.txt", ifstream::in);
    log.open("../Lab3/log.txt", ofstream::out);



    int correct=0,wrong=0,weird=0;

    while (!data.eof()) {
        auto start = chrono::high_resolution_clock::now();
        string tempString;
        data >> tempString;

        cout << tempString.substr(4) << "\n";

        int n, m;
        data >> n >> m;

        int **matrix;
        matrix = new int *[n];

        for (int i = 0; i < n; i++) {
            matrix[i] = new int[m];
            for (int j = 0; j < m; j++) {
                data >> matrix[i][j];
            }
        }

        vector<int> order;
        vector<int> weights = sortByWeight(n, m, matrix);

        //order.push_back(weights[0]);

        for (int i = 0; i < n; i++) {
            //order.push_back(weights[i]);
            int index = weights[i];
            int minCMax = 1000000;
            vector<int> bestOrder;
            for (int j = 0; j < int(order.size()) + 1; j++) {
                auto temp = order;
                temp.insert(temp.begin() + j, index);
                auto curCMax = CMax(i + 1, m, matrix, temp);
                if (curCMax < minCMax) {
                    minCMax = curCMax;
                    bestOrder = temp;
                }
            }
            order = bestOrder;
        }

        data >> tempString;

        int corCMAX;
        data >> corCMAX;
        int thisCMAX = CMax(n, m, matrix, order);

        vector<int> corOrder;

        for (int i = 0; i < n; i++) {
            int helper;
            data >> helper;
            corOrder.push_back(helper - 1);
        }
        //cout << "\n" << CMax(n,m,matrix,order) << "\n";

        log << iter << "\n";
        for(int i  = 0;i<n;i++)
        {
            log << order[i] << " ";
        }



        if (corCMAX == thisCMAX) {
            bool orderIsCorrect = true;
            for(int i = 0;i<n;i++)
            {
                if(corOrder[i] != order[i])
                {
                    cout << "ERROR\n\n";
                    orderIsCorrect = false;
                    break;
                }
            }
            if(orderIsCorrect)
            {
                correct++;
                cout << "OK\n";
            }
        } else if (corCMAX > thisCMAX) {
            weird++;
            cout << corCMAX << " | " << thisCMAX << "\n";
        } else {
            wrong++;
            cout << "ERROR\n";
        }
        iter++;
        if (iter == 121) {
            break;
        }

        auto elapsed = chrono::high_resolution_clock::now() - start;
        cout << chrono::duration_cast<chrono::milliseconds>(elapsed) << "\n\n";

        //delete matrix;
    }
}