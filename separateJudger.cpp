#include "separateJudger.h"


string SeparateJudger::separate[] = {
	"，", "。", "！", "？", "、", "：", "；", "“", "”", "‘", "’",
	",", ".", "!", "?", ":", ";", "\"", "'"
};

STRING_SET SeparateJudger::dict = SeparateJudger::createSet();

STRING_SET SeparateJudger::createSet() {
	STRING_SET ret;
	for (int i = 0; i < getArrayLen(separate); i++) {
		ret.insert(separate[i]);
	}
	return ret;
}

bool SeparateJudger::isSeparate(string str) {
	return dict.count(str);
}
