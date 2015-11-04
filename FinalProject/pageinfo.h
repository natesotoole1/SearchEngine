#ifndef PAGEINFO_H
#define PAGEINFO_H

#include <string>

using namespace std;
/*! \brief
 *  In the inverted index, pages are assigned integer IDs to improve performance.
 *  PageInfo objects hold the data corresponding with said IDs.
 */
class PageInfo
{
public:
    PageInfo();
    ~PageInfo();
    PageInfo(string theContent, string theContributor, string theTimestamp, string theTitle); ///< The only constructor ever called.

    // Getters.
    string get_content();
    string get_contributor();
    string get_timestamp();
    string get_title();
    int get_totalWords();

    // Setters.
    void set_content(string theContent);
    void set_contributor(string theInfo);
    void set_timestamp(string theTimestamp);
    void set_title(string theTitle);
    void set_totalWords(int theTotal);

    void incr_totalWords(int incr); ///< Increment totalWords by a given value.
private:
    string content;
    string contributorNameOrIP;
    string timestamp;
    string title;
    int totalWords;
};

#endif // PAGEINFO_H
