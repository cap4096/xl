#include "serialize.hh"
#include <iostream>



int main(int argc, char const *argv[])
{
    std::vector<int> iv;
    std::vector<std::string> sv;

    std::map<int , std::string> mi;
    std::map<std::string, int> ms;

    iv.push_back(0);
    iv.push_back(1);
    iv.push_back(2);
    iv.push_back(3);
    iv.push_back(4);

    sv.push_back("A");
    sv.push_back("B");
    sv.push_back("C");
    sv.push_back("D");
    std::cout << "iv: " << to_string(iv) << "\n\n";
    std::cout << "sv: " << to_string(sv) << "\n\n";


    mi[1] = "A";
    mi[2] = "B";
    mi[3] = "C";
    mi[4] = "D";
    mi[5] = "E";

    ms["A"] = 1;
    ms["B"] = 2;
    ms["C"] = 3;
    ms["D"] = 4;
    ms["E"] = 5;

    std::cout << "mi: " << to_string(mi) << "\n\n";
    std::cout << "si: " << to_string(ms) << "\n\n";

    
    return 0;
}
