
#include "include/SamplerInfinite.h"
#include "include/FFTProcessor.h"
#include "include/AudioFileParse.h"
#include <qdebug.h>
#include <qlogging.h>
#include <string>
#include <filesystem>
#include <regex>


Backend::SamplerInfinite::SamplerInfinite()
:     config{
          8192,       // chunkSize
          44100,      // sampleRate
          1,          // channels
          0           // productDurationSamples
      }

{

};

Backend::SamplerInfinite::~SamplerInfinite(){};

void Backend::SamplerInfinite::process(const QString& freqs, const std::vector<std::string>& filePaths, const std::map<std::string, double>& freqMap,
    const std::map<double, std::string>& freqToNote, const bool& isAppend)
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
        parts.push_back(freqMap.at(slicedFreq));

        start = end + 2;

    }
    qDebug("Arvjrifrjihrfiuht");

    std::string slicedFreq = freqsStr.substr(start);
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

        std::filesystem::path p(song);
        auto songName = p.stem().string();

        if (isAppend)
            songName = "appendage";

        FFTProcessor fftProcessor(config.chunkSize, config.sampleRate, m_freqStrength);

        AudioFileParse parser;

        parser.readAudioFileAsMono(song);

        int n = parser.size();

        int num_chunks = (n + config.chunkSize - 1) / config.chunkSize;

        // this window is pointless vvv possibly make a control for it... possibly eat mushroom and think
        // parser.applyHanningWindow();

        fftProcessor.compute(parser.getAudioData(), parts, config.productDurationSamples, false);

        // wtf do i do with you??? vvv
        const auto& chunks = fftProcessor.getMagnitudes();

        // wtf do i do with you??? vvv
        const std::vector<double>& audioCopy = parser.getAudioData();

        int i = 0;
        for (auto& [k, v] : fftProcessor.getSampleStorage()) {
            // this inner loop is terrible. could easily mismatch frequency to samples vvv
            std::filesystem::path dirPath = m_outputDirectory + '/' + freqToNote.at(parts[i]);
            std::filesystem::create_directory(dirPath);
            // make a control that chooses an existing audio file to append new audio to
            // for now, make the choice automatically the 'appendage'.wav
            std::string finalProductName = m_outputDirectory + '/' + freqToNote.at(parts[i]) + "/" + songName + freqToNote.at(parts[i]) + ".wav";
            if (isAppend)
                parser.appendWavFile(v, finalProductName);
            else
                parser.writeWavFile(v, finalProductName);
            i++;
        }
    }

    qDebug("FINISHED!");

}

void Backend::SamplerInfinite::setFreqStrength(double freqStrength) {m_freqStrength = freqStrength;}

void Backend::SamplerInfinite::setOutputDirectory(std::string outputDirectory) {m_outputDirectory = outputDirectory;}








