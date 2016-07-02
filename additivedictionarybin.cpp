#include "additivedictionarybin.h"

#include <fstream>

AdditiveDictionaryBin::AdditiveDictionaryBin()
{

}


bool AdditiveDictionaryBin::compare(std::string A, std::string B){
    return A.length() > B.length();
}

bool comp(ADWord A,ADWord B){
    return A.getAmount() > B.getAmount();
}

bool AdditiveDictionaryBin::equal(std::string A, std::string B){
    return (A.compare(B) == 0);
}


bool  AdditiveDictionaryBin::toDoFromFile(std::string file_name, unsigned amount, bool (AdditiveDictionaryBin::*todo)(std::string, unsigned)){
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

bool  AdditiveDictionaryBin::addValue(std::string value, unsigned amount = 1){
   ADWord V(value, amount);
   treeElement<ADWord> *in = BinTree::findValue(*(new ADWord(value, amount)));
   if (in){
       in->getValuePointer()->setAmount(in->getValue().getAmount() + amount);
   }else{
        BinTree::addValue(V);
   }
   return true;
}

bool AdditiveDictionaryBin::findValue(std::string value, unsigned amount = 1){
    treeElement<ADWord> *in = BinTree::findValue(*(new ADWord(value, amount)));
    return in != 0;
}

bool AdditiveDictionaryBin::delValue(std::string value, unsigned amount = 1){
    ADWord V(value, amount);
    BinTree::delValue(V);
    return true;
}

