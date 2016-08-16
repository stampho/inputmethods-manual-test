#include "window.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <controlview.h>
#include <testview.h>
#include <webview.h>

Window::Window(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addWidget(new ControlView(this));
    leftLayout->addWidget(new WebView(this));

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addWidget(new TestView(this));

    setLayout(mainLayout);
}

Window::~Window()
{

}
