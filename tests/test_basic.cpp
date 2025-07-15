#include <gtest/gtest.h>
#include "../src/lob_engine/OrderBook.h"
#include "../src/strategies/FixedSpreadStrategy.h"

TEST(OrderBookTest, BasicOrderMatching) {
    OrderBook book;
    
    // Add a bid order
    Order bid{1, Side::Bid, 100.0, 100};
    auto trades = book.addOrder(bid);
    EXPECT_EQ(trades.size(), 0); // No trades yet
    
    // Add an ask order that crosses
    Order ask{2, Side::Ask, 99.0, 50};
    trades = book.addOrder(ask);
    EXPECT_EQ(trades.size(), 1); // Should match
    
    // Check best prices
    EXPECT_EQ(book.getBestBid(), 100.0);
    EXPECT_EQ(book.getBestAsk(), 0.0); // Ask was fully filled
}

TEST(FixedSpreadStrategyTest, BasicQuoting) {
    OrderBook book;
    
    // Add some market orders to establish prices
    Order bid{1, Side::Bid, 100.0, 100};
    Order ask{2, Side::Ask, 102.0, 100};
    book.addOrder(bid);
    book.addOrder(ask);
    
    // Create strategy with 2.0 spread
    FixedSpreadStrategy strategy(2.0, 50);
    
    // Generate quotes
    auto quotes = strategy.generateQuotes(book);
    
    // Should generate both bid and ask quotes
    EXPECT_EQ(quotes.size(), 2);
    
    // Check quote prices (should be around mid-price ± spread/2)
    double midPrice = book.getMidPrice();
    EXPECT_NEAR(quotes[0].price, midPrice - 1.0, 0.01);
    EXPECT_NEAR(quotes[1].price, midPrice + 1.0, 0.01);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
} 