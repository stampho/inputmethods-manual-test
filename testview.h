#ifndef TESTVIEW_H
#define TESTVIEW_H

#include <QTextCharFormat>
#include <QWidget>

class QPushButton;
class QTableView;

class TestView : public QWidget
{
    Q_OBJECT
public:
    explicit TestView(QWidget *parent = 0);

public slots:
    void loadTestData(const QString &);
    void startTest();

signals:
    void sendEvent(int, int, QTextCharFormat::UnderlineStyle, const QColor &, const QColor &, const QString &);

private:
    QTableView *m_tableView;
    QPushButton *m_testButton;
};

#endif // TESTVIEW_H
