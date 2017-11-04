#include <thread>

#include "Wav.h"

int main(){
	Wav wav("BalloonPop01.wav");

	// wav.Load("BalloonPop01.wav");

	printf("Play\n");
	wav.WavToBuffer();
	wav.Play();

	// create wav from data
	{
		unsigned char *data;

		int length_data;
		int nChannels;
		int nSamplesPerSec;
		int wBitsPerSample;

		wav.Get_Properties(&nChannels, &nSamplesPerSec, &wBitsPerSample);
		printf("\nnChannels: %d\nnSamplesPerSec: %d\nwBitsPerSample: %d\n", nChannels, nSamplesPerSec, wBitsPerSample);

		data = new unsigned char[length_data = wav.length_wav];

		for (int i = 0; i < wav.length_wav; i++){
			data[i] = wav.data[i];
		}

		Wav new_wav(nChannels, nSamplesPerSec, wBitsPerSample);

		// new_wav.Set_Properties(nChannels, nSamplesPerSec, wBitsPerSample);

		new_wav.Create(data, length_data);
		new_wav.WavToBuffer();
		new_wav.Play();
		new_wav.Save("BalloonPop02.wav");

		delete[] data;
	}

	printf("\nRecord\n");
	wav.Record(2000);

	printf("Play\n");
	wav.Play();

	wav.BufferToWav();
	wav.Save("record.wav");


	printf("\nRecord\n");
	std::thread thread = wav.Record_Thread(2000);
	thread.detach();

	printf("Interrupt\n");
	wav.recording = false;

	return 0;
}