#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

// Function to find the minimum number of announcement times required
// to notify all classes, given their start and end times
std::vector<int> find_minimum_announcement_times(const std::vector<std::pair<int, int>>& classes) {
    std::vector<int> announcement_times;

    // If no classes are provided, return an empty vector
    if (classes.empty()) {
        return announcement_times;
    }

    // Sort classes by their end times in ascending order
    std::vector<std::pair<int, int>> sorted_classes = classes;
    std::sort(sorted_classes.begin(), sorted_classes.end(), [](const auto& a, const auto& b) {
        return a.second < b.second;
        });

    // Initialize the end time of the first class
    int last_end_time = sorted_classes[0].second;
    // Add the first announcement time
    announcement_times.push_back(last_end_time);

    // Iterate through the sorted classes to find all necessary announcement times
    for (size_t i = 1; i < sorted_classes.size(); ++i) {
        int start_time = sorted_classes[i].first;
        // If the start time of the current class is after or at the last end time, add a new announcement time
        if (start_time >= last_end_time) {
            last_end_time = sorted_classes[i].second;
            announcement_times.push_back(last_end_time);
        }
    }

    return announcement_times;
}

int main() {
    // Test condition
    std::vector<std::pair<int, int>> classes = {
        {1, 20}, {14, 17}, {12, 18}, {22, 30}, {27, 42},
        {20, 36}, {33, 56}, {40, 60}
    };

    std::vector<int> announcement_times = find_minimum_announcement_times(classes);

    std::cout << "Minimum number of announcements: " << announcement_times.size() << " at times: ";
    for (int time : announcement_times) {
        std::cout << time << ", ";
    }
    std::cout << std::endl;

    return 0;
}