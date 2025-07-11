#include "OrderBook.h"
#include <gtest/gtest.h>

TEST(OrderBook, SimpleExactFill) {
  OrderBook ob;
  ob.addOrder({1, Side::Ask, 10.0, 5});
  auto trades = ob.addOrder({2, Side::Bid, 10.0, 5});
  ASSERT_EQ(trades.size(), 1);
  EXPECT_EQ(std::get<0>(trades[0]), 1);       
  EXPECT_EQ(std::get<1>(trades[0]), 5);       
  EXPECT_DOUBLE_EQ(std::get<2>(trades[0]), 10.0); 