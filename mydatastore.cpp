#include "mydatastore.h"
#include "util.h"
#include <iostream>

using namespace std;

MyDataStore::MyDataStore()
{
}

MyDataStore::~MyDataStore()
{
    vector<Product*>::iterator pit;

    for(pit = products_.begin(); pit != products_.end(); pit++) {
        delete *pit;
    }

    map<string, User*>::iterator uit;

    for(uit = users_.begin(); uit != users_.end(); uit++) {
        delete uit->second;
    }
}

void MyDataStore::addProduct(Product* p)
{
    products_.push_back(p);

    set<string> words = p->keywords();
    set<string>::iterator it;

    for(it = words.begin(); it != words.end(); it++) {
        string word = convToLower(*it);
        keywordIndex_[word].insert(p);
    }
}

void MyDataStore::addUser(User* u)
{
    string username = convToLower(u->getName());

    users_[username] = u;
    carts_[username] = vector<Product*>();
}

vector<Product*> MyDataStore::search(vector<string>& terms, int type)
{
    vector<Product*> hits;

    if(terms.size() == 0) {
        return hits;
    }

    set<Product*> result;

    if(type == 0) {
        string firstTerm = convToLower(terms[0]);

        map<string, set<Product*> >::iterator it;
        it = keywordIndex_.find(firstTerm);

        if(it == keywordIndex_.end()) {
            return hits;
        }

        result = it->second;

        for(size_t i = 1; i < terms.size(); i++) {
            string term = convToLower(terms[i]);

            it = keywordIndex_.find(term);

            if(it == keywordIndex_.end()) {
                result.clear();
                break;
            }

            result = setIntersection(result, it->second);
        }
    }
    else if(type == 1) {
        for(size_t i = 0; i < terms.size(); i++) {
            string term = convToLower(terms[i]);

            map<string, set<Product*> >::iterator it;
            it = keywordIndex_.find(term);

            if(it != keywordIndex_.end()) {
                result = setUnion(result, it->second);
            }
        }
    }

    set<Product*>::iterator it;

    for(it = result.begin(); it != result.end(); it++) {
        hits.push_back(*it);
    }

    return hits;
}

void MyDataStore::dump(ostream& ofile)
{
    ofile << "<products>" << endl;

    vector<Product*>::iterator pit;

    for(pit = products_.begin(); pit != products_.end(); pit++) {
        (*pit)->dump(ofile);
    }

    ofile << "</products>" << endl;

    ofile << "<users>" << endl;

    map<string, User*>::iterator uit;

    for(uit = users_.begin(); uit != users_.end(); uit++) {
        uit->second->dump(ofile);
    }

    ofile << "</users>" << endl;
}

bool MyDataStore::addToCart(string username, Product* p)
{
    username = convToLower(username);

    if(users_.find(username) == users_.end()) {
        return false;
    }

    carts_[username].push_back(p);

    return true;
}

bool MyDataStore::viewCart(string username)
{
    username = convToLower(username);

    if(users_.find(username) == users_.end()) {
        return false;
    }

    vector<Product*>& cart = carts_[username];

    for(size_t i = 0; i < cart.size(); i++) {
        cout << "Item " << i + 1 << endl;
        cout << cart[i]->displayString() << endl;
        cout << endl;
    }

    return true;
}

bool MyDataStore::buyCart(string username)
{
    username = convToLower(username);

    map<string, User*>::iterator userIt;
    userIt = users_.find(username);

    if(userIt == users_.end()) {
        return false;
    }

    User* user = userIt->second;
    vector<Product*>& cart = carts_[username];

    vector<Product*>::iterator it = cart.begin();

    while(it != cart.end()) {
        Product* p = *it;

        if(p->getQty() > 0 &&
           user->getBalance() >= p->getPrice()) {

            p->subtractQty(1);
            user->deductAmount(p->getPrice());

            it = cart.erase(it);
        }
        else {
            it++;
        }
    }

    return true;
}