#include <iostream>
#include <fstream>
#include "printtuple.h"
#include "parser.h"

int main(int argC, char** argV) {
    if (argC < 3) {
        std::cout << std::endl << "Please, specify input and output files as first two arguments" << std::endl;
        return 0;
    }

    std::ifstream input(argV[1]);
    std::ofstream output(argV[2]);

    if (!input.is_open()) {
        std::cout << std::endl << "Cannot open input file, check the filepath: " << argV[1] << std::endl;
        return 0;
    }

    if (!output.is_open()) {
        std::cout << std::endl << "Cannot open output file, check the filepath: " << argV[2] << std::endl;
        input.close();
        return 0;
    }


    auto parser = CSVParser<int, int, int, int, int>(input);
    for (auto it : parser){
        output << it << std::endl;
    }

    return 0;
}
