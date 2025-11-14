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
                     const bool& isAppend, const bool& isInterpolate);

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

        double m_freqStrength;
        std::string m_outputDirectory;
	};
}
