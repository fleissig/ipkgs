#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include <string>
#include <iostream>

class functions
{
public:
    functions();
};

std::vector<std::string> executeCommand(const std::string &command);

std::vector<std::string> getDefaultSetPackages(const std::string &architecture);

std::vector<std::string> getManuallyInstalledPackages();

template<typename T>
void printContainer(const T &t)
{
    for(const auto &i : t) {
        std::cout << i << std::endl;
    }
}

std::vector<std::string> getInstalledPackagesByUser(const std::string &architecture, bool notShowDeps, bool recIsDep);

std::vector<std::string> whyNoReason(const std::string &architecture);

bool isDep(const std::vector<std::string> &whyOutput, bool recIsDep);

#endif // FUNCTIONS_H
