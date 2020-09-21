#include "AudioFile.hpp"
#include <iostream>
#include "rubberband/RubberBandStretcher.h"

// Credits for WAV File Management: https://github.com/adamstark/AudioFile

int main(int argc, char ** argv) {
	(void) argc;
	(void) argv;

	AudioFile<float> audioFile;
	audioFile.load("test.wav");
	audioFile.printSummary();


	std::cout << "Creating stretcher..." << std::endl;
	RubberBand::RubberBandStretcher::Options options = 0;
	RubberBand::RubberBandStretcher stretcher(audioFile.getSampleRate(), audioFile.getNumChannels(), options);
	stretcher.setTimeRatio(2);
	std::cout << "Created" << std::endl;

	std::vector<float> * test = audioFile.samples.data();
	std::vector<float*> dummyVector;

	for (int i = 0; i < audioFile.getNumChannels(); i++) {
		dummyVector.push_back(audioFile.samples[i].data());
	}

	float * * sampleArray = dummyVector.data();
	std::cout << "Converted into float**" << std::endl;

	stretcher.study(sampleArray, (unsigned long int) audioFile.getNumSamplesPerChannel(), (bool) true);
	std::cout << "Samples now required: " << stretcher.getSamplesRequired() << std::endl;
	stretcher.process(sampleArray, (unsigned long int) audioFile.getNumSamplesPerChannel(), (bool) true);
	std::cout << "Samples required after: " << stretcher.getSamplesRequired() << "; available: " << stretcher.available() << std::endl;

	audioFile.setAudioBufferSize(audioFile.getNumChannels(), stretcher.available());

	test = audioFile.samples.data();
	dummyVector.clear();

	for (int i = 0; i < audioFile.getNumChannels(); i++) {
		dummyVector.push_back(audioFile.samples[i].data());
	}

	sampleArray = dummyVector.data();
	stretcher.retrieve(sampleArray, stretcher.available());
	audioFile.save("test_out.wav", AudioFileFormat::Wave);

	return 0;
}
