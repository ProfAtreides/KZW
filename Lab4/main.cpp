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

int main() {
    ifstream data;
    ofstream log;

    data.open("../Lab4/data.txt", ifstream::in);
    log.open("../Lab4/log.txt", ofstream::out);

    vector<int> order;

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

        for(int i = 0; i < 10000;i++) {
            auto tempOrder = order;

            int firstIndex = rand()%n, secondIndex = rand()%n;

            swap(tempOrder[firstIndex], tempOrder[secondIndex]);

            int currCMAX = CMax(n, m, matrix, tempOrder);

            if(i%10000 && t > 0.66)
            {
                t *= 0.81;
            }


            int delta = currCMAX - lastCMax;

            if (delta < 0) {
                lastCMax = currCMAX;
                order = tempOrder;
            }
            else {
                double chance = exp(-delta / t);
                double randomChance = rand() % 1000 / 1000.0;
                if (randomChance <= chance)
                {
                    lastCMax = currCMAX;
                    order = tempOrder;
                }
            }
            if(bestCMAX > currCMAX)
            {
                bestCMAX = currCMAX;
                bestT = t;
            }
            log << currCMAX <<" "<< i << "\n";
        }

        cout << bestCMAX << " " << bestT <<" "<< t << "\n";



}

