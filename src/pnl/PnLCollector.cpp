#include "PnLCollector.h"
#include <fstream>
#include <iostream>
#include <iomanip>

PnLCollector::PnLCollector(double initialCash)
    : cash_(initialCash), position_(0), realizedPnL_(0.0), avgPrice_(0.0) {
}

void PnLCollector::onTrade(const Trade& trade, double currentPrice) {
    int contraId = std::get<0>(trade);
    int qty = std::get<1>(trade);
    double price = std::get<2>(trade);
    
    // Determine if this was a buy or sell for our strategy
    // For now, we'll assume positive position means we're long
    // This logic might need to be refined based on your specific needs
    
    if (position_ >= 0) {
        // We're buying (increasing position)
        double cost = qty * price;
        cash_ -= cost;
        position_ += qty;
        
        // Update average price
        if (position_ > 0) {
            avgPrice_ = (avgPrice_ * (position_ - qty) + cost) / position_;
        }
    } else {
        // We're selling (decreasing position)
        double proceeds = qty * price;
        cash_ += proceeds;
        position_ += qty;
        
        // Calculate realized P&L if we're closing a position
        if (position_ == 0) {
            realizedPnL_ += proceeds - (avgPrice_ * qty);
            avgPrice_ = 0.0;
        }
    }
    
    // Add history point
    addHistoryPoint(0.0, currentPrice); // TODO: Add proper timestamp
}

double PnLCollector::getMarkToMarket(double currentPrice) const {
    return cash_ + (position_ * currentPrice);
}

double PnLCollector::getUnrealizedPnL(double currentPrice) const {
    if (position_ == 0) return 0.0;
    return position_ * (currentPrice - avgPrice_);
}

double PnLCollector::getTotalPnL(double currentPrice) const {
    return getMarkToMarket(currentPrice) - 100000.0; // Assuming 100k initial cash
}

void PnLCollector::addHistoryPoint(double timestamp, double currentPrice) {
    PnLPoint point;
    point.timestamp = timestamp;
    point.cash = cash_;
    point.position = position_;
    point.markToMarket = getMarkToMarket(currentPrice);
    point.unrealizedPnL = getUnrealizedPnL(currentPrice);
    point.realizedPnL = realizedPnL_;
    point.totalPnL = getTotalPnL(currentPrice);
    
    history_.push_back(point);
}

void PnLCollector::exportToCSV(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }
    
    file << "Timestamp,Cash,Position,MarkToMarket,UnrealizedPnL,RealizedPnL,TotalPnL\n";
    
    for (const auto& point : history_) {
        file << std::fixed << std::setprecision(2)
             << point.timestamp << ","
             << point.cash << ","
             << point.position << ","
             << point.markToMarket << ","
             << point.unrealizedPnL << ","
             << point.realizedPnL << ","
             << point.totalPnL << "\n";
    }
    
    file.close();
}

void PnLCollector::reset() {
    cash_ = 100000.0;
    position_ = 0;
    realizedPnL_ = 0.0;
    avgPrice_ = 0.0;
    history_.clear();
} 