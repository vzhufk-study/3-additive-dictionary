#ifndef HTCHAINED_H
#define HTCHAINED_H

#include <deque>
#include <list>
#include <array>

const unsigned default_amount = 100;

template <class valueType>
class HTChained
{
    std::deque<std::list<valueType>> value;
    unsigned amount;
public:


    HTChained(unsigned amount = default_amount){
        this->amount = amount;
        for (unsigned i = 0; i < amount; ++i){
            value.push_back(*(new std::list<valueType>));
        }
    }

    bool add(valueType *element, unsigned (*hash_function)(valueType*)){
        unsigned index = hash_function(element);
        index %= amount;
        value.operator [](index).push_front(*element);
        return true;
    }

    valueType *find(valueType *X,  unsigned (*hash_function)(valueType*), bool (*comp)(valueType*, valueType*)){
        unsigned index = hash_function(X);
        index %= amount;
        for (typename std::list<valueType>::iterator it=value.operator [](index).begin(); it != value.operator [](index).end(); ++it){
               if (comp(X, &*it)){
                   return &*it;
               }
        }
        return NULL;
    }

    bool del(valueType *X,  unsigned (*hash_function)(valueType*), bool (*comp)(valueType*, valueType*)){
        unsigned index = hash_function(X);
        index %= amount;
        for (typename std::list<valueType>::iterator it = value.operator [](index).begin(); it != value.operator [](index).begin(); ++it){
            if (comp(X, &*it)){
                (value.operator [](index)).erase(it);
                return true;
            }
        }
        return false;
    }

    std::list<valueType> out(){
        std::list<valueType> result;

        for ( unsigned i = 0; i < amount; ++i){
            result.splice(result.end(), value.operator [](i), value.operator [](i).begin(), value.operator [](i).end());
        }
        return result;
    }
};

#endif // HTCHAINED_H
