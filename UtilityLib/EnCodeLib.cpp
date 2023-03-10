#include "UtilityLib.h"
/// <summary>
/// 将Utf8转换成Ansi
/// </summary>
/// <param name="szU8">传入的Utf8内容</param>
/// <param name="szBuf">返回Ansi内容</param>
/// <param name="unBufSize">内容大小上限</param>
void EnCodeLib::UTF8_to_ANSI(char* szU8,char* szBuf,unsigned int unBufSize)
{
    int wcsLen = MultiByteToWideChar(CP_UTF8, NULL, szU8, strlen(szU8), NULL, 0);
    wchar_t* wszString = new wchar_t[wcsLen + 1];
    MultiByteToWideChar(CP_UTF8, NULL, szU8, strlen(szU8), wszString, wcsLen);
    wszString[wcsLen] = '\0';

    int ansiLen = WideCharToMultiByte(CP_ACP, NULL, wszString, wcslen(wszString), NULL, 0, NULL, NULL);
    char* szAnsi = new char[ansiLen + 1];
    WideCharToMultiByte(CP_ACP, NULL, wszString, wcslen(wszString), szAnsi, ansiLen, NULL, NULL);
    szAnsi[ansiLen] = '\0';
    memcpy_s(szBuf, unBufSize, szAnsi, ansiLen + 1);
    delete[] wszString;
    delete[] szAnsi;
}
/// <summary>
/// 将宽字符转换成Ansi
/// </summary>
/// <param name="wstr">宽字符内容</param>
/// <returns></returns>
std::string ConvertWideToANSI(const std::wstring& wstr)
{
    int count = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.length(), NULL, 0, NULL, NULL);
    std::string str(count, 0);
    WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, &str[0], count, NULL, NULL);
    return str;
}
/// <summary>
/// 将Ansi转换成宽字符
/// </summary>
/// <param name="str">Ansi内容</param>
/// <returns></returns>
std::wstring ConvertAnsiToWide(const std::string& str)
{
    int count = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), NULL, 0);
    std::wstring wstr(count, 0);
    MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), &wstr[0], count);
    return wstr;
}
/// <summary>
/// 将宽字符转换成Utf8
/// </summary>
/// <param name="wstr">宽字符内容</param>
/// <returns></returns>
std::string ConvertWideToUtf8(const std::wstring& wstr)
{
    int count = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), wstr.length(), NULL, 0, NULL, NULL);
    std::string str(count, 0);
    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &str[0], count, NULL, NULL);
    return str;
}
/// <summary>
/// 将Utf8转换成宽字符
/// </summary>
/// <param name="str">Utf8内容</param>
/// <returns></returns>
std::wstring ConvertUtf8ToWide(const std::string& str)
{
    int count = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), NULL, 0);
    std::wstring wstr(count, 0);
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), &wstr[0], count);
    return wstr;
}