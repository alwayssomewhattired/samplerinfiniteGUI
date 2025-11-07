
#include "include/SamplerInfinite.h"
#include <qdebug.h>
#include <qlogging.h>


Backend::SamplerInfinite::SamplerInfinite()
:     config{
          8192,       // chunkSize
          44100,      // sampleRate
          1,          // channels
          0           // productDurationSamples
      }

{
    qDebug("oh yeah ! ! !\n");


};

Backend::SamplerInfinite::~SamplerInfinite(){};

void Backend::SamplerInfinite::process(const QString& freqs)
{
    qDebug("process :)\n");
    qDebug() << freqs << "\n";
}
