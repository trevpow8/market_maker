#include "Simulator.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

Simulator::Simulator(std::unique_ptr<Strategy> strategy)
    : strategy_(std::move(strategy)), currentTime_(0.0) {
}

bool Simulator::loadEventsFromCSV(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return false;
    }
    
    std::string line;
    // Skip header
    std::getline(file, line);
    
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        
        MarketEvent event;
        
        // Parse CSV line: timestamp,orderId,side,price,quantity
        std::getline(ss, token, ',');
        event.timestamp = std::stod(token);
        
        std::getline(ss, token, ',');
        event.orderId = std::stoi(token);
        
        std::getline(ss, token, ',');
        event.side = (token == "BID") ? Side::Bid : Side::Ask;
        
        std::getline(ss, token, ',');
        event.price = std::stod(token);
        
        std::getline(ss, token, ',');
        event.quantity = std::stoi(token);
        
        events_.push_back(event);
    }
    
    // Sort events by timestamp
    std::sort(events_.begin(), events_.end(), 
              [](const MarketEvent& a, const MarketEvent& b) {
                  return a.timestamp < b.timestamp;
              });
    
    return true;
}

void Simulator::run() {
    reset();
    
    for (const auto& event : events_) {
        currentTime_ = event.timestamp;
        
        // Process external market event
        processEvent(event);
        
        // Run strategy to generate quotes
        processStrategyQuotes();
    }
    
    // Final P&L calculation
    double finalPrice = orderBook_.getMidPrice();
    if (finalPrice > 0) {
        pnlCollector_.addHistoryPoint(currentTime_, finalPrice);
    }
}

void Simulator::processEvent(const MarketEvent& event) {
    Order order{event.orderId, event.side, event.price, event.quantity};
    auto trades = orderBook_.addOrder(order);
    processTrades(trades);
}

void Simulator::processStrategyQuotes() {
    // Generate quotes from strategy
    auto quotes = strategy_->generateQuotes(orderBook_);
    
    // Submit quotes to order book
    for (const auto& quote : quotes) {
        Order order{quote.id, quote.side, quote.price, quote.quantity};
        auto trades = orderBook_.addOrder(order);
        processTrades(trades);
        
        // Track our active orders
        activeOrders_.push_back(quote.id);
    }
}

void Simulator::processTrades(const std::vector<Trade>& trades) {
    double currentPrice = orderBook_.getMidPrice();
    
    for (const auto& trade : trades) {
        // Update P&L
        pnlCollector_.onTrade(trade, currentPrice);
        
        // Notify strategy of trade
        strategy_->onTrade(trade);
    }
}

void Simulator::exportResults(const std::string& filename) const {
    pnlCollector_.exportToCSV(filename);
}

void Simulator::reset() {
    orderBook_ = OrderBook();
    pnlCollector_.reset();
    strategy_->reset();
    currentTime_ = 0.0;
    activeOrders_.clear();
} 