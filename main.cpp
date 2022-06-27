#include <iostream>
#include <vector>

void merge(std::vector<int> &array, int const left, int const mid, int const right)
{
    auto const subArrayOne = mid - left + 1;
    auto const subArrayTwo = right - mid;

    auto *leftArray = new int[subArrayOne],
            *rightArray = new int[subArrayTwo];

    for (auto i = 0; i < subArrayOne; i++)
        leftArray[i] = array[left + i];
    for (auto j = 0; j < subArrayTwo; j++)
        rightArray[j] = array[mid + 1 + j];

    auto indexOfSubArrayOne = 0,
    indexOfSubArrayTwo = 0;
    int indexOfMergedArray = left;

    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
        if (leftArray[indexOfSubArrayOne] >= rightArray[indexOfSubArrayTwo]) {
            array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else {
            array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }

    while (indexOfSubArrayOne < subArrayOne) {
        array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }

    while (indexOfSubArrayTwo < subArrayTwo) {
        array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
}

void mergeSort(std::vector<int> &array, int const begin, int const end)
{
    if (begin >= end)
        return;

    auto mid = begin + (end - begin) / 2;
    mergeSort(array, begin, mid);
    mergeSort(array, mid + 1, end);
    merge(array, begin, mid, end);
}

void solution() {
    int n;
    std::cin >> n;

    int zeros_counter = 0;
    int ones_counter = 0;

    std::vector<int> zero_array;
    std::vector<int> one_array;

    std::string temp;
    int len;
    for (int i = 0; i < n; ++i) {
        std::cin >> len >> temp;

        if (temp[0] == temp[temp.size() - 1]) {
            if (temp[0] == '0') zeros_counter += len;
            else ones_counter += len;
        } else {
            if (temp[0] == '0') zero_array.push_back(len);
            else one_array.push_back(len);
        }
    }

    if (zero_array.size() + one_array.size() == 0) {
        std::cout << (zeros_counter > ones_counter ? zeros_counter : ones_counter);
        return;
    }

    mergeSort(zero_array, 0, (int) zero_array.size() - 1);
    mergeSort(one_array, 0, (int) one_array.size() - 1);


    if (zero_array.size() > one_array.size()) one_array.push_back(0);
    if (zero_array.size() < one_array.size()) zero_array.push_back(0);

    len = (int) std::min(zero_array.size(), one_array.size());
    int answer = zeros_counter + ones_counter;

    for (int i = 0; i < len; ++i) {
        answer += zero_array[i] + one_array[i];
    }
    std::cout << answer;

}

int main() {

    solution();

    return 0;
}
