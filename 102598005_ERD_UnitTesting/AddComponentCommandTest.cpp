#include "gtest/gtest.h"
#include "AddComponentCommand.h"

class AddComponentCommandTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		_model = new ERModel();
		_commandEntity = AddComponentCommand(_model, make_pair(entity, ""), "PC", QPointF(0, 0));
		_commandAttribute = AddComponentCommand(_model, make_pair(attribute, ""), "ID", QPointF(0, 0));
		_commandRelation = AddComponentCommand(_model, make_pair(relation, ""), "Has", QPointF(0, 0));
	}

	virtual void TearDown()
	{
		delete _model;
	}
	ERModel* _model;
	AddComponentCommand _commandEntity;
	AddComponentCommand _commandAttribute;
	AddComponentCommand _commandRelation;
};

// 測試執行新增元件
TEST_F(AddComponentCommandTest, execute)
{
	EXPECT_EQ(0, _model->getComponentSize());
	
	_commandEntity.execute();
	EXPECT_EQ(1, _model->getComponentSize());
	EXPECT_EQ(0, _model->getNodeID());
	EXPECT_EQ(entity, _model->getNodeType(0).first);
	EXPECT_EQ("PC", _model->getNodeText(0));

	_commandAttribute.execute();
	EXPECT_EQ(2, _model->getComponentSize());
	EXPECT_EQ(1, _model->getNodeID());
	EXPECT_EQ(attribute, _model->getNodeType(1).first);
	EXPECT_EQ("ID", _model->getNodeText(1));

	_commandRelation.execute();
	EXPECT_EQ(3, _model->getComponentSize());
	EXPECT_EQ(2, _model->getNodeID());
	EXPECT_EQ(relation, _model->getNodeType(2).first);
	EXPECT_EQ("Has", _model->getNodeText(2));
}

// 測試刪除新增的元件
TEST_F(AddComponentCommandTest, unexecute)
{
	_commandEntity.execute();
	EXPECT_EQ(1, _model->getComponentSize());
	_commandAttribute.execute();
	EXPECT_EQ(2, _model->getComponentSize());
	_commandRelation.execute();
	EXPECT_EQ(3, _model->getComponentSize());

	_commandRelation.unexecute();
	EXPECT_EQ(2, _model->getComponentSize());
	_commandRelation.unexecute();
	EXPECT_EQ(1, _model->getComponentSize());
	_commandRelation.unexecute();
	EXPECT_EQ(0, _model->getComponentSize());
}