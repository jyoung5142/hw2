#include "clothing.h"
#include "util.h"
#include <sstream>

using namespace std;

Clothing::Clothing(string category, string name, double price, int qty,
                   string size, string brand)
    : Product(category, name, price, qty),
      size_(size),
      brand_(brand)
{
}

Clothing::~Clothing()
{
}

set<string> Clothing::keywords() const
{
    set<string> result = parseStringToWords(name_);
    set<string> brandWords = parseStringToWords(brand_);

    result = setUnion(result, brandWords);

    return result;
}

string Clothing::displayString() const
{
    stringstream ss;

    ss << name_ << endl;
    ss << "Size: " << size_ << " Brand: " << brand_ << endl;
    ss << price_ << " " << qty_ << " left.";

    return ss.str();
}

void Clothing::dump(ostream& os) const
{
    Product::dump(os);
    os << size_ << endl;
    os << brand_ << endl;
}