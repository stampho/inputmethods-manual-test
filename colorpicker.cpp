#include "colorpicker.h"

#include <QColorDialog>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>

ColorPicker::ColorPicker(QWidget *parent)
    : QWidget(parent)
    , m_colorInput(new QLineEdit)
    , m_selectButton(new QPushButton)
{
    m_selectButton->setText(tr("Choose"));

    QHBoxLayout *layout = new QHBoxLayout;
    layout->setMargin(0);
    layout->addWidget(m_colorInput);
    layout->addWidget(m_selectButton);
    setLayout(layout);

    connect(m_colorInput, &QLineEdit::textChanged, this, &ColorPicker::colorStringChanged);
    connect(m_selectButton, &QPushButton::clicked, this, &ColorPicker::selectButtonClicked);
}

QColor ColorPicker::color() const
{
    return QColor(m_colorInput->text());
}

void ColorPicker::setColor(const QColor &color)
{
    if (color.isValid())
        m_colorInput->setText(color.name(QColor::HexArgb));
}

void ColorPicker::colorStringChanged(const QString &colorString)
{
    QColor color(colorString);
    QPalette palette;

    palette.setColor(QPalette::Base, color.isValid() ? color : QColor(Qt::white));
    m_colorInput->setPalette(palette);
}

void ColorPicker::selectButtonClicked()
{
    QColor selectedColor = QColorDialog::getColor(color().isValid() ? color() : Qt::white,
                                                  this,
                                                  "Select Color",
                                                  QColorDialog::ShowAlphaChannel);
    setColor(selectedColor);
}
