#include <map>
#include <vector>

enum class Side { Bid, Ask };

struct Order {
    int    id;
    Side   side;
    double price;
    int    quantity;
};

class OrderBook {
public:
    std::vector<std::tuple<int,int,double>> addOrder(const Order& o);

private:
    std::map<double, std::map<int,int>, std::greater<>> bids_;
    std::map<double, std::map<int,int>, std::less<>>    asks_;
};