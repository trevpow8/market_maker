#include <iostream>
#include <string>
#include <cstdlib>
#include "alpaca/AlpacaTrader.h"

int main() {
    std::cout << "Alpaca Paper Trading Test\n";
    std::cout << "=========================\n\n";
    
    // Read API keys from environment variables
    std::string apiKey = std::getenv("ALPACA_API_KEY") ? std::getenv("ALPACA_API_KEY") : "";
    std::string apiSecret = std::getenv("ALPACA_API_SECRET") ? std::getenv("ALPACA_API_SECRET") : "";
    
    if (apiKey.empty() || apiSecret.empty()) {
        std::cerr << "Missing Alpaca API key or secret in environment variables!\n";
        std::cerr << "Please set ALPACA_API_KEY and ALPACA_API_SECRET in your shell.\n";
        return 1;
    }
    
    // Create AlpacaTrader instance
    AlpacaTrader trader(apiKey, apiSecret);
    
    // Test connection
    std::cout << "Testing connection...\n";
    if (trader.testConnection()) {
        std::cout << "✓ Connection successful!\n\n";
        
        // Get account information
        nlohmann::json accountInfo;
        if (trader.getAccountInfo(accountInfo)) {
            std::cout << "Account Information:\n";
            std::cout << "  Account ID: " << accountInfo["id"] << "\n";
            std::cout << "  Status: " << accountInfo["status"] << "\n";
            std::cout << "  Cash: $" << accountInfo["cash"] << "\n";
            std::cout << "  Portfolio Value: $" << accountInfo["portfolio_value"] << "\n";
            std::cout << "  Pattern Day Trader: " << (accountInfo["pattern_day_trader"] ? "Yes" : "No") << "\n\n";
        }
        
        // Test getting current price for a stock
        std::string symbol = "AAPL";
        double price;
        if (trader.getCurrentPrice(symbol, price)) {
            std::cout << "Current " << symbol << " price: $" << price << "\n\n";
        }
        
        // Test getting positions
        std::vector<AlpacaPosition> positions;
        if (trader.getPositions(positions)) {
            std::cout << "Current Positions:\n";
            if (positions.empty()) {
                std::cout << "  No positions\n";
            } else {
                for (const auto& pos : positions) {
                    std::cout << "  " << pos.symbol << ": " << pos.qty << " shares @ $" << pos.avg_entry_price 
                              << " (P&L: $" << pos.unrealized_pl << ")\n";
                }
            }
            std::cout << "\n";
        }
        
        // Test getting open orders
        std::vector<AlpacaOrder> openOrders;
        if (trader.getOpenOrders(openOrders)) {
            std::cout << "Open Orders:\n";
            if (openOrders.empty()) {
                std::cout << "  No open orders\n";
            } else {
                for (const auto& order : openOrders) {
                    std::cout << "  " << order.symbol << " " << order.side << " " << order.qty 
                              << " @ $" << order.price << " (Status: " << order.status << ")\n";
                }
            }
            std::cout << "\n";
        }
        
    } else {
        std::cout << "✗ Connection failed!\n";
        std::cout << "Please check your API keys and internet connection.\n";
        return 1;
    }
    
    return 0;
} 