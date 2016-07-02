#include "AdditiveDictionaryHTC.h"

#include <fstream>

AdditiveDictionaryHTC::AdditiveDictionaryHTC():  HTChained()
{

}



unsigned hash_func(ADWord *A){
    unsigned h = 1;

    for (unsigned i = 0; i < A->getValue().length(); i++)
    {
        h += A->getValue()[i];
    }

    return h;
}



bool equal(ADWord* A, ADWord* B){
    return (A->getValue().compare(B->getValue()) == 0);
}



bool  AdditiveDictionaryHTC::addValue(std::string value, unsigned amount){
    ADWord V(value, amount);
    ADWord *in = HTChained::find(&V, hash_func, equal);

    if (in){
        in->setAmount(in->getAmount() + amount);
    }else{
        HTChained::add(&V, hash_func);
    }return true;
}

bool  AdditiveDictionaryHTC::toDoFromFile(std::string file_name, unsigned amount, bool (AdditiveDictionaryHTC::*todo)(std::string, unsigned int)){
    std::ifstream file;
    file.open(file_name);

    std::string word;
    unsigned count = 0;
    while (file>>word && ++count < amount) {
        (this->*todo)(word, 1);
    }
    file.close();
    return true;
}


bool  AdditiveDictionaryHTC::findValue(std::string value, unsigned amount){
    ADWord V(value, amount);
    HTChained::find(&V, hash_func, equal);
    return true;
}

bool  AdditiveDictionaryHTC::delValue(std::string value, unsigned amount){
    ADWord V(value, amount);
    HTChained::del(&V, hash_func, equal);
    return true;
}
