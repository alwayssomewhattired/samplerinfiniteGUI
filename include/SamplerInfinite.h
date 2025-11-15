#pragma once
#include <QList>
#include <map>

namespace Backend {
	class SamplerInfinite
	{
	public:
        SamplerInfinite();
		~SamplerInfinite();

        void process(const QString& freqs, const std::vector<std::string>& filePaths, const std::map<std::string, double>& freqMap,
            const std::map<double, std::string>& freqToNote, const std::map<int, std::string>& i_freqToNote,
                     const bool& isAppend, const bool& isInterpolate, const int& crossfadeSamples);

        void setFreqStrength(double freqStrength);

        void setOutputDirectory(std::string outputDirectory);

	private:
		struct Config {
			int chunkSize;
			int sampleRate;
			int channels;
			int productDurationSamples;
		};
		Config config;

        double m_freqStrength{1.0};
        std::string m_outputDirectory;
	};
}
