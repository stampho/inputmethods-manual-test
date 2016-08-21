#include "webview.h"

#include <QWebEnginePage>
#include <QWebEngineSettings>

WebView::WebView(QWidget *parent)
    : QWebEngineView(parent)
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    setFixedWidth(300);

    const QString html = QStringLiteral(
            "<html><head>"
            "   <style>"
            "       input {"
            "           width: 250px; height: 50px; font-size: 28pt;"
            "           position: absolute; top: 50%; left: 50%; margin-left: -125px; margin-top: -25px;"
            "           font-family: serif"
            "       }"
            "       body { background-color: black; }"
            "   </style>"
            "</head>"
            "<body onload='document.getElementById(\"input1\").focus();'>"
            "   <input type='text' id='input1' />"
            "</body></html>");

    // TODO(pvarga): Do we need this?
    page()->settings()->setFontFamily(QWebEngineSettings::SerifFont, "FooSerifFont");
    setHtml(html);
}
