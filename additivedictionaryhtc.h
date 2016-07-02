#ifndef AdditiveDictionaryHTC_H
#define AdditiveDictionaryHTC_H

#include <htchained.h>

#include <string>
#include <adword.h>


class AdditiveDictionaryHTC: public HTChained<ADWord>
{
public:
    AdditiveDictionaryHTC();
    bool addValue(std::string, unsigned);
    bool findValue(std::string, unsigned);
    bool delValue(std::string, unsigned);

    bool toDoFromFile(std::string, unsigned, bool (AdditiveDictionaryHTC::*todo)(std::string, unsigned int));

};

#endif // AdditiveDictionaryHTC_H
