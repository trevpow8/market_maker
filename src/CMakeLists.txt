add_library(lob_engine
    lob_engine/OrderBook.cpp
)
target_include_directories(lob_engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(simulator main.cpp)
target_link_libraries(simulator PRIVATE lob_engine)