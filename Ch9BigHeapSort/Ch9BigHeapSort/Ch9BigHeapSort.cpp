// Ch9BigHeapSort.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include "Heap.cpp"

void processInput(std::shared_ptr<std::ifstream>, std::vector<int>&);
int main(const int argc, const char* argv[])
{
    //default, no parameters passed other than the program name
    if (argc == 1) {
        std::string input = "ch9nums1.dat";
        std::cout << "Using the default of this program.\n";
        std::cout << "Using a min heap to sort " << input << "'s data descending.\n";
        std::shared_ptr<std::ifstream> inFile = std::make_shared<std::ifstream>(input);
        std::vector<int> vec{};
        processInput(inFile, vec);
        MinHeap<int> heap(vec);
        heap.print([](int& num) { std::cout << num << " "; });
    }

    //flag and input file passed
    else if (argc == 3) {
        std::vector<int> vec{};
        std::shared_ptr<std::ifstream> inFile = std::make_shared<std::ifstream>(argv[2]);
        //ascending order option
        if (!strcmp(argv[1], "-a")) {
            processInput(inFile, vec);
            MaxHeap<int> heap(vec);
            heap.print([](int& num) { std::cout << num << " "; });
        }
        //descending order option
        else if (!strcmp(argv[1], "-d")) {
            processInput(inFile, vec);
            MinHeap<int> heap(vec);
            heap.print([](int& num) { std::cout << num << " "; });
        }
        //flag does not match -a or -d
        else {
            std::cout << argv[1] << std::endl;
            std::cout << "Invalid flag. Please pass -a or -d as the first parameter.\n";
        }
    }
    else if (argc == 4) {
        std::vector<int> vec{};
        std::shared_ptr<std::ifstream> inFile = std::make_shared<std::ifstream>(argv[2]);
        std::shared_ptr<std::ostream> outFile = std::make_shared<std::ofstream>(argv[3]);
        //ascending order option
        if (!strcmp(argv[1], "-a")) {
            processInput(inFile, vec);
            MaxHeap<int> heap(vec);
            heap.print([outFile](int& num) {*outFile << num << " "; });
            std::cout << "Output written to " << argv[3] << "!\n";
        }
        //descending order option
        else if (!strcmp(argv[1], "-d")) {
            processInput(inFile, vec);
            MinHeap<int> heap(vec);
            heap.print([outFile](int& num) {*outFile << num << " "; });
            std::cout << "Output written to " << argv[3] << "!\n";
        }
        //flag does not match -a or -d
        else {
            std::cout << argv[1] << std::endl;
            std::cout << "Invalid flag. Please pass -a or -d as the first parameter.\n";
        }
    }
       //error, must pass -a or -d followed by input filepath
    else {
        std::cout << "Please pass -a (ascending or -d (descending) followed by an input filepath\n";
        std::cout << "Optional: Pass output filepath.\n";
    }
    return 0;
}
//reads input file and stores the inputs in a vector
void processInput(std::shared_ptr<std::ifstream> file, std::vector<int>& vec)
{
    //process a text file of integers
    std::string numstr{};
    while (!file->eof()) {
        std::getline(*file, numstr, '\n');
        if (numstr == "") {
            break;
        }
        vec.push_back(std::stoi(numstr));
        numstr.clear();
    }
}