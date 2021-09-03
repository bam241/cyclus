#ifndef CYCLUS_SRC_TRADER_MANAGEMENT_H_
#define CYCLUS_SRC_TRADER_MANAGEMENT_H_

#include "error.h"
#include "exchange_context.h"
#include "product.h"
#include "material.h"
#include "trader.h"

namespace cyclus {

// template specializations to support inheritance and virtual functions
template<class T>
inline static std::set<typename RequestPortfolio<T>::Ptr>
    QueryRequests(std::shared_ptr<Trader> t) {
  throw StateError("Non-specialized version of QueryRequests not supported");
}

template<>
inline std::set<RequestPortfolio<Material>::Ptr>
    QueryRequests<Material>(std::shared_ptr<Trader> t) {
  return t->GetMatlRequests();
}

template<>
inline std::set<RequestPortfolio<Product>::Ptr>
    QueryRequests<Product>(std::shared_ptr<Trader> t) {
  return t->GetProductRequests();
}

template<class T>
inline static std::set<typename BidPortfolio<T>::Ptr>
    QueryBids(std::shared_ptr<Trader> t, typename CommodMap<T>::type& map) {
  throw StateError("Non-specialized version of QueryBids not supported");
}

template<>
inline std::set<BidPortfolio<Material>::Ptr>
    QueryBids<Material>(std::shared_ptr<Trader> t, CommodMap<Material>::type& map) {
  return t->GetMatlBids(map);
}

template<>
inline std::set<BidPortfolio<Product>::Ptr>
    QueryBids<Product>(std::shared_ptr<Trader> t, CommodMap<Product>::type& map) {
  return t->GetProductBids(map);
}

template<class T>
inline static void PopulateTradeResponses(
    std::shared_ptr<Trader> trader,
    const std::vector< Trade<T> >& trades,
    std::vector< std::pair<Trade<T>, typename T::Ptr> >& responses) {
  throw StateError("Non-specialized version of "
                   "PopulateTradeResponses not supported");
}

template<>
inline void PopulateTradeResponses<Material>(
    std::shared_ptr<Trader> trader,
    const std::vector< Trade<Material> >& trades,
    std::vector<std::pair<Trade<Material>, Material::Ptr> >& responses) {
  std::dynamic_pointer_cast<Trader>(trader)->GetMatlTrades(trades, responses);
}

template<>
inline void PopulateTradeResponses<Product>(
    std::shared_ptr<Trader> trader,
    const std::vector< Trade<Product> >& trades,
    std::vector<std::pair<Trade<Product>, Product::Ptr> >& responses) {
  trader->GetProductTrades(trades, responses);
}

template<class T>
inline static void AcceptTrades(
    std::shared_ptr<Trader> trader,
    const std::vector< std::pair<Trade<T>, typename T::Ptr> >& responses) {
  throw StateError("Non-specialized version of AcceptTrades not supported");
}

template<>
inline void AcceptTrades(
    std::shared_ptr<Trader> trader,
    const std::vector< std::pair<Trade<Material>, Material::Ptr> >& responses) {
  std::dynamic_pointer_cast<Trader>(trader)->AcceptMatlTrades(responses);
}

template<>
inline void AcceptTrades(
    std::shared_ptr<Trader> trader,
    const std::vector< std::pair<Trade<Product>, Product::Ptr> >& responses) {
  trader->AcceptProductTrades(responses);
}

}  // namespace cyclus

#endif  // CYCLUS_SRC_TRADER_MANAGEMENT_H_
