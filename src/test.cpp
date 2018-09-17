#include "gtypes.hh"
#include "file_store.hh"
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
    std::cout << "iv: " << dbg::dump(iv) << "\n\n";
    std::cout << "sv: " << dbg::dump(sv) << "\n\n";


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

    std::cout << "mi: " << dbg::dump(mi) << "\n\n";
    std::cout << "si: " << dbg::dump(ms) << "\n\n";



    FileStore s;

    auto f = s.load("test_input/ex1.xl");

    std::cout << "Error: " << dbg::dump(s.errorMessages) << "\n\n";

    std::cout << dbg::dump(f) << "\n\n";


    return 0;
}
