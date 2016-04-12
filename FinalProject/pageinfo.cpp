/* Search Engine Project
 * CSE 2341: Data Stuctures
 * 12/06/15
 * Nate O'Toole
 * Brandon McFarland
 * Ashvin Asava
 **/
#include "pageinfo.h"

PageInfo::PageInfo()
{

}

PageInfo::~PageInfo()
{

}

PageInfo::PageInfo(string theContent, string theContributor, string theTimestamp, string theTitle)
    : totalWords(0), content(theContent), contributorNameOrIP(theContributor), timestamp(theTimestamp), title(theTitle)
{

}

string PageInfo::get_content()
{
    return content;
}

string PageInfo::get_contributor()
{
    return contributorNameOrIP;
}

string PageInfo::get_timestamp()
{
    return timestamp;
}

string PageInfo::get_title()
{
    return title;
}

int PageInfo::get_totalWords()
{
    return totalWords;
}

void PageInfo::set_content (string theContent)
{
    content = theContent;
}

void PageInfo::set_contributor(string theInfo)
{
    contributorNameOrIP = theInfo;
}

void PageInfo::set_timestamp(string theTimestamp)
{
    timestamp = theTimestamp;
}

void PageInfo::incr_totalWords(int incr)
{
    totalWords += incr;
}

void PageInfo::set_title(string theTitle)
{
    title = theTitle;
}

void PageInfo::set_totalWords(int theTotal)
{
    totalWords = theTotal;
}
