#include "cs5532.h"

int main(int argc, char *argv[]) {
	int word_rate = WORD_RATE_6P25SPS;
	if (argc == 2){
		int input = atoi(argv[1]);
		switch (input)
		{
		case 1: word_rate = WORD_RATE_6P25SPS;break;
		case 2: word_rate = WORD_RATE_200SPS;break;
		}
	}

	printf("The word rate of calibration is %d.\n", (word_rate == WORD_RATE_6P25SPS ? 75:240));
	cs5532_init();
	cs5532_reset();
	calibrate(SELF_OFFSET, VRS, ((word_rate) << 16) );
	calibrate(SELF_GAIN, VRS, ((word_rate) << 16) );
	return 1;
}
