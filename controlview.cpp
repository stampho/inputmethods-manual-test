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
{
    m_underlineStyleCombo->addItem(tr("No Underline"), QVariant(QTextCharFormat::NoUnderline));
    m_underlineStyleCombo->addItem(tr("Single Underline"), QVariant(QTextCharFormat::SingleUnderline));

    m_startSpin->setMinimum(-99);
    m_endSpin->setMinimum(-99);

    m_sendEventButton->setText(tr("Send Input Method Event"));

    QFormLayout *layout = new QFormLayout;
    layout->addRow(tr("Underline Style:"), m_underlineStyleCombo);
    layout->addRow(tr("Underline Color:"), m_underlineColorPicker);
    layout->addRow(tr("Background Color:"), m_backgroundColorPicker);
    layout->addRow(tr("Start:"), m_startSpin);
    layout->addRow(tr("End:"), m_endSpin);
    layout->addRow(tr("Input:"), m_inputLine);
    layout->addRow(m_sendEventButton);
    setLayout(layout);

    connect(m_sendEventButton, &QPushButton::clicked, this, &ControlView::createAndSendInputMethodEvent);
}

void ControlView::receiveInputMethodData(int start,
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
}

void ControlView::createAndSendInputMethodEvent()
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

    emit sendInputMethodEvent(im);
}
