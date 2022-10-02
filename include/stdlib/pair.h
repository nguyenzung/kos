#ifndef PAIR
#define PAIR

namespace std
{

template <typename K, typename V>
class Pair 
{
    K first_;

public:
    const K &first;
    V second;

    Pair(K key, V value):first(first_)
    {
        this->first_ = key;
        this->second = value;
    }
    
    Pair& operator = (V value)
    {
        this->second = value;
        return *this;
    }

    Pair& operator++()
    {
        this->second++;
        return *this;
    }

    Pair& operator++(int)
    {
        ++(*this);
        return *this;
    }

    Pair& operator--()
    {
        this->second--;
        return *this;
    }

    Pair& operator--(int)
    {
        --(*this);
        return *this;
    }
};

template <typename K, typename V>
Pair<K, V>* makePair(K key, V value)
{
    Pair<K, V> *pair = new Pair<K,V>(key, value);
    return pair;
}

}
#endif