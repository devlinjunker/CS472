#include <stdio.h>
int main()
{
	char* str = "racecar";
	
	char* start = str;
	char* end = str + (7-1);

	while(start != end){
		if(*start != *end){
			return 0;
		}
		start++;
		end--;
	}

	return 1;
}


