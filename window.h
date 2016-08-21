#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>

class ControlView;
class QLabel;
class ReferenceView;
class TestView;
class WebView;

class Window : public QWidget
{
    Q_OBJECT

public:
    Window(QWidget *parent = 0);
    ~Window();

private:
    ControlView *m_controlView;
    ReferenceView *m_referenceView;
    WebView *m_webView;
    TestView *m_testView;

    QLabel *m_referenceProcessed;
    QLabel *m_webProcessed;
};

#endif // WINDOW_H
