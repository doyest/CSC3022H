
#ifndef AUDIO_H_
#define AUDIO_H_
#include <memory>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <cstdint>
#include <algorithm>
#include <numeric>
#include <vector>




	template <typename T, int Channel> class Audio
	{
		private:
		std::vector<T> info;
		int frequency;
		int SIZE;
		int MONO_STEREO;
		int fileSize;
		int BITSIZE;

		public:

			//constructor
			Audio(int sRate, int sSize): frequency(sRate), SIZE(sSize), MONO_STEREO(Channel)
			{

			}





			Audio(const Audio & other) : frequency(other.frequency), SIZE(other.SIZE), MONO_STEREO(other.MONO_STEREO), fileSize(other.fileSize), BITSIZE(other.BITSIZE)
			{
				info = other.info;
			}

			Audio(Audio && other) : frequency(other.frequency), SIZE(other.SIZE), MONO_STEREO(other.MONO_STEREO), fileSize(other.fileSize), BITSIZE(other.BITSIZE)
			{
				this->info = other.info;

			}


			Audio operator=(const Audio & other)
			{
				frequency = other.frequency;
				SIZE = other.SIZE;
				MONO_STEREO = other.MONO_STEREO;
				fileSize = other.fileSize;
				BITSIZE = other.BITSIZE;
				info = other.info;
				return *this;
			}


			Audio operator=(Audio && other)
			{
				frequency = other.frequency;
				SIZE = other.SIZE;
				MONO_STEREO = other.MONO_STEREO;
				fileSize = other.fileSize;
				BITSIZE = other.BITSIZE;
				info = other.info;



				return *this;
			}


			~Audio()=default;


			void load(std::string fileName)
			{
				using namespace std;
				ifstream input;

				input.open(fileName, ios::binary);
				if(input.is_open())
				{

					input.seekg(0,input.end);
					fileSize = (int)(input.tellg());
					input.seekg(0, input.beg);


					BITSIZE = fileSize/(this->MONO_STEREO);

					info.resize(BITSIZE);

					char * arr = new char[BITSIZE];

					input.read(arr, BITSIZE);
					for(int i = 0; i < BITSIZE; i++)
					{
						info[i] = (T)(arr[i]);
					}
					delete arr;
					input.close();
				}

			}


			void save(std::string outputName)
			{
				using namespace std;
				ofstream output(outputName, ios::binary);
				if(output.is_open())
				{
					char * arr = new char[BITSIZE];
					for(int i = 0; i < BITSIZE; ++i)
					{
						arr[i] = (char)info[i];
					}

					output.write(arr, BITSIZE);
					delete arr;
					output.close();
				}
			}



			Audio operator| (Audio & other)
		    {

				using namespace std;

				Audio SONG(this->frequency, this->SIZE);
				SONG.fileSize = this->fileSize + other.fileSize;
				SONG.BITSIZE = this->BITSIZE + other.BITSIZE;
				SONG.info.resize(SONG.BITSIZE);
				int size = this->info.size();
				int sizeRhs = other.info.size();



				for(int i = 0; i < size; i++)
				{

					SONG.info[i] = this->info[i];
				}


				for(int i = size, k=0; k < sizeRhs; i++,k++)
				{

				    SONG.info[i] = other.info[k];
				}

				return SONG;
			}
			Audio operator* (std::pair<float,float> size_fac)
			{
				using namespace std;

				Audio SONG(this->frequency, this->SIZE);
				SONG.fileSize = this->fileSize;
				SONG.BITSIZE = this->BITSIZE;
				SONG.info.resize(SONG.BITSIZE);
				int size = SONG.info.size();


				for(int i = 0; i < size; i++)
				{

					SONG.info[i] = this->info[i] * size_fac.first;
				}
				return SONG;
			}


			Audio operator+ (Audio & other)
			{
				using namespace std;

				Audio SONG(this->frequency, this->SIZE);
				SONG.fileSize = this->fileSize + other.fileSize;
				SONG.BITSIZE = this->BITSIZE;
				SONG.info.resize(SONG.BITSIZE);


				int size = this->info.size();


				for(int i = 0; i < size; i++)
				{

					SONG.info[i] = this->info[i] + other.info[i];
				}



				return SONG;
			}


			Audio operator^ (std::pair<int,int> size_fac)
			{
				using namespace std;

				Audio SONG(this->frequency, this->SIZE);
				SONG.fileSize = this->fileSize - (size_fac.second*frequency - size_fac.first*frequency);
				SONG.BITSIZE = this->BITSIZE - (size_fac.second*frequency - size_fac.first*frequency);
				SONG.info.resize(SONG.BITSIZE);
				int size = info.size();

				

				for(int i = 0; i < size_fac.first*frequency; i++)
				{

					SONG.info[i] = this->info[i];

				}

				int pos = size_fac.first*frequency;
				for(int i = size_fac.second*frequency; i < size; i++)
				{

					SONG.info[pos] = this->info[i];
					pos++;
				}
				return SONG;
			}


			Audio reverseClip ()
			{
				using namespace std;

				Audio SONG(this->frequency, this->SIZE);
				SONG.fileSize = this->fileSize;
				SONG.BITSIZE = this->BITSIZE;
				SONG.info.resize(SONG.BITSIZE);
				SONG.info = this->info;


				std::reverse(SONG.info.begin(),SONG.info.end());
				return SONG;
			}





	};





	//partial template specialization for stereo sounds
	template <typename T> class Audio<T,2>
	{
		private:
		std::vector<std::pair<T,T> > info;
		int frequency;
		int SIZE;
		int MONO_STEREO;
		int fileSize;
		int BITSIZE;

		public:

			//constructor
			Audio(int sRate, int sSize)
			{
				frequency = sRate;
				SIZE = sSize;
				MONO_STEREO = 2;
			}

			//destructor
			~Audio()
			{

			}

			//copy constructor
			Audio(const Audio & other) : frequency(other.frequency), SIZE(other.SIZE), MONO_STEREO(other.MONO_STEREO), fileSize(other.fileSize),
					BITSIZE(other.BITSIZE),info ( other.info)
			{

			}
			//move constructor
			Audio(Audio && other) : frequency(other.frequency), SIZE(other.SIZE), MONO_STEREO(other.MONO_STEREO), fileSize(other.fileSize), BITSIZE(other.BITSIZE)
			,info(std::move(other.info))
			{



			}

			//copy assignment
			Audio operator=( Audio & other)
			{
				this->frequency = other.frequency;
				this->SIZE = other.SIZE;
				this->MONO_STEREO = other.MONO_STEREO;
				this->fileSize = other.fileSize;
				this->BITSIZE = other.BITSIZE;
				this->info = other.info;
				return *this;
			}

			//move assignment
			Audio operator=( Audio&& other)
			{
				this->frequency = other.frequency;
				this->SIZE = other.SIZE;
				this->MONO_STEREO = other.MONO_STEREO;
				this->fileSize = other.fileSize;
				this->BITSIZE = other.BITSIZE;
				this->info = other.info;


				return *this;
			}

			//reads raw file and stores it into image object
			void load(std::string fileName)
			{
				using namespace std;
				ifstream input;
				//read a binary file
				input.open(fileName, ios::binary);
				if(input.is_open())
				{
					//get file size
					input.seekg(0,input.end);
					fileSize = (int)(input.tellg());
					input.seekg(0, input.beg);

					//size of vector
					BITSIZE = fileSize/MONO_STEREO;

					//16bit
					if(SIZE == 16)
					{
						BITSIZE*=2;
					}

					info.resize(BITSIZE);

					char * arr = new char[BITSIZE*2];
					//read binary info block
					input.read(arr, BITSIZE*2);
					int pos = 0;
					for(int i = 0; i < BITSIZE; i++)
					{
						pair<T, T> p;
						p.first = arr[pos];
						pos++;
						p.second = arr[pos];
						pos++;
						info[i] = p;
					}
					delete arr;
					input.close();
				}

			}

			//save file
			void save(std::string outputName)
			{
				using namespace std;
				ofstream output(outputName, ios::binary);
				if(output.is_open())
				{
					char * arr = new char[BITSIZE*2];
					int pos = 0;
					for(int i = 0; i < this->info.size(); i++)
					{
						//store pair values for left and right
						arr[pos] = this->info[i].first;
						pos++;
						arr[pos] = this->info[i].second;
						pos++;
					}

					if(SIZE == 8)
					{
						output.write(arr, BITSIZE*2);
					}

					else
					{
						output.write(arr, BITSIZE);
					}

					delete arr;
					output.close();
				}
			}


			Audio operator| (Audio & other)
			{

				using namespace std;
				//AudioClip -> new object. copy attributes
				Audio SONG(this->frequency, this->SIZE);
				SONG.fileSize = this->fileSize + other.fileSize;
				SONG.BITSIZE = this->BITSIZE + other.BITSIZE;


				SONG.info.resize(SONG.BITSIZE);
				int size = this->info.size();
				int sizeRhs = other.info.size();


				if(SIZE == 16)
				{
					size /= 2;
					sizeRhs /= 2;
				}


				for(int i = 0; i < size; i++)
				{

					SONG.info[i] = this->info[i];
				}


				for(int i = size, k=0; k < sizeRhs; i++,k++)
				{

					SONG.info[i] = other.info[k];
				}

				return SONG;
			}



			Audio operator* (std::pair<float,float> size_fac)
			{
				using namespace std;

				Audio SONG(this->frequency, this->SIZE);
				SONG.fileSize = this->fileSize;
				SONG.BITSIZE = this->BITSIZE;
				SONG.info.resize(SONG.BITSIZE);
				int size = SONG.info.size();


				for(int i = 0; i < size; i++)
				{


					SONG.info[i].first = this->info[i].first * size_fac.first;

					SONG.info[i].second = this->info[i].second * size_fac.second;
				}
				return SONG;
			}


			Audio operator+ (Audio & other)
			{
				using namespace std;

				Audio SONG(this->frequency, this->SIZE);
				SONG.fileSize = this->fileSize + other.fileSize;
				SONG.BITSIZE = this->BITSIZE;
				SONG.info.resize(SONG.BITSIZE);


				int size = this->info.size();


				for(int i = 0; i < size; i++)
				{

					SONG.info[i].first = this->info[i].first + other.info[i].first;
					SONG.info[i].second = this->info[i].second + other.info[i].second;
				}



				return SONG;
			}


			Audio operator^ (std::pair<int,int> size_fac)
			{
				using namespace std;
				Audio SONG(this->frequency, this->SIZE);
				SONG.fileSize = this->fileSize - (size_fac.second*frequency - size_fac.first*frequency);
				SONG.BITSIZE = this->BITSIZE - (size_fac.second*frequency - size_fac.first*frequency);
				SONG.info.resize(SONG.BITSIZE);
				int size = info.size();


				for(int i = 0; i < size_fac.first*frequency; i++)
				{

					SONG.info[i] = this->info[i];

				}

				int pos = size_fac.first*frequency;
				for(int i = size_fac.second*frequency; i < size; i++)
				{

					SONG.info[pos] = this->info[i];
					pos++;
				}
				return SONG;
			}


			Audio reverseClip ()
			{
				using namespace std;

				Audio SONG(this->frequency, this->SIZE);
				SONG.fileSize = this->fileSize;
				SONG.BITSIZE = this->BITSIZE;
				SONG.info.resize(SONG.BITSIZE);
				SONG.info = this->info;


				std::reverse(SONG.info.begin(),SONG.info.end());
				return SONG;
			}






	};




#endif /* AUDIO_H_ */
