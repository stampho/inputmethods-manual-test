#include "window.h"

#include <QApplication>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <controlview.h>
#include <testview.h>
#include <webview.h>

#include <QDebug>

Window::Window(QWidget *parent)
    : QWidget(parent)
    , m_controlView(new ControlView)
    , m_webView(new WebView)
    , m_testView(new TestView)
{
    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addWidget(m_controlView);
    leftLayout->addWidget(m_webView);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addWidget(m_testView);

    setLayout(mainLayout);

    connect(m_controlView, &ControlView::forwardEvent, [=](QInputMethodEvent im) {
        bool processed = QApplication::sendEvent(m_webView->focusProxy(), &im);
        qDebug() << processed;
    });
}

Window::~Window()
{

}
