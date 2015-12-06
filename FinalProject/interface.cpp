/* Search Engine Project
 * CSE 2341: Data Stuctures
 * 05/03/2015
 * Nate O'Toole
 * Kiko Whiteley
 **/

#include "interface.h"

Interface::Interface()
    : built(false), endProgram(false), mode(0), wikiPath("WikiBooks.xml")
{
    cout << "\nWelcome to KITESearch!\n" << endl;
    choose_structure();
}

void Interface::choose_structure(){
    string ds;
    cout<< "Choose a data structure to store WikiBooks information:\n";
    cout<< "=>\tHashTable\n=>\tAVLTree\n";
    cin >> ds;
    ds = toLowerCase(ds);
    cout << "Your choice was " << ds << endl;

    while (!built){
        if(ds.substr(0,3) == "avl"){
            run_AVL();
        }else if (ds.substr(0,4) == "hash"){
            run_hash();
        }else {
            cout<< "sorry. I did not understand " << ds <<endl;
            choose_structure();
        }
    }
    cout << "Now that the " << dsBuilt  << " is built" << endl;
    set_mode();
}


void Interface::set_mode(){
    while(!endProgram){
        cout<< "Enter the Mode" << endl;
        cout<< "=> Interactive" << endl;
        cout<< "=> Maintenance" << endl;
        cout << "Mode: ";
        cin >> modeStr;
        modeStr = toLowerCase(modeStr);
        bool check = false;
        while(!check){
            if (modeStr == "interactive" ){
                cout << " You have selected " << modeStr <<endl;
                mode = 1;
                modeStr= "";
                run_interactive();
            }
            else if (modeStr == "maintenance"){
                cout << " You have selected " << modeStr <<endl;
                mode = 2;
                modeStr = "";
                run_maintenance();
            }
            else{
                cout<< "Invalid command \""<< modeStr << "\""<< endl;
                cout<< "\nEnter the Mode" << endl;
                cout<< "=> Interactive" << endl;
                cout<< "=> Maintenance" << endl;
                cout << "Mode: ";
                cin >> modeStr;
                modeStr = toLowerCase(modeStr);
            }
        }
    }
}
void Interface::get_command(){

    cout<< "Enter command: ";
    cin >> cmd;
    cmd = toLowerCase(cmd);
    cout << "Your command was " << cmd << endl;
    cout << "correct? (yes or no)" << endl;
    cin >> asr;
    asr = toLowerCase(asr);
    if (asr == "no") re_command();
    else if (asr == "yes") command(cmd,asr);
    else {
        cout<<"Invalid answer\n";
        get_command();
    }
}

void Interface::command(string cmd, string asr){
    bool check = false;
    while(!check){
        if (asr == "yes"){
            if(mode == 1){
                if (cmd == ""){
                    cout << "There was no command" << endl;
                    run_interactive();
                }else if(cmd == "search"){
                    search();
                    
                }else if(cmd == "options"){
                    run_interactive();
                }else if(cmd == "setmode"){
                    set_mode();
                }else if (cmd == "runavl"){
                    if (dsBuilt == "AVL Tree")
                    {
                        cout << "AVL is already built.  Would you like to add a file to\nthis index? (yes or no) \n";
                        cin >> asr;
                        asr = toLowerCase(asr);
                        while (!((asr == "yes") || (asr == "no")))
                        {
                            cout<<"Invalid command.  Reenter \"yes\" or \"no\"\n";
                            cin >> asr;
                            asr = toLowerCase(asr);
                        }
                        if (asr == "yes")
                        {
                            cout<<"Please provide the file path\n";
                            cin >> asr;
                            add_file_to_index(asr);
                            asr.clear();
                            re_command();
                        }
                    }
                    else if (dsBuilt == "Hash Table")
                    {
                        cout<< "switch index from Hash Table to AVL Tree" <<endl;
                        clear_index();
                        run_AVL();
                    }
                }else if(cmd == "runhash"){
                    if (dsBuilt == "Hash Table")
                    {
                        cout << "Hash Table is already built.  Would you like to add a file to\nthis index? (yes or no) \n";
                        cin >> asr;
                        asr = toLowerCase(asr);
                        while (!((asr == "yes") || (asr == "no")))
                        {
                            cout<<"Invalid command.  Reenter \"yes\" or \"no\"\n";
                            cin >> asr;
                            asr = toLowerCase(asr);
                        }
                        if (asr == "yes")
                        {
                            cout<<"Please provide the file path\n";
                            cin >> asr;
                            add_file_to_index(asr);
                            asr.clear();
                            re_command();
                        }
                    }
                    else if (dsBuilt == "AVL Tree")
                    {
                        cout<< "switch index from Hash Table to AVL Tree" <<endl;
                        clear_index();
                        run_hash();
                    }
                }else if(cmd == "addfile"){
                    permissionDenied(cmd);
                }else if (cmd == "clearindex"){
                    permissionDenied(cmd);
                }else if(cmd == "quit"){
                    quit();
                } else {
                    cout<<"I did not understand that command";
                    run_interactive();
                }
            }else if (mode == 2){
                if(cmd == "clearindex"){
                    clear_index();
                    re_command();
                }else if(cmd == "addfile"){
                    string path;
                    cout<< "please input the file path to the file you would like to add to the index" << endl;
                    cout<< " to go back type back or type anything else to continue"<<endl;
                    cout << ":"<<endl;
                    cin >> path;
                    if (path != "back"){
                        cout << "File Path = "<< path <<endl;
                        add_file_to_index(path);
                        re_command();
                    }else{
                        run_maintenance();
                    }
                }else if(cmd == "setmode"){
                    set_mode();
                }else if(cmd == "search"){
                    permissionDenied(cmd);
                }else if (cmd == "runavl"){
                    permissionDenied(cmd);
                }else if(cmd == "runhash"){
                    permissionDenied(cmd);
                }else if(cmd == "options"){
                    run_interactive();
                }else if(cmd == "quit"){
                    quit();
                }else{
                    cout<<"I did not understand that command" << endl;
                    run_maintenance();
                }
            }
        }else if (asr == "no"){
            cout << "returning" <<endl;
            re_command();
        }else {
            cout<< "I did not understand '"<< asr << "'"<< endl;
            cout << "Your command was " << cmd << endl;
            cout << "correct? (yes or no)" << endl;
            cin >> asr;
            asr = toLowerCase(asr);
        }
    }
}

void Interface::run_interactive(){
    cout << " \nInteractive Mode" << endl;
    cout << "Here are the commands we have available" << endl;
    cout << "   => setMode" <<endl;
    cout << "   => search" << endl;
    cout << "   => runAVL" << endl;
    cout << "   => runHash" << endl;
    cout << "   => type options to repeat these options at any time" << endl;
    get_command();
}

void Interface::run_maintenance(){
    cout << "Maintenance Mode:" <<endl;
    cout << "Here are the commands we have available" << endl;
    cout << "   => setMode" <<endl;
    cout << "   => clearIndex" << endl;
    cout << "   => addFile" << endl;
    get_command();
}

void Interface::search(){
   string sQuery = "";
   string mQuery = "";
   string input = "";
   cout<< "You Chose Search!" << endl;
   cout << "      Use 'AND' at the beginnign of your query to docs with both words in them" << endl;
   cout << "      Use 'OR' at the beginning of your query to get docs that have any of the words in them" << endl;
   cout << "      Use 'NOT' in between results with words to exclude results" << endl;
   cout << "      Enclose two words in '[' and ']' delimited by a space" << endl;
   cout << "      If you enclose more then two words for search, you'll be asked to put new criteria for search" << endl;
   cout << "      Examples: AND Boston NOT Pig"<< endl;
   cout << "                OR Boston Pig"<< endl;
   cout << "                Boston" << endl;
   cout << "Please enter your query here: " << endl;
   cin >> input;

   getline(cin, sQuery);
   sQuery = input +=  sQuery ;
   istringstream streamQuery(sQuery);
   string fWord;
    streamQuery >> fWord;
    transform(streamQuery.begin(), streamQuery.end(), streamQuery.begin(), ::tolower);
   if (fWord == "AND" || fWord == "OR")

   //  Check for two-word
    bool multi = false;
   if (sQuery[0] == '[')
   {
       //  Check if more then two words
       int i = 0;
       int numb_of_words = 1;
       while (sQuery[i] != ']')
       {
           if (sQuery[i] == ' ')
               numb_of_words ++;

           if (numb_of_words > 2)
           {
               cout << "Multi-words can only be two words" << endl;
               search();
           }

           i++;
       }
      multi = true;
      // mQuery = sQuery.substr(1, sQuery.length()-2);
      // sQuery = mQuery;
   }

   cout << "Searching for " << sQuery << endl;
   handler.run_queries(sQuery, multi);

   search();
}












/*void Interface::search(){
    string sQuery = "";
    string input = "";
    cout<< "You Chose Search!" << endl;
    cout << "      Use 'AND' at the beginnign of your query to docs with both words in them" << endl;
    cout << "      Use 'OR' at the beginning of your query to get docs that have any of the words in them" << endl;
    cout << "      Use 'NOT' in between results with words to exclude results" << endl;
    cout << "      Examples: AND Boston NOT Pig"<< endl;
    cout << "                OR Boston Pig"<< endl;
    cout << "                Boston" << endl;
    cout << "Please enter your query here: " << endl;
    cin >> input;
    getline(cin, sQuery);
    sQuery = input +=  sQuery ;
    handler.run_queries(sQuery);
    
    re_command();
}
*/
void Interface::run_AVL(){
    Timer t = Timer("AVL Tree");
    if(built == true){
        clear_index();
    }
    cout<< "Building AVL Tree" << endl;
    cout<< "Building..." << endl;
    handler = IndexHandler(false);
    handler.read_file(wikiPath);
    cout<< "AVL Tree Built" << endl;
    built = true;
    dsBuilt = "AVL Tree";
}

void Interface::run_hash(){
    Timer t = Timer("Hash Table");
    if(built == true){
        clear_index();
    }
    cout<< "Building Hash Table" << endl;
    cout<< "Building..." << endl;
    handler = IndexHandler(true);
    handler.read_file(wikiPath);
    cout<< "Hash Table Built" << endl;
    built = true;
    dsBuilt = "Hash Table";
}
void Interface::add_file_to_index(string path){
    ifstream isInBuildDirectory(path);
    if (isInBuildDirectory)
    {
        handler.read_file(path);
        cout<<"File added.\n"<<endl;

    }
    else cout<<"File not found for the provided path.\n";
}
void Interface::permissionDenied(string w){
    string asr = "";
    bool t = false;
    if (mode == 1){
        cout << "You are in ineractive mode" << endl;
        cout << "you are not allowed to call " << w << "in interactive mode" << endl;
        cout << "Would you like to switch to maintenance and run the command? (yes or no)" << endl;
        cin >> asr;
        asr = toLowerCase(asr);
        while(!t){
            if (asr == "yes"){
                mode = 2;
                t = true;
                command(w, "yes");
            }else if (asr == "no"){
                t = true;
                run_interactive();
            }else{
                cout<< "I did not understand '"<< asr << "'"<< endl;
                t = true;
                permissionDenied(w);
            }
        }
    }else if (mode == 2){
        cout << "You are in maintenance mode" << endl;
        cout << "you are not allowed to call " << w << "in maintenance mode" << endl;
        cout << "Would you like to switch to interactive and run the command? (yes or no)" << endl;
        cin >> asr;
        asr = toLowerCase(asr);
        while(!t){
            if (asr == "yes"){
                mode = 1;
                t = true;
                command(w, "yes");
            }else if (asr == "no"){
                t = true;
                run_maintenance();
            }else{
                cout<< "I did not understand '"<< asr << "'"<< endl;
                t = true;
                permissionDenied(w);
            }
        }
    }
    
}

//if they want to perform another command
void Interface::re_command(){
    string asr = "";
    bool end = false;
    while (!endProgram)
    {
        cout<< "would you like to perform another command? (yes or no) " << endl;
        cin >> asr;
        asr = toLowerCase(asr);
        while (!end){
            if(asr == "yes"){
                if (mode == 1){
                    run_interactive();
                }else if (mode == 2){
                    run_maintenance();
                }
            }else if(asr == "no"){
                quit();
                end = true;
                endProgram = true;
            }else{
                cout << "Im sorry. I didnt understand "<< asr <<endl;
                end = true;
                re_command();
            }
        }
    }
}

void Interface::clear_index(){
    if (built == true){
        handler.clear_index();
        built = false;
    }
    cout <<"The Index has been emptied\n" << endl;
    dsBuilt.clear();
    choose_structure();
}


void Interface::quit(){
    cout<<"Thank you very much for using KITESearch!" << endl;
    clear_index();
    exit(1);
    exit(1);
}

string Interface::toLowerCase(string w){
    for(int i = 0; i < w.length(); i ++){
        w[i] = tolower(w[i]);
    }
    return w;
}

