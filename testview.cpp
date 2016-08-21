#include "testview.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QStandardItemModel>
#include <QTableView>
#include <QTest>
#include <QTextCharFormat>

#include <QDebug>

TestView::TestView(QWidget *parent)
    : QWidget(parent)
    , m_tableView(new QTableView)
    , m_testButton(new QPushButton)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setMinimumWidth(400);

    m_testButton->setText(QStringLiteral("Start Test"));
    connect(m_testButton, &QPushButton::clicked, this, &TestView::startTest);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_tableView);
    layout->addWidget(m_testButton);
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

    // Dummy test entry #1
    model->setItem(0, 0, new QStandardItem("This is Qt"));
    model->setItem(0, 1, new QStandardItem("8"));
    model->setItem(0, 2, new QStandardItem("10"));
    model->setItem(0, 3, new QStandardItem("1"));
    model->setItem(0, 4, new QStandardItem("#ffff0000"));
    model->setItem(0, 5, new QStandardItem("1"));
    model->setItem(0, 6, new QStandardItem("#ff00ff00"));

    // Dummy test entry #2
    model->setItem(1, 0, new QStandardItem("This is Qt"));
    model->setItem(1, 1, new QStandardItem("5"));
    model->setItem(1, 2, new QStandardItem("7"));
    model->setItem(1, 3, new QStandardItem("1"));
    model->setItem(1, 4, new QStandardItem("green"));
    model->setItem(1, 5, new QStandardItem("1"));
    model->setItem(1, 6, new QStandardItem("red"));

    // Dummy test entry #3
    model->setItem(2, 0, new QStandardItem("The End"));
    model->setItem(2, 1, new QStandardItem("0"));
    model->setItem(2, 2, new QStandardItem("3"));
    model->setItem(2, 3, new QStandardItem("1"));
    model->setItem(2, 4, new QStandardItem("#ff0000ff"));
    model->setItem(2, 5, new QStandardItem("0"));
    model->setItem(2, 6, new QStandardItem(""));
}

void TestView::startTest()
{
    QStandardItemModel *model = static_cast<QStandardItemModel *>(m_tableView->model());

    for (int row = 0; row < model->rowCount(); ++row) {
        m_tableView->selectRow(row);
        const QString &input = model->data(model->index(row, 0)).toString();
        const int start = model->data(model->index(row, 1)).toInt();
        const int end = model->data(model->index(row, 2)).toInt();
        const QTextCharFormat::UnderlineStyle underlineStyle = static_cast<QTextCharFormat::UnderlineStyle>(model->data(model->index(row, 3)).toInt());
        const QColor &underlineColor = qvariant_cast<QColor>(model->data(model->index(row, 4)));
        const bool backgroundEnabled = model->data(model->index(row, 5)).toBool();

        QColor backgroundColor;
        if (backgroundEnabled)
            backgroundColor = qvariant_cast<QColor>(model->data(model->index(row, 6)));

        emit sendEvent(start, end, underlineStyle, underlineColor, backgroundColor, input);
        QTest::qWait(1000);
    }
}
