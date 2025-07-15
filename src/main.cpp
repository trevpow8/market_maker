#include <iostream>
#include <memory>
#include "simulator/Simulator.h"
#include "strategies/FixedSpreadStrategy.h"

int main() {
    std::cout << "Market Maker Simulator\n";
    std::cout << "======================\n\n";
    
    // Create a fixed spread strategy
    auto strategy = std::make_unique<FixedSpreadStrategy>(2.0, 100); // 2.0 spread, 100 quantity
    
    // Create simulator
    Simulator simulator(std::move(strategy));
    
    // Load market events (you'll need to create this CSV file)
    std::string eventsFile = "market_events.csv";
    if (!simulator.loadEventsFromCSV(eventsFile)) {
        std::cout << "Failed to load market events from " << eventsFile << "\n";
        std::cout << "Creating sample market events...\n";
        
        // For now, we'll create a simple example without external events
        // In a real scenario, you'd load from CSV
    }
    
    // Run simulation
    std::cout << "Running simulation...\n";
    simulator.run();
    
    // Export results
    std::string resultsFile = "pnl_results.csv";
    simulator.exportResults(resultsFile);
    std::cout << "Results exported to " << resultsFile << "\n";
    
    // Print summary
    const auto& pnl = simulator.getPnLCollector();
    std::cout << "\nSimulation Summary:\n";
    std::cout << "Final Cash: $" << pnl.getCash() << "\n";
    std::cout << "Final Position: " << pnl.getPosition() << "\n";
    
    double finalPrice = 100.0; // Placeholder - in real scenario, get from order book
    std::cout << "Mark-to-Market: $" << pnl.getMarkToMarket(finalPrice) << "\n";
    std::cout << "Total P&L: $" << pnl.getTotalPnL(finalPrice) << "\n";
    
    return 0;
}