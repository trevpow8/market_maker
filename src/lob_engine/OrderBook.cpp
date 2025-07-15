#include "OrderBook.h"
#include <algorithm>    


template<typename BookType>
void OrderBook::matchAgainst(BookType& bookRef,
                             Order& incoming,
                             std::vector<Trade>& trades)
{
    
    while (incoming.quantity > 0 && !bookRef.empty()) {
        
        auto it = bookRef.begin();
        double priceLevel = it->first;

        
        bool crosses = (incoming.side == Side::Bid)
            ? (incoming.price >= priceLevel)  
            : (incoming.price <= priceLevel); 

        if (!crosses) 
            break;

        
        auto& ordersAtPrice = it->second; 
        for (auto ordIt = ordersAtPrice.begin();
             ordIt != ordersAtPrice.end() && incoming.quantity > 0; )
        {
            int  contraId   = ordIt->first;
            int& contraQty  = ordIt->second;
            int  tradeQty   = std::min(contraQty, incoming.quantity);

            trades.emplace_back(contraId, tradeQty, priceLevel);

            contraQty        -= tradeQty;
            incoming.quantity -= tradeQty;

            if (contraQty == 0)
                ordIt = ordersAtPrice.erase(ordIt);
            else
                ++ordIt;
        }

        if (ordersAtPrice.empty())
            bookRef.erase(it);
    }
}

std::vector<Trade> OrderBook::addOrder(const Order& o) {
    std::vector<Trade> trades;
    Order incoming = o;  

    if (incoming.side == Side::Bid) {
        auto& bookRef = asks_;   
        matchAgainst(bookRef, incoming, trades);
    } else {
        auto& bookRef = bids_;   
        matchAgainst(bookRef, incoming, trades);
    }

    if (incoming.quantity > 0) {
        if (incoming.side == Side::Bid) {
            bids_[incoming.price][incoming.id] = incoming.quantity;
        } else {
            asks_[incoming.price][incoming.id] = incoming.quantity;
        }
    }

    return trades;
}

double OrderBook::getBestBid() const {
    if (bids_.empty()) {
        return 0.0;
    }
    return bids_.begin()->first;
}

double OrderBook::getBestAsk() const {
    if (asks_.empty()) {
        return 0.0;
    }
    return asks_.begin()->first;
}

double OrderBook::getMidPrice() const {
    double bestBid = getBestBid();
    double bestAsk = getBestAsk();
    
    if (bestBid <= 0 || bestAsk <= 0) {
        return 0.0;
    }
    
    return (bestBid + bestAsk) / 2.0;
}