#ifndef CONTROLVIEW_H
#define CONTROLVIEW_H

#include <QInputMethodEvent>
#include <QTextCharFormat>
#include <QWidget>

class ColorPicker;
class QComboBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QSpinBox;

class ControlView : public QWidget
{
    Q_OBJECT
public:
    explicit ControlView(QWidget *parent = 0);

public slots:
    void sendEvent(int, int, QTextCharFormat::UnderlineStyle, const QColor &, const QColor &, const QString &);
    void sendEvent();

signals:
    void forwardEvent(QInputMethodEvent);

private:
    QComboBox *m_underlineStyleCombo;
    ColorPicker *m_underlineColorPicker;
    ColorPicker *m_backgroundColorPicker;
    QSpinBox *m_startSpin;
    QSpinBox *m_endSpin;
    QLineEdit *m_inputLine;
    QPushButton *m_sendEventButton;
    QLabel *m_processedLabel;

    bool m_eventSent;
};

#endif // CONTROLVIEW_H
