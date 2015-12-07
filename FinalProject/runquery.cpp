

#include "runquery.h"

//RunQuery::RunQuery()
//{

//}

RunQuery::~RunQuery()
{

}

RunQuery::RunQuery(IndexInterface& theIndex) : index(theIndex)
{
    sortedResults = vector<resultPair>();
    pageIDs = index.getPages();
}

void multiWordQuery(){

}

void singleWordQuery(){


}

void andQuery(){

}

void notQuery(){

}

void orQuery(){

}




