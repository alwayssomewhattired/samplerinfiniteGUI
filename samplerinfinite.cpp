#include "samplerinfinite.h"
#include "./ui_samplerinfinite.h"
#include "audiodropwidget.h"
#include <QScrollBar>
#include "include/SamplerInfinite.h"


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

    auto *freqDisplayWidget = ui->freqDisplay;
    auto *searchableComboBox = ui->searchablecombobox;

    connect(searchableComboBox, &SearchableComboBox::itemSelected, this, [this, freqDisplayWidget](const QString &text){
        freqDisplayWidget->setReadOnly(true);


        QTextCharFormat format;
        format.setForeground(Qt::green);

        QTextCursor cursor(freqDisplayWidget->textCursor());
        cursor.movePosition(QTextCursor::End);
        cursor.insertText(text + "\n" + "\n", format);

        freqDisplayWidget->verticalScrollBar()->setValue(freqDisplayWidget->verticalScrollBar()->maximum());
    });

    auto *startButton = ui->startButton;

    connect(startButton, &QPushButton::clicked, this, [this, freqDisplayWidget](){
        // pass frequencies as std::vector<double>
        // const QList<double>& freqs = m_frequencies.getterFreqs();
        m_backend.process(freqDisplayWidget->toPlainText());
    });

}

SamplerInfinite::~SamplerInfinite()
{
    delete ui;
}
