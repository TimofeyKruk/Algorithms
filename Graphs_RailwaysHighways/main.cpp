#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <cfloat>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

int main() {
    FILE *fileIn;
    fileIn = fopen("input.txt", "r");
    ofstream fout("output.txt");

    //Type 0 - highway, 1 - railway
    int n, m, x, y, type;
    double price;
    fscanf(fileIn, "%d", &n);
    fscanf(fileIn, "%d", &m);

    //Separate adjacency lists
    //Firstly endCity, then price
    vector<vector<pair<int, double>>> highways(n);
    vector<vector<pair<int, double>>> railways(n);


    for (int i = 0; i < m; ++i) {
        fscanf(fileIn, "%d %d %d %lf", &x, &y, &type, &price);
        x--;
        y--;

        if (type == 0) //is highway
        {
            highways[x].emplace_back(make_pair(y, price));
            highways[y].emplace_back(make_pair(x, price));
        }
        if (type == 1) //is railway
        {
            railways[x].emplace_back(make_pair(y, price));
            railways[y].emplace_back(make_pair(x, price));
        }
    }

    int startCity, endCity;
    fscanf(fileIn, "%d", &startCity);
    fscanf(fileIn, "%d", &endCity);

    //Decrease, as cities are stored starting from 0
    startCity--;
    endCity--;

    vector<double> lengthHighway(n, DBL_MAX);
    vector<double> lengthRailway(n, DBL_MAX);

    //First is current length, second is city(counting starts from 1, so it is needed to decrease before accessing memory)
    //************Highways NEGATIVE, railways POSITIVE**********
    set<pair<double, int>> set;

    double fee = 1.1;
    //As we have fee for every starting edge, right away put all surrounding edges into set with fee
    int city;
    //Highway
    for (int j = 0; j < highways[startCity].size(); ++j) {
        city = highways[startCity][j].first;
        price = highways[startCity][j].second;
        lengthHighway[city] = price * fee;    // 10 per cent fee
        set.insert(make_pair(lengthHighway[city], -(city + 1)));   //As it is highway, made city negative
    }
    //Railway
    for (int j = 0; j < railways[startCity].size(); ++j) {
        city = railways[startCity][j].first;
        price = railways[startCity][j].second;
        lengthRailway[city] = price * fee;    // 10 per cent fee
        set.insert(make_pair(lengthRailway[city], (city + 1)));   //As it is railway, made city positive
    }

    // ******* MAIN PART *******
    int currentCity;
    double currentLength;
    double length;
    int currentType;
    int temp;

    while (!set.empty()) {
        currentLength = set.begin()->first;
        temp = set.begin()->second;
        if (temp < 0)//is highway
            currentType = 0;
        else
            currentType = 1;// is railway

        currentCity = abs(temp) - 1;

        set.erase(set.begin());

        switch (currentType) {
            //highway
            case 0: {
                //highway
                for (int j = 0; j < highways[currentCity].size(); ++j) {
                    city = highways[currentCity][j].first;
                    length = highways[currentCity][j].second;

                    if (lengthHighway[city] > (currentLength + length)) {
                        lengthHighway[city] = currentLength + length;
                        set.insert(make_pair(lengthHighway[city], -(city + 1)));
                    }
                }
                //railways (with fee)
                for (int j = 0; j < railways[currentCity].size(); ++j) {
                    city = railways[currentCity][j].first;
                    length = railways[currentCity][j].second;

                    if (lengthRailway[city] > (currentLength + (length * fee))) {
                        lengthRailway[city] = currentLength + (length * fee);
                        set.insert(make_pair(lengthRailway[city], (city + 1)));
                    }
                }
            }
                break;

                //railway
            case 1: {
                //highway (with fee)
                for (int j = 0; j < highways[currentCity].size(); ++j) {
                    city = highways[currentCity][j].first;
                    length = highways[currentCity][j].second;

                    if (lengthHighway[city] > (currentLength + (length * fee))) {
                        lengthHighway[city] = currentLength + (length * fee);
                        set.insert(make_pair(lengthHighway[city], -(city + 1)));
                    }
                }
                //railways
                for (int j = 0; j < railways[currentCity].size(); ++j) {
                    city = railways[currentCity][j].first;
                    length = railways[currentCity][j].second;

                    if (lengthRailway[city] > (currentLength + length)) {
                        lengthRailway[city] = currentLength + length;
                        set.insert(make_pair(lengthRailway[city], (city + 1)));
                    }
                }
            }
                break;
        }
    }

    if (lengthHighway[endCity] == DBL_MAX && lengthRailway[endCity] == DBL_MAX) {
        fout << "No\n";
    } else {
        fout << "Yes\n" << std::fixed << std::setprecision(2)
             << std::min(lengthHighway[endCity], lengthRailway[endCity]) << '\n';
    }

    fclose(fileIn);
    fout.close();
    return 0;
}