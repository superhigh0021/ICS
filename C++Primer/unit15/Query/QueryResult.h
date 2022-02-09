#pragma once
#include<iostream>
#include<set>
#include<map>
#include<memory>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

using line_no = std::vector<std::string>::size_type;


class QueryResult {
    friend std::ostream& print(std::ostream&, const QueryResult&);

public:
    QueryResult(std::string s,
                std::shared_ptr<std::set<line_no>> p,
                std::shared_ptr<std::vector<std::string>> f)
        : sought(s), lines(p), file(f) {}
    auto begin(){return lines->cbegin();}
    auto end(){return lines->cend();}
    auto get_file(){return file;}

private:
    std::string sought; //查询单词
    std::shared_ptr<std::set<line_no>> lines;
    std::shared_ptr<std::vector<std::string>> file;
};

ostream& print(ostream& os,const QueryResult &qr){
    os<<qr.sought<<" occurs "<<qr.lines->size()<<" times"<<endl;
    for(auto num:*qr.lines)
    os<<"\t(line"<<num+1<<")"<<*(qr.file->begin()+num)<<endl;
    return os;
}