#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <iomanip>

using namespace std;

class Table {
protected:
    vector<vector<string>> data;

public:
    Table() {}

    void addData(const vector<vector<string>>& newData) {
        data = newData;
    }

    void printTable() const {
        for (const auto& row : data) {
            for (const auto& cell : row) {
                cout << cell << "\t";
            }
            cout << endl;
        }
    }
};

vector<double> createProbabilityTable(int numMessages) {
    vector<double> probabilities(numMessages);

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dis(0.0, 1.0);

    double sum = 0.0;
    for (int i = 0; i < numMessages; ++i) {
        probabilities[i] = dis(gen);
        sum += probabilities[i];
    }

    for (int i = 0; i < numMessages; ++i) {
        probabilities[i] /= sum;
    }

    return probabilities;
}



// Функція для виведення таблиці
void printTable(const vector<vector<double>>& table, char rows, char column,bool flag = true) {
    for (int i = 0; i <= table[0].size(); ++i) {
        if (i == 0) {
            if(flag)
                std::cout << "Pe(m)" << "    ";
            else 
                std::cout << "Pe(m)-P(m)" << "    ";
        }
        else 
        std::cout << column << i << "       ";
    }
    std::cout << std::endl;
    int j = 1;
    for (const auto& row : table) {
        std::cout << rows << j << "\t";
        for (double val : row) {
            cout << fixed << setprecision(6) << val << " ";
        }
        cout << endl;
        j++;
    }
}

void printTable(const vector<double>& table, char c) {
    double sum = 0;
    for (int i = 1; i <= table.size(); ++i) {
        std::cout << c << i << "       ";
    }
    std::cout << std::endl;
    for (const auto& row : table) {
            cout << fixed << setprecision(6) << row << " ";
            sum += row;
    }
    cout << "Summary = " << sum << endl << endl;
}



int main() {
    Table encryptionFunctionTable;

    vector<vector<string>> encryptionFunctionData = {
        {"f(m,k)", "M1", "M2", "M3", "M4", "M5", "M6"},
        {    "K1", "E4", "E5", "E6", "E1", "E2", "E3"},
        {    "K2", "E1", "E2", "E3", "E4", "E5", "E6"},
        {    "K3", "E5", "E6", "E1", "E2", "E3", "E4"},
        {    "K4", "E6", "E1", "E2", "E3", "E4", "E5"},
        {    "K5", "E3", "E4", "E5", "E6", "E1", "E2"},
        {    "K6", "E2", "E3", "E4", "E5", "E6", "E1"}
    };
    encryptionFunctionTable.addData(encryptionFunctionData);

    cout << "Encryption Function Table:" << endl;
    encryptionFunctionTable.printTable();

    int numMessages = 6;

     vector<double> probabilityTableM = createProbabilityTable(numMessages);
     vector<double> probabilityTableK = createProbabilityTable(numMessages);
     vector<double> probabilityTableKAll;

     for (int i = 0; i < numMessages; i++) {
         probabilityTableKAll.push_back(1.0 / 6.0);
     }

    cout << "Probability Table M: P(m)" << endl;
    printTable(probabilityTableM,'M');

    cout << "Probability Table K: P(k)" << endl;
    printTable(probabilityTableK,'K');

    cout << "Probability Table K: P(k)(rivnoimovirna)" << endl;
    printTable(probabilityTableKAll, 'K');

    vector<vector<double>> aposterM;
    for (int i = 0; i < probabilityTableM.size(); ++i) {
        aposterM.push_back(probabilityTableM);
    }

    for (int i = 0; i < probabilityTableM.size(); ++i) {
        for (int j = 0; j < probabilityTableM.size(); ++j) {
            aposterM[j][i] = probabilityTableM[i];
        }
    }

    printTable(aposterM, 'E','M');

    vector<vector<double>> aposterDelimM = aposterM;
    for (int i = 0; i < probabilityTableM.size(); ++i) {
        for (int j = 0; j < probabilityTableM.size(); ++j) {
            aposterDelimM[j][i] = aposterM[j][i] - probabilityTableM[i];
        }
    }

    printTable(aposterDelimM, 'E', 'M',false);
    Table encryptionRectData;

    vector<vector<string>> encryptionRect = {
        {"f(m,k)",  "M1", "M2", "M3", "M4", "M5", "M5", "M6"},
        {    "K1",  "E4", "E5", "E6", "E7", "E1", "E2", "E3"},
        {    "K2",  "E1", "E2", "E3", "E4", "E5", "E6", "E7"},
        {    "K3",  "E7", "E1", "E2", "E3", "E4", "E5", "E6"},
        {    "K4",  "E6", "E7", "E1", "E2", "E3", "E4", "E5"},
        {    "K5",  "E5", "E6", "E7", "E1", "E2", "E3", "E4"},
        {    "K6",  "E3", "E4", "E5", "E6", "E7", "E1", "E2"},
        {    "K7",  "E2", "E3", "E4", "E5", "E6", "E7", "E1"},
        {    "K8",  "E4", "E5", "E6", "E7", "E1", "E2", "E3"},
        {    "K9",  "E1", "E2", "E3", "E4", "E5", "E6", "E7"},
        {    "K10",  "E7", "E1", "E2", "E3", "E4", "E5", "E6"},
        {    "K11",  "E6", "E7", "E1", "E2", "E3", "E4", "E5"},
        {    "K12",  "E5", "E6", "E7", "E1", "E2", "E3", "E4"},
        {    "K13",  "E3", "E4", "E5", "E6", "E7", "E1", "E2"},
        {    "K14",  "E2", "E3", "E4", "E5", "E6", "E7", "E1"}

    };
    encryptionRectData.addData(encryptionRect);

    cout << "Encryption Function Table: Rectangle" << endl;
    encryptionRectData.printTable();

    numMessages = 7;

    vector<double> probabilityTableMRect = createProbabilityTable(numMessages);
    vector<double> probabilityTableKRect = createProbabilityTable(numMessages*2);
    vector<double> probabilityTableKAllRect;

    for (int i = 0; i < numMessages*2; i++) {
        probabilityTableKAllRect.push_back(1.0 / 14.0);
    }

    cout << "Probability Table M: P(m)" << endl;
    printTable(probabilityTableMRect, 'M');

    cout << "Probability Table K: P(k)" << endl;
    printTable(probabilityTableKRect, 'K');

    cout << "Probability Table K: P(k)(rivnoimovirna)" << endl;
    printTable(probabilityTableKAllRect, 'K');

    vector<vector<double>> aposterMRect;
    for (int i = 0; i < probabilityTableMRect.size(); ++i) {
        aposterMRect.push_back(probabilityTableMRect);
    }

    for (int i = 0; i < probabilityTableMRect.size(); ++i) {
        for (int j = 0; j < probabilityTableMRect.size(); ++j) {
            aposterMRect[j][i] = probabilityTableMRect[i];
        }
    }

    printTable(aposterMRect, 'E', 'M');

    vector<vector<double>> aposterDelimMRect = aposterMRect;
    for (int i = 0; i < probabilityTableMRect.size(); ++i) {
        for (int j = 0; j < probabilityTableMRect.size(); ++j) {
            aposterDelimMRect[j][i] = aposterMRect[j][i] - probabilityTableMRect[i];
        }
    }
    printTable(aposterDelimMRect, 'E', 'M', false);

    return 0;
}