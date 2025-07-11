#include <map>
#include <vector>

enum class Side { Bid, Ask };

struct Order {
    int    id;
    Side   side;
    double price;
    int    quantity;
};

using Trade = std::tuple<int/*contraId*/,int/*qty*/,double/*price*/>;


class OrderBook {
public:
    std::vector<std::tuple<int,int,double>> addOrder(const Order& o);

private:
    std::map<double, std::map<int,int>, std::greater<>> bids_;
    std::map<double, std::map<int,int>, std::less<>>    asks_;

    template<typename BookType>
    void matchAgainst(BookType& bookRef, Order& incoming, std::vector<Trade>& trades);
};