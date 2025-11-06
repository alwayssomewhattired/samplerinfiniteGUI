#ifndef SAMPLERINFINITE_H
#define SAMPLERINFINITE_H

#include <QMainWindow>
#include <QList>
#include "frequencies.h"


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
    Frequencies freqs;

};
#endif // SAMPLERINFINITE_H
