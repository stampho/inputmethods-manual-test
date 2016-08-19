#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>

class ControlView;
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
    WebView *m_webView;
    TestView *m_testView;
};

#endif // WINDOW_H
