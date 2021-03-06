#include "mainwindow.h"

#include <QApplication>
#include <QFormLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>

#include "controlview.h"
#include "referenceview.h"
#include "testview.h"
#include "webview.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_controlView(new ControlView)
    , m_referenceView(new ReferenceView)
    , m_webView(new WebView)
    , m_testView(new TestView)
    , m_referenceProcessed(new QLabel)
    , m_webProcessed(new QLabel)
{
    m_controlView->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_controlView->setFixedWidth(300);

    m_webView->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_webView->setFixedWidth(280);
    m_webView->setFixedHeight(150);

    m_testView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_testView->setMinimumWidth(400);

    QWidget *centralWidget = new QWidget;

    QGroupBox *referenceGroup = new QGroupBox(QStringLiteral("Reference"));
    referenceGroup->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    referenceGroup->setMinimumWidth(300);
    QFormLayout *referenceProcessedForm = new QFormLayout;
    referenceProcessedForm->addRow(tr("Processed:"), m_referenceProcessed);
    QVBoxLayout *referenceLayout = new QVBoxLayout;
    referenceLayout->addWidget(m_referenceView);
    referenceLayout->addLayout(referenceProcessedForm);
    referenceGroup->setLayout(referenceLayout);

    QGroupBox *webGroup = new QGroupBox(QStringLiteral("Web"));
    webGroup->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    webGroup->setMinimumWidth(300);
    QFormLayout *webProcessedForm = new QFormLayout;
    webProcessedForm->addRow(tr("Processed:"), m_webProcessed);
    QVBoxLayout *webLayout = new QVBoxLayout;
    webLayout->addWidget(m_webView);
    webLayout->addLayout(webProcessedForm);
    webGroup->setLayout(webLayout);

    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addWidget(m_controlView);
    leftLayout->addWidget(referenceGroup);
    leftLayout->addWidget(webGroup);

    QHBoxLayout *centralLayout = new QHBoxLayout;
    centralLayout->addLayout(leftLayout);
    centralLayout->addWidget(m_testView);

    connect(m_testView, &TestView::sendInputMethodData, m_controlView, &ControlView::receiveInputMethodData);
    connect(m_testView, &TestView::requestInputMethodEvent, m_controlView, &ControlView::createAndSendInputMethodEvent);

    connect(m_controlView, &ControlView::sendInputMethodEvent, [=](QInputMethodEvent im) {
        bool processed;
        QString resultText;

        processed = QApplication::sendEvent(m_referenceView->referenceInput(), &im);
        resultText = processed ? QStringLiteral("<font color='green'>TRUE</font>")
                               : QStringLiteral("<font color='red'>FALSE</font>");
        m_referenceProcessed->setText(resultText);

        processed = QApplication::sendEvent(m_webView->focusProxy(), &im);
        resultText = processed ? QStringLiteral("<font color='green'>TRUE</font>")
                               : QStringLiteral("<font color='red'>FALSE</font>");
        m_webProcessed->setText(resultText);
    });

    centralWidget->setLayout(centralLayout);
    setCentralWidget(centralWidget);
    setWindowTitle(tr("Input Methods Format Manual Test"));
}

MainWindow::~MainWindow()
{

}
