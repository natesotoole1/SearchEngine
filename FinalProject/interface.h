#ifndef INTERFACE_H
#define INTERFACE_H

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <stdlib.h>

#include "indexhandler.h"
#include "queryprocessor.h"
#include "timer.h"

using namespace std;
/*! \brief
 * Interface is the User Interface
 */
class Interface
{
public:

    Interface(); ///< constructor
    void choose_structure(); ///< allows the user before anything runs to choose the data structure
    void set_mode(); ///< gets either interactive or maintenance mode
    void get_command(); ///< gets the command inputed
    void re_command(); ///< called when command is over and checks if person would like to perform another
    void command(string, string);///<checks command for different modes
    void search(); ///< gets the query from the user input
    void run_AVL(); ///< creates AVL Interface
    void run_hash(); ///< creates Hash Interface
    void run_maintenance(); ///< if mode == 1, run maintenance mode
    void add_file_to_index(string); ///< add file to index with the given file path
    void clear_index(); ///< clears index of whichever data struture is created
    string toLowerCase(string); ///< turns words to lower case
    void run_interactive();///<runs interactive mode with the ability to search run avl and hash table
    void quit();///< called when person no longer wants to create commands
    void permissionDenied(string); ///< command invalid
    string get_filePath(); ///< gets file path

private:
    const string wikiPath; ///< initializes wikibooks.xml as the initial path
    int mode; ///< for setmode function
    bool built; ///< checks if index is built
    bool endSearch; ///< ends search
    bool endProgram; ///< ends program
    string dsBuilt, modeStr, cmd, asr; ///< strings used during the command statements
    IndexHandler handler; ///< called when the index is created
};

#endif // INTERFACE_H
