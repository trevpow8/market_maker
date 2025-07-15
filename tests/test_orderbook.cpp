#include "../src/lob_engine/OrderBook.h"
#include <gtest/gtest.h>

TEST(OrderBook, SimpleExactFill) {
  OrderBook ob;
  ob.addOrder({1, Side::Ask, 10.0, 5});
  auto trades = ob.addOrder({2, Side::Bid, 10.0, 5});
  ASSERT_EQ(trades.size(), 1);
  EXPECT_EQ(std::get<0>(trades[0]), 1);       
  EXPECT_EQ(std::get<1>(trades[0]), 5);       
  EXPECT_DOUBLE_EQ(std::get<2>(trades[0]), 10.0); 
}
TEST(OrderBook, PartialFill) {
  OrderBook ob;
  ob.addOrder({1, Side::Ask, 10.0, 5});
  auto trades = ob.addOrder({2, Side::Bid, 10.0, 3});
  ASSERT_EQ(trades.size(), 1);
  EXPECT_EQ(std::get<0>(trades[0]), 1);       
  EXPECT_EQ(std::get<1>(trades[0]), 3);       
  EXPECT_DOUBLE_EQ(std::get<2>(trades[0]), 10.0); 
}
TEST(OrderBook, NoFill) {
  OrderBook ob;
  ob.addOrder({1, Side::Ask, 10.0, 5});
  auto trades = ob.addOrder({2, Side::Bid, 9.0, 5});
  ASSERT_EQ(trades.size(), 0);
}

TEST(OrderBook, ZeroQuantityNoOp) {
    OrderBook ob;
    ob.addOrder({1, Side::Ask, 100.0, 5});
    auto trades = ob.addOrder({2, Side::Bid, 100.0, 0});
    EXPECT_TRUE(trades.empty());
    auto trades2 = ob.addOrder({3, Side::Bid, 100.0, 5});
    ASSERT_EQ(trades2.size(), 1);
    EXPECT_EQ(std::get<1>(trades2[0]), 5);
  }

  TEST(OrderBook, NoCrossInsertion) {
    OrderBook ob;
    auto trades = ob.addOrder({1, Side::Bid, 90.0, 5});
    EXPECT_TRUE(trades.empty());
    ob.addOrder({2, Side::Ask, 100.0, 5});
    auto trades2 = ob.addOrder({3, Side::Ask, 90.0, 5});
    ASSERT_EQ(trades2.size(), 1);
    EXPECT_EQ(std::get<0>(trades2[0]), 1);   
  }
