#include "AlpacaTrader.h"
#include <iostream>
#include <sstream>

AlpacaTrader::AlpacaTrader(const std::string& apiKey, const std::string& apiSecret)
    : apiKey_(apiKey), apiSecret_(apiSecret), baseUrl_("https://paper-api.alpaca.markets") {
    std::cout << "AlpacaTrader initialized with base URL: " << baseUrl_ << std::endl;
}

bool AlpacaTrader::testConnection() {
    std::cout << "Testing connection to Alpaca API..." << std::endl;
    nlohmann::json response;
    return makeRequest("/v2/account", "GET", nlohmann::json{}, response);
}

bool AlpacaTrader::getAccountInfo(nlohmann::json& accountInfo) {
    std::cout << "Getting account information..." << std::endl;
    return makeRequest("/v2/account", "GET", nlohmann::json{}, accountInfo);
}

bool AlpacaTrader::placeOrder(const std::string& symbol, 
                              const std::string& side, 
                              double qty, 
                              double price,
                              std::string& orderId) {
    std::cout << "Placing order: " << side << " " << qty << " " << symbol << " @ $" << price << std::endl;
    
    nlohmann::json order = {
        {"symbol", symbol},
        {"qty", std::to_string(qty)},
        {"side", side},
        {"type", "limit"},
        {"time_in_force", "gtc"},
        {"limit_price", std::to_string(price)}
    };
    
    nlohmann::json response;
    if (makeRequest("/v2/orders", "POST", order, response)) {
        orderId = response["id"];
        std::cout << "Order placed successfully! Order ID: " << orderId << std::endl;
        return true;
    }
    return false;
}

bool AlpacaTrader::getOrderStatus(const std::string& orderId, AlpacaOrder& order) {
    std::cout << "Getting status for order: " << orderId << std::endl;
    nlohmann::json response;
    std::string endpoint = "/v2/orders/" + orderId;
    
    if (makeRequest(endpoint, "GET", nlohmann::json{}, response)) {
        order.id = response["id"];
        order.symbol = response["symbol"];
        order.side = response["side"];
        order.qty = std::stod(response["qty"].get<std::string>());
        order.price = std::stod(response["limit_price"].get<std::string>());
        order.status = response["status"];
        order.timestamp = response["created_at"];
        return true;
    }
    return false;
}

bool AlpacaTrader::getOpenOrders(std::vector<AlpacaOrder>& orders) {
    std::cout << "Getting open orders..." << std::endl;
    nlohmann::json response;
    if (makeRequest("/v2/orders?status=open", "GET", nlohmann::json{}, response)) {
        orders.clear();
        for (const auto& orderJson : response) {
            AlpacaOrder order;
            order.id = orderJson["id"];
            order.symbol = orderJson["symbol"];
            order.side = orderJson["side"];
            order.qty = std::stod(orderJson["qty"].get<std::string>());
            order.price = std::stod(orderJson["limit_price"].get<std::string>());
            order.status = orderJson["status"];
            order.timestamp = orderJson["created_at"];
            orders.push_back(order);
        }
        return true;
    }
    return false;
}

bool AlpacaTrader::cancelOrder(const std::string& orderId) {
    std::cout << "Canceling order: " << orderId << std::endl;
    nlohmann::json response;
    std::string endpoint = "/v2/orders/" + orderId;
    return makeRequest(endpoint, "DELETE", nlohmann::json{}, response);
}

bool AlpacaTrader::getPositions(std::vector<AlpacaPosition>& positions) {
    std::cout << "Getting positions..." << std::endl;
    nlohmann::json response;
    if (makeRequest("/v2/positions", "GET", nlohmann::json{}, response)) {
        positions.clear();
        for (const auto& posJson : response) {
            AlpacaPosition pos;
            pos.symbol = posJson["symbol"];
            pos.qty = std::stod(posJson["qty"].get<std::string>());
            pos.avg_entry_price = std::stod(posJson["avg_entry_price"].get<std::string>());
            pos.market_value = std::stod(posJson["market_value"].get<std::string>());
            pos.unrealized_pl = std::stod(posJson["unrealized_pl"].get<std::string>());
            positions.push_back(pos);
        }
        return true;
    }
    return false;
}

bool AlpacaTrader::getCurrentPrice(const std::string& symbol, double& price) {
    std::cout << "Getting current price for " << symbol << "..." << std::endl;
    nlohmann::json response;
    std::string endpoint = "/v2/stocks/" + symbol + "/trades/latest";
    
    if (makeRequest(endpoint, "GET", nlohmann::json{}, response)) {
        price = std::stod(response["trade"]["p"].get<std::string>());
        return true;
    }
    
    
    std::cout << "Trying alternative price endpoint..." << std::endl;
    endpoint = "/v2/stocks/" + symbol + "/quotes/latest";
    if (makeRequest(endpoint, "GET", nlohmann::json{}, response)) {
        double bid = std::stod(response["quote"]["bp"].get<std::string>());
        double ask = std::stod(response["quote"]["ap"].get<std::string>());
        price = (bid + ask) / 2.0;
        return true;
    }
    
    return false;
}

cpr::Header AlpacaTrader::getAuthHeaders() {
    return {
        {"APCA-API-KEY-ID", apiKey_},
        {"APCA-API-SECRET-KEY", apiSecret_},
        {"Content-Type", "application/json"}
    };
}

bool AlpacaTrader::makeRequest(const std::string& endpoint, 
                               const std::string& method,
                               const nlohmann::json& body,
                               nlohmann::json& response) {
    std::string url = baseUrl_ + endpoint;
    std::cout << "Making " << method << " request to: " << url << std::endl;
    
    cpr::Response cprResponse;
    
    if (method == "GET") {
        cprResponse = cpr::Get(cpr::Url{url}, getAuthHeaders());
    } else if (method == "POST") {
        std::cout << "Request body: " << body.dump() << std::endl;
        cprResponse = cpr::Post(cpr::Url{url}, getAuthHeaders(), cpr::Body{body.dump()});
    } else if (method == "DELETE") {
        cprResponse = cpr::Delete(cpr::Url{url}, getAuthHeaders());
    }
    
    std::cout << "Response status: " << cprResponse.status_code << std::endl;
    std::cout << "Response body: " << cprResponse.text << std::endl;
    
    if (cprResponse.status_code == 200 || cprResponse.status_code == 201) {
        try {
            response = nlohmann::json::parse(cprResponse.text);
            return true;
        } catch (const std::exception& e) {
            std::cerr << "Failed to parse JSON response: " << e.what() << std::endl;
            return false;
        }
    } else {
        std::cerr << "HTTP " << cprResponse.status_code << ": " << cprResponse.text << std::endl;
        return false;
    }
} 