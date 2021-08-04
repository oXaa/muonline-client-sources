#ifndef _CkString_H
#define _CkString_H
#include "Chilkat_C.h"

HCkString CkString_Create(void);
void CkString_Dispose(HCkString handle);
BOOL CkString_getUtf8(HCkString handle);
void CkString_putUtf8(HCkString handle, BOOL newVal);
void CkString_append(HCkString handle, const char *s);
void CkString_appendAnsi(HCkString handle, const char *s);
void CkString_appendChar(HCkString handle, char c);
void CkString_appendCurrentDateRfc822(HCkString handle);
void CkString_appendDateRfc822(HCkString handle, SYSTEMTIME *sysTime);
void CkString_appendEnc(HCkString handle, const char *s, const char *encoding);
void CkString_appendHexData(HCkString handle, const unsigned char *data, int dataLen);
void CkString_appendInt(HCkString handle, int n);
void CkString_appendLastWindowsError(HCkString handle);
void CkString_appendN(HCkString handle, const char *s, int numBytes);
void CkString_appendNU(HCkString handle, const wchar_t *unicode, int numChars);
void CkString_appendStr(HCkString handle, HCkString str);
void CkString_appendU(HCkString handle, const wchar_t *unicode);
void CkString_appendUtf8(HCkString handle, const char *s);
void CkString_base64Decode(HCkString handle, const char *charset);
void CkString_base64Encode(HCkString handle, const char *charset);
BOOL CkString_beginsWith(HCkString handle, const char *sSubstr);
BOOL CkString_beginsWithStr(HCkString handle, HCkString s);
char CkString_charAt(HCkString handle, int idx);
wchar_t CkString_charAtU(HCkString handle, int idx);
void CkString_chopAtFirstChar(HCkString handle, char c1);
void CkString_chopAtStr(HCkString handle, HCkString str);
void CkString_clear(HCkString handle);
HCkString CkString_clone(HCkString handle);
int CkString_compareStr(HCkString handle, HCkString str);
BOOL CkString_containsSubstring(HCkString handle, const char *pattern);
BOOL CkString_containsSubstringNoCase(HCkString handle, const char *pattern);
int CkString_countCharOccurances(HCkString handle, char ch);
void CkString_decodeXMLSpecial(HCkString handle);
void CkString_eliminateChar(HCkString handle, char ansiChar, int startIndex);
void CkString_encodeXMLSpecial(HCkString handle);
BOOL CkString_endsWith(HCkString handle, const char *s);
BOOL CkString_endsWithStr(HCkString handle, HCkString s);
void CkString_entityDecode(HCkString handle);
void CkString_entityEncode(HCkString handle);
BOOL CkString_equals(HCkString handle, const char *s);
BOOL CkString_equalsIgnoreCase(HCkString handle, const char *s);
BOOL CkString_equalsIgnoreCaseStr(HCkString handle, HCkString s);
BOOL CkString_equalsStr(HCkString handle, HCkString s);
const char *CkString_getAnsi(HCkString handle);
HCkString CkString_getChar(HCkString handle, int idx);
const char *CkString_getEnc(HCkString handle, const char *encoding);
int CkString_getNumChars(HCkString handle);
int CkString_getSizeAnsi(HCkString handle);
int CkString_getSizeUnicode(HCkString handle);
int CkString_getSizeUtf8(HCkString handle);
const char *CkString_getString(HCkString handle);
const wchar_t *CkString_getUnicode(HCkString handle);
const char *CkString_getStringUtf8(HCkString handle);
void CkString_hexDecode(HCkString handle, const char *charset);
void CkString_hexEncode(HCkString handle, const char *charset);
int CkString_indexOf(HCkString handle, const char *s);
int CkString_indexOfStr(HCkString handle, HCkString s);
int CkString_intValue(HCkString handle);
char CkString_lastChar(HCkString handle);
BOOL CkString_loadFile(HCkString handle, const char *fileName, const char *charset);
BOOL CkString_matches(HCkString handle, const char *s);
BOOL CkString_matchesStr(HCkString handle, HCkString str);
void CkString_minimizeMemory(HCkString handle);
void CkString_prepend(HCkString handle, const char *s);
void CkString_qpDecode(HCkString handle, const char *charset);
void CkString_qpEncode(HCkString handle, const char *charset);
int CkString_removeAll(HCkString handle, HCkString str);
void CkString_removeCharOccurances(HCkString handle, char c);
void CkString_removeChunk(HCkString handle, int charStartPos, int numChars);
BOOL CkString_removeFirst(HCkString handle, HCkString str);
int CkString_replaceAll(HCkString handle, HCkString str, HCkString replacement);
int CkString_replaceAllOccurances(HCkString handle, const char *pattern, const char *replacement);
void CkString_replaceChar(HCkString handle, char c1, char c2);
BOOL CkString_replaceFirst(HCkString handle, HCkString str, HCkString replacement);
BOOL CkString_replaceFirstOccurance(HCkString handle, const char *pattern, const char *replacement);
BOOL CkString_saveToFile(HCkString handle, const char *filename, const char *charset);
void CkString_setStr(HCkString handle, HCkString s);
void CkString_setString(HCkString handle, const char *s);
void CkString_setStringAnsi(HCkString handle, const char *s);
void CkString_setStringU(HCkString handle, const wchar_t *unicode);
void CkString_setStringUtf8(HCkString handle, const char *s);
void CkString_shorten(HCkString handle, int n);
HCkStringArray CkString_split(HCkString handle, char splitChar, BOOL exceptDoubleQuoted, BOOL exceptEscaped, BOOL keepEmpty);
HCkStringArray CkString_split2(HCkString handle, const char *splitCharSet, BOOL exceptDoubleQuoted, BOOL exceptEscaped, BOOL keepEmpty);
HCkStringArray CkString_splitAtWS(HCkString handle);
HCkString CkString_substring(HCkString handle, int startCharIdx, int numChars);
void CkString_toCRLF(HCkString handle);
void CkString_toLF(HCkString handle);
void CkString_toLowerCase(HCkString handle);
void CkString_toUpperCase(HCkString handle);
HCkStringArray CkString_tokenize(HCkString handle, char *punctuation);
void CkString_trim(HCkString handle);
void CkString_trim2(HCkString handle);
void CkString_trimInsideSpaces(HCkString handle);
void CkString_urlDecode(HCkString handle, const char *charset);
void CkString_urlEncode(HCkString handle, const char *charset);
#endif
