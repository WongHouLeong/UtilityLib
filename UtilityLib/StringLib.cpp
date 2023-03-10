#include "UtilityLib.h"
/// <summary>
/// 将十六进制数组打印到字符串变量
/// </summary>
/// <param name="arrHex">传入数组</param>
/// <param name="unArrSize">数组大小</param>
/// <param name="szBuf">返回字符串</param>
/// <param name="unBufSize">返回字符串大小上限</param>
void StringLib::HexArr2Str(const unsigned char arrHex[], unsigned int unArrSize, char* szBuf, unsigned int unBufSize)
{
	memset(szBuf, 0, unBufSize);
	strcat_s(szBuf, unBufSize, "{");
	for (unsigned int i = 0; i < unArrSize; i++)
	{
		if (i != 0)
			strcat_s(szBuf, unBufSize, ",");
		char cTmpBuf[5];
		sprintf_s(cTmpBuf, "0x%02X", arrHex[i]); //%02x 表示以16进制的格式输出整bai数类型的数值，输出域宽为2，右对齐，不足的用字符0替代。
		strcat_s(szBuf, unBufSize, cTmpBuf);
	}
	strcat_s(szBuf, unBufSize, "}");
}
/// <summary>
/// 具有printf功能的DebugOutput
/// </summary>
/// <param name="pszFormat">字符串格式</param>
/// <param name="">参数</param>
void StringLib::DbgPrintf(const char* pszFormat, ...)
{
	char szBuf[4096] = "[Debug] ";
	char szTmp[4096]{ 0 };
	va_list argList(0); //va_list 用于保存参数
	va_start(argList, pszFormat);//遍历参数列表，并保存至argList
	vsprintf_s(szTmp, pszFormat, argList);//将字符串及参数进行格式化打印至szBuf
	va_end(argList);//检索所有参数后，va_end 将指针重置为 NULL，与va_start成对出现
	strcat_s(szBuf, szTmp);
	strcat_s(szBuf, "\n");
	OutputDebugStringA(szBuf);//输出结果
}

/// <summary>
/// 使用Debug打印字符串(宽字符)
/// </summary>
/// <param name="szTitle">标题</param>
/// <param name="szData">内容</param>
void StringLib::DbgOutPut_W(const wchar_t* szTitle,const wchar_t* szData)
{
	wchar_t szHead[] = L"[Debug] ";
	//wchar_t szEnd[] = L"";
	unsigned int uStrLen = wcslen(szData);
	//unsigned int uBufLen = uStrLen + wcslen(szHead) + wcslen(szTitle) + wcslen(szEnd) +1;//+1是为了结尾的\0
	unsigned int uBufLen = uStrLen + wcslen(szHead) + wcslen(szTitle) + 1;//+1是为了结尾的\0
	wchar_t* szBuf = new wchar_t[uBufLen];
	memset(szBuf, 0x0, uBufLen* sizeof(wchar_t));
	wcscat_s(szBuf, uBufLen, szHead);
	wcscat_s(szBuf, uBufLen, szTitle);
	memcpy_s(&szBuf[wcslen(szHead)+ wcslen(szTitle)], uBufLen * sizeof(wchar_t), szData, uStrLen* sizeof(wchar_t)+2);//+2是为了把\0也包进来
	//wcscat_s(szBuf, uBufLen , szEnd);
	OutputDebugStringW(szBuf);
	delete[] szBuf;
}
/// <summary>
///  将printf功能输出到变量,例子:StringLib::GetPrintf("函数异常：%s", szResult, MAX_PATH, lpProcName);
/// </summary>
/// <param name="pszFormat">字符串格式</param>
/// <param name="szBuf">返回结果</param>
/// <param name="unBufSize">结果的上限大小</param>
/// <param name="">参数</param>

void StringLib::GetPrintf(const char* pszFormat, char* szBuf, unsigned int unBufSize, ...)
{
	memset(szBuf, 0x0, unBufSize);
	va_list argList(0); //va_list 用于保存参数
	va_start(argList, pszFormat);//遍历参数列表，并保存至argList
	vsprintf_s(szBuf, unBufSize, pszFormat, argList);//将字符串及参数进行格式化打印至szBuf
	va_end(argList);//检索所有参数后，va_end 将指针重置为 NULL，与va_start成对出现
	strcat_s(szBuf, unBufSize, "\n");
}
/// <summary>
/// 传入一个文件路径，返回该文件名.副档名
/// </summary>
/// <param name="lpFilePath">文件路径</param>
/// <param name="szBuf">用于文件名返回</param>
/// <param name="unBufSize">文件名上限长度</param>
void StringLib::GetFileName(const char* lpFilePath, char* szBuf, unsigned int unBufSize)
{
	memset(szBuf, 0x0, unBufSize);
	char szExtension[_MAX_EXT];
	_splitpath_s(lpFilePath, NULL, 0, NULL, 0, szBuf, unBufSize, szExtension, _MAX_EXT);
	strcat_s(szBuf, unBufSize, szExtension);
}