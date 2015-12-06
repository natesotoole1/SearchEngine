#ifndef HASHTABLEINTERFACE_H
#define HASHTABLEINTERFACE_H

#include "docparser.h"
#include "hashtableindex.h"
#include "indexinterface.h"
#include "term.h"

#include <fstream>
#include <iostream>
#include <string>
// #include <unordered_map>
#include <mapping.cpp>

using namespace std;

typedef _map<int, int> pageMap;
/*! \brief
 * Holds 26 HashTableIndexes, one for each letter of the alphabet.
 * Inherits from IndexInterface.
 */
class HashTableInterface : public IndexInterface
{
public:
    HashTableInterface();
    ~HashTableInterface();
};

#endif // HASHTABLEINTERFACE_H
