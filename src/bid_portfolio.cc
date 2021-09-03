#include "bid_portfolio.h"

#include "trader.h"



namespace cyclus {


  std::string GetTraderPrototype(std::shared_ptr<Trader> bidder){
    return bidder->manager()->prototype();
  }


  std::string GetTraderSpec(std::shared_ptr<Trader> bidder){
    return bidder->manager()->spec();
  }


} // namespace cyclus