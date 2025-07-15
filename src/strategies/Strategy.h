#pragma once

#include <vector>
#include "../lob_engine/OrderBook.h"


class OrderBook;

struct Quote {
    int id;
    Side side;
    double price;
    int quantity;
    
    
    Quote(int id, Side side, double price, int quantity)
        : id(id), side(side), price(price), quantity(quantity) {}
};

class Strategy {
public:
    virtual ~Strategy() = default;
    
    
    virtual std::vector<Quote> generateQuotes(const OrderBook& orderBook) = 0;
    
    
    virtual void setParameters(const std::map<std::string, double>& params) = 0;
    
    virtual void onTrade(const Trade& trade) = 0;
    virtual void reset() = 0;
}; 