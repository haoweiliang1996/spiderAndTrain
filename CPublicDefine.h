#ifndef _PUBLICDEFINE_H_
#define _PUBLICDEFINE_H_
//
static const int CT_SENTENCE_BEGIN = 1;
static const int CT_SENTENCE_END = 4;
static const int CT_SINGLE = 5;
static const int CT_DELIMITER = CT_SINGLE + 1;
static const int CT_CHINESE = CT_SINGLE + 2;
static const int CT_LETTER = CT_SINGLE + 3;
static const int CT_NUM = CT_SINGLE + 4;
static const int CT_INDEX = CT_SINGLE + 5;
static const int CT_OTHER = CT_SINGLE + 12;
static const float SIM_ALPHA=0.95;
static const bool POS_TAG=true;      //是否词性标记,true为有词性标记，false为没有词性标记
#endif //_PUBLICDEFINE_H_