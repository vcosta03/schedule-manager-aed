#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
    std::ifstream inputFile("schedule/classes.csv");
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    std::vector<std::string> ucCodes;
    std::vector<std::string> classCodes;

    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream lineStream(line);
        std::string ucCode, classCode;
        std::getline(lineStream, ucCode, ',');
        std::getline(lineStream, classCode, ',');

        ucCodes.push_back(ucCode);
        classCodes.push_back(classCode);
    }

    inputFile.close();

    // Now you have the data in the vectors ucCodes and classCodes.
    // You can process them as needed.

    for (size_t i = 0; i < ucCodes.size(); ++i) {
        std::cout << "UcCode: " << ucCodes[i] << " ClassCode: " << classCodes[i] << std::endl;
    }

    std::cout << argv[0] << std::endl;

    return 0;
}
