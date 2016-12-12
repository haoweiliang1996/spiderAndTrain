#include "StringOp.h"


CStringOp::CStringOp(void)
{
}


CStringOp::~CStringOp(void)
{
}
size_t CStringOp::Find(const string& str, const string& sub)
{
	 size_t nSize1 = str.size();
	 size_t nSize2 = sub.size();
 
	 if( nSize1==0 || nSize2==0 || nSize1<nSize2 )
	  return string::npos;
 
	 size_t k = 0;
	 size_t d = nSize1 - nSize2;
 
	 while ( k <= d )
	 {
	  if ( sub == str.substr(k, nSize2) )
	   return k;
 
	  if ( str[k] < 0 )
	   k += 2;
	  else
	   ++k;
	 }
 
	 return string::npos;
} 
size_t CStringOp::Find_Last_Of(const string& str, const string& sub)
{
	 size_t nSize1 = str.size();
	 size_t nSize2 = sub.size();
 
	 if( nSize1==0 || nSize2==0 || nSize1<nSize2 )
	  return string::npos;
 
	 size_t k = 0;
	 size_t d = nSize1 - nSize2;
	 int index=-1;
 
	 while ( k <= d )
	 {
		if ( sub == str.substr(k, nSize2) )
		{
			index=k;
		}
 
		if ( str[k] < 0 )
		k += 2;
		else
		++k;
	 }
	 if(index>=0&&index<nSize1)
		 return index;
	 else
		return string::npos;
} 
//findany
size_t CStringOp::FindAny(const string& str, const vector<string>& subs, string& foundStr)
{
	vector<string>::const_iterator itor = subs.begin();
	size_t t = 0;
	size_t min = string::npos;
	for(; itor!=subs.end(); ++itor)
	{
		if(itor->size()==0) continue;

		t = Find(str, *itor);
		if(t != string::npos)
		{
			if(min==string::npos || t<min)
			{
				min = t;
				foundStr = *itor;
			}
		}
	}
	return min;
}
//
//将strSource按strSep拆分成字符串数组
//
//
//将strSource按strSep拆分成字符串数组
//
bool CStringOp::Split(vector<string> &arrResult, const string& strSource, const string& strSep)
{
	arrResult.clear();
	string strSplit = strSource;

	if (strSep == "")//分隔符为空，一个字一个字读入
	{
	    int nSize = strSource.size();
        for( int ix=0; ix<nSize; ++ix )
        {
            if( strSource.at(ix) > 0 )//Ascii字符
            {
                strSplit = strSource.substr(ix, 1);
                arrResult.push_back(strSplit);
            }
            else if( (ix+1 < nSize))//汉字
            {
                strSplit = strSource.substr(ix++, 2);
                arrResult.push_back(strSplit);
            }
        }
	}
	else//分隔符不为空，按分隔符切分
	{
        string::size_type nEnd = 0;

        if ( !strSep.empty() )
        {
            while ( (nEnd = Find(strSplit, strSep)) != string::npos )
            {
                string item = strSplit.substr(0, nEnd);
                if ( item != "" )
                {
                    arrResult.push_back(item);
                }
                strSplit = strSplit.substr(nEnd + strSep.size());
            }

            if ( strSplit != "" )
            {
                arrResult.push_back(strSplit);
            }
        }
	}

	return true;
}
//Split
//remove_null : 是否删除空的项
//remove_sep  : 在split后的各个项中，是否删除分隔符
vector<string> CStringOp::Split(const string& strSource, const vector<string>& strsSep, const bool remove_null, const bool remove_sep)
{
	vector<string> vRes;
	string strSplit = strSource;
	string::size_type nEnd = 0;
	string foundStr;

	if ( strsSep.size()!=0 )
	{
		while ( (nEnd = FindAny(strSplit, strsSep, foundStr)) != string::npos )
		{
			string item = strSplit.substr(0, nEnd);			
			if(remove_null)
			{
				if(!item.empty())
				{
					vRes.push_back(item);
				}
			}
			else
			{
				vRes.push_back(item);
			}
			if(!remove_sep)
				vRes.push_back(foundStr);
			strSplit = strSplit.substr(nEnd + foundStr.length());
		}
		if(remove_null)
		{
			if(!strSplit.empty())
			{
				vRes.push_back(strSplit);
			}
		}
		else
		{
			vRes.push_back(strSplit);
		}
	}
	return vRes;
}
vector<string> CStringOp::getSequence(const string& str)
{
	vector<string> resultVec;
	 int ix=0,nSize=str.size();
	 string word;
	 while(ix<nSize)
	 {
		 if(str[ix]<0&&ix<nSize-1)
		 {
			 string str1(1,str[ix]);
			 string str2(1,str[ix+1]);
			 word=str1+str2;
			 ix+=2;
		 }
		 else
		 {
			 string str1(1,str[ix]);
			 word=str1;
			 ix++;
		 }
		 resultVec.push_back(word);
	 }
	 return resultVec;
}
string CStringOp::tolowercase(const string& str)
{
	string strResult="";
	int ix=0, nSize=str.size();
	while ( ix < nSize )
	{
		if ( (str[ix] < 0) && (ix+1 < nSize) )//双字节字符，如汉字等
		{
			strResult+=str.substr(ix,2);
			ix+=2;
		}
		else
		{
			strResult+=(char)tolower(str[ix]);
			++ix;
		}
	}
	return strResult;
}
/*
	去掉首尾连续的指定的字符
*/
string CStringOp::trim(const string& str,const string& delimiters)
{
	string result="";
	vector<string> seqVec=getSequence(str);
	int len=seqVec.size();
	bool flag=false;
	int begin_index=0;
	int end_index=len-1;
	for(int i=0;i<len;++i)
	{
		if(Find(delimiters,seqVec[i])!=string::npos&&!flag)
		{
			flag=false;	
			//控制句子只是标点符号或空格
			if(i==len-1)
			{
				begin_index=i+1;
			}
		}
		else
		{
			begin_index=i;
			break;
		}
	}
	flag=false;
	for(int i=len-1;i>=0;--i)
	{
		if(Find(delimiters,seqVec[i])!=string::npos&&!flag)
		{
			flag=false;			
		}
		else
		{
			end_index=i;
			break;
		}
	}
	for(int ix=begin_index;ix<=end_index;++ix)
	{
		result+=seqVec[ix];
	}
	return result;
}
int CStringOp::CharType(const string& str)
{
	if( str.size() == 1 )
	{
		string delimiters = " *!,.?()[]{}+=_//<>&%$#@";
		if( str.find_first_of(delimiters) != string::npos )
			return CT_DELIMITER;
		else
			return CT_SINGLE;
	}
	else if( str.size() == 2 )
	{
		unsigned char c1 = str[0];
		unsigned char c2 = str[1];

		/*
			code  +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F
			A2A0     ⅰ ⅱ ⅲ ⅳ ⅴ ⅵ ⅶ ⅷ ⅸ ⅹ     
			A2B0   ⒈ ⒉ ⒊ ⒋ ⒌ ⒍ ⒎ ⒏ ⒐ ⒑ ⒒ ⒓ ⒔ ⒕ ⒖
			A2C0  ⒗ ⒘ ⒙ ⒚ ⒛ ⑴ ⑵ ⑶ ⑷ ⑸ ⑹ ⑺ ⑻ ⑼ ⑽ ⑾
			A2D0  ⑿ ⒀ ⒁ ⒂ ⒃ ⒄ ⒅ ⒆ ⒇ ① ② ③ ④ ⑤ ⑥ ⑦
			A2E0  ⑧ ⑨ ⑩   ㈠ ㈡ ㈢ ㈣ ㈤ ㈥ ㈦ ㈧ ㈨ ㈩ 
			A2F0   Ⅰ Ⅱ Ⅲ Ⅳ Ⅴ Ⅵ Ⅶ Ⅷ Ⅸ Ⅹ Ⅺ Ⅻ     
		*/
		if( c1 == 162 )
			return CT_INDEX;

		//０ １ ２ ３ ４ ５ ６ ７ ８ ９
		else if( (c1 == 163) && (c2 > 175) && (c2 < 186) )
			return CT_NUM;

		//ＡＢＣＤＥＦＧＨＩＪＫＬＭＮＯＰＱＲＳＴＵＶＷＸＹＺ
		//ａｂｃｄｅｆｇｈｉｊｋｌｍｎｏｐｑｒｓｔｕｖｗｘｙｚ 
		else if( (c1 == 163) && (c2 >= 193 && c2 <= 218 || c2 >= 225 && c2 <= 250) )
			return CT_LETTER;

		/*
			code  +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F
			A1A0     　 、 。 · ˉ ˇ ¨ 〃 々 — ～ ‖ … ‘ ’
			A1B0  “ ” 〔 〕 〈 〉 《 》 「 」 『 』 〖 〗 【 】
			A1C0  ± × ÷ ∶ ∧ ∨ ∑ ∏ ∪ ∩ ∈ ∷ √ ⊥ ∥ ∠
			A1D0  ⌒ ⊙ ∫ ∮ ≡ ≌ ≈ ∽ ∝ ≠ ≮ ≯ ≤ ≥ ∞ ∵
			A1E0  ∴ ♂ ♀ ° ′ ″ ℃ ＄ ¤ ￠ ￡ ‰ § № ☆ ★
			A1F0  ○ ● ◎ ◇ ◆ □ ■ △ ▲ ※ → ← ↑ ↓ 〓   
			以下除了字母和数字的部分
			code  +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F
			A3A0     ！ ＂ ＃ ￥ ％ ＆ ＇ （ ） ＊ ＋ ， － ． ／
			A3B0                                ： ； ＜ ＝ ＞ ？
			A3C0  ＠ 
			A3D0                                   ［ ＼ ］ ＾ ＿
			A3E0  ｀ 
			A3F0                                   ｛ ｜ ｝ ￣ 
		*/
		else if( (c1 == 161) || (c1 == 163) )
			return CT_DELIMITER;

		else if( (c1 >= 176) && (c1 <= 247) )
			return CT_CHINESE;

		else
			return CT_OTHER;
	}
	else
		return CT_OTHER;
}
