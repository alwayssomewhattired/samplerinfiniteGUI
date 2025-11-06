#include "samplerinfinite.h"
#include "./ui_samplerinfinite.h"
#include "audiodropwidget.h"
#include <QScrollBar>


SamplerInfinite::SamplerInfinite(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SamplerInfinite)
{
    ui->setupUi(this);
    this->showMaximized();

    ui->fileBrowser->setReadOnly(true);
    ui->fileBrowser->setFrameShape(QFrame::NoFrame);


    auto *dropWidget = ui->widget;

    connect(dropWidget, &AudioDropWidget::audioDropped, this, [&](const QString &filePath){
        qDebug() << "file dropped: " << filePath;

        QTextCharFormat format;
        format.setForeground(Qt::green);

        QTextCursor cursor(ui->fileBrowser->textCursor());
        cursor.movePosition(QTextCursor::End);
        cursor.insertText(filePath + "\n" + "\n", format);

        ui->fileBrowser->verticalScrollBar()->setValue(ui->fileBrowser->verticalScrollBar()->maximum());
    });


}

SamplerInfinite::~SamplerInfinite()
{
    delete ui;
}
