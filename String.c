/******************************************************************************
AUTHOR : RAYAN LABAY
REVIEWER :
DATE : 10.5.22
REVISION :
******************************************************************************/

#include <stdio.h>  /* printf */
#include <stdlib.h> /* tolower */
#include <assert.h> /* assert */
#include <stddef.h> /* size_t */
#include <string.h>
#include <ctype.h>  /* tolower */
#include "String.h" /* string functions */
#define MAX_TOKEN_NUMBER 100
/******************************************************************************
DESCRIPTION:
returns the length of a given string. 

RETURN VALUE:
 * length of a given string.
 * 0 if string is NULL.
 
STATUS: DONE
******************************************************************************/
size_t StrLen(const char *str)
{
	const char* end = str;
	while(*end++);
	return !str ? (size_t) NULL : (size_t) (end - str - 1);	
}
/****************************************************************************** 
DESCRIPTION:
Compares 2 strings lexicographically. 

RETURN VALUE:
 * 0  if str1 == str2
 * <0 if str1 < str2
 * >0 if str1 > str2  
STATUS: DONE
******************************************************************************/
int StrCmp (const char *str1, const char *str2)
{
	while(*str1 && *str1++ == *str2++ );
	return *str1 - *str2;	
}
/****************************************************************************** 
DESCRIPTION:
Copies one src string to dst. 

RETURN VALUE:
 * pointer to dst, where copied value is.
STATUS: DONE
******************************************************************************/
char *StrCpy(char *dest, const char *src)
{
	char* dest_t = dest;
	while(*src)
	{
		*dest++ = *src++;
	}
	*dest = '\0';
	return dest_t;
}
/****************************************************************************** 
DESCRIPTION:
Copies one src string to dst, up to n elements. 

RETURN VALUE:
 * pointer to dst, where copied value is.
 * if n > len(src), then dst will be padded untill length is n.
STATUS: DONE
******************************************************************************/
char *StrNCpy(char *dest, const char *src, size_t n)
{
	char *dest_t = dest;
	size_t i = 0;
	for(i = 0; i < n; i++)
	{
		if(!*src)
			break;
		*dest++ = *src++;	
	}
	while(*src++) *dest++ = '\0';
	return dest_t;	
}
/****************************************************************************** 
DESCRIPTION:
Compares 2 strings neglecting lower or upper case.


RETURN VALUE:
 * 0  if str1 == str2
 * <0 if str1 < str2
 * >0 if str1 > str2 
STATUS: DONE
******************************************************************************/
int StrCaseCmp(const char *str1, const char *str2)
{
	while(tolower(*(str1++)) == tolower(*(str2++)) && !( *str1 == '\0' || 
	*str2 == '\0'));
	return *str1 > *str2 ? 1 : *str1 < *str2 ? -1 : 0;	
}
/****************************************************************************** 
DESCRIPTION:
returns pointer to the first location where c appears in str.


RETURN VALUE:
 * pointer to the first location where c appears in str.
 * NULL if c doesnt appear in str. 
STATUS: DONE
******************************************************************************/
char *StrChr( const char *str, int c )
{
	while(*str != c && *str != '\0')
	{
		str++;
	}
	return (char*)str;
}
/****************************************************************************** 
DESCRIPTION:
duplicates str to another location, allocates new memory and pastes it there. 


RETURN VALUE:
 * pointer to the allocated memory where the duplicated value is.
 * NULL if str is NULL. 
STATUS: DONE
NOTE: test doesnt work
******************************************************************************/
char * StrDup( const char *str )
{
	int len = strlen(str) + 1;
	char* newstr = (char*)malloc(len);
	if(str == NULL) return NULL;
	return strcpy(newstr, str);
}
/****************************************************************************** 
DESCRIPTION:
Concatenates two strings, src at the end of dest, doesnt allocate new memory.


RETURN VALUE:
 * pointer to dest. 
STATUS: DONE
******************************************************************************/
char *StrCat(char *dest, const char *src)
{
	char *dest_t = dest;
	if(!src) return dest;
	while(*++dest);
	*dest++ = *src++;	
	strcpy(dest, src);
	return dest_t;	
}
/****************************************************************************** 
DESCRIPTION:
Concatenates two strings, src at the end of dest, up to n elements.
Doesnt allocate new memory.


RETURN VALUE:
 * pointer to dest. 
STATUS: DONE
******************************************************************************/
char *StrNCat(char *dest, const char *src, size_t n)
{
	char *dest_t = dest;
	if(!src) return NULL;
	while(*++dest);
	*dest++ = *src++;	
	strncpy(dest, src, n - 1);
	return dest_t;	
}
/****************************************************************************** 
DESCRIPTION:
Finds the location of the substring needle in haystack and returns pointer to
it.


RETURN VALUE:
 * pointer to first appearance of needle in haystack. 
 * NULL if needle not found in haystack.
STATUS: DONE
******************************************************************************/
char *StrStr(const char *haystack, const char *needle)
{
	int j = 0, needle_len = strlen(needle);
	while(*haystack++)
	{
		if(*haystack == *(needle + j))
		{
			j++;
			if( j == needle_len )
				return (char*) (haystack - needle_len + 1);
		}else
		{
			j = 0;
		}
	}
	return NULL;
}
/****************************************************************************** 
DESCRIPTION:
static function, finds if c is in str.

RETURN VALUE:
 * 1 if c found.
 * 0 if c was not found.
******************************************************************************/
static int IsInStr(char* str, char c)
{
	while(*str != c && *str != '\0' ) str++;
	return *str == '\0' ? 0 : 1;
}
/****************************************************************************** 
DESCRIPTION:
Counts how many characters from the begining of str1 are from the set of 
unique(str2), if str2 = "ABB", set(str2) = {A,B}.

RETURN VALUE:
 * as described above.
STATUS: DONE
******************************************************************************/
size_t StrSpn(const char *str1, const char *str2)
{
	int seen = 0;
	while(*str1)
	{
		if(! IsInStr((char*)str2, *str1++))
		{
			if(seen > 0)
				return seen;
			seen = 0;
		}
		else
		{
			
			seen++;
		}
	}
	return seen == 0 ? 0 : seen;
}
/****************************************************************************** 
DESCRIPTION:
Checks if a given string is a palindrome.

RETURN VALUE:
 * 1 if str is palindrome.
 * 0 if not.
STATUS: DONE
******************************************************************************/
int IsPalindrome(char* str)
{
	int len = strlen(str);
	int i = 0;
	for(i = 0; i < len/2; i++)
		if(str[i] != str[len-1-i])
			return 0;
	return 1;
}
/****************************************************************************** 
							ADVANCED
								|	
								|
******************************************************************************/

/****************************************************************************** 
DESCRIPTION:
static function used in strtok. frees memory of the tokens.
******************************************************************************/
/*
static void FreeTokens(){
	int i = 0;
	for(i = 0; i < g_tokens_size; i++ )
	{
		free(g_tokens[g_tokens]);			
	}
	free(tokens);
}
static void InitTokens(){
	g_token = (char*)malloc(sizeof(char*)*MAX_TOKEN_NUMBER);	
}
*/
/****************************************************************************** 
DESCRIPTION:
reads in a string, divides it to tokens according to delim, then each time
strtok is called, it provides another token, from left to right.

RETURN VALUE:
 * next token.
 * NULL if no tokens left.
******************************************************************************/
/*
char *StrTok(char *str, const char *delim)
 {
 	int delim_len = strlen(delim);
 	if(last_str && strcmp(str, last_str) == 0)
 	{
 		first_token = (char*)malloc(strlen(str) + 1);
 		last_str = str;
 	}
 	last_str = str;
 	strncpy(first_token, last_str, strlen(
 				strstr(last_str, delim) - last_str);
 	
 	if(*str)
 		return first_token;
 	
 	while(s = strstr(last_str, delim))
 	{
 		if(s == prev_s + delim_len)
		{
			prev_s = s;
			continue;
		}  
 		str = s + delim + len;
 		if(!str)
 			break;
 		next_pos = str;
 	}
 	
 	return strstr(str, delim) + delim_len; 	
 }
 */
/****************************************************************************** 
DESCRIPTION:
static function to check if number contains the digit 7.
******************************************************************************/
/*
static int Contains7(int number)
{
	while(number)
	{
		if(number%10 = 7)
			return 1;
		number/=10;
	}
	return 0;
}*/
/****************************************************************************** 
DESCRIPTION:
7 Boom, prints all numbers that contain 7 or are divisble by 7.
for all others print BOOM. in the range(from,to)
******************************************************************************/
/*
void 7BOOM(int from, int to)
{
	int i = from;
	for(i = from; i < to; i++)
	{
		if(Contains7(i) || i % 7 == 0)
			printf("%d\n", i);
		else
			printf("BOOM\n");
	}
}
*/
/****************************************************************************** 
DESCRIPTION:
removes white spaces from str, from begining in the middle or at the end.
******************************************************************************/
/*
void SpaceReview(char* str)
{
	if(!str || !*str) return NULL;
	char* ret = (char*)malloc(strlen(str) + 1);
	char* tmp = (char*)malloc(strlen(str) + 1);
	sif(isspace(*str))
		strcpy(str, str + 1);
	while(*str)
	{
		while(s = strtok(str, " \t\r\n\f\v"))
		{
			
			switch(*(strstr(str, s) - 1))
			{
			case ' ' : strcpy(tmp, " "); 
			case '\t': strcpy(tmp, "\t");
			case '\n': strcpy(tmp, "\n");
			case '\f': strcpy(tmp, "\f");
			case '\v': strcpy(tmp, "\v");
			case '\r': strcpy(tmp, "\r");
			}
			strcat(tmp, s);
			strcat(ret, tmp);
		}			
	}
	strcpy(str, ret);
	free(ret);
}
*/











