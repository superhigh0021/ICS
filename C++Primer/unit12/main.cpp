#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <numeric>
#include <set>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

using line_no = std::vector<std::string>::size_type;

class QueryResult;

class TextQuery {
public:
    TextQuery(std::ifstream&);
    QueryResult query(const std::string&) const;

private:
    // QueryResult需要的结果是TextQuery的内部成员
    // 如果直接使用数据结构可能会造成过程中的拷贝代价太大
    // 因此可以用指向该数据机构的指针来维护数据
    std::shared_ptr<std::vector<std::string>> file;
    std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};

TextQuery::TextQuery(ifstream& is) : file(new vector<string>) {
    string text;
    while (getline(is, text)) {
        file->push_back(text);
        int n = file->size() - 1;
        istringstream line(text);
        string word;
        while (line >> word) {
            //如果单词不在wm中，以之为下标在wm中添加一项
            auto& lines = wm[word];
            if (!lines)
                lines.reset(new set<line_no>);
            lines->insert(n);
        }
    }
}

class QueryResult {
    friend std::ostream& print(std::ostream&, const QueryResult&);

public:
    QueryResult(std::string s,
                std::shared_ptr<std::set<line_no>> p,
                std::shared_ptr<std::vector<std::string>> f) : sought(s), lines(p), file(f) {}

private:
    std::string sought; //查询单词
    std::shared_ptr<std::set<line_no>> lines;
    std::shared_ptr<std::vector<std::string>> file;
};

QueryResult TextQuery::query(const string& sought) const {
    //如果未找到sought，返回一个指向此set的指针
    static shared_ptr<set<line_no>> nodata(new set<line_no>);
    auto loc = wm.find(sought);
    if (loc == wm.end())
        return QueryResult(sought, nodata, file);
    else
        return QueryResult(sought, loc->second, file);
}

ostream& print(ostream& os,const QueryResult &qr){
    os<<qr.sought<<" occurs "<<qr.lines->size()<<" times"<<endl;
    for(auto num:*qr.lines)
    os<<"\t(line"<<num+1<<")"<<*(qr.file->begin()+num)<<endl;
    return os;
}

void runQueries(ifstream& infile) {
    TextQuery tq(infile);
    while (true) {
        cout << "enter word to look for, or q to quit: ";
        string s;
        if (!(cin >> s) || s == "q") break;
        print(cout, tq.query(s)) << endl;
    }
}

int main(int argc,char**argv){
    ifstream file("text.txt");
    runQueries(file);

    return 0;
}