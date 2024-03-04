#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

struct rpq {
    int r;
    int p;
    int q;
};

vector<rpq> loadData(ifstream &stream, int n) {
    vector<rpq> data;
    for (int i = 0; i < n; i++) {
        string currentValue;
        rpq rpqInLine;
        stream >> rpqInLine.r;
        stream >> rpqInLine.p;
        stream >> rpqInLine.q;
        data.push_back(rpqInLine);
    }
    return data;
}

void printData(vector<rpq> data) {
    for (auto temp: data) {
        cout << temp.r << " " << temp.p << " " <<  temp.q << "\n";
    }
}

int countCMax(vector <rpq> data)
{
    int t = 0;
    int cmax = 0;
    for(auto rpq: data)
    {
        t = max(t,rpq.r) + rpq.p;
        cmax = max(t+rpq.q,cmax);
    }

    return cmax;
}



int main() {
    ifstream data;

    data.open("../data.txt",ifstream::in);

    cout<<data.is_open()<<"\n";

    vector<rpq> data1;
    vector<rpq> data2;
    vector<rpq> data3;
    vector<rpq> data4;

    while (data.good()) {
        string shouldBe24;
        data >> shouldBe24;
        if (shouldBe24 == "24" || shouldBe24 == "48") {
            if (data1.empty()) {
                data1 = loadData(data, stoi(shouldBe24));
            } else if (data2.empty())
                data2 = loadData(data,stoi(shouldBe24));
            else if (data3.empty())
                data3 = loadData(data,stoi(shouldBe24));
            else
                data4 = loadData(data,stoi(shouldBe24));
        }
    }

    cout << "Data 1:\n";
    printData(data1);
    cout << "Data 2:\n";
    printData(data2);
    cout << "Data 3:\n";
    printData(data3);
    cout << "Data 4:\n";
    printData(data4);

    cout << countCMax(data1) + countCMax(data2) + countCMax(data3) + countCMax(data4);

    return 0;
}
