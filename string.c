/******************************************************************************
my own string library implementation
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
desc:       calculate the length of a string excluding the terminating
            null byte ('\0').

ret val:    the strlen() function returns the number of bytes in the
            string pointed to by s.
******************************************************************************/
size_t strlen(const char *str)
{
	const char* end = str;
	while(*end++);
	return !str ? (size_t) NULL : (size_t) (end - str - 1);	
}
/****************************************************************************** 
desc:   compare two strings
retval: integer indicating the result of the comparison, as follows:

       • 0, if the s1 and s2 are equal;
       • a negative value if s1 is less than s2;
       • a positive value if s1 is greater than s2.

       The  strncmp() function is similar, except it compares only the first (at most) n bytes of
       s1 and s2.
******************************************************************************/
int strcmp(const char *str1, const char *str2)
{
	while(*str1 && *str1++ == *str2++ );
	return *str1 - *str2;	
}
/****************************************************************************** 
desc:       copy a string
            The  strcpy() function copies the string pointed to by src, including the terminating null
            byte ('\0'), to the buffer pointed to by dest. 
            the strncpy() function is similar, except that at most n bytes of src are  copied.  

            if the length of src is less than n, strncpy() writes additional null bytes to dest to en‐
            sure that a total of n bytes are written.
ret val:    a pointer to the destination string dest.
******************************************************************************/
char *strcpy(char *dest, const char *src)
{
	char* dest_t = dest;
	while(*src)
	{
		*dest++ = *src++;
	}
	*dest = '\0';
	return dest_t;
}

char *strncpy(char *dest, const char *src, size_t n)
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
desc:   compare two strings ignoring case
        The  strcasecmp() function performs a byte-by-byte comparison of the strings s1 and s2,
        ignoring the case of the characters. It returns an integer less than, equal to,
        or greater than zero if s1 is found, respectively, to be less than, to match,
        or be greater than s2. The strncasecmp() function is similar, except that it compares
        no more than n bytes of s1 and s2.

ret val:
       strcasecmp() and strncasecmp() functions return an integer
       less than, equal to, or greater than zero if s1 is, after ignoring case,
       found to be less than, to match, or be greater than s2, respectively.
******************************************************************************/
int strcasecmp(const char *str1, const char *str2)
{
	while(tolower(*(str1++)) == tolower(*(str2++)) && !( *str1 == '\0' || 
	*str2 == '\0'));
	return *str1 > *str2 ? 1 : *str1 < *str2 ? -1 : 0;	
}
/****************************************************************************** 
desc:       locate character in string

ret val:    a pointer to the first occurrence of the character c in the string
            str.
******************************************************************************/
char *strchr( const char *str, int c )
{
	while(*str != c && *str != '\0')
	{
		str++;
	}
	return (char*)str;
}
/****************************************************************************** 
desc:       duplicate a string
ret val:    on success, the strdup() function returns a pointer to the
            duplicated string.  It returns NULL if insufficient memory was
            available, with errno set to indicate the cause of the error.
******************************************************************************/
char *strdup( const char *str )
{
	int len = strlen(str) + 1;
	char* newstr = (char*)malloc(len);
	if(str == NULL) return NULL;
	return strcpy(newstr, str);
}
/****************************************************************************** 
desc:       concatenate two strings

ret val:    a pointer to the resulting string dest.
******************************************************************************/
char *strcat(char *dest, const char *src)
{
	char *dest_t = dest;
	if(!src) return dest;
	while(*++dest);
	*dest++ = *src++;	
	strcpy(dest, src);
	return dest_t;	
}

char *strncat(char *dest, const char *src, size_t n)
{
	char *dest_t = dest;
	if(!src) return NULL;
	while(*++dest);
	*dest++ = *src++;	
	strncpy(dest, src, n - 1);
	return dest_t;	
}
/****************************************************************************** 
desc:       locate a substring

ret val:    a pointer to the beginning of the located substring,
            or NULL if the substring is not found.
******************************************************************************/
char *strstr(const char *haystack, const char *needle)
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
desc: get length of a prefix substring

ret val: returns the number of bytes in the initial segment of s which consist only of bytes from accept.
******************************************************************************/
static int is_in_str(char* str, char c)
{
	while(*str != c && *str != '\0' ) str++;
	return *str == '\0' ? 0 : 1;
}
size_t strspn(const char *str1, const char *str2)
{
	int seen = 0;
	while(*str1)
	{
		if(! is_in_str((char*)str2, *str1++))
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



