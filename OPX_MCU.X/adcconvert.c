//
// File   : adcconvert.c
// Author : YSW
// Created on 2016.06.09
//
// Brief : adc convert 
// Detail : adc <-> temperature
//

#include "adcconvert.h"
#include "def_var.h"

#define TEMP_MINIMUM 46

/* Define  --------------------------------------------------------------*/
typedef struct 
{
	U16 raw; // adc raw value
	U16 temp;// temperature C
} T_adc_convert;

/* Define variable  -----------------------------------------------------*/

static T_adc_convert temp_table_micom[]=
{
	{166,473},
	// fake start
	{179,490},
	{192,510},	
	{205,530},
	{218,540},	
	// fake	end
	{226,558},
	{231,568},
	// fake start
	{245,580},
	{258,600},	
	{271,620},
	{284,640},
	{297,660},
	// fake end
	{322,675},
	{326,679},
	{329,681},
	{338,690},
	// fake start
	{362,710},
	{374,720},
	{398,740},
	{422,760},
	{446,780},
	{470,800},
	{494,820},
	{518,840},
	{532,860},
	{556,880},	
	// fake end	
	{566,893},
	{576,902},
	{597,920},
	{610,930},
	{634,950},
	{657,970},
	{681,990},
	{693,1000},
	{733,1030},
	{766,1069},
	{789,1077},
	{806,1090},
	{820,1102},
	{833,1110},
	{868,1140},
	{891,1160},
	{928,1188},
	{930,1191},
    {4095,2000},// max	
};

U16 mcu_adcvalue_to_temp(U16 adcvalue)
{
	U16 i;
	U16 result = TEMP_MINIMUM;
	U16 raw_count = sizeof(temp_table_micom) / sizeof(T_adc_convert);
	// check 24 voltage (micom refer)


	// select base table
	

	// matching adc value to temp(int)

	for(i=0; i < raw_count; i++)
	{
		if ( adcvalue >= temp_table_micom[i].raw && 
					adcvalue < temp_table_micom[i+1].raw )
		{
					result =  temp_table_micom[i].temp / 10;
					break;
		}
	}

	return result;	
}

U16 mcu_temp_to_adcvalue(U16 temp)
{
    U16 i;
    U16 result = 0;
    U16 raw_count = sizeof(temp_table_micom) / sizeof(T_adc_convert);
    
    for(i=0; i < raw_count; i++)
	{
		if ( temp >= (temp_table_micom[i].temp / 10) && 
					temp < (temp_table_micom[i+1].temp / 10) )
		{
					result =  temp_table_micom[i].raw;
					break;
		}
	}
    
    return result;
}