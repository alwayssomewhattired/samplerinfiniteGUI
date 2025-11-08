#pragma once
#include <QList>
#include <map>

namespace Backend {
	class SamplerInfinite
	{
	public:
        SamplerInfinite();
		~SamplerInfinite();

        void process(const QString& freqs, const std::vector<std::string>& filePaths, const std::map<std::string, double>& freqMap);

	private:
		struct Config {
			int chunkSize;
			int sampleRate;
			int channels;
			int productDurationSamples;
		};

		Config config;
	};
}
