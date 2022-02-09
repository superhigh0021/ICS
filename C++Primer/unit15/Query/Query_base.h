#pragma once
#include "TextQuery.h"

class Query_base {
    friend class Query;

protected:
    virtual ~Query_base() = default;

private:
    virtual QueryResult eval(const TextQuery&) const = 0;
    virtual std::string rep() const = 0;
};