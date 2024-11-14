#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char** argv)
{
    std::string filename;
    std::cout << "파일 이름을 입력: ";
    std::getline(std::cin, filename);

    std::ofstream outFile(filename);
    if (!outFile)
    {
        std::cerr << "Err!" << std::endl;
        return 1;
    }

    std::string line;
    while (true)
    {
        std::getline(std::cin, line);
        if (line == "exit")
            break;
        outFile << line << std::endl;
    }
    outFile.close();


    return 0;
}
