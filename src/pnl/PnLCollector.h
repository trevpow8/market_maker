#pragma once

#include <vector>
#include <map>
#include "../lob_engine/OrderBook.h"

struct PnLPoint {
    double timestamp;
    double cash;
    int position;
    double markToMarket;
    double unrealizedPnL;
    double realizedPnL;
    double totalPnL;
};

class PnLCollector {
public:
    PnLCollector(double initialCash = 100000.0);
    
    // Record trades and update P&L
    void onTrade(const Trade& trade, double currentPrice);
    
    // Get current state
    double getCash() const { return cash_; }
    int getPosition() const { return position_; }
    double getMarkToMarket(double currentPrice) const;
    double getUnrealizedPnL(double currentPrice) const;
    double getRealizedPnL() const { return realizedPnL_; }
    double getTotalPnL(double currentPrice) const;
    
    // Get historical data
    const std::vector<PnLPoint>& getHistory() const { return history_; }
    
    // Export results
    void exportToCSV(const std::string& filename) const;
    
    // Reset for new simulation
    void reset();
    
    // Add history point (public for simulator access)
    void addHistoryPoint(double timestamp, double currentPrice);

private:
    double cash_;
    int position_;
    double realizedPnL_;
    double avgPrice_;
    std::vector<PnLPoint> history_;
}; 