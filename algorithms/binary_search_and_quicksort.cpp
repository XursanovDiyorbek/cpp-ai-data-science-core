#include <iostream>
#include <vector>
#include <algorithm>

/**
 * Binary Search Algorithm
 * Time Complexity: O(log N)
 * Space Complexity: O(1)
 *
 * Performs binary search on a sorted vector.
 * Returns the index of target if found, otherwise returns -1.
 */
int binarySearch(const std::vector<int>& arr, int target) {
    int left = 0;
    int right = static_cast<int>(arr.size()) - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

/**
 * Partition helper function for QuickSort
 * Uses Lomuto partition scheme.
 */
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

/**
 * QuickSort Algorithm
 * Average Time Complexity: O(N log N)
 * Space Complexity: O(log N) recursive stack space
 */
void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}

int main() {
    std::vector<int> data = {34, 7, 23, 32, 5, 62, 32, 2, 0};

    std::cout << "Original array: ";
    for (int num : data) {
        std::cout << num << " ";
    }
    std::cout << "\n";

    // Perform QuickSort O(N log N)
    quickSort(data, 0, static_cast<int>(data.size()) - 1);

    std::cout << "Sorted array (QuickSort): ";
    for (int num : data) {
        std::cout << num << " ";
    }
    std::cout << "\n";

    // Perform Binary Search O(log N)
    int target = 23;
    int index = binarySearch(data, target);
    if (index != -1) {
        std::cout << "Element " << target << " found at index " << index << "\n";
    } else {
        std::cout << "Element " << target << " not found.\n";
    }

    return 0;
}
