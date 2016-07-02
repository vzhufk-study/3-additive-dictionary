#ifndef ADDITIVEDICTIONARYHASH_H
#define ADDITIVEDICTIONARYHASH_H

#include <hash.h>

#include <string>
#include <adword.h>


class AdditiveDictionaryHash: public hashTable<ADWord>
{
public:
    AdditiveDictionaryHash();
    bool addValue(std::string, unsigned);

    bool toDoFromFile(std::string, unsigned, bool (AdditiveDictionaryHash::*todo)(std::string, unsigned int));

    bool findValue(std::string, unsigned);

    bool delValue(std::string, unsigned);

    bool compare(std::string, std::string);
    bool equal(std::string, std::string);
};

#endif // AdditiveDictionaryHash_H
