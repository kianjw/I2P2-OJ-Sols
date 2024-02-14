#include <iostream>
#include <vector>
#include <map>

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
            
            // Update min and max
            if (data.size() == 1 || num.compare(minElement) < 0) {
                minElement = num;
            }
            if (data.size() == 1 || num.compare(maxElement) > 0) {
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
