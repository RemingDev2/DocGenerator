#include <iostream>
#include "src/headers/DocGenerator.h"


int main()
{
    std::cout << "Start\n";

    DocGenerator obj;
    obj.generateDoc(false, true, 34, "FrontPage");

    std::cout << "Finished\n";

    return 0;
}

// prerequisites: name of the Excel file without .docx
//                name of the front page without .docx
//                front page need to be complete (without remaining lines)
//                Excel file format: cat, quest, ans1, ans2, ans3, ..., ans10
//                               or: cat, quest, ans1
//                                               ans2
//                                               ans3
//                                               ...
//                                               ansINF
