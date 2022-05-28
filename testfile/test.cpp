#include <functional>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

class String {
public:
    //friend size_t hasher(const String& s);
    String(string s)
        : sstr(s) {}
    bool operator==(const String& s)const {
        return this->sstr == s.sstr;
    }
    string str()const{
        return sstr;
    }

private:
    string sstr;
};

namespace std{
template<>
struct hash<String>{
    typedef size_t result_type;
    typedef String argument_type;
    size_t operator()(const String& s)const{
        return hash<string>()(s.str());
    }
};
}

struct op{
    size_t operator()(const String& s)const{
        return hash<string>()(s.str());
    }
};

int main() {

    String ss("abc");
    unordered_set<String,op> s(42);
    s.insert(ss);

    return 0;
}