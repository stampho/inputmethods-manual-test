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
    void startOrCancelTest();
    void collectAndSendData();

signals:
    void sendInputMethodData(int, int, QTextCharFormat::UnderlineStyle, const QColor &, const QColor &, const QString &);
    void requestInputMethodEvent();

private:
    QTableView *m_tableView;
    QPushButton *m_testButton;

    bool m_testRunning;
};

#endif // TESTVIEW_H
