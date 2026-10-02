#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
    std::set<T> returnSet;

    typename std::set<T>::iterator it;

    for(it = s1.begin(); it!= s1.end(); ++it){
        //find will return end if it doesn't find *it 
        if(s2.find(*it) != s2.end()){
            returnSet.insert(*it);
        }
    }

    return returnSet;
}
template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
    //can literally just insert both sets and non-unique values will cancel out
    std::set<T> returnSet = s1;

    typename std::set<T>::iterator it;

    for(it = s2.begin(); it != s2.end(); ++it) {
        returnSet.insert(*it);
    }
    return returnSet;
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
