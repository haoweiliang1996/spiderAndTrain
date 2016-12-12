#include <string>
#include <set>

using namespace std;

typedef set<string> STRING_SET;

template<class T>
int getArrayLen(T& array) {
	return (sizeof(array) / sizeof(array[0]));
}


class SeparateJudger {
private:
	static string separate[];
	static STRING_SET dict;
	static STRING_SET createSet();
public:
	static bool isSeparate(string str);
};
