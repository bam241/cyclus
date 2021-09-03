#include "timeseries.h"

namespace cyclus {
namespace toolkit {

std::map<std::string, std::vector<time_series_listener_t> > TIME_SERIES_LISTENERS;

template <>
void RecordTimeSeries<POWER>(std::shared_ptr<Agent> agent, double value, std::string units) {
  RecordTimeSeries<double>("Power", agent, value, units);
}

template <>
void RecordTimeSeries<ENRICH_SWU>(std::shared_ptr<Agent> agent, double value, std::string units) {
  RecordTimeSeries<double>("EnrichmentSWU", agent, value, units);
}

template <>
void RecordTimeSeries<ENRICH_FEED>(std::shared_ptr<Agent> agent, double value, std::string units) {
  RecordTimeSeries<double>("EnrichmentFeed", agent, value, units);
}

}  // namespace toolkit
}  // namespace cyclus
