#include "testview.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QStandardItemModel>
#include <QTableView>

TestView::TestView(QWidget *parent)
    : QWidget(parent)
    , m_tableView(new QTableView)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setMinimumWidth(400);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_tableView);
    layout->addWidget(new QPushButton("Start Test"));
    setLayout(layout);

    QStandardItemModel *model = new QStandardItemModel(2, 7, this);
    model->setHorizontalHeaderItem(0, new QStandardItem(tr("Input")));
    model->setHorizontalHeaderItem(1, new QStandardItem(tr("Start")));
    model->setHorizontalHeaderItem(2, new QStandardItem(tr("End")));
    model->setHorizontalHeaderItem(3, new QStandardItem(tr("Underline")));
    model->setHorizontalHeaderItem(4, new QStandardItem(tr("Underline Color")));
    model->setHorizontalHeaderItem(5, new QStandardItem(tr("Background")));
    model->setHorizontalHeaderItem(6, new QStandardItem(tr("Background Color")));

    m_tableView->setModel(model);

    model->setItem(0, 0, new QStandardItem("This is Qt"));
    model->setItem(0, 1, new QStandardItem("8"));
    model->setItem(0, 2, new QStandardItem("10"));
    model->setItem(0, 3, new QStandardItem("1"));
    model->setItem(0, 4, new QStandardItem("#ffff0000"));
    model->setItem(0, 5, new QStandardItem("1"));
    model->setItem(0, 6, new QStandardItem("#ff00ff00"));
}
