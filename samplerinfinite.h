#ifndef SAMPLERINFINITE_H
#define SAMPLERINFINITE_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui {
class SamplerInfinite;
}
QT_END_NAMESPACE

class SamplerInfinite : public QMainWindow
{
    Q_OBJECT

public:
    SamplerInfinite(QWidget *parent = nullptr);
    ~SamplerInfinite();

private:
    Ui::SamplerInfinite *ui;
};
#endif // SAMPLERINFINITE_H
