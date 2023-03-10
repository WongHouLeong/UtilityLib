#include "UtilityLib.h"
/// <summary>
/// ��Utf8ת����Ansi
/// </summary>
/// <param name="szU8">�����Utf8����</param>
/// <param name="szBuf">����Ansi����</param>
/// <param name="unBufSize">���ݴ�С����</param>
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
/// �����ַ�ת����Ansi
/// </summary>
/// <param name="wstr">���ַ�����</param>
/// <returns></returns>
std::string ConvertWideToANSI(const std::wstring& wstr)
{
    int count = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.length(), NULL, 0, NULL, NULL);
    std::string str(count, 0);
    WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, &str[0], count, NULL, NULL);
    return str;
}
/// <summary>
/// ��Ansiת���ɿ��ַ�
/// </summary>
/// <param name="str">Ansi����</param>
/// <returns></returns>
std::wstring ConvertAnsiToWide(const std::string& str)
{
    int count = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), NULL, 0);
    std::wstring wstr(count, 0);
    MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), &wstr[0], count);
    return wstr;
}
/// <summary>
/// �����ַ�ת����Utf8
/// </summary>
/// <param name="wstr">���ַ�����</param>
/// <returns></returns>
std::string ConvertWideToUtf8(const std::wstring& wstr)
{
    int count = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), wstr.length(), NULL, 0, NULL, NULL);
    std::string str(count, 0);
    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &str[0], count, NULL, NULL);
    return str;
}
/// <summary>
/// ��Utf8ת���ɿ��ַ�
/// </summary>
/// <param name="str">Utf8����</param>
/// <returns></returns>
std::wstring ConvertUtf8ToWide(const std::string& str)
{
    int count = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), NULL, 0);
    std::wstring wstr(count, 0);
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), &wstr[0], count);
    return wstr;
}