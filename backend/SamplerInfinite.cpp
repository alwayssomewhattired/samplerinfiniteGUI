
#include "include/SamplerInfinite.h"
#include <qdebug.h>
#include <qlogging.h>
#include "include/FFTProcessor.h"
#include "include/AudioFileParse.h"


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

void Backend::SamplerInfinite::process(const QString& freqs, const std::vector<std::string>& filePaths, const std::map<std::string, double>& freqMap)
{
    qDebug("process :)\n");
    qDebug() << freqs << "\n";

    // frequency splitting logic in here... move to a utils at some point
    std::string freqsStr = freqs.toStdString();
    std::vector<double> parts;
    std::string::size_type start = 0;
    std::string::size_type end;

    while ((end = freqsStr.find("\n\n", start)) != std::string::npos)
    {

        std::string slicedFreq = freqsStr.substr(start, end - start);
        qDebug("Before at");
        parts.push_back(freqMap.at(slicedFreq));
        qDebug("After at");
        // this passes

        start = end + 2;
        qDebug("joe shmo");

    }
    qDebug("Arvjrifrjihrfiuht");

    std::string slicedFreq = freqsStr.substr(start);
    qDebug() << "the otehr one:" << slicedFreq;
    if (!slicedFreq.empty())
        parts.push_back(freqMap.at(slicedFreq));

    // parts is now the stringified-split version of freq as a vector
    // convert to double using map as lookup

    for (double& ffreq : parts)
    {
        qDebug() << "frequency: " << ffreq;
    }


    // 1. each song
    for (const std::string& song : filePaths)
    {

        FFTProcessor fftProcessor(config.chunkSize, config.sampleRate);

        AudioFileParse parser;

        parser.readAudioFileAsMono(song);



        // make a size member
        int n = parser.size();

        int num_chunks = (n + config.chunkSize - 1) / config.chunkSize;

        parser.applyHanningWindow();

        fftProcessor.compute(parser.getAudioData(), parts, config.productDurationSamples, false);

        const auto& chunks = fftProcessor.getMagnitudes();
        const std::vector<double>& audioCopy = parser.getAudioData();
    }
    qDebug("FINISHED!");

}









