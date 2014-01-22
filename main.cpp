#include <iostream>

#include "functions.h"

using namespace std;

int main(int argc, char **argv)
{
    string arch = argc >= 2 ? argv[1] : "";

    while(arch != "amd64" && arch != "i386") {
        cout << "architecture(amd64 or i386) = ";
        cin >> arch;
    }
    auto result = getInstalledPackagesByUser(arch);
    printContainer(result);
    return 0;
}

