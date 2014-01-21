#include <iostream>

#include "functions.h"

using namespace std;

int main()
{
//    cout << "Hello World!" << endl;
    auto result = getInstalledPackagesByUser("amd64");
    printContainer(result);
//    whynot("amd64");
    return 0;
}

