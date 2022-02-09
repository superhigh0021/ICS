#pragma once

//这是管理Query_base继承体系的接口类

#include "WordQuery.h"

class Query {
    friend Query operator~(const Query&);
    friend Query operator|(const Query&, const Query&);
    friend Query operator&(const Query&, const Query&);

public:
    Query(const std::string&);
    QueryResult eval(const TextQuery& t) const { return q->eval(t); }
    std::string rep() const { return q->rep(); }

private:
    Query(std::shared_ptr<Query_base> query)
        : q(query) {}

    //!这玩意儿才是重中之重
    std::shared_ptr<Query_base> q;
};

inline Query::Query(const std::string& s)
    : q(new WordQuery(s)) {}

std::ostream& operator<<(std::ostream& os, const Query& query) {
    return os << query.rep();
}