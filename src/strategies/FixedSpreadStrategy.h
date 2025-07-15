#pragma once

#include "Strategy.h"
#include <map>

class FixedSpreadStrategy : public Strategy {
public:
    FixedSpreadStrategy(double spread = 1.0, int quantity = 100);
    
    std::vector<Quote> generateQuotes(const OrderBook& orderBook) override;
    void setParameters(const std::map<std::string, double>& params) override;
    void onTrade(const Trade& trade) override;
    void reset() override;

private:
    double spread_;
    int quantity_;
    int nextOrderId_;
    
    
    double getBestBid(const OrderBook& orderBook) const;
    double getBestAsk(const OrderBook& orderBook) const;
    double getMidPrice(const OrderBook& orderBook) const;
}; 