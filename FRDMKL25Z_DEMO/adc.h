#ifndef ADC_H
#define ADC_H
#define VBG_VALUE (1.00)

#ifdef __cplusplus
  extern "C" {
#endif

void Init_ADC(void);
float Measure_VRail(void);
extern unsigned res;
		
#ifdef __cplusplus
	}
	#endif
#endif	