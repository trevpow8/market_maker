find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(test_orderbook test_orderbook.cpp)
target_link_libraries(test_orderbook PRIVATE lob_engine ${GTEST_LIBRARIES} pthread)
add_test(NAME OrderBookTest COMMAND test_orderbook)