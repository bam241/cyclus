#include "prey.h"

#include <sstream>

namespace cyclus {

Prey::Prey(cyclus::Context* ctx)
    : cyclus::Facility(ctx),
      commod(""),
      dead(0),
      nchildren(1),
      birth_freq(1),
      age(0) {}

void Prey::EnterNotify() {
  cyclus::Facility::EnterNotify();
  context()->RegisterTrader(Trader::shared_from_this());
}

void Prey::Decommission() {
  context()->UnregisterTrader(Trader::shared_from_this());
  cyclus::Facility::Decommission();
}

void Prey::Tick() {
  LOG(cyclus::LEV_INFO3, "Prey") << name() << " is ticking {";
  LOG(cyclus::LEV_INFO4, "Prey") << "will offer " << 1
                                 << " units of "
                                 << commod << ".";
  LOG(cyclus::LEV_INFO3, "Prey") << "}";
}

void Prey::GiveBirth() {
  bool policy = dead ? birth_and_death : true;
  if (age % birth_freq == 0 && policy) {
    LOG(cyclus::LEV_INFO3, "Prey") << name() << " is having children";
    for (int i = 0; i < nchildren; ++i) {
      context()->SchedBuild(NULL, prototype());
    }
  }
}

void Prey::Tock() {
  LOG(cyclus::LEV_INFO3, "Prey") << name() << " is tocking {";

  if (dead) {
    LOG(cyclus::LEV_INFO3, "Prey") << name() << " got eaten";
    context()->SchedDecom(Agent::shared_from_this());
    LOG(cyclus::LEV_INFO3, "Prey") << "}";
  }

  GiveBirth();

  age++;  // getting older

  LOG(cyclus::LEV_INFO3, "Prey") << "}";
}

std::set<cyclus::BidPortfolio<cyclus::Product>::Ptr>
Prey::GetProductBids(
    cyclus::CommodMap<cyclus::Product>::type& commod_requests) {
  using cyclus::Bid;
  using cyclus::BidPortfolio;
  using cyclus::CapacityConstraint;
  using cyclus::Product;
  using cyclus::Request;

  std::set<BidPortfolio<Product>::Ptr> ports;

  if (commod_requests.count(commod) > 0) {
    BidPortfolio<Product>::Ptr port(new BidPortfolio<Product>());
    std::vector<Request<Product>*>& requests =
        commod_requests.at(commod);
    std::vector<Request<Product>*>::iterator it;
    for (it = requests.begin(); it != requests.end(); ++it) {
      // Offer one wabbit
      port->AddBid(*it, Product::CreateUntracked(1, ""), Trader::shared_from_this());
    }
    CapacityConstraint<Product> cc(1);  // only 1 wabbit!
    port->AddConstraint(cc);
    ports.insert(port);
  }
  return ports;
}

void Prey::GetProductTrades(
    const std::vector< cyclus::Trade<cyclus::Product> >& trades,
    std::vector<std::pair<cyclus::Trade<cyclus::Product>,
                          cyclus::Product::Ptr> >& responses) {
  using cyclus::Product;
  using cyclus::Trade;

  double provided = 0;
  double current_capacity = 1;  // only 1 rabbit!
  std::vector< cyclus::Trade<cyclus::Product> >::const_iterator it;
  for (it = trades.begin(); it != trades.end(); ++it) {
    double qty = it->amt;
    current_capacity -= qty;
    provided += qty;
    Product::Ptr response = Product::Create(Agent::shared_from_this(), qty, "");
    responses.push_back(std::make_pair(*it, response));
    LOG(cyclus::LEV_INFO5, "Prey") << name() << " just received an order"
                                     << " for " << qty
                                     << " of " << commod;
  }
  if (cyclus::IsNegative(current_capacity)) {
    std::stringstream ss;
    ss << "is being asked to provide " << provided
       << " but its capacity is " << 1<< ".";
    throw cyclus::ValueError(Agent::InformErrorMsg(ss.str()));
  }

  if (provided > 0) dead = 1;  // They came from... behind!
}

extern "C" cyclus::Agent* ConstructPrey(cyclus::Context* ctx) {
  return new Prey(ctx);
}

}  // namespace cyclus
