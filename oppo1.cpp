#include <string>
#include <fstream>
#include <vector>
#include <regex>
#include <iostream>

using namespace std;

struct workInfo {
    string studentName;
    string topic;
    string date;
};



workInfo extractWorkInfo(const string& line) {

    regex dateRegex(R"(\d{1,2}[.]\d{1,2}[.]\d{2,4})");

    smatch matches;
    vector<string> extracted;

    string temp = line;

    while (regex_search(temp, matches, regex(R"((\d{1,2}[.]\d{1,2}[.]\d{2,4})|(".*?"))"))) {
        extracted.push_back(matches[0]);
        temp = matches.suffix().str();
    }

    string topic, studentName, date;


    for (int i = 0; i < extracted.size(); i++) {
        if (regex_match(extracted[i], dateRegex)) {
            date = extracted[i];
            extracted.erase(extracted.begin() + i);
        }
    }

    studentName = extracted[0];
    topic = extracted[1];


    return { studentName, topic, date };
}


void printStruct(workInfo& info) {
    cout << info.studentName << "\t\t" << info.topic << "\t\t" << info.date << "\n";
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");


    ifstream in("in.txt");
    if (!in) {
        cout << "file is not found!" << endl;
        return 0;
    }
    vector<workInfo> list;
    string line;

    while (getline(in, line)) {
        workInfo info = extractWorkInfo(line);
        if (!info.date.empty() or !info.topic.empty() or !info.studentName.empty()) {
            list.push_back(info);
        }
        else {
            cout << "The data from this line was read wrong: " << line << endl;
        }
    }

    for (int i = 0; i < list.size(); i++) {
        printStruct(list[i]);
    }

}