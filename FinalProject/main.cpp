/* Search Engine Project
 * CSE 2341: Data Stuctures
 * 12/06/15
 * Nate O'Toole
 * Brandon McFarland
 * Ashvin Asava
 **/
#include "indexhandler.h"
#include "interface.h"

using namespace std;


int main()
{
    // Use clock_t objects to track the program's total runtime.
    /*clock_t start, end;
    // Get the number of clicks already used by the program.
    start = clock();
    */

    //IndexHandler handler = IndexHandler(true);

    // Only happens when the persistence index needs to be written
    // or rewritten (for add_file).  This takes about 30 minutes.
    //handler.read_file("WikiBooks.xml");


    Interface ui = Interface();

    // Init page infos for WikiBooks.xml.


    // To write the persistence index.
   //  handler->index_document("WikiBooks.xml");

    // It is assumed that the WikiBooks are written to a persistence file
    // before the program ever starts for the user.

    // The PageInfo objects still must be written, however, containing
    // all the page information and associated text.

    // Before activating the interface, read the WikiBooks file into a hash
    // table to write the persistence file.

   /* // Get the number of clicks used up to now.
    end = clock();

    // The total number of seconds elapsed is the difference in number of
    // clicks used since the very beginning and end of the program divided
    // by the number of clicks used in a real second.
    float timeElapsed = ((float)end - (float)start) / CLOCKS_PER_SEC;

    std::cout<<"A total of "<<timeElapsed<<" seconds were used.";
*/
    return 0;
}
