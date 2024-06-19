#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <random>

using namespace std;

int CMax(int n, int m, int **matrix, vector<int> order) {
    int CMax = 0;

    int *t = new int[m]{0};

    for (int i = 0; i < n; i++) {
        int tempTime = t[0];
        for (int j = 0; j < m; j++) {
            tempTime = max(tempTime, t[j]);
            tempTime += matrix[order[i]][j];
            t[j] = tempTime;
        }
    }

    CMax = t[m - 1];

    delete[] t;

    return CMax;
}

void addNewTabu(const vector<int>& newPath,vector<vector<int>>tabuList,int tabuMaxSize){
    if(tabuList.size()>=tabuMaxSize){
        tabuList.erase(tabuList.begin());
    }
    tabuList.push_back(newPath);
}

bool checkForTabu(const vector<int>& path,const vector<vector<int>>&tabuList) {
    for (const auto& tabu : tabuList) {
        if (tabu == path) {
            return true;
        }
    }
    return false;
}

void randTillDifferent(vector<int> &order, const vector <vector<int>>& tabuList) {

    int n = order.size();

    while(true) {
        auto tempOrder = order;
        int firstIndex = rand() % n, secondIndex = rand() % n;
        swap(tempOrder[firstIndex], tempOrder[secondIndex]);
        if (!checkForTabu(tempOrder,tabuList)){
            addNewTabu(tempOrder,tabuList,5);
            break;
        }
    }
}

int main() {
    ifstream data;
    ofstream log, logT;

    data.open("../Lab5/data.txt", ifstream::in);
    log.open("../Lab5/log.txt", ofstream::out);
    logT.open("../Lab5/logT.txt", ofstream::out);

    vector<int> order;

    const int tabuMaxSize = 5;

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

    int lastCMax = 501258;

    for (int i = 0; i < n; i++) {
        order.push_back(i);
    }

    double bestT = -1;
    int bestCMAX = 215125;

    srand(time(NULL));

    double t = 100;

    vector<vector<int>> tabuList;

    const int iter_number = 20000;
    const int reduce_t_every = 10;
    const double cooling_rate = 0.05;

    for (int i = 0; i < iter_number; i++) {
        auto tempOrder = order;

        randTillDifferent(tempOrder,tabuList);

        int currCMAX = CMax(n, m, matrix, tempOrder);

        if (i % reduce_t_every == reduce_t_every - 1) {
            //logT << t << " ";
            t -= cooling_rate;
            //logT << t << "\n";
        }

        double delta = currCMAX - lastCMax;

        if (delta <= 0) {
            lastCMax = currCMAX;
            order = tempOrder;
        } else {
            double chance = exp(-delta / t);
            double randomChance = (rand() % 100) / 100.0;
            logT << chance << " " << randomChance<<  "\n";
            if (randomChance < chance) {
                lastCMax = currCMAX;
                order = tempOrder;
            }
        }
        if (bestCMAX > lastCMax) {
            bestCMAX = lastCMax;
            bestT = t;
        }
        log << lastCMax << " " << i << "\n";
    }

    cout << bestCMAX << " " << bestT << " " << t << "\n";


}

