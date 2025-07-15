#pragma once

#include <memory>
#include <vector>
#include <string>
#include "../lob_engine/OrderBook.h"
#include "../strategies/Strategy.h"
#include "../pnl/PnLCollector.h"

struct MarketEvent {
    double timestamp;
    int orderId;
    Side side;
    double price;
    int quantity;
};

class Simulator {
public:
    Simulator(std::unique_ptr<Strategy> strategy);
    
    // Load market events from CSV file
    bool loadEventsFromCSV(const std::string& filename);
    
    // Run simulation
    void run();
    
    // Get results
    const PnLCollector& getPnLCollector() const { return pnlCollector_; }
    
    // Export results
    void exportResults(const std::string& filename) const;
    
    // Reset for new simulation
    void reset();

private:
    std::unique_ptr<Strategy> strategy_;
    OrderBook orderBook_;
    PnLCollector pnlCollector_;
    std::vector<MarketEvent> events_;
    
    // Simulation state
    double currentTime_;
    std::vector<int> activeOrders_;
    
    // Helper methods
    void processEvent(const MarketEvent& event);
    void processStrategyQuotes();
    void processTrades(const std::vector<Trade>& trades);
}; 