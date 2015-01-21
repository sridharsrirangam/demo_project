#include <MKL25Z4s.H> //modified name for the MKL25Z4 header file.."s" was added to indicate the changed version

void Delay (uint32_t dly) {
  volatile uint32_t t;

	for (t=dly*10000; t>0; t--)
		;
}
