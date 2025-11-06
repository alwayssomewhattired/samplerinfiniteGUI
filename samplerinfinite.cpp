#include "samplerinfinite.h"
#include "./ui_samplerinfinite.h"
#include "audiodropwidget.h"

SamplerInfinite::SamplerInfinite(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SamplerInfinite)
{
    ui->setupUi(this);

    auto *dropWidget = ui->widget;

    connect(dropWidget, &AudioDropWidget::audioDropped, this, [&](const QString &filePath){
        qDebug() << "file dropped: " << filePath;
    });

}

SamplerInfinite::~SamplerInfinite()
{
    delete ui;
}
