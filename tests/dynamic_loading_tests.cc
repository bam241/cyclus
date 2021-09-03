#include <gtest/gtest.h>

#include <stdlib.h>
#include <fstream>
#include <iostream>
#include "boost/filesystem.hpp"

#include "agent.h"
#include "context.h"
#include "dynamic_module.h"
#include "env.h"
#include "error.h"
#include "pyhooks.h"
#include "recorder.h"
#include "timer.h"

namespace fs = boost::filesystem;
using cyclus::DynamicModule;
using cyclus::AgentSpec;
using cyclus::Agent;

TEST(DynamicLoadingTests, ConstructTestFacility) {
  cyclus::PyStart();
  cyclus::Recorder rec;
  cyclus::Timer ti;
  cyclus::Context* ctx = new cyclus::Context(&ti, &rec);
  EXPECT_NO_THROW(DynamicModule::Make(ctx, AgentSpec("tests:TestFacility:TestFacility")));
  EXPECT_NO_THROW(DynamicModule::CloseAll());
  cyclus::PyStop();
}

TEST(DynamicLoadingTests, LoadLibError) {
  cyclus::PyStart();
  cyclus::Recorder rec;
  cyclus::Timer ti;
  cyclus::Context* ctx = new cyclus::Context(&ti, &rec);
  EXPECT_THROW(DynamicModule::Make(ctx, AgentSpec("foo:foo:not_a_fac")), cyclus::IOError);
  cyclus::PyStop();
}

TEST(DynamicLoadingTests, Exists) {
  cyclus::PyStart();
  EXPECT_TRUE(DynamicModule::Exists(AgentSpec("tests:TestFacility:TestFacility")));
  EXPECT_FALSE(DynamicModule::Exists(AgentSpec("foo:foo:not_a_fac")));
  cyclus::PyStop();
}

TEST(DynamicLoadingTests, CloneTestFacility) {
  cyclus::PyStart();
  cyclus::Recorder rec;
  cyclus::Timer ti;
  cyclus::Context* ctx = new cyclus::Context(&ti, &rec);
  EXPECT_NO_THROW(std::shared_ptr<Agent> fac = DynamicModule::Make(ctx, AgentSpec("tests:TestFacility:TestFacility"));
                  std::shared_ptr<Agent> clone(fac->Clone()););
  DynamicModule::CloseAll();
  cyclus::PyStop();
}
