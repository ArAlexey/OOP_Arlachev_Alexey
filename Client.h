#pragma once
#include <string>

using namespace std;

class Client 
{
    string name;
public:
    Client(const string& name);
    string getName() const;
    string getType() const;
};