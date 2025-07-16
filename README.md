# Market Maker Simulator

A C++ market making system that connects to Alpaca's paper trading API for live algorithmic trading.

## 🚀 What We've Built

### Core Components
- **OrderBook Engine** - Matches orders and maintains bid/ask books
- **Strategy Interface** - Abstract base for different market making strategies
- **FixedSpreadStrategy** - Simple symmetric spread strategy
- **PnL Collector** - Tracks cash, position, and mark-to-market P&L
- **Alpaca Integration** - Real API connection for paper trading
- **Simulator Core** - Orchestrates the entire trading system

### Current Features
✅ **Live Alpaca Connection** - Tested and working  
✅ **Order Placement** - Can place limit orders  
✅ **Account Management** - View positions, cash, portfolio  
✅ **Strategy Framework** - Plug-and-play strategy system  
✅ **P&L Tracking** - Real-time profit/loss calculation  

## 🏗️ Architecture

```
┌─────────────────┐    ┌─────────────────┐    ┌─────────────────┐
│   Strategy      │    │   OrderBook     │    │   Alpaca API    │
│   (FixedSpread) │───▶│   (Matching)    │───▶│   (Paper Trade) │
└─────────────────┘    └─────────────────┘    └─────────────────┘
         │                       │                       │
         ▼                       ▼                       ▼
┌─────────────────┐    ┌─────────────────┐    ┌─────────────────┐
│   PnL Collector │    │   Simulator     │    │   Dashboard     │
│   (Tracking)    │    │   (Orchestrator)│    │   (Monitoring)  │
└─────────────────┘    └─────────────────┘    └─────────────────┘
```

## 🛠️ Setup & Installation

### Prerequisites
- C++17 compiler
- CMake 3.15+
- Homebrew (for dependencies)

### Dependencies
```bash
brew install cpr nlohmann-json
```

### Build
```bash
mkdir build && cd build
cmake ..
make
```

### Environment Variables
Set your Alpaca API credentials:
```bash
export ALPACA_API_KEY="your_key_here"
export ALPACA_API_SECRET="your_secret_here"
```

## 🧪 Testing

### Test Alpaca Connection
```bash
./src/test_alpaca
```

### Run Unit Tests
```bash
./tests/market_maker_tests
```

### Test After Hours
```bash
./src/after_hours_test
```

## 📊 Current Status

**✅ Working:**
- Alpaca API connection
- Account information retrieval
- Order placement and management
- Basic strategy framework
- P&L tracking system

**🔄 In Progress:**
- Live market data integration
- Real-time order management
- Dashboard development

**📋 Next Steps:**
- WebSocket market data feed
- Live strategy execution
- Real-time dashboard
- Risk management features

## 🎯 Next Phase: Live Market Making

### What We'll Build Next

1. **Live Market Data Feed**
   - WebSocket connection to Alpaca's real-time data
   - Continuous price updates
   - Order book maintenance

2. **Live Strategy Execution**
   - Real-time quote generation
   - Automatic order placement
   - Order cancellation and replacement

3. **Dashboard & Monitoring**
   - Real-time P&L display
   - Position tracking
   - Order status monitoring
   - Performance metrics

4. **Risk Management**
   - Position limits
   - Loss limits
   - Slippage controls

### How It Will Work Tomorrow

**During Market Hours (9:30 AM - 4:00 PM ET):**
1. Connect to Alpaca's live market data
2. Generate quotes using your strategy
3. Place orders automatically
4. Track fills and update P&L
5. Cancel/replace orders as market moves

**After Hours:**
- Orders queue for next market open
- Can still place/cancel orders
- No live price data available

## 🎮 Quick Start

1. **Set your API keys:**
   ```bash
   export ALPACA_API_KEY="your_key"
   export ALPACA_API_SECRET="your_secret"
   ```

2. **Test connection:**
   ```bash
   ./src/test_alpaca
   ```

3. **Run the simulator:**
   ```bash
   ./src/market_maker
   ```

## 📈 Strategy Examples

### Fixed Spread Strategy
- Places symmetric bid/ask orders around mid-price
- Configurable spread and quantity
- Simple but effective for liquid stocks

### Future Strategies
- Inventory-based strategies
- Mean reversion strategies
- Statistical arbitrage
- Custom algorithms

## 🔧 Configuration

### Strategy Parameters
```cpp
// In FixedSpreadStrategy
double spread_ = 2.0;    // Spread in dollars
int quantity_ = 100;     // Order size
```

### Risk Limits
```cpp
// Coming soon
double maxPosition = 1000;
double maxLoss = 1000;
double maxDrawdown = 0.05;
```

## 📝 Development Notes

- **Language:** C++17
- **Build System:** CMake
- **HTTP Client:** cpr
- **JSON:** nlohmann/json
- **Testing:** GoogleTest
