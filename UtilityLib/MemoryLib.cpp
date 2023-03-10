#include "UtilityLib.h"
/// <summary>
/// 读取内存(突破内存保护)
/// </summary>
/// <param name="hProcess">进程句柄</param>
/// <param name="dwBaseAddress">读取地址</param>
/// <param name="lpBuffer">用于存放读取的内容</param>
/// <param name="nSize">读取大小</param>
/// <returns></returns>
bool MemoryLib::ReadProcessMemory(HANDLE hProcess, DWORD dwBaseAddress, LPVOID lpBuffer, SIZE_T nSize)
{
	DWORD dwOldProtect(0); //用于备份原有的内存属性
	SIZE_T dwNumberOfBytesRead(0); //用于获取成功读取字节的数量
	VirtualProtectEx(hProcess, (LPVOID)dwBaseAddress, nSize, PAGE_EXECUTE_READWRITE, &dwOldProtect);//修改内存属性，避免内存保护出现读写问题
	bool bResult = ::ReadProcessMemory(hProcess, (LPCVOID)dwBaseAddress, lpBuffer, nSize, &dwNumberOfBytesRead); //读取内存
	VirtualProtectEx(hProcess, (LPVOID)dwBaseAddress, nSize, dwOldProtect, &dwOldProtect);//恢复旧内存属性
	if (bResult == false || dwNumberOfBytesRead != nSize)//检查返回值，检查读取长度是否一致
		return false;
	return true;
}
/// <summary>
/// 写入内存(突破内存保护)
/// </summary>
/// <param name="hProcess">进程句柄</param>
/// <param name="dwBaseAddress">写入地址</param>
/// <param name="lpBuffer">用于存放待写入的内容</param>
/// <param name="nSize">写入大小</param>
/// <returns></returns>
bool MemoryLib::WriteProcessMemory(HANDLE hProcess, DWORD dwBaseAddress, LPCVOID lpBuffer, SIZE_T nSize)
{
	DWORD dwOldProtect(0); //用于备份原有的内存属性
	SIZE_T dwNumberOfBytesWritten(0); //用于获取成功写入字节的数量
	VirtualProtectEx(hProcess, (LPVOID)dwBaseAddress, nSize, PAGE_EXECUTE_READWRITE, &dwOldProtect);//修改内存属性，避免内存保护出现读写问题
	bool bResult = ::WriteProcessMemory(hProcess, (LPVOID)dwBaseAddress, lpBuffer, nSize, &dwNumberOfBytesWritten); //读取内存
	VirtualProtectEx(hProcess, (LPVOID)dwBaseAddress, nSize, dwOldProtect, &dwOldProtect);//恢复旧内存属性
	if (bResult == false || dwNumberOfBytesWritten != nSize)//检查返回值，检查读取长度是否一致
		return false;
	return true;
}
