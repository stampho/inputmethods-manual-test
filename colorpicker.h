#ifndef COLORPICKER_H
#define COLORPICKER_H

#include <QColor>
#include <QWidget>

class QLineEdit;
class QPushButton;

class ColorPicker : public QWidget
{
    Q_OBJECT
public:
    explicit ColorPicker(QWidget *parent = 0);

    QColor color() const;
    void setColor(const QColor &);

public slots:
    void colorStringChanged(const QString &);
    void selectButtonClicked();

private:
    QLineEdit *m_colorInput;
    QPushButton *m_selectButton;
};

#endif // COLORPICKER_H
