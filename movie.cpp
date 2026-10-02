#include "movie.h"
#include "util.h"
#include <sstream>

using namespace std;

Movie::Movie(string category, string name, double price, int qty,
             string genre, string rating)
    : Product(category, name, price, qty),
      genre_(genre),
      rating_(rating)
{
}

Movie::~Movie()
{
}

set<string> Movie::keywords() const
{
    set<string> result = parseStringToWords(name_);
    result.insert(convToLower(genre_));

    return result;
}

string Movie::displayString() const
{
    stringstream ss;

    ss << name_ << endl;
    ss << "Genre: " << genre_ << " Rating: " << rating_ << endl;
    ss << price_ << " " << qty_ << " left.";

    return ss.str();
}

void Movie::dump(ostream& os) const
{
    Product::dump(os);
    os << genre_ << endl;
    os << rating_ << endl;
}