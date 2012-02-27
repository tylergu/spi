#include "common/common_unittest.h"
#include "agent/context.h"

// For testing SpContext

namespace {


class ContextTest : public testing::Test {
  public:
  ContextTest() {
  }

  protected:

  virtual void SetUp() {
  }

  virtual void TearDown() {
  }
};

TEST_F(ContextTest, default_setting) {
  sp::SpAgent::ptr agent = sp::SpAgent::Create();
  ASSERT_TRUE(agent);

  MockEvent::ptr event = MockEvent::Create();
  agent->SetInitEvent(event);
  agent->Go();

  ASSERT_TRUE(agent->context());
  EXPECT_TRUE(agent->context()->init_entry());
  EXPECT_TRUE(agent->context()->init_exit() == NULL);
  EXPECT_TRUE(agent->context()->ipc_mgr() == NULL);
  EXPECT_TRUE(agent->context()->init_propeller() == agent->init_propeller());
  EXPECT_FALSE(agent->context()->IsDirectcallOnlyEnabled());
  EXPECT_FALSE(agent->context()->IsIpcEnabled());
  EXPECT_TRUE(agent->context()->init_entry_name().size() > 0);
  EXPECT_TRUE(agent->context()->init_exit_name().size() == 0);
}

TEST_F(ContextTest, customized_setting) {
  sp::SpAgent::ptr agent = sp::SpAgent::Create();
  ASSERT_TRUE(agent);

  MockEvent::ptr event = MockEvent::Create();
  agent->SetInitEvent(event);

  sp::SpParser::ptr parser = sp::SpParser::Create();
  ASSERT_TRUE(parser);

  sp::SpPropeller::ptr propeller = sp::SpPropeller::Create();
  ASSERT_TRUE(propeller);

  agent->SetParser(parser);
  agent->SetInitEntry("wrapper_entry");
  agent->SetInitExit("wrapper_exit");
  agent->SetInitPropeller(propeller);

  agent->EnableDirectcallOnly(true);
  agent->EnableIpc(true);

  agent->Go();

  ASSERT_TRUE(agent->context());
  EXPECT_TRUE(agent->context()->init_entry());
  EXPECT_TRUE(agent->context()->init_exit());

  EXPECT_TRUE(agent->context()->ipc_mgr());
  EXPECT_TRUE(agent->context()->init_propeller() == propeller);
  EXPECT_TRUE(agent->context()->IsDirectcallOnlyEnabled());
  EXPECT_TRUE(agent->context()->IsIpcEnabled());
  EXPECT_TRUE(agent->context()->init_entry_name().size() > 0);
  EXPECT_TRUE(agent->context()->init_exit_name().size() > 0);

}

TEST_F(ContextTest, customized_setting_parse_only) {
  sp::SpAgent::ptr agent = sp::SpAgent::Create();
  MockEvent::ptr event = MockEvent::Create();
  agent->SetInitEvent(event);

  ASSERT_TRUE(agent);
  agent->EnableParseOnly(true);

  agent->Go();

  ASSERT_FALSE(agent->context());

}

}