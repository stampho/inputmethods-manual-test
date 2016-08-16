#include "controlview.h"

#include <QComboBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>

ControlView::ControlView(QWidget *parent)
    : QWidget(parent)
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setFixedWidth(300);

    QFormLayout *layout = new QFormLayout;
    layout->addRow(tr("Underline Style:"), new QComboBox);
    layout->addRow(tr("Underline Color:"), new QLineEdit);
    layout->addRow(tr("Background Color:"), new QLineEdit);
    layout->addRow(tr("Start:"), new QSpinBox);
    layout->addRow(tr("End:"), new QSpinBox);
    layout->addRow(tr("Input:"), new QLineEdit);
    layout->addRow(new QPushButton(tr("Send Event")));
    layout->addRow(tr("Processed:"), new QLabel("Pass"));
    setLayout(layout);
}
