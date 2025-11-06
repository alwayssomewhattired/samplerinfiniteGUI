#ifndef AUDIODROPWIDGET_H
#define AUDIODROPWIDGET_H

#include <QWidget>
#include <QString>
#include <QUrl>

class AudioDropWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AudioDropWidget(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event) override;

signals:
    void audioDropped(const QString &filePath);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;
};

#endif // AUDIODROPWIDGET_H
