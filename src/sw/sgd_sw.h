/*===============================================================*/
/*                                                               */
/*                          sgd_sw.h                             */
/*                                                               */
/*             Software version of spam filtering.               */
/*                                                               */
/*===============================================================*/

#include "../host/typedefs.h"

void SgdLR_sw( DataType    data[NUM_FEATURES * NUM_TRAINING],
               LabelType   label[NUM_TRAINING],
               FeatureType theta[NUM_FEATURES]);
//https://kuleuven-my.sharepoint.com/:w:/g/personal/yuming_chang_student_kuleuven_be/ERCXyOwRTxdFmj_DeVmD7MABsYnT9vJUxrynx415I3jUnw?e=1h2ulI