#include "AdditiveDictionaryHash.h"

#include <fstream>

AdditiveDictionaryHash::AdditiveDictionaryHash(): hashTable<ADWord>::hashTable(100000)
{
    ;
}


bool AdditiveDictionaryHash::compare(std::string A, std::string B){
    return A.length() > B.length();
}


unsigned hash_function(ADWord *X){
    return X->getAmount();
}

bool equ(ADWord *A,   ADWord *B){
    if (A == 0 || B == 0){
        return false;
    }else{
        return (A->getValue().compare(B->getValue()) == 0);
    }

}


bool  AdditiveDictionaryHash::addValue(std::string value, unsigned amount){
   ADWord *in = hashTable::find(new ADWord(value, amount), hash_function, equ);
   if (in){
       in->setAmount(in->getAmount() + amount);
   }else{

        hashTable::add(new ADWord(value, amount), hash_function);
   }
   return true;
}

bool  AdditiveDictionaryHash::toDoFromFile(std::string file_name, unsigned amount, bool (AdditiveDictionaryHash::*todo)(std::string, unsigned int)){
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

bool  AdditiveDictionaryHash::findValue(std::string value, unsigned amount){
    ADWord *in = hashTable<ADWord>::find(new ADWord(value, amount), hash_function, equ);
    return in != 0;
}

bool  AdditiveDictionaryHash::delValue(std::string value, unsigned amount){
    ADWord V(value, amount);
    return hashTable<ADWord>::del(&V, hash_function, equ);
}

