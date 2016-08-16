#ifndef COLORPICKER_H
#define COLORPICKER_H

#include <QWidget>

class QLineEdit;
class QPushButton;

class ColorPicker : public QWidget
{
    Q_OBJECT
public:
    explicit ColorPicker(QWidget *parent = 0);

public slots:
    void colorStringChanged(const QString &);
    void selectButtonClicked();

private:
    QLineEdit *m_colorInput;
    QPushButton *m_selectButton;
};

#endif // COLORPICKER_H
