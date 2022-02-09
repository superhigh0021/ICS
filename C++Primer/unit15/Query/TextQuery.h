#pragma once
#include "QueryResult.h"
#include <fstream>
#include <sstream>

class TextQuery {
public:
    TextQuery(std::ifstream&);
    QueryResult query(const std::string&) const;
    void show_set(){
        for(auto i:wm)
            cout<<i.first<<' ';
    }

private:
    // QueryResult需要的结果是TextQuery的内部成员
    // 如果直接使用数据结构可能会造成过程中的拷贝代价太大
    // 因此可以用指向该数据机构的指针来维护数据
    std::shared_ptr<std::vector<std::string>> file;
    std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
    static std::string clean_up(const std::string&);
};

TextQuery::TextQuery(ifstream& is)
    : file(new vector<string>) {
    string text;
    while (getline(is, text)) {
        file->push_back(text);
        int n = file->size() - 1;
        istringstream line(text);
        string word;
        while (line >> word) {
            //如果单词不在wm中，以之为下标在wm中添加一项
            word=clean_up(word);
            auto& lines = wm[word];
            if (!lines)
                lines.reset(new set<line_no>);
            lines->insert(n);
        }
    }
}

QueryResult TextQuery::query(const string& sought) const {
    //如果未找到sought，返回一个指向此set的指针
    static shared_ptr<set<line_no>> nodata(new set<line_no>);
    auto loc = wm.find(clean_up(sought));
    if (loc == wm.end())
        return QueryResult(sought, nodata, file);
    else
        return QueryResult(sought, loc->second, file);
}

std::string TextQuery::clean_up(const std::string& str) {
    string ret{""};
    for (auto i : str)
        if (!ispunct(i))
            ret += i;
    return ret;
}