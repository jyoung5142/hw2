#include "book.h"
#include "util.h"
#include <sstream>

using namespace std;

Book::Book(const string category, const string name, double price, int qty, const string isbn, const string author) : Product(category, name, price, qty), isbn_(isbn), author_(author)
{

}

Book::~Book()
{
}

set<string> Book::keywords() const
{
    set<string> returnSet;
    returnSet = parseStringToWords(name_);
    set<string> authorWords;
    authorWords = parseStringToWords(author_);
    returnSet = setUnion(returnSet, authorWords);
    returnSet.insert(convToLower(isbn_));
    return returnSet;
}

string Book::displayString() const
{
    stringstream ss;
    ss << name_ << endl;
    ss << "Author: " << author_ << " ISBN: " << isbn_ << endl;
    ss << price_ << " " << qty_ << " left.";
    return ss.str();
}

void Book::dump(ostream& os) const
{
    Product::dump(os);

    os << isbn_ << endl;
    os << author_ << endl;
}