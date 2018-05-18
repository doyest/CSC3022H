/*
 * driver.cpp
 *
 *  Created on: May 10, 2018
 *      Author: OFENTSE TSHEPE
 */

#include "Audio.h"
#include <iostream>
#include <sstream>
#include <cstdint>

int main(int argc, char *argv[])
{
	using namespace std;



	//variables representing command line input
	int sampleRate;
	int bitCount;
	int noChannels;
	string outputName = "out.raw";
	string option;
	string inputName1;
	string inputName2;

	stringstream ss;

	ss << argv[2];
	ss >> sampleRate;
	ss.clear();


	ss << argv[4];
	ss >> bitCount;
	ss.clear();


	ss << argv[6];
	ss >> noChannels;
	ss.clear();

	string outputOption;
	ss << argv[7];
	ss >> outputOption;
	ss.clear();
	int argPosition;
	if(outputOption == "-o")
	{

		ss << argv[8];
		ss >> outputName;
		ss.clear();
		argPosition = 9;
	}

	else
	{
		argPosition = 7;
	}

	ss << argv[argPosition];
	ss >> option;
	ss.clear();
	argPosition++;


	if(option == "-add")
	{

		ss << argv[argPosition];
		ss >> inputName1;
		ss.clear();
		argPosition++;


		ss << argv[argPosition];
		ss >> inputName2;
		ss.clear();
		argPosition++;


		if(bitCount == 8)
		{

			if(noChannels == 1)
			{
				Audio<int8_t,1> audioClip1(sampleRate,8);
				Audio<int8_t,1> audioClip2(sampleRate,8);
				audioClip1.load(inputName1);
				audioClip2.load(inputName2);


				Audio<int8_t,1> audioClip3(sampleRate,8);
				audioClip3 = audioClip1 + audioClip2;
				audioClip3.save(outputName);

			}


			if(noChannels == 2)
			{
				Audio<int8_t,2> audioClip1(sampleRate,8);
				Audio<int8_t,2> audioClip2(sampleRate,8);
				audioClip1.load(inputName1);
				audioClip2.load(inputName2);

				//add 2 audio files together
				Audio<int8_t,2> audioClip3(sampleRate,8);
				audioClip3 = audioClip1 + audioClip2;
				audioClip3.save(outputName);
			}

		}

		//16 bit sounds
		else if(bitCount == 16)
		{
			//mono sounds
			if(noChannels == 1)
			{
				Audio<int16_t,1> audioClip1(sampleRate,16);
				Audio<int16_t,1> audioClip2(sampleRate,16);
				audioClip1.load(inputName1);
				audioClip2.load(inputName2);

				//add 2 audio files together
				Audio<int16_t,1> audioClip3(sampleRate,16);
				audioClip3 = audioClip1 + audioClip2;
				audioClip3.save(outputName);
			}

			//stereo sounds
			if(noChannels == 2)
			{
				Audio<int16_t,2> audioClip1(sampleRate,16);
				Audio<int16_t,2> audioClip2(sampleRate,16);
				audioClip1.load(inputName1);
				audioClip2.load(inputName2);


				Audio<int16_t,2> audioClip3(sampleRate,16);
				audioClip3 = audioClip1 + audioClip2;
				audioClip3.save(outputName);
			}
		}
	}


	if(option == "-cut")
	{
		int r1;
		int r2;

		ss << argv[argPosition];
		ss >> r1;
		ss.clear();
		argPosition++;


		ss << argv[argPosition];
		ss >> r2;
		ss.clear();
		argPosition++;

		ss << argv[argPosition];
		ss >> inputName1;
		ss.clear();
		argPosition++;


		pair<int, int> factor;
		factor.first = r1;
		factor.second = r2;


		if(bitCount == 8)
		{
			if(noChannels == 1)
			{
				Audio<int8_t,1> audioClip1(sampleRate,8);
				audioClip1.load(inputName1);


				Audio<int8_t,1> audioClip3(sampleRate,8);
				audioClip3 = audioClip1 ^ factor;
				audioClip3.save(outputName);

			}


			if(noChannels == 2)
			{
				Audio<int8_t,2> audioClip1(sampleRate,8);
				audioClip1.load(inputName1);


				Audio<int8_t,2> audioClip3(sampleRate,8);
				audioClip3 = audioClip1 ^ factor;
				audioClip3.save(outputName);
			}

		}

		else if(bitCount == 16)
		{

			if(noChannels == 1)
			{
				Audio<int16_t,1> audioClip1(sampleRate,16);
				audioClip1.load(inputName1);


				Audio<int16_t,1> audioClip3(sampleRate,16);
				audioClip3 = audioClip1 ^ factor;
				audioClip3.save(outputName);
			}


			if(noChannels == 2)
			{
				Audio<int16_t,2> audioClip1(sampleRate,16);
				audioClip1.load(inputName1);


				Audio<int16_t,2> audioClip3(sampleRate,16);
				audioClip3 = audioClip1 ^ factor;
				audioClip3.save(outputName);
			}
		}
	}

	if(option == "-radd")
	{

		ss << argv[argPosition];
		ss >> inputName1;
		ss.clear();
	}


	if(option == "-cat")
	{
		

		ss << argv[argPosition];
		ss >> inputName1;
		ss.clear();
		argPosition++;
		ss << argv[argPosition];
		ss >> inputName2;
		ss.clear();


		if(bitCount == 8)
		{
			

			if(noChannels == 1)
			{
				
				Audio<int8_t,1> audioClip1(sampleRate,8);
				Audio<int8_t,1> audioClip2(sampleRate,8);
				audioClip1.load(inputName1);
				audioClip2.load(inputName2);


				Audio<int8_t,1> audioClip3(sampleRate,8);
				audioClip3 = audioClip1 | audioClip2;
				audioClip3.save(outputName);

			}


			if(noChannels == 2)
			{
				
				Audio<int8_t,2> audioClip1(sampleRate,8);
				Audio<int8_t,2> audioClip2(sampleRate,8);
				audioClip1.load(inputName1);
				audioClip2.load(inputName2);


				Audio<int8_t,2> audioClip3(sampleRate,8);
				audioClip3 = audioClip1 | audioClip2;
				audioClip3.save(outputName);
			}

		}

		else if(bitCount == 16)
		{

			if(noChannels == 1)
			{
				Audio<int16_t,1> audioClip1(sampleRate,16);
				Audio<int16_t,1> audioClip2(sampleRate,16);
				audioClip1.load(inputName1);
				audioClip2.load(inputName2);


				Audio<int16_t,1> audioClip3(sampleRate,16);
				audioClip3 = audioClip1 | audioClip2;
				audioClip3.save(outputName);
			}


			if(noChannels == 2)
			{
				Audio<int16_t,2> audioClip1(sampleRate,16);
				Audio<int16_t,2> audioClip2(sampleRate,16);
				audioClip1.load(inputName1);
				audioClip2.load(inputName2);


				Audio<int16_t,2> audioClip3(sampleRate,16);
				audioClip3 = audioClip1 | audioClip2;
				audioClip3.save(outputName);
			}
		}
	}


	if(option == "-v")
	{
		float r1;
		float r2;

		ss << argv[argPosition];
		ss >> r1;
		ss.clear();
		argPosition++;

		ss << argv[argPosition];
		ss >> r2;
		ss.clear();
		argPosition++;


		ss << argv[argPosition];
		ss >> inputName1;
		ss.clear();
		argPosition++;


		pair<float, float> factor;
		factor.first = r1;
		factor.second = r2;
		if(bitCount == 8)
		{

			if(noChannels == 1)
			{
				Audio<int8_t,1> audioClip1(sampleRate,8);
				audioClip1.load(inputName1);

				Audio<int8_t,1> audioClip3(sampleRate,8);
				audioClip3 = audioClip1 * factor;
				audioClip3.save(outputName);

			}


			if(noChannels == 2)
			{
				Audio<int8_t,2> audioClip1(sampleRate,8);
				audioClip1.load(inputName1);


				Audio<int8_t,2> audioClip3(sampleRate,8);
				audioClip3 = audioClip1 * factor;
				audioClip3.save(outputName);
			}

		}


		else if(bitCount == 16)
		{
			if(noChannels == 1)
			{
				Audio<int16_t,1> audioClip1(sampleRate,16);
				audioClip1.load(inputName1);


				Audio<int16_t,1> audioClip3(sampleRate,16);
				audioClip3 = audioClip1 * factor;
				audioClip3.save(outputName);

			if(noChannels == 2)
			{
				Audio<int16_t,2> audioClip1(sampleRate,16);
				audioClip1.load(inputName1);


				Audio<int16_t,2> audioClip3(sampleRate,16);
				audioClip3 = audioClip1 * factor;
				audioClip3.save(outputName);
			}
		}
	}


	if(option == "-rev")
	{
		//input file 1
		ss << argv[argPosition];
		ss >> inputName1;
		ss.clear();
		argPosition++;




		if(bitCount == 8)

			if(noChannels == 1)
			{
				Audio<int8_t,1> audioClip1(sampleRate,8);
				audioClip1.load(inputName1);


				Audio<int8_t,1> audioClip3(sampleRate,8);
				audioClip3 = audioClip1.reverseClip();
				audioClip3.save(outputName);

			}


			if(noChannels == 2)
			{
				Audio<int8_t,2> audioClip1(sampleRate,8);
				audioClip1.load(inputName1);


				Audio<int8_t,2> audioClip3(sampleRate,8);
				audioClip3 = audioClip1.reverseClip();
				audioClip3.save(outputName);
			}

		}


		else if(bitCount == 16)
		{

			if(noChannels == 1)
			{
				Audio<int16_t,1> audioClip1(sampleRate,16);
				audioClip1.load(inputName1);


				Audio<int16_t,1> audioClip3(sampleRate,16);
				audioClip3 = audioClip1.reverseClip();
				audioClip3.save(outputName);
			}


			if(noChannels == 2)
			{
				Audio<int16_t,2> audioClip1(sampleRate,16);
				audioClip1.load(inputName1);


				Audio<int16_t,2> audioClip3(sampleRate,16);
				audioClip3 = audioClip1.reverseClip();
				audioClip3.save(outputName);
			}
		}
	}

	if(option == "-rms")
	{

	}

	if(option == "-norm")
	{
		//input file 2
		ss << argv[argPosition];
		ss >> inputName1;
		ss.clear();
	}



}



