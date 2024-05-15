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
    Table() = default;

    void add_data(const vector<vector<string>>& new_data) {
        data = new_data;
    }

    void print_table() const {
        for (const auto& row : data) {
            for (const auto& cell : row) {
                cout << cell << "\t";
            }
            cout << endl;
        }
    }
};

vector<double> create_probability_table(int num_messages) {
    vector<double> probabilities(num_messages);

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dis(0.0, 1.0);

    double sum = 0.0;
    for (int i = 0; i < num_messages; ++i) {
        probabilities[i] = dis(gen);
        sum += probabilities[i];
    }

    for (int i = 0; i < num_messages; ++i) {
        probabilities[i] /= sum;
    }

    return probabilities;
}

void print_table(const vector<vector<double>>& table, char rows, char column, bool flag = true) {
    for (int i = 0; i <= table[0].size(); ++i) {
        if (i == 0) {
            if (flag)
                cout << "Pe(m)" << "    ";
            else
                cout << "Pe(m)-P(m)" << "    ";
        }
        else
            cout << column << i << "       ";
    }
    cout << endl;
    int j = 1;
    for (const auto& row : table) {
        cout << rows << j << "\t";
        for (double val : row) {
            cout << fixed << setprecision(6) << val << " ";
        }
        cout << endl;
        j++;
    }
}

void print_table(const vector<double>& table, char c) {
    double sum = 0;
    for (int i = 1; i <= table.size(); ++i) {
        cout << c << i << "       ";
    }
    cout << endl;
    for (const auto& row : table) {
        cout << fixed << setprecision(6) << row << " ";
        sum += row;
    }
    cout << "Summary = " << sum << endl << endl;
}

int main() {
    Table encryption_function_table;

    vector<vector<string>> encryption_function_data = {
        {"f(m,k)", "M1", "M2", "M3", "M4", "M5", "M6"},
        {"K1", "E4", "E5", "E6", "E1", "E2", "E3"},
        {"K2", "E1", "E2", "E3", "E4", "E5", "E6"},
        {"K3", "E5", "E6", "E1", "E2", "E3", "E4"},
        {"K4", "E6", "E1", "E2", "E3", "E4", "E5"},
        {"K5", "E3", "E4", "E5", "E6", "E1", "E2"},
        {"K6", "E2", "E3", "E4", "E5", "E6", "E1"}
    };
    encryption_function_table.add_data(encryption_function_data);

    cout << "Encryption Function Table:" << endl;
    encryption_function_table.print_table();

    int num_messages = 6;

    vector<double> probability_table_m;
    vector<double> probability_table_k;
    vector<double> probability_table_k_all;

    probability_table_m = create_probability_table(num_messages);
    probability_table_k = create_probability_table(num_messages);
    for (int i = 0; i < num_messages; i++) {
        probability_table_k_all.push_back(1.0 / 6.0);
    }

    cout << "Probability Table M: P(m)" << endl;
    print_table(probability_table_m, 'M');

    cout << "Probability Table K: P(k)" << endl;
    print_table(probability_table_k, 'K');

    cout << "Probability Table K: P(k)(rivnoimovirna)" << endl;
    print_table(probability_table_k_all, 'K');

    vector<vector<double>> aposter_m(num_messages, probability_table_m);

    for (int i = 0; i < num_messages; ++i) {
        for (int j = 0; j < num_messages; ++j) {
            aposter_m[j][i] = probability_table_m[i];
        }
    }

    print_table(aposter_m, 'E', 'M');

    vector<vector<double>> aposter_delim_m = aposter_m;
    for (int i = 0; i < num_messages; ++i) {
        for (int j = 0; j < num_messages; ++j) {
            aposter_delim_m[j][i] = aposter_m[j][i] - probability_table_m[i];
        }
    }

    print_table(aposter_delim_m, 'E', 'M', false);
    Table encryption_rect_data;

    vector<vector<string>> encryption_rect = {
        {"f(m,k)",  "M1", "M2", "M3", "M4", "M5", "M5", "M6"},
        {"K1",  "E4", "E5", "E6", "E7", "E1", "E2", "E3"},
        {"K2",  "E1", "E2", "E3", "E4", "E5", "E6", "E7"},
        {"K3",  "E7", "E1", "E2", "E3", "E4", "E5", "E6"},
        {"K4",  "E6", "E7", "E1", "E2", "E3", "E4", "E5"},
        {"K5",  "E5", "E6", "E7", "E1", "E2", "E3", "E4"},
        {"K6",  "E3", "E4", "E5", "E6", "E7", "E1", "E2"},
        {"K7",  "E2", "E3", "E4", "E5", "E6", "E7", "E1"},
        {"K8",  "E4", "E5", "E6", "E7", "E1", "E2", "E3"},
        {"K9",  "E1", "E2", "E3", "E4", "E5", "E6", "E7"},
        {"K10",  "E7", "E1", "E2", "E3", "E4", "E5", "E6"},
        {"K11",  "E6", "E7", "E1", "E2", "E3", "E4", "E5"},
        {"K12",  "E5", "E6", "E7", "E1", "E2", "E3", "E4"},
        {"K13",  "E3", "E4", "E5", "E6", "E7", "E1", "E2"},
        {"K14",  "E2", "E3", "E4", "E5", "E6", "E7", "E1"}

    };
    encryption_rect_data.add_data(encryption_rect);

    cout << "Encryption Function Table: Rectangle" << endl;
    encryption_rect_data.print_table();

    num_messages = 7;

    vector<double> probability_table_m_rect;
    vector<double> probability_table_k_rect;
    vector<double> probability_table_k_all_rect;

    probability_table_m_rect = create_probability_table(num_messages);
    probability_table_k_rect = create_probability_table(num_messages * 2);
    for (int i = 0; i < num_messages * 2; i++) {
        probability_table_k_all_rect.push_back(1.0 / 14.0);
    }

    cout << "Probability Table M: P(m)" << endl;
    print_table(probability_table_m_rect, 'M');

    cout << "Probability Table K: P(k)" << endl;
    print_table(probability_table_k_rect, 'K');

    cout << "Probability Table K: P(k)(rivnoimovirna)" << endl;
    print_table(probability_table_k_all_rect, 'K');

    vector<vector<double>> aposter_m_rect(num_messages, probability_table_m_rect);

    for (int i = 0; i < num_messages; ++i) {
        for (int j = 0; j < num_messages; ++j) {
            aposter_m_rect[j][i] = probability_table_m_rect[i];
        }
    }

    print_table(aposter_m_rect, 'E', 'M');

    vector<vector<double>> aposter_delim_m_rect = aposter_m_rect;
    for (int i = 0; i < num_messages; ++i) {
        for (int j = 0; j < num_messages; ++j) {
            aposter_delim_m_rect[j][i] = aposter_m_rect[j][i] - probability_table_m_rect[i];
        }
    }
    print_table(aposter_delim_m_rect, 'E', 'M', false);

    return 0;
}
