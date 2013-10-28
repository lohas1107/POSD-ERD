#include "gtest/gtest.h"
#include "ComponentFactory.h"

class ComponentFactoryTest : public ::testing::Test
{
protected:
	ComponentFactory _factory;
};

// 整合測試產生元件
TEST_F(ComponentFactoryTest, createComponent)
{
	ERComponent* component = _factory.createComponent(make_pair(entity, "E"));
	EXPECT_EQ(entity, component->getType().first);
	EXPECT_EQ("Entity", component->getType().second);
	delete component;
	component = _factory.createComponent(make_pair(attribute, "A"));
	EXPECT_EQ(attribute, component->getType().first);
	EXPECT_EQ("Attribute", component->getType().second);
	delete component;
	component = _factory.createComponent(make_pair(relation, "R"));
	EXPECT_EQ(relation, component->getType().first);
	EXPECT_EQ("Relation", component->getType().second);
	delete component;
	component = _factory.createComponent(make_pair(connection, "C"));
	EXPECT_EQ(connection, component->getType().first);
	EXPECT_EQ("Connection", component->getType().second);
	delete component;
	component = _factory.createComponent(make_pair(none, "N"));
	EXPECT_EQ(NULL, component);
	delete component;
}