#include <iostream>
#include <time.h>
#include <chrono>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>

std::ifstream ExcerptFile ("Excerpts.txt");

float WPM;
float Accuracy;

std::string lineValue;
std::string input;

int RandomRange(int min, int max) {
    int range = max - min + 1;
    return rand() % range + min;
}

std::string findLine(int lineToFind) {
    ExcerptFile.open("Excerpts.txt");
    int line_no = 0;
    std::string sLine;
    while (line_no != lineToFind) {
        std::getline(ExcerptFile, sLine);
        ++line_no;
    }

    if (line_no == lineToFind) {
        // sLine contains the second line in the file.
        ExcerptFile.close();
        sLine = sLine.substr(0, sLine.size() - 2);
        lineValue = sLine;
        return sLine;
    }
    else {
        ExcerptFile.close();
        return "ERROR: The file either could not be opened, or is not as long as your number.\n";
        // The file contains fewer than two lines.
    }
}

int countLines() {
    ExcerptFile.open("Excerpts.txt");
    int lines_count = std::count(std::istreambuf_iterator<char>(ExcerptFile), std::istreambuf_iterator<char>(), '\d');
    ExcerptFile.close();
    return lines_count;
}

std::string grabParagraph() {
    int randnum = RandomRange(1, countLines());
    std::string fileValue = findLine(randnum);

    return fileValue;
}

float checkAccuracy() {
    float correctChars = 0;

    if (lineValue.size() == input.size() || lineValue.size() < input.size()) {
        for (std::string::size_type i = 0; i < lineValue.size(); ++i) {
            if (lineValue[i] == input[i]) {
                ++correctChars;
            }
        } 
    }
    else if (lineValue.size() > input.size()) {
        for (std::string::size_type i = 0; i < input.size(); ++i) {
            if (lineValue[i] == input[i]) {
                ++correctChars;
            }
        }
    }

    return ((correctChars / lineValue.length()) * 100);
}

int main()
{
    srand(time(NULL));
    std::string foo;
    float accuracy;

    std::cout << "Hit enter to begin typing: " << std::endl << std::endl;
    std::cin >> foo;

    std::string paragraph = grabParagraph();

    auto startTime = std::chrono::high_resolution_clock::now();

    std::cout << paragraph << std::endl;
    std::cin >> input;

    auto endTime = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = endTime - startTime;

    WPM = (paragraph.length() / 4.7) / (elapsed.count() / 60);
    std::cout << elapsed.count() << std::endl << (paragraph.length() / 5) << std::endl;
    accuracy = checkAccuracy();

    std::cout << "Your WPM is: " << WPM << std::endl;
    std::cout << "Your accuracy was: " << accuracy << "%" << std::endl;
}