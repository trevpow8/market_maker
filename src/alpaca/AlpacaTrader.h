#pragma once

#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

struct AlpacaOrder {
    std::string id;
    std::string symbol;
    std::string side;  
    double qty;
    double price;
    std::string status;  
    std::string timestamp;
};

struct AlpacaPosition {
    std::string symbol;
    double qty;
    double avg_entry_price;
    double market_value;
    double unrealized_pl;
};

class AlpacaTrader {
public:
    AlpacaTrader(const std::string& apiKey, const std::string& apiSecret);
    
    bool testConnection();
    
    bool getAccountInfo(nlohmann::json& accountInfo);
    
    bool placeOrder(const std::string& symbol, 
                   const std::string& side, 
                   double qty, 
                   double price,
                   std::string& orderId);
    
    
    bool getOrderStatus(const std::string& orderId, AlpacaOrder& order);
    
    
    bool getOpenOrders(std::vector<AlpacaOrder>& orders);
    
    
    bool cancelOrder(const std::string& orderId);
    
    
    bool getPositions(std::vector<AlpacaPosition>& positions);
    
    
    bool getCurrentPrice(const std::string& symbol, double& price);

private:
    std::string apiKey_;
    std::string apiSecret_;
    std::string baseUrl_;
    
    
    cpr::Header getAuthHeaders();
    bool makeRequest(const std::string& endpoint, 
                    const std::string& method,
                    const nlohmann::json& body,
                    nlohmann::json& response);
}; 