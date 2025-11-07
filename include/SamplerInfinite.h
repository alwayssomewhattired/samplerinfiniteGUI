#pragma once
#include <QList>

namespace Backend {
	class SamplerInfinite
	{
	public:
        SamplerInfinite();
		~SamplerInfinite();

        void process(const QString& freqs);

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
