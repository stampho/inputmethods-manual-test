#include "testview.h"

#include <QFile>
#include <QVBoxLayout>
#include <QPushButton>
#include <QRegExp>
#include <QStandardItemModel>
#include <QTableView>
#include <QTest>
#include <QTextCharFormat>

#include <QDebug>

TestView::TestView(QWidget *parent)
    : QWidget(parent)
    , m_tableView(new QTableView)
    , m_testButton(new QPushButton)
    , m_testRunning(false)
{
    m_testButton->setText(QStringLiteral("Start Test"));
    connect(m_testButton, &QPushButton::clicked, this, &TestView::startOrCancelTest);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_tableView);
    layout->addWidget(m_testButton);
    setLayout(layout);

    QStandardItemModel *model = new QStandardItemModel(0, 6, this);
    model->setHorizontalHeaderItem(0, new QStandardItem(tr("Input")));
    model->setHorizontalHeaderItem(1, new QStandardItem(tr("Start")));
    model->setHorizontalHeaderItem(2, new QStandardItem(tr("End")));
    model->setHorizontalHeaderItem(3, new QStandardItem(tr("Underline")));
    model->setHorizontalHeaderItem(4, new QStandardItem(tr("Underline Color")));
    model->setHorizontalHeaderItem(5, new QStandardItem(tr("Background Color")));

    m_tableView->setModel(model);
    connect(m_tableView, &QTableView::clicked, this, &TestView::collectAndSendData);

    loadTestData(":/testdata.csv");
}

void TestView::loadTestData(const QString &testDataPath)
{
    QFile testDataFile(testDataPath);
    if (!testDataFile.open(QIODevice::ReadOnly)) {
        qWarning() << "Unable to open " << testDataFile.fileName() << ":" << testDataFile.errorString();
        return;
    }

    QTextStream testDataStream(&testDataFile);
    while (!testDataStream.atEnd()) {
        QString line = testDataStream.readLine();
        QRegExp data("^\"(.*)\"\\s*,\\s*(-?\\d+)\\s*,\\s*(-?\\d+)\\s*,\\s*(\\d+)\\s*,\\s*\"(.*)\"\\s*,\\s*\"(.*)\"\\s*$");
        if (!data.exactMatch(line))
            continue;

        QStandardItemModel *model = qobject_cast<QStandardItemModel *>(m_tableView->model());

        QList<QStandardItem *> row;
        for (int i = 1; i < data.captureCount(); ++i)
            row.append(new QStandardItem(data.cap(i)));

        model->appendRow(row);
    }

    testDataFile.close();
}

void TestView::startOrCancelTest()
{
    if (m_testRunning) {
        m_testRunning = false;
        m_testButton->setText(QStringLiteral("Start Test"));
        return;
    }

    m_testRunning = true;
    m_testButton->setText(QStringLiteral("Cancel Test"));

    int firstRowIndex = m_tableView->currentIndex().row() + 1;
    if (firstRowIndex == m_tableView->model()->rowCount())
        firstRowIndex = 0;

    for (int row = firstRowIndex; row < m_tableView->model()->rowCount(); ++row) {
        if (!m_testRunning)
            break;

        m_tableView->selectRow(row);
        collectAndSendData();
        emit requestInputMethodEvent();

        QTest::qWait(1000);
    }

    if (m_testRunning) {
        m_testRunning = false;
        m_testButton->setText(QStringLiteral("Start Test"));
    }
}

void TestView::collectAndSendData()
{
    int row = m_tableView->currentIndex().row();
    QStandardItemModel *model = static_cast<QStandardItemModel *>(m_tableView->model());

    const QString &input = model->data(model->index(row, 0)).toString();
    const int start = model->data(model->index(row, 1)).toInt();
    const int end = model->data(model->index(row, 2)).toInt();
    const QTextCharFormat::UnderlineStyle underlineStyle = static_cast<QTextCharFormat::UnderlineStyle>(model->data(model->index(row, 3)).toInt());
    const QColor &underlineColor = qvariant_cast<QColor>(model->data(model->index(row, 4)));
    const QColor &backgroundColor = qvariant_cast<QColor>(model->data(model->index(row, 6)));

    emit sendInputMethodData(start, end, underlineStyle, underlineColor, backgroundColor.isValid() ? backgroundColor : Qt::white, input);
}
