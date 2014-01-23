#include "functions.h"

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cerrno>

using namespace std;

functions::functions()
{
}

vector<string> executeCommand(const string &command)
{
    FILE * fp ;
    fp = popen(command.c_str(),"r");
    errno = 0;
    if (fp == 0) {
        perror("popen");
        if (errno == 0) {
            printf("%s", "allocation memory\n");
        }
        exit(1);
    }
    const int SIZE = 256;
    char buffer[SIZE];
    vector<string> output;
    string line;
    while (!feof(fp)) {
        if (fgets(buffer, sizeof(buffer), fp)) {
            line += buffer;
            if (line[line.length()-1] == '\n') {
                output.push_back(line.substr(0, line.length()-1));
                line = "";
            }
        }
    }
    if (pclose(fp) == -1) {
        perror("pclose");
    }
    return output;
}


std::vector<string> getDefaultSetPackages(const string &architecture)
{
    string command = "aptitude search \'(~prequired|~pimportant|~pstandard|~E)(?architecture("
            + architecture + ")|?architecture(all))\' | sed \'s/A/ /\' | awk \'{print $2}\'";
    auto result = executeCommand(command.c_str());
    return result;
}


std::vector<string> getManuallyInstalledPackages()
{
    string command = "aptitude search \'~i!~M\' | awk \'{print $2}\'";
    auto result = executeCommand(command.c_str());
    return result;
}


std::vector<string> getInstalledPackagesByUser(const string &architecture, bool notShowDeps, bool recIsDep)
{
    auto mpkgs = getManuallyInstalledPackages();
    auto defpgks = getDefaultSetPackages(architecture);

    std::vector<string> ans;
    for(const auto &m : mpkgs) {
        bool mIsDef = false;
        for(const auto &d : defpgks) {
            if(m == d) {
                mIsDef = true;
                break;
            }
        }
        if(!mIsDef) {
            if(notShowDeps) {
                auto whyOutput = executeCommand("aptitude why " + m);
                if(!isDep(whyOutput, recIsDep))
                {
                    ans.push_back(m);
                }
            }
            else {
                ans.push_back(m);
            }
        }
    }
    return ans;
}


std::vector<string> whyNoReason(const string &architecture)
{
    std::vector<string> ans;
    auto m = getInstalledPackagesByUser(architecture, false, false);
    for(const auto &i : m) {
        auto output = executeCommand("aptitude why " + i);
        if(output.size() == 1
                && output[0] == "Unable to find a reason to install " + i + ".")
        {
            ans.push_back(i);
        }
    }
    return ans;
}


bool isDep(const std::vector<string> &whyOutput, bool recIsDep)
{
    if(whyOutput.size() != 0) {
        bool isDep = whyOutput[whyOutput.size()-1].find("Depends") != string::npos;
        if(isDep)
            return true;
        else {
            if(recIsDep) {
                bool isRec = whyOutput[whyOutput.size()-1].find("Recommends") != string::npos;
                if(isRec)
                    return true;
            }
        }
    }
    return false;
}
