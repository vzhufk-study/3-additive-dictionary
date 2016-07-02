#ifndef HASH_H
#define HASH_H

#include <deque>
#include <list>
#include <string>

template <class valueType>
class hashTable
{
    std::deque<valueType*> value;
    unsigned amount;

public:
    hashTable(){
        amount = 0;
    }

    hashTable(unsigned n){
        amount = n;
        for (unsigned i = 0; i < n; ++i){
            value.push_back(NULL);
        }
    }

    bool add(valueType *element, unsigned (*hash_function)(valueType*)){
        unsigned index = hash_function(element);
        index %= amount;
        unsigned count = 0;
        while (value[index]!=NULL){
            ++count;
            if (count > amount){
                return false;
            }

            ++index;
            index %= amount;
        }

        value[index] = element;
        return true;
    }

    valueType *find(valueType *X,  unsigned (*hash_function)(valueType*), bool (*comp)(valueType*, valueType*)){
        unsigned index = hash_function(X);
        index %= amount;
        unsigned count = 0;
        while (!comp(value[index], X) && value[index]!=NULL){
            ++count;
            if (count > amount){
                return NULL;
            }

            ++index;
            index %= amount;
        }

        return value[index];
    }

    bool del(valueType *X, unsigned (*hash_function)(valueType*), bool (*comp)(valueType*, valueType*)){
        //FIND
        unsigned index = hash_function(X);
        index %= amount;
        unsigned count = 0;
        while (!comp(value[index], X) && value[index]!=NULL){
            ++count;
            if (count > amount){
                return false;
            }

            ++index;
            index %= amount;
        }

        unsigned del = index;
        ++index;
        index %= amount;

        unsigned prev;
        while(value[index] != NULL && del != index){
            if (hash_function(value[del]) == hash_function(value[index])){
                if (index == 0){
                    prev = amount - 1;
                }else{
                    prev = index - 1;
                }

                value[prev] = value[index];
                //value[index] = NULL;

            }
            ++index;
            index %= amount;
        }
        value[index] = NULL;
        return true;
    }



    std::list<valueType> out(){
        std::list<valueType> result;
        for ( unsigned i = 0; i < amount; ++i){
            if (value[i]){
                result.push_back(*value[i]);
            }
        }
        return result;
    }
};
#endif // HASH_H
