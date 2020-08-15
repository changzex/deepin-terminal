#include "ut_listview_test.h"

#define private public
#include "itemwidget.h"
#include "listview.h"
#include "customcommandpanel.h"
#include "remotemanagementpanel.h"
#include "utils.h"
#undef private

//Google GTest 相关头文件
#include <gtest/gtest.h>

//Qt单元测试相关头文件
#include <QTest>
#include <QtGui>
#include <QSignalSpy>
#include <QDebug>


UT_ListView_Test::UT_ListView_Test()
{
}

void UT_ListView_Test::SetUp()
{
}

void UT_ListView_Test::TearDown()
{
}

TEST_F(UT_ListView_Test, CustomCommandListViewTest)
{
    CustomCommandPanel panel;
    panel.resize(242, 600);
    panel.show();

    ListView cmdListWidget(ListType_Custom, &panel);

    QList<QAction *> cmdActionList;
    const int cmdCount = 10;
    for(int i=0; i<=cmdCount; i++)
    {
        QString key = QString(QChar('A'+i));
        QAction *newAction = new QAction;
        newAction->setText(QString("cmd_%1").arg(i));
        newAction->setShortcut(QKeySequence(QString("Ctrl+Shift+%1").arg(key)));
        cmdListWidget.addItem(ItemFuncType_Item, newAction->text(), newAction->shortcut().toString());

        cmdActionList.append(newAction);
    }

    QObject::connect(&cmdListWidget, &ListView::itemClicked, &panel, &CustomCommandPanel::doCustomCommand);
    QObject::connect(&cmdListWidget, &ListView::listItemCountChange, &panel, &CustomCommandPanel::refreshCmdSearchState);
    QObject::connect(&cmdListWidget, &ListView::focusOut, &panel, &CustomCommandPanel::onFocusOut);

    ASSERT_EQ(cmdActionList.isEmpty(), false);

    QAction *firstAction = cmdActionList.first();
    QString firstCmdName = firstAction->text();
    EXPECT_EQ(firstCmdName, QString("cmd_%1").arg(0));

    QAction *lastAction = cmdActionList.last();
    QString lastCmdName = lastAction->text();
    EXPECT_EQ(lastCmdName, QString("cmd_%1").arg(cmdCount));

    cmdListWidget.removeItem(ItemFuncType_Item, firstCmdName);
    EXPECT_EQ(cmdListWidget.count(), cmdActionList.size()-1);

    QString updateCmdName = Utils::getRandString().toLower();
    cmdListWidget.updateItem(ItemFuncType_Item, lastCmdName, updateCmdName);

    QList<ItemWidget*> itemWidgetList = cmdListWidget.m_itemList;
    ItemWidget *lastItemWidget = itemWidgetList.last();
    EXPECT_EQ(lastItemWidget->m_firstText, updateCmdName);

    //释放内存
    for(int i=0; i<cmdActionList.size(); i++)
    {
        QAction *action = cmdActionList.at(i);
        delete action;
    }
}

TEST_F(UT_ListView_Test, RemoteManagementListViewTest)
{
}
