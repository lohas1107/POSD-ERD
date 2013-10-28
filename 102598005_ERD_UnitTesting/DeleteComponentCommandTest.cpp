#include "gtest/gtest.h"
#include "DeleteComponentCommand.h"

class DeleteComponentCommandTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		_model = new ERModel();
		_model->addComponent(make_pair(entity, ""), "PC");
		_model->addComponent(make_pair(attribute, ""), "ID");
		_model->addComponent(make_pair(relation, ""), "Has");
	}

	virtual void TearDown()
	{
		delete _model;
	}
	ERModel* _model;
};

// 測試執行刪除元件
TEST_F(DeleteComponentCommandTest, execute)
{
	EXPECT_EQ(3, _model->getComponentSize());
	DeleteComponentCommand deleteEntity(_model, 0);
	deleteEntity.execute();
	EXPECT_EQ(2, _model->getComponentSize());
	DeleteComponentCommand deleteAttribute(_model, 1);
	deleteAttribute.execute();
	EXPECT_EQ(1, _model->getComponentSize());
	DeleteComponentCommand deleteRelation(_model, 2);
	deleteRelation.execute();
	EXPECT_EQ(0, _model->getComponentSize());
}

// 測試回覆刪除元件
TEST_F(DeleteComponentCommandTest, unexecute)
{
	DeleteComponentCommand deleteEntity(_model, 0);
	deleteEntity.execute();
	DeleteComponentCommand deleteAttribute(_model, 1);
	deleteAttribute.execute();
	DeleteComponentCommand deleteRelation(_model, 2);
	deleteRelation.execute();
	EXPECT_EQ(0, _model->getComponentSize());

	deleteRelation.unexecute();
	EXPECT_EQ(1, _model->getComponentSize());
	EXPECT_EQ(relation, _model->getNodeType(2).first);
	EXPECT_EQ("Has", _model->getNodeText(2));

	deleteAttribute.unexecute();
	EXPECT_EQ(2, _model->getComponentSize());
	EXPECT_EQ(attribute, _model->getNodeType(1).first);
	EXPECT_EQ("ID", _model->getNodeText(1));

	deleteEntity.unexecute();
	EXPECT_EQ(3, _model->getComponentSize());
	EXPECT_EQ(entity, _model->getNodeType(0).first);
	EXPECT_EQ("PC", _model->getNodeText(0));
}