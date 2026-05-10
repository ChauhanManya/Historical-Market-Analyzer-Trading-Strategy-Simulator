#include "CSVParser.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>

using namespace std;

PriceHistory* CSVParser::loadHistory(const string& filename) {
    ifstream file(filename.c_str());

    if (!file.is_open()) {
        return nullptr;
    }

    PriceHistory* history = new PriceHistory();

    string line;

    if (!getline(file, line)) {
        delete history;
        return nullptr;
    }

    vector<string> headers;
    string headerItem;
    stringstream headerStream(line);

    while (getline(headerStream, headerItem, ',')) {
        headers.push_back(headerItem);
    }

    int dateIndex = -1;
    int openIndex = -1;
    int highIndex = -1;
    int lowIndex = -1;
    int closeIndex = -1;
    int volumeIndex = -1;

    for (int i = 0; i < (int)headers.size(); i++) {
        if (headers[i] == "Date") {
            dateIndex = i;
        } else if (headers[i] == "Open") {
            openIndex = i;
        } else if (headers[i] == "High") {
            highIndex = i;
        } else if (headers[i] == "Low") {
            lowIndex = i;
        } else if (headers[i] == "Close") {
            closeIndex = i;
        } else if (headers[i] == "Volume") {
            volumeIndex = i;
        }
    }

    if (dateIndex == -1 || openIndex == -1 || highIndex == -1 ||
        lowIndex == -1 || closeIndex == -1 || volumeIndex == -1) {
        delete history;
        return nullptr;
    }

    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        vector<string> fields;
        string item;
        stringstream ss(line);

        while (getline(ss, item, ',')) {
            fields.push_back(item);
        }

        if ((int)fields.size() <= dateIndex ||
            (int)fields.size() <= openIndex ||
            (int)fields.size() <= highIndex ||
            (int)fields.size() <= lowIndex ||
            (int)fields.size() <= closeIndex ||
            (int)fields.size() <= volumeIndex) {
            continue;
        }

        string date = fields[dateIndex];

        if (!dateInRange(date, "2000-01-01", "2020-01-01")) {
            continue;
        }

        if (fields[openIndex].empty() ||
            fields[highIndex].empty() ||
            fields[lowIndex].empty() ||
            fields[closeIndex].empty() ||
            fields[volumeIndex].empty() ||
            fields[openIndex] == "null" ||
            fields[highIndex] == "null" ||
            fields[lowIndex] == "null" ||
            fields[closeIndex] == "null" ||
            fields[volumeIndex] == "null") {
            continue;
        }

        double open = atof(fields[openIndex].c_str());
        double high = atof(fields[highIndex].c_str());
        double low = atof(fields[lowIndex].c_str());
        double close = atof(fields[closeIndex].c_str());
        long volume = atol(fields[volumeIndex].c_str());

        history->append(date, open, high, low, close, volume);
    }

    return history;
}

bool CSVParser::dateInRange(const string& date,
                            const string& start,
                            const string& end) {
    return date >= start && date <= end;
}

int CSVParser::extractYear(const string& date) {
    if (date.length() < 4) {
        return 0;
    }

    return atoi(date.substr(0, 4).c_str());
}

int CSVParser::extractMonth(const string& date) {
    if (date.length() < 7) {
        return 0;
    }

    return atoi(date.substr(5, 2).c_str());
}