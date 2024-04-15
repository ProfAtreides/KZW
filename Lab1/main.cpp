#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <chrono>

using namespace std;

struct rpq {
    int r; // receive time
    int p; // produce time
    int q; // cooling time
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
        cout << temp.r << " " << temp.p << " " << temp.q << "\n";
    }
}

void printOrder(vector<int> order) {
    cout << "\n";
    for (int i = 0; i < order.size(); i++) {
        cout << order[i] + 1 << " ";
    }
    cout << "\n";
}


int countCMAXbyOrder(vector<rpq> data, vector<int> order) {
    //printOrder(order);
    int t = 0;
    int cmax = 0;
    for (int i = 0; i < order.size(); i++) {
        auto rpq = data[order[i]];
        t = max(t, rpq.r) + rpq.p;
        cmax = max(t + rpq.q, cmax);
    }
    return cmax;
}

//Sort by difference between p + q and r
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

// tl;dr Schrage after lobotomy
// 112447
vector<int> algorithmTwo(vector<rpq> items) {
    vector<pair<rpq, int>> unusedItems;

    for (int i = 0; i < items.size(); i++) {
        unusedItems.emplace_back(items[i], i);
    }

    int currentTime = 0;

    vector<int> order;

    while (!unusedItems.empty()) {
        vector<int> indexesOfItemsInTime;

        int minTime = 1200000;

        for (int i = 0; i < unusedItems.size(); i++) {
            if (unusedItems[i].first.r < minTime) {
                minTime = unusedItems[i].first.r;
            }
            if (unusedItems[i].first.r <= currentTime) {
                indexesOfItemsInTime.push_back(i);
            }
        }

        if (indexesOfItemsInTime.empty()) {
            currentTime = minTime;
            continue;
        }

        int minTimeAfterP = 1200000;
        int maxTimeAfterQ = -1;
        int indexOfMinPQdiff = -1;
        for (int i = 0; i < indexesOfItemsInTime.size(); i++) {
            int minTimeAfterProductionOfItem = (currentTime > unusedItems[indexesOfItemsInTime[i]].first.r) ?
                                               currentTime + unusedItems[indexesOfItemsInTime[i]].first.p :
                                               unusedItems[indexesOfItemsInTime[i]].first.r +
                                               unusedItems[indexesOfItemsInTime[i]].first.p;
            if (minTimeAfterProductionOfItem < minTimeAfterP &&
                minTimeAfterProductionOfItem + unusedItems[indexesOfItemsInTime[i]].first.q > maxTimeAfterQ) {
                minTimeAfterP = currentTime + unusedItems[indexesOfItemsInTime[i]].first.p;
                maxTimeAfterQ = currentTime +
                                unusedItems[indexesOfItemsInTime[i]].first.p +
                                unusedItems[indexesOfItemsInTime[i]].first.q;
                indexOfMinPQdiff = indexesOfItemsInTime[i];
            }
        }
        if (indexOfMinPQdiff == -1) {
            continue;
        }
        currentTime += unusedItems[indexOfMinPQdiff].first.p;
        order.push_back(unusedItems[indexOfMinPQdiff].second);
        unusedItems.erase(unusedItems.begin() + indexOfMinPQdiff);
    }

    return order;
}

// Removed checking for maximum cooling time
// 152284
vector<int> algorithmThree(vector<rpq> items) {
    vector<pair<rpq, int>> unusedItems;

    for (int i = 0; i < items.size(); i++) {
        unusedItems.emplace_back(items[i], i);
    }

    int currentTime = 0;

    vector<int> order;

    while (!unusedItems.empty()) {
        vector<int> indexesOfItemsInTime;

        int minTime = 1200000;

        for (int i = 0; i < unusedItems.size(); i++) {
            if (unusedItems[i].first.r < minTime) {
                minTime = unusedItems[i].first.r;
            }
            if (unusedItems[i].first.r <= currentTime) {
                indexesOfItemsInTime.push_back(i);
            }
        }

        if (indexesOfItemsInTime.empty()) {
            currentTime = minTime;
            continue;
        }

        int minTimeAfterP = 1200000;
        int indexOfMinPQDiff = -1;
        for (int i = 0; i < indexesOfItemsInTime.size(); i++) {
            int minTimeAfterProductionOfItem = (currentTime > unusedItems[indexesOfItemsInTime[i]].first.r) ?
                                               currentTime + unusedItems[indexesOfItemsInTime[i]].first.p :
                                               unusedItems[indexesOfItemsInTime[i]].first.r +
                                               unusedItems[indexesOfItemsInTime[i]].first.p;
            if (minTimeAfterProductionOfItem < minTimeAfterP) {
                minTimeAfterP = currentTime + unusedItems[indexesOfItemsInTime[i]].first.p;
                indexOfMinPQDiff = indexesOfItemsInTime[i];
            }
        }
        if (indexOfMinPQDiff == -1) {
            continue;
        }
        currentTime += unusedItems[indexOfMinPQDiff].first.p;
        order.push_back(unusedItems[indexOfMinPQDiff].second);
        unusedItems.erase(unusedItems.begin() + indexOfMinPQDiff);
    }

    return order;
}

// Improved algorithmTwo by swapping items till further improvements aren't possible
// 100227
vector<int> algorithmFour(vector<rpq> items) {
    vector<pair<rpq, int>> unusedItems;

    for (int i = 0; i < items.size(); i++) {
        unusedItems.emplace_back(items[i], i);
    }

    int currentTime = 0;
    vector<int> order;

    while (!unusedItems.empty()) {
        vector<int> indexesOfItemsInTime;
        int minTime = 1200000;
        for (int i = 0; i < unusedItems.size(); i++) {
            if (unusedItems[i].first.r < minTime) {
                minTime = unusedItems[i].first.r;
            }
            if (unusedItems[i].first.r <= currentTime) {
                indexesOfItemsInTime.push_back(i);
            }
        }

        if (indexesOfItemsInTime.empty()) {
            currentTime = minTime;
            continue;
        }

        int minTimeAfterP = 1200000;
        int maxTimeAfterQ = -1;
        int indexOfMinPQdiff = -1;
        for (int i = 0; i < indexesOfItemsInTime.size(); i++) {
            int minTimeAfterProductionOfItem = (currentTime > unusedItems[indexesOfItemsInTime[i]].first.r) ?
                                               currentTime + unusedItems[indexesOfItemsInTime[i]].first.p :
                                               unusedItems[indexesOfItemsInTime[i]].first.r +
                                               unusedItems[indexesOfItemsInTime[i]].first.p;
            if (minTimeAfterProductionOfItem < minTimeAfterP &&
                minTimeAfterProductionOfItem + unusedItems[indexesOfItemsInTime[i]].first.q > maxTimeAfterQ) {
                minTimeAfterP = currentTime + unusedItems[indexesOfItemsInTime[i]].first.p;
                maxTimeAfterQ = currentTime +
                                unusedItems[indexesOfItemsInTime[i]].first.p +
                                unusedItems[indexesOfItemsInTime[i]].first.q;
                indexOfMinPQdiff = indexesOfItemsInTime[i];
            }
        }
        if (indexOfMinPQdiff == -1) {
            continue;
        }
        currentTime += unusedItems[indexOfMinPQdiff].first.p;
        order.push_back(unusedItems[indexOfMinPQdiff].second);
        unusedItems.erase(unusedItems.begin() + indexOfMinPQdiff);
    }

    bool CMAXHasImproved = true;
    while(CMAXHasImproved){
        CMAXHasImproved = false;
        for(int i = 0;i < items.size();i++)
        {
            for(int j = 0;j<items.size();j++)
            {
                if(i!=j)
                {
                    vector<int> tempOrder = order;
                    swap(tempOrder[i],tempOrder[j]);
                    if(countCMAXbyOrder(items,tempOrder) < countCMAXbyOrder(items,order))
                    {
                        CMAXHasImproved = true;
                        order = tempOrder;
                    }
                }
            }
        }
    }

    return order;
}

int countCMax(vector<rpq> data) {
    return countCMAXbyOrder(data, algorithmFour(data));
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

    while (!data.eof()) {
        string isData;
        data >> isData;
        if (isData.size() > 0 && isData[0] == 'd')
        {
            int n;
            data >> n;
            switch (isData[isData.size() - 1]) {
                case '0':
                    data0 = loadData(data, n);
                    break;
                case '1':
                    data1 = loadData(data, n);
                    break;
                case '2':
                    data2 = loadData(data, n);
                    break;
                case '3':
                    data3 = loadData(data, n);
                    //printData(data3);
                    break;
                case '4':
                    data4 = loadData(data, n);
                    //printData(data4);
                    break;
            }
        }
    }

    cout << "CMAX for data.1: " << countCMax(data1) << "\n"
         << "CMAX for data.2: " << countCMax(data2) << "\n"
         << "CMAX for data.3: " << countCMax(data3) << "\n"
         << "CMAX for data.4: " << countCMax(data4) << "\n";

    auto start = chrono::high_resolution_clock::now();
    cout << "Total value: " << countCMax(data1) + countCMax(data2) +
                               countCMax(data3) + countCMax(data4) << "\n";
    auto end = chrono::high_resolution_clock::now();
    cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms\n";

    getchar();
}
