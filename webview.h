#ifndef WEBVIEW_H
#define WEBVIEW_H

#include <QWebEngineView>

class WebView : public QWebEngineView
{
    Q_OBJECT
public:
    //explicit WebView(QWidget *parent = 0);
    WebView(QWidget *parent = 0);
};

#endif // WEBVIEW_H
