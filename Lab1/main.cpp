#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

struct rpq {
    int r; // receive time
    int p; // produce time
    int q; // cooling time
};

//Sort by diffrence between p + q and r
// 122006
vector<int> algorithmOne(vector<rpq> items) {
    int minT = 1200000;

    vector<pair<int, int>> orderByBiggestProdToDelDIff;

    for (int i = 0; i < items.size(); i++) {
        orderByBiggestProdToDelDIff.push_back(make_pair((items[i].p + items[i].r - items[i].q), i));
    }

    vector<int> order;

    for (int i = 0; i < items.size(); i++) {
        for (int j = i; j < items.size(); j++) {
            // NOTE TO SELF CHECK IF USING FURTHER MINIMIZING OF R WOULD SPEED UP PROGRAM
            if (orderByBiggestProdToDelDIff[i].first > orderByBiggestProdToDelDIff[j].first) {
                auto temp = orderByBiggestProdToDelDIff[i];
                orderByBiggestProdToDelDIff[i] = orderByBiggestProdToDelDIff[j];
                orderByBiggestProdToDelDIff[j] = temp;
            }
        }
    }

    for (auto item: orderByBiggestProdToDelDIff) {
        order.push_back(item.second);
    }
    return order;
}

// Sort by p then find neighbours
//
vector<int> algorithmTwo(vector<rpq> items) {

    vector <pair<rpq,int>> rpqAndOrder;

    for(int i = 0; i < items.size();i++)
    {
        rpqAndOrder.push_back(make_pair(items[i],i));
    }

    for (int i = 0; i < items.size(); i++) {
        for (int j = i; j < items.size(); j++) {
            if (rpqAndOrder[i].first.p > rpqAndOrder[j].first.p) {
                auto temp = rpqAndOrder[i].first.p;
                rpqAndOrder[i].first.p = rpqAndOrder[j].first.p;
                rpqAndOrder[j].first.p = temp;
            }
        }
    }

    for(int i = 1;i < items.size()-1;i++)
    {
        int minRQ=min(rpqAndOrder[i].first.r,rpqAndOrder[i].first.q);
        int prevMinRQ = min(rpqAndOrder[i-1].first.r,rpqAndOrder[i-1].first.q);
        int nextMinRQ = min(rpqAndOrder[i+1].first.r,rpqAndOrder[i+1].first.q);
        if(minRQ < prevMinRQ)
        {
            auto temp = rpqAndOrder[i].first.p;
            rpqAndOrder[i].first.p = rpqAndOrder[i+1].first.p;
            rpqAndOrder[i+1].first.p = temp;
        }
    }

    vector <int> order;

    for (auto item: rpqAndOrder) {
        order.push_back(item.second);
    }

    return order;
}

int countCMAXbyOrder(vector<rpq> data) {
    auto order=algorithmTwo(data);
    int t = 0;
    int cmax = 0;
    for (int i = 0; i < order.size(); i++) {
        auto rpq = data[order[i]];
        t = max(t, rpq.r) + rpq.p;
        cmax = max(t + rpq.q, cmax);
    }
    return cmax;
}

int countCMAXbyOrder(vector<rpq> data,vector<int> order) {
    int t = 0;
    int cmax = 0;
    for (int i = 0; i < order.size(); i++) {
        auto rpq = data[order[i]];
        t = max(t, rpq.r) + rpq.p;
        cmax = max(t + rpq.q, cmax);
    }
    return cmax;
}

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
        cout << temp.r << " " << temp.p << " " << temp.q << "\n";
    }
}

int countCMax(vector<rpq> data) {
    int t = 0;
    int cmax = 0;
    for (auto rpq: data) {
        t = max(t, rpq.r) + rpq.p;
        cmax = max(t + rpq.q, cmax);
    }
    return cmax;
}


int main() {
    ifstream data;
    data.open("../data.txt", ifstream::in);
    //cout << data.is_open() << "\n";

    vector<rpq> data0;
    vector<rpq> data1;
    vector<rpq> data2;
    vector<rpq> data3;
    vector<rpq> data4;

    while (data.good()) {
        string shouldBe24;
        data >> shouldBe24;
        if(shouldBe24 == "7")
        {
            data0 = loadData(data, stoi(shouldBe24));
        }
        if (shouldBe24 == "24" || shouldBe24 == "48") {
            if (data1.empty()) {
                data1 = loadData(data, stoi(shouldBe24));
            } else if (data2.empty())
                data2 = loadData(data, stoi(shouldBe24));
            else if (data3.empty())
                data3 = loadData(data, stoi(shouldBe24));
            else
                data4 = loadData(data, stoi(shouldBe24));
        }
    }

    cout << countCMAXbyOrder(data0) << "\n";

   //

   cout << countCMAXbyOrder(data1) << " " <<  countCMAXbyOrder(data2) << " " <<
            countCMAXbyOrder(data3) << " " << countCMAXbyOrder(data4) <<"\n";

    cout << countCMAXbyOrder(data1) + countCMAXbyOrder(data2) +
            countCMAXbyOrder(data3) + countCMAXbyOrder(data4) << "\n";

   /*
    cout << "Data 1:\n";
    printData(data1);
    cout << "Data 2:\n";
    printData(data2);
    cout << "Data 3:\n";
    printData(data3);
    cout << "Data 4:\n";
    printData(data4);

    cout << countCMax(data1) + countCMax(data2) + countCMax(data3) + countCMax(data4);
    */
    return 0;
}
