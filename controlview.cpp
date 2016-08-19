#include "controlview.h"

#include <QCoreApplication>
#include <QComboBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QTextCharFormat>
#include <QTextCursor>
#include <QInputMethodEvent>

#include "colorpicker.h"

ControlView::ControlView(QWidget *parent)
    : QWidget(parent)
    , m_underlineStyleCombo(new QComboBox)
    , m_underlineColorPicker(new ColorPicker)
    , m_backgroundColorPicker(new ColorPicker)
    , m_startSpin(new QSpinBox)
    , m_endSpin(new QSpinBox)
    , m_inputLine(new QLineEdit)
    , m_sendEventButton(new QPushButton)
    , m_processedLabel(new QLabel)
    , m_eventSent(false)
{
    m_underlineStyleCombo->addItem(tr("No Underline"), QVariant(QTextCharFormat::NoUnderline));
    m_underlineStyleCombo->addItem(tr("Single Underline"), QVariant(QTextCharFormat::SingleUnderline));
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setFixedWidth(300);

    m_sendEventButton->setText(tr("Send Event"));
    // TODO(pvarga): Implement this
    m_processedLabel->setText("<font color='green'>PASS</font>");

    QFormLayout *layout = new QFormLayout;
    layout->addRow(tr("Underline Style:"), m_underlineStyleCombo);
    layout->addRow(tr("Underline Color:"), m_underlineColorPicker);
    layout->addRow(tr("Background Color:"), m_backgroundColorPicker);
    layout->addRow(tr("Start:"), m_startSpin);
    layout->addRow(tr("End:"), m_endSpin);
    layout->addRow(tr("Input:"), m_inputLine);
    layout->addRow(m_sendEventButton);
    layout->addRow(tr("Processed:"), m_processedLabel);
    setLayout(layout);

    connect(m_sendEventButton, SIGNAL(clicked(bool)), this, SLOT(sendEvent()));
    connect(m_inputLine, &QLineEdit::textChanged, [=]() {
        if (m_eventSent) {
            QCoreApplication::sendEvent(m_inputLine, new QInputMethodEvent(QString(), QList<QInputMethodEvent::Attribute>()));
            m_eventSent = false;
        }
    });
}

void ControlView::sendEvent(int start,
                            int end,
                            QTextCharFormat::UnderlineStyle underlineStyle,
                            const QColor &underlineColor,
                            const QColor &backgroundColor,
                            const QString &input)
{
    m_startSpin->setValue(start);
    m_endSpin->setValue(end);
    // TODO(pvarga): Choose index by data
    m_underlineStyleCombo->setCurrentIndex(underlineStyle);
    m_underlineColorPicker->setColor(underlineColor);
    m_backgroundColorPicker->setColor(backgroundColor);
    m_inputLine->setText(input);

    sendEvent();
}

void ControlView::sendEvent()
{
    int start = m_startSpin->value();
    int end = m_endSpin->value();

    QTextCharFormat format;
    format.setUnderlineStyle(static_cast<QTextCharFormat::UnderlineStyle>(m_underlineStyleCombo->currentData().toInt()));
    format.setUnderlineColor(m_underlineColorPicker->color());

    const QColor &backgroundColor = m_backgroundColorPicker->color();
    if (backgroundColor.isValid())
        format.setBackground(QBrush(backgroundColor));

    QList<QInputMethodEvent::Attribute> attrs;
    attrs.append(QInputMethodEvent::Attribute(QInputMethodEvent::TextFormat, start, end, format));
    QInputMethodEvent im(m_inputLine->text(), attrs);
    m_inputLine->clear();

    QCoreApplication::sendEvent(m_inputLine, &im);
    m_eventSent = true;

    // TODO(pvarga): send event to WebView too
    emit forwardEvent(im);
}
