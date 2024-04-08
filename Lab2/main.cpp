#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>

using namespace std;

struct pwd {
    int p;
    int w;
    int d;
};

int cost(int costOfRest, int p, int w, int d, int t) {
    t += p;
    if (t > d) {
        t -= d;
    } else {
        t = 0;
    }
    return costOfRest + t * w;
}

int countCMax(int indexToIgnore, vector<int> indexes) {
    int index = 0;
    for (int i = 0; i < indexes.size(); i++) {
        if (indexes[i] != indexToIgnore) {
            index += indexes[i];
        }
    }
    return index;
}

int main() {
    ifstream data;
    data.open("../Lab2/data.txt", ifstream::in);

    while (!data.eof())
    {
        string line;
        getline(data, line);
        if(!line.contains("data"))
            continue;
        int n;
        data >> n;

        pwd pwd[n];

        for (int i = 0; i < n; i++) {
            data >> pwd[i].p;
            data >> pwd[i].w;
            data >> pwd[i].d;
        }


        const int caseN = int(pow(2, n));

        int minC[caseN];
        minC[0] = 0;

        // 9 - A + D == pwd[0][0] + pwd[3][0]
        // 1 - A 2^0 A + B = 3 A + C = 5
        // 2 - B 2^1 B + C = 6
        // 4 - C 2^2
        // 8 - D 2^3 A+B+C=7 A + B = 1 + 2 + C A + B B + C A + C

        int t = 0;

        for (int i = 1; i < caseN; i++) {
            int minPen = 1000000;

            for (int val =1, b = 0; val <= i; b++, val =  1 << b){
                int addTime = 0;
                int bitSum = i - val & val;
                if((bitSum) == val) {
                    //cout << (i & val) << "\n";
                    continue;
                }
                for(int j = 0; j < n; j++){
                    if((i - val) & (1 << j)){
                        addTime += pwd[j].p;
                    }
                }

                //cout << i << " " << i - val << " " << val << " | ";

                int additionalSum = minC[i - val];
                int cMax = cost(additionalSum, pwd[b].p, pwd[b].w, pwd[b].d, addTime);
                if (cMax < minPen) {
                    minPen = cMax;
                }
            }
            //cout << "\n";
            minC[i] = minPen;
        }

        cout << minC[caseN - 1] << "\n";
    }
}