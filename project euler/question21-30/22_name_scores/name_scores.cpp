/*
Names scores
Problem 22

Using names.txt (right click and 'Save Link/Target As...'), a 46K text file containing over five-thousand first names, begin by sorting it into alphabetical order. Then working out the alphabetical value for each name, multiply this value by its alphabetical position in the list to obtain a name score.

For example, when the list is sorted into alphabetical order, COLIN, which is worth 3 + 15 + 12 + 9 + 14 = 53, is the 938th name in the list. So, COLIN would obtain a score of 938 × 53 = 49714.

What is the total of all the name scores in the file?

*/
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <string.h>
std::vector<std::string> getNameList(const char *fileName)
{
    std::vector<std::string> List;
    std::ifstream file;
    std::string line;
    file.open(fileName);
    if (file.is_open())
    {
        while (file.good())
        {
            std::getline(file, line, ',');
            List.push_back(line);
        }
    }
    else
    {
        std::cerr << "Unable to open the file: " << fileName << std::endl;
    }
    file.close();
    return List;
}
void outputfile(const std::vector<std::string> &output)
{
    std::ofstream out;
    out.open("result.txt");
    if (out.is_open())
    {
        while (out.good())
        {
            for (int i = 0; i < output.size(); i++)
            {
                out << output[i] << " ";
            }
            break;
        }
    }
    else
    {
        std::cerr << "can't create file." << std::endl;
    }
    out.close();
}
bool sort(const std::string &s1, const std::string &s2)
{
    return strcasecmp(s1.c_str(), s2.c_str()) <= 0;
}

int main(int argc, char const *argv[])
{
    std::vector<std::string> nameList = getNameList(argv[1]);
    std::sort(nameList.begin(), nameList.end(), sort);
    long total_sum = 0;
    for (long i = 0; i < nameList.size(); i++)
    {
        unsigned long sum_in_name = 0;
        for (int j = 0; j < nameList[i].size(); j++)
        {
            int ascii = nameList[i][j];
            if (i == 937)
                std::cout << nameList[i][j];
            if (ascii <= 90 && ascii >= 65)
            {
                sum_in_name += (ascii - 64);
            }
            else
            {
                continue;
            }
        }
        total_sum += (sum_in_name * (i + 1));
    }
    std::cout << "Total sum:" << total_sum << "size:" << nameList.size() << std::endl;
    outputfile(nameList);
    return 0;
}
