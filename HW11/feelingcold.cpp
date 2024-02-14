#include <iostream>
#include <vector>
#include <map>

bool numericCompare(std::string a,std::string b) {
    if (a.size() == b.size()) {
        return a < b;  // Lexicographical comparison for equal length strings
    }
    return a.size() < b.size();
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    int n;
    std::cin >> n;

    std::vector<std::string> data;
    std::map<std::string, int> occurrence;
    std::string minElement, maxElement;

    while (n--) {
        std::string instruction;
        std::cin >> instruction;

        if (instruction == "insert") {
            std::string num;
            std::cin >> num;
            data.push_back(num);
            occurrence[num]++;
            
            // Update min and max using numeric comparison
            if (data.size() == 1 || numericCompare(num, minElement)) {
                minElement = num;
            }
            if (data.size() == 1 || numericCompare(maxElement, num)) {
                maxElement = num;
            }
        } else if (instruction == "min") {
            if (!data.empty()) {
                std::cout << minElement << '\n';
            }
        } else if (instruction == "max") {
            if (!data.empty()) {
                std::cout << maxElement << '\n';
            }
        } else if (instruction == "find") {
            int idx;
            std::cin >> idx;
            if (idx > 0 && idx <= data.size()) {
                std::cout << data[idx - 1] << '\n';
            }
        } else if (instruction == "amount") {
            std::string num;
            std::cin >> num;
            std::cout << occurrence[num] << '\n';
        }
    }

    return 0;
}
