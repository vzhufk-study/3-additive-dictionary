#ifndef ADDITIVEDICTIONARY_H
#define ADDITIVEDICTIONARY_H

#include <bintree.h>

#include <string>
#include <adword.h>


class AdditiveDictionaryBin: public BinTree<ADWord>
{
public:
    AdditiveDictionaryBin();
    bool addValue(std::string, unsigned);
    bool toDoFromFile(std::string, unsigned, bool (AdditiveDictionaryBin::*todo)(std::string, unsigned int));

    bool findValue(std::string, unsigned);

    bool delValue(std::string, unsigned);

    bool compare(std::string, std::string);
    bool equal(std::string, std::string);
};

#endif // ADDITIVEDICTIONARY_H
