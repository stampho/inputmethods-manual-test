#include "referenceview.h"

#include <QVBoxLayout>

ReferenceView::ReferenceView(QWidget *parent)
    : QWidget(parent)
    , m_referenceInput(new QLineEdit)
{
    m_referenceInput->setMinimumHeight(50);
    m_referenceInput->setMaximumWidth(250);
    m_referenceInput->setFont(QFont(QStringLiteral("Serif"), 28));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_referenceInput);
    setLayout(layout);
}

QLineEdit *ReferenceView::referenceInput()
{
    return m_referenceInput;
}
