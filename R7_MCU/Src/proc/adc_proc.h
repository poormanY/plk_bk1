#ifndef	_ADC_PROC_H_
#define	_ADC_PROC_H_

#include "..//define.h"

#define	MAX_B_PLUS_TABLE_INDEX		161
#define	MAX_TEMPER_TABLE_INDEX		28

enum ADC_ID 
{ 
	ADC_ID_NONE = 0x00, 
	ADC_ID_B_PLUS, 		// AN1
	ADC_ID_IG,          // AN2
	ADC_ID_TEMP, 		// AN3
	ADC_ID_TURN_R = 0x09,	// AN9
	ADC_ID_TURN_L = 0x0B,	// AN11
	ADC_ID_MAX 
};

typedef	struct 
{
	U16	b_plus;
	U16	ig;
	U16	temp;
	U16	turn_l;
	U16	turn_r;
}ADC_INFO;

enum ADC_ID2
{
    ADC_ID_TURN_LEFT = 0x00,
    ADC_ID_TURN_RIGHT,
    ADC_ID_IG_CHK_MCU,
    ADC_ID_REAR_LAMP,
    ADC_ID_WIPER_IN = 0x09,
    ADC_ID_BRAKE = 0x14,
	ADC_ID_MAX2
};

//#define	 MCU_VDD_5V_THERMISTOR_VDD_5V
#define	 MCU_VDD_3_3V_THERMISTOR_VDD_5V

#if defined(MCU_VDD_5V_THERMISTOR_VDD_5V)
U16 g_temperature_table[MAX_TEMPER_TABLE_INDEX] =
{
	0x165, 0x1AF, 0x200, 0x256, 0x2AE,
	0x307, 0x35C, 0x3AE, 0x3FA, 0x43F,
	0x47E, 0x4B6, 0x4E6, 0x510, 0x535,
	0x553, 0x56E, 0x585, 0x597, 0x5A8,
	0x5B6, 0x5C2, 0x5CC, 0x5D5,
};
#elif defined(MCU_VDD_3_3V_THERMISTOR_VDD_5V)
U16 g_temperature_table[MAX_TEMPER_TABLE_INDEX] =
{
	26,  33,  42,  53,  66, 	// 0  ~ 20
	82,  101, 124, 150, 181, 	// 25 ~ 45
	215, 254, 298, 345, 396, 	// 50 ~ 70
	451, 508, 567, 627, 688, 	// 75 ~ 95
	748, 807, 865, 921, 975 	// 100 ~ 120
};
#endif

U16 g_bplus_volt_table[MAX_B_PLUS_TABLE_INDEX] = 
{
	330, 333, 337, 340, 344, 347, 351, 354, 358, 361,	// 10V ~ 10.9V
	365, 368, 372, 375, 379, 382, 386, 389, 393, 396,	// 11V ~ 11.9V
	400, 403, 407, 410, 414, 417, 421, 424, 428, 431, 	// 12V ~ 12.9V
	435, 439, 443, 447, 451, 455, 459, 463, 467, 471,	// 13V ~ 13.9V
	475, 479, 483, 487, 491, 495, 499, 503, 507, 511,	// 14V ~ 14.9V
	515, 518, 522, 525, 529, 532, 536, 539, 543, 546,	// 15V ~ 15.9V
	550, 553, 557, 560, 564, 567, 571, 575, 578, 582,	// 16V ~ 16.9V
	585, 588, 592, 595, 599, 602, 606, 609, 613, 616,	// 17V ~ 17.9V
	620, 623, 627, 630, 634, 637, 641, 644, 648, 651,	// 18V ~ 18.9V
	655, 658, 662, 665, 669, 672, 676, 679, 683, 686,	// 19V ~ 19.9V
	690, 693, 697, 700, 704, 707, 711, 714, 718, 721,	// 20V ~ 20.9V
	725, 728, 732, 735, 739, 742, 746, 749, 753, 756, 	// 21V ~ 21.9V
	760, 763, 767, 770, 774, 777, 781, 784, 788, 791,	// 22V ~ 22.9V
	795, 799, 803, 807, 811, 815, 819, 823, 827, 831,	// 23V ~ 23.9V
	835, 838, 842, 845, 849, 852, 856, 859, 863, 866,	// 24V ~ 24.9V
	870, 874, 878, 882, 886, 890, 894, 898, 902, 906,	// 25V ~ 25.9V
	910													// 26V
};	

void		adc_proc_init(void);
void 		adc_proc(void);
void        adc_proc2(void);
ADC_INFO	adc_proc_get_info(void);


#endif