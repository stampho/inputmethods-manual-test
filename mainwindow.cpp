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
    QWidget *centralWidget = new QWidget;

    QGroupBox *referenceGroup = new QGroupBox(QStringLiteral("Reference"));
    QFormLayout *referenceProcessedForm = new QFormLayout;
    referenceProcessedForm->addRow(tr("Processed:"), m_referenceProcessed);
    QVBoxLayout *referenceLayout = new QVBoxLayout;
    referenceLayout->addWidget(m_referenceView);
    referenceLayout->addLayout(referenceProcessedForm);
    referenceGroup->setLayout(referenceLayout);

    QGroupBox *webGroup = new QGroupBox(QStringLiteral("Web"));
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
    // TODO(pvarga): Resizing doesn't grow Test View
    centralLayout->addWidget(m_testView);

    connect(m_testView, SIGNAL(sendEvent(int,int,QTextCharFormat::UnderlineStyle,QColor,QColor,QString)),
            m_controlView, SLOT(sendEvent(int,int,QTextCharFormat::UnderlineStyle,QColor,QColor,QString)));

    connect(m_controlView, &ControlView::forwardEvent, [=](QInputMethodEvent im) {
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

    // TODO(pvarga): This is for testing only. Remove it.
    connect(m_webView, &WebView::loadFinished, [=]() {
        m_controlView->sendEvent(1, 3, QTextCharFormat::SingleUnderline, Qt::red, QColor(), QStringLiteral("Test message"));
    });
}

MainWindow::~MainWindow()
{

}
