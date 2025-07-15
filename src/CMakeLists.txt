# LOB Engine library
add_library(lob_engine
    lob_engine/OrderBook.cpp
)
target_include_directories(lob_engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Strategies library
add_library(strategies
    strategies/FixedSpreadStrategy.cpp
)
target_include_directories(strategies PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(strategies PRIVATE lob_engine)

# PnL library
add_library(pnl
    pnl/PnLCollector.cpp
)
target_include_directories(pnl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(pnl PRIVATE lob_engine)

# Simulator library
add_library(simulator
    simulator/Simulator.cpp
)
target_include_directories(simulator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(simulator PRIVATE lob_engine strategies pnl)

# Alpaca library
add_library(alpaca
    alpaca/AlpacaTrader.cpp
)
target_include_directories(alpaca PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    /opt/homebrew/include
)
target_link_libraries(alpaca PRIVATE 
    /opt/homebrew/lib/libcpr.dylib
)

# Main executable
add_executable(market_maker main.cpp)
target_link_libraries(market_maker PRIVATE lob_engine strategies pnl simulator alpaca)

# Alpaca test executable
add_executable(test_alpaca test_alpaca.cpp)
target_include_directories(test_alpaca PRIVATE /opt/homebrew/include)
target_link_libraries(test_alpaca PRIVATE alpaca)

# After hours test executable
add_executable(after_hours_test test_after_hours.cpp)
target_include_directories(after_hours_test PRIVATE /opt/homebrew/include)
target_link_libraries(after_hours_test PRIVATE alpaca)