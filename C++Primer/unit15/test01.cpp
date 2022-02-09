#include <iostream>
#include <memory>
#include <set>
using namespace std;

class Quote {
public:
    Quote() = default;
    Quote(const std::string& book, double sales_price)
        : bookNo(book), price(sales_price) {}
    std::string isbn() const { return bookNo; }
    virtual double net_price(std::size_t n) const { return n * price; }
    virtual ~Quote() = default;

private:
    std::string bookNo;

protected:
    double price = 0.0;
};

class Disc_quote : public Quote {
public:
    Disc_quote() = default;
    Disc_quote(const std::string& book, double price, std::size_t qty, double disc)
        : Quote(book, price), quantity(qty), discount(disc) {}
    virtual double next_price(std::size_t) const = 0;

protected:
    std::size_t quantity = 0;
    double discount = 0.0;
};

class Bulk_quote : public Disc_quote {
public:
    Bulk_quote() = default;
    Bulk_quote(const std::string& book, double pricfe, std::size_t qty, double disc)
        : Disc_quote(book, price, qty, disc) {}
    double net_price(std::size_t) const override;
};

class Basket {
public:
    friend void print_static(const Basket& b);
    void add_item(const std::shared_ptr<Quote>& sale) {
        items.insert(sale);
    }
    double total_receipt(std::ostream&) const;

private:
    static bool compare(const std::shared_ptr<Quote>& lhs, const std::shared_ptr<Quote>& rhs) {
        return lhs->isbn() < rhs->isbn();
    }
    std::multiset<std::shared_ptr<Quote>, decltype(compare)*> items{compare};
};

double print_total(ostream& os, const Quote& item, size_t n) {
    double ret = item.net_price(n);
    os << "ISBN: " << item.isbn()
       << " # sold: " << n << " total due: " << ret << endl;
    return ret;
}


int main(void) {
    return 0;
}