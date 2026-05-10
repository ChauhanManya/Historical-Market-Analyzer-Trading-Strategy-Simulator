#include "CSVParser.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;
PriceHistory* CSVParser::loadHistory(const string& filename)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        return nullptr;
    }

    PriceHistory* history = new PriceHistory();

    string line;
    getline(file, line); // skip header row

    while (getline(file, line))
    {
        stringstream ss(line);
        string date, open, high, low, close, adjClose, volume;

        getline(ss, date, ',');
        getline(ss, open, ',');
        getline(ss, high, ',');
        getline(ss, low, ',');
        getline(ss, close, ',');
        getline(ss, adjClose, ',');
        getline(ss, volume, ',');

        // convert close + volume
        double closePrice = stod(close);
        double o = stod(open);
        double h = stod(high);
        double l = stod(low);
        long v = stol(volume);

        history->append(date, o, h, l, closePrice, v);
    }

    return history;
}
bool CSVParser::dateInRange(const string& date,
                            const string& start,
                            const string& end)
{
    return (date >= start && date <= end);
}

int CSVParser::extractYear(const string& date)
{
    return stoi(date.substr(0, 4));
}
int CSVParser::extractMonth(const string& date)
{
    return stoi(date.substr(5, 2));
}