#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

std::vector<int> find_pa_times(const std::vector<std::pair<int, int>>& classes) {
    std::vector<int> pa_times;

    if (classes.empty()) {
        return pa_times;        // returning clear vector if amount of classes is 0
    }

    // Using std::sort(QuickSort) to sort end class data in raising order, using comparator
    std::vector<std::pair<int, int>> sorted_classes = classes;
    std::sort(sorted_classes.begin(), sorted_classes.end(), [](const auto& a, const auto& b) {
        return a.second < b.second;
    });

    // Starting from the end of first class
    int last_end_time = sorted_classes[0].second;

    // Pushing to our vector 1 announcement time
    pa_times.push_back(last_end_time);

    // Checking if there are classes which are still not notified do the same logic as previous
    for (size_t i = 1; i < sorted_classes.size(); ++i) {
        int start_time = sorted_classes[i].first;
        if (start_time >= last_end_time) {
            last_end_time = sorted_classes[i].second;
            pa_times.push_back(last_end_time);
        }
    }

    return pa_times;
}

int main() {
    // test condition
    std::vector<std::pair<int, int>> classes = { {1, 20},
        {14, 17}, {12, 18}, {22, 30}, {27, 42},
        {20, 36}, {33, 56}, {40, 60} };

    std::vector<int> pa_times = find_pa_times(classes);

    std::cout << "min amount of announcements: " << pa_times.size() << " at time: ";
    for (int time : pa_times) {
        std::cout << time << ", ";
    }
    std::cout << std::endl;

    return 0;
}