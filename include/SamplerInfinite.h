#pragma once

namespace Backend {
	class SamplerInfinite
	{
	public:
		SamplerInfinite();
		~SamplerInfinite();

        void process();

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
