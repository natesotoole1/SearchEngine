/* Search Engine Project
 * CSE 2341: Data Stuctures
 * 05/03/2015
 * Kiko Whiteley
 **/
#include "termbucket.h"

TermBucket::TermBucket()
{
    root = NULL;
}

TermBucket::~TermBucket()
{

}

void TermBucket::add_term_to_bucket(Term* term)
{

    // If there are no terms in the bucket, set root to newTerm.
    if (!root)
    {
        root = term;
        return;
    }

    // Otherwise, insert newTerm at the end of the linked list.
    Term* curr = root;
    while (curr->get_next()) curr = curr->get_next();
    curr->set_next(term);
}

Term* TermBucket::find(string term)
{
    if (!root) return NULL;

    Term* curr = root;
    if (curr->get_name().compare(term) == 0) return curr;
    while (curr->get_next())
    {
        curr = curr->get_next();
        if (curr->get_name().compare(term) == 0) return curr;
    }
    return NULL;
}

bool TermBucket::has_word(string term)
{
    if (!root) return false;

    // Iterate through the linked list at this bucket,
    // checking each word for a match.
    Term* curr = root;
    if (curr->get_name().compare(term) == 0) return true;
    while (curr->get_next())
    {
        curr = curr->get_next();
        if (curr->get_name().compare(term) == 0) return true;
    }

    // By this point, it's checked every term (with no matches),
    // so return false.
    return false;
}

void TermBucket::write_term_bucket(ofstream &persistence)
{
    if (!root) return;

    // Iterate through the linked list and print each term.
    Term* curr = root;
    curr->write_term(persistence);
    while (curr->get_next())
    {
        curr = curr->get_next();
        curr->write_term(persistence);
    }
}

void TermBucket::clear(){

    if (!root) return;

    Term* curr = root;
    Term* old;
    while(curr->get_next()){
        old = curr;
        curr = curr->get_next();
        delete old;
    }
}
