#include "client.h"

Client::Client(const string& name) : name(name) {}

string Client::getName() const 
{
    return name;
}

string Client::getType() const 
{
    return "Физическое лицо";
}