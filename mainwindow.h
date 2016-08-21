#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class ControlView;
class QLabel;
class ReferenceView;
class TestView;
class WebView;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    ControlView *m_controlView;
    ReferenceView *m_referenceView;
    WebView *m_webView;
    TestView *m_testView;

    QLabel *m_referenceProcessed;
    QLabel *m_webProcessed;
};

#endif // MAINWINDOW_H
