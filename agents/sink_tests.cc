#include <gtest/gtest.h>

#include "sink.h"

#include "context.h"
#include "facility_tests.h"
#include "agent_tests.h"

using cyclus::Sink;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
class SinkTest : public ::testing::Test {
 protected:
  cyclus::TestContext tc_;
  Sink* src_facility_;

  virtual void SetUp() {
    src_facility_ = new Sink(tc_.get());
  }

  virtual void TearDown() {}
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
TEST_F(SinkTest, clone) {
  Sink* cloned_fac = dynamic_cast<Sink*> (src_facility_->Clone());
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
TEST_F(SinkTest, InitialState) {
  // Test things about the initial state of the facility here
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
TEST_F(SinkTest, Print) {
  EXPECT_NO_THROW(std::string s = src_facility_->str());
  // Test Sink specific aspects of the print method here
}


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
TEST_F(SinkTest, ReceiveMessage) {
  // Test Sink specific behaviors of the ReceiveMessage function here
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
TEST_F(SinkTest, Tick) {
  int time = 1;
  ASSERT_NO_THROW(src_facility_->Tick());
  // Test Sink specific behaviors of the Tick function here
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
TEST_F(SinkTest, Tock) {
  int time = 1;
  EXPECT_NO_THROW(src_facility_->Tock());
  // Test Sink specific behaviors of the Tock function here
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
std::shared_ptr<cyclus::Agent> SinkConstructor(cyclus::Context* ctx) {
  return std::shared_ptr<cyclus::Agent>(new Sink(ctx));
}

// Required to get functionality in cyclus agent unit tests library
#ifndef CYCLUS_AGENT_TESTS_CONNECTED
int ConnectAgentTests();
static int cyclus_agent_tests_connected = ConnectAgentTests();
#define CYCLUS_AGENT_TESTS_CONNECTED cyclus_agent_tests_connected
#endif  // CYCLUS_AGENT_TESTS_CONNECTED

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
INSTANTIATE_TEST_CASE_P(SinkFac, FacilityTests,
                        ::testing::Values(&SinkConstructor));

INSTANTIATE_TEST_CASE_P(SinkFac, AgentTests,
                        ::testing::Values(&SinkConstructor));
