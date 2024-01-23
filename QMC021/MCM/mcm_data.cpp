#include "mcm_data.h"

#define  MCMDATA_EXPORT_ATTRIBUTE(var)   { sizeof(var), &var }

MCM_Data::MCM_Data()
{

}


const    quint8 * MCM_Data::get_sdn_list_data(quint8 ch)
{

}

const    quint8 * MCM_Data::get_fault_code_string(quint8 ch)
{

}

quint32  MCM_Data::get_mcm_data(quint8 ch, mcm_data_code_t code)
{

}

bool     MCM_Data::get_mcm_device_sta(quint8 ch, mcm_device_sta_code_t code)
{

}

quint8   MCM_Data::get_sdn_code(quint8 ch)
{

}

const    quint8 * MCM_Data::get_sdn_info(quint8 sdnCode, quint8 bmsToutCode)
{

}
