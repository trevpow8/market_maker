#include "FixedSpreadStrategy.h"
#include "../lob_engine/OrderBook.h"

FixedSpreadStrategy::FixedSpreadStrategy(double spread, int quantity)
    : spread_(spread), quantity_(quantity), nextOrderId_(1) {
}

std::vector<Quote> FixedSpreadStrategy::generateQuotes(const OrderBook& orderBook) {
    std::vector<Quote> quotes;
    
    double bestBid = getBestBid(orderBook);
    double bestAsk = getBestAsk(orderBook);
    
    if (bestBid <= 0 || bestAsk <= 0) {
        return quotes;
    }
    
    double midPrice = getMidPrice(orderBook);
    
    double bidPrice = midPrice - spread_ / 2.0;
    double askPrice = midPrice + spread_ / 2.0;
    
    if (bidPrice > bestBid) {
        quotes.emplace_back(nextOrderId_++, Side::Bid, bidPrice, quantity_);
    }
    
    if (askPrice < bestAsk) {
        quotes.emplace_back(nextOrderId_++, Side::Ask, askPrice, quantity_);
    }
    
    return quotes;
}

void FixedSpreadStrategy::setParameters(const std::map<std::string, double>& params) {
    auto it = params.find("spread");
    if (it != params.end()) {
        spread_ = it->second;
    }
    
    it = params.find("quantity");
    if (it != params.end()) {
        quantity_ = static_cast<int>(it->second);
    }
}

void FixedSpreadStrategy::onTrade(const Trade& trade) {
    (void)trade; 
}

void FixedSpreadStrategy::reset() {
    nextOrderId_ = 1;
}

double FixedSpreadStrategy::getBestBid(const OrderBook& orderBook) const {
    return orderBook.getBestBid();
}

double FixedSpreadStrategy::getBestAsk(const OrderBook& orderBook) const {
    return orderBook.getBestAsk();
}

double FixedSpreadStrategy::getMidPrice(const OrderBook& orderBook) const {
    return orderBook.getMidPrice();
} 