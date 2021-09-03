#include <gtest/gtest.h>

#include "agent.h"

#include "test_context.h"
#include "test_agents/test_agent.h"

namespace cyclus {

TEST(AgentClassTests, lifetime) {
  TestContext tc;
  std::shared_ptr<Agent> a(new TestAgent(tc.get()));

  EXPECT_EQ(-1, a->lifetime());
  EXPECT_NO_THROW(a->lifetime(42));
  EXPECT_EQ(42, a->lifetime());
  a->Build(NULL);
  EXPECT_THROW(a->lifetime(13), ValueError);
  EXPECT_EQ(42, a->lifetime());
}

TEST(AgentClassTests, FamilyTree) {
  TestContext tc;

  std::shared_ptr<Agent> child(new TestAgent(tc.get()));
  std::shared_ptr<Agent> parent(new TestAgent(tc.get()));
  std::shared_ptr<Agent> grandparent(new TestAgent(tc.get()));

  // family tree
  EXPECT_TRUE(grandparent->InFamilyTree(grandparent));
  EXPECT_FALSE(grandparent->InFamilyTree(child));
  EXPECT_FALSE(grandparent->InFamilyTree(parent));
  EXPECT_TRUE(parent->InFamilyTree(parent));
  EXPECT_FALSE(parent->InFamilyTree(child));
  EXPECT_FALSE(parent->InFamilyTree(grandparent));
  EXPECT_TRUE(child->InFamilyTree(child));
  EXPECT_FALSE(child->InFamilyTree(parent));
  EXPECT_FALSE(child->InFamilyTree(grandparent));
  // ancestor
  EXPECT_FALSE(grandparent->AncestorOf(grandparent));
  EXPECT_FALSE(grandparent->AncestorOf(child));
  EXPECT_FALSE(grandparent->AncestorOf(parent));
  EXPECT_FALSE(parent->AncestorOf(parent));
  EXPECT_FALSE(parent->AncestorOf(child));
  EXPECT_FALSE(parent->AncestorOf(grandparent));
  EXPECT_FALSE(child->AncestorOf(child));
  EXPECT_FALSE(child->AncestorOf(parent));
  EXPECT_FALSE(child->AncestorOf(grandparent));
  // decendent
  EXPECT_FALSE(grandparent->DecendentOf(grandparent));
  EXPECT_FALSE(grandparent->DecendentOf(child));
  EXPECT_FALSE(grandparent->DecendentOf(parent));
  EXPECT_FALSE(parent->DecendentOf(parent));
  EXPECT_FALSE(parent->DecendentOf(child));
  EXPECT_FALSE(parent->DecendentOf(grandparent));
  EXPECT_FALSE(child->DecendentOf(child));
  EXPECT_FALSE(child->DecendentOf(parent));
  EXPECT_FALSE(child->DecendentOf(grandparent));

  parent->Build(grandparent);
  child->Build(parent);

  // family tree
  EXPECT_TRUE(grandparent->InFamilyTree(grandparent));
  EXPECT_TRUE(grandparent->InFamilyTree(child));
  EXPECT_TRUE(grandparent->InFamilyTree(parent));
  EXPECT_TRUE(parent->InFamilyTree(parent));
  EXPECT_TRUE(parent->InFamilyTree(child));
  EXPECT_TRUE(parent->InFamilyTree(grandparent));
  EXPECT_TRUE(child->InFamilyTree(child));
  EXPECT_TRUE(child->InFamilyTree(parent));
  EXPECT_TRUE(child->InFamilyTree(grandparent));
  // ancestor
  EXPECT_FALSE(grandparent->AncestorOf(grandparent));
  EXPECT_TRUE(grandparent->AncestorOf(child));
  EXPECT_TRUE(grandparent->AncestorOf(parent));
  EXPECT_FALSE(parent->AncestorOf(parent));
  EXPECT_TRUE(parent->AncestorOf(child));
  EXPECT_FALSE(parent->AncestorOf(grandparent));
  EXPECT_FALSE(child->AncestorOf(child));
  EXPECT_FALSE(child->AncestorOf(parent));
  EXPECT_FALSE(child->AncestorOf(grandparent));
  // decendent
  EXPECT_FALSE(grandparent->DecendentOf(grandparent));
  EXPECT_FALSE(grandparent->DecendentOf(child));
  EXPECT_FALSE(grandparent->DecendentOf(parent));
  EXPECT_FALSE(parent->DecendentOf(parent));
  EXPECT_FALSE(parent->DecendentOf(child));
  EXPECT_TRUE(parent->DecendentOf(grandparent));
  EXPECT_FALSE(child->DecendentOf(child));
  EXPECT_TRUE(child->DecendentOf(parent));
  EXPECT_TRUE(child->DecendentOf(grandparent));
}

} // namespace cyclus
