#include "audiodropwidget.h"
#include <QDropEvent>
#include <QMimeData>
#include <QDebug>
#include <QLabel>
#include <QVBoxLayout>

AudioDropWidget::AudioDropWidget(QWidget *parent) : QWidget(parent)
{
    setAcceptDrops(true);
    setAttribute(Qt::WA_StyledBackground, true); // make stylesheets apply

    auto *layout = new QVBoxLayout(this);
    QLabel *label = new QLabel("Drop your audio file here", this);
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);
    setLayout(layout);
    }

void AudioDropWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls())
    {
        for (const QUrl &url : event->mimeData()->urls())
        {
            if (url.toLocalFile().endsWith(".mp3") ||
                url.toLocalFile().endsWith(".wav") ||
                url.toLocalFile().endsWith(".flac"))
            {
                event->acceptProposedAction();
                return;
            }
        }
    }
    event->ignore();
}

void AudioDropWidget::dropEvent(QDropEvent *event)
{
    for (const QUrl &url : event->mimeData()->urls())
    {
        QString filePath = url.toLocalFile();
        qDebug() << "file: " << filePath;
        emit audioDropped(filePath);
    }
}
