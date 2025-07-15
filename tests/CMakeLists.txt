# Find GoogleTest
find_package(GTest REQUIRED)

# Test executable
add_executable(market_maker_tests test_basic.cpp)
target_link_libraries(market_maker_tests 
    PRIVATE 
    GTest::gtest 
    GTest::gtest_main
    lob_engine
    strategies
)

# Include directories
target_include_directories(market_maker_tests PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Add test
add_test(NAME MarketMakerTests COMMAND market_maker_tests)