#ifndef REFERENCEVIEW_H
#define REFERENCEVIEW_H

#include <QLineEdit>
#include <QWidget>

class ReferenceView : public QWidget
{
    Q_OBJECT
public:
    explicit ReferenceView(QWidget *parent = 0);
    QLineEdit *referenceInput();

private:
    QLineEdit *m_referenceInput;
};

#endif // REFERENCEVIEW_H
