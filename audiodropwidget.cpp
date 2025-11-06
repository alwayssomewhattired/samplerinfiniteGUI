#include "audiodropwidget.h"
#include <QDropEvent>
#include <QMimeData>
#include <QDebug>
#include <QPainter>
#include <QPaintEvent>

AudioDropWidget::AudioDropWidget(QWidget *parent) : QWidget(parent)
{
    setAcceptDrops(true);
    qDebug() << "AudioDropWidget constructed!";
    setAutoFillBackground(true);
    setAttribute(Qt::WA_StyledBackground, true); // make stylesheets apply
    setStyleSheet("background-color: rgba(255, 0, 255, 100); border: 2px dashed magenta;");
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

void AudioDropWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter p(this);
    p.fillRect(rect(), QColor(255, 0, 255, 50)); // faint magenta overlay
    p.setPen(QPen(Qt::magenta, 3, Qt::DashLine));
    p.drawRect(rect().adjusted(1, 1, -1, -1));
}
