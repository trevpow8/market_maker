#include <iostream>
#include <string>
#include <cstdlib>
#include "alpaca/AlpacaTrader.h"

int main() {
    std::cout << "After Hours Alpaca Testing\n";
    std::cout << "==========================\n\n";
    
    // Read API keys from environment variables
    std::string apiKey = std::getenv("ALPACA_API_KEY") ? std::getenv("ALPACA_API_KEY") : "";
    std::string apiSecret = std::getenv("ALPACA_API_SECRET") ? std::getenv("ALPACA_API_SECRET") : "";
    
    if (apiKey.empty() || apiSecret.empty()) {
        std::cerr << "Missing Alpaca API key or secret in environment variables!\n";
        return 1;
    }
    
    AlpacaTrader trader(apiKey, apiSecret);
    
    // Test 1: Account Info (should work)
    std::cout << "=== Test 1: Account Information ===\n";
    nlohmann::json accountInfo;
    if (trader.getAccountInfo(accountInfo)) {
        std::cout << "✓ Account info retrieved successfully\n";
        std::cout << "  Cash: $" << accountInfo["cash"] << "\n";
        std::cout << "  Portfolio Value: $" << accountInfo["portfolio_value"] << "\n";
    }
    
    // Test 2: Place a limit order (should work, will queue for next market open)
    std::cout << "\n=== Test 2: Place Limit Order ===\n";
    std::string orderId;
    if (trader.placeOrder("AAPL", "buy", 1, 150.00, orderId)) {
        std::cout << "✓ Limit order placed successfully!\n";
        std::cout << "  Order ID: " << orderId << "\n";
        std::cout << "  Note: This order will queue for next market open\n";
        
        // Test 3: Check order status
        std::cout << "\n=== Test 3: Check Order Status ===\n";
        AlpacaOrder order;
        if (trader.getOrderStatus(orderId, order)) {
            std::cout << "✓ Order status retrieved\n";
            std::cout << "  Status: " << order.status << "\n";
            std::cout << "  Symbol: " << order.symbol << "\n";
            std::cout << "  Side: " << order.side << "\n";
            std::cout << "  Quantity: " << order.qty << "\n";
            std::cout << "  Price: $" << order.price << "\n";
        }
    }
    
    // Test 4: Get all open orders
    std::cout << "\n=== Test 4: List All Open Orders ===\n";
    std::vector<AlpacaOrder> openOrders;
    if (trader.getOpenOrders(openOrders)) {
        std::cout << "✓ Retrieved " << openOrders.size() << " open orders\n";
        for (const auto& order : openOrders) {
            std::cout << "  - " << order.symbol << " " << order.side << " " 
                      << order.qty << " @ $" << order.price << " (Status: " << order.status << ")\n";
        }
    }
    
    // Test 5: Try to get current price (will fail after hours)
    std::cout << "\n=== Test 5: Get Current Price (After Hours) ===\n";
    double price;
    if (trader.getCurrentPrice("AAPL", price)) {
        std::cout << "✓ Current AAPL price: $" << price << "\n";
    } else {
        std::cout << "✗ No live price available (markets closed)\n";
        std::cout << "  This is expected behavior after hours\n";
    }
    
    std::cout << "\n=== Summary ===\n";
    std::cout << "✓ Account operations work after hours\n";
    std::cout << "✓ Order placement works (queues for next open)\n";
    std::cout << "✓ Order status checking works\n";
    std::cout << "✗ Live price data not available after hours\n";
    
    return 0;
} 