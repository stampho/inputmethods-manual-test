#ifndef TESTVIEW_H
#define TESTVIEW_H

#include <QWidget>

class QTableView;

class TestView : public QWidget
{
    Q_OBJECT
public:
    explicit TestView(QWidget *parent = 0);

private:
    QTableView *m_tableView;
};

#endif // TESTVIEW_H
