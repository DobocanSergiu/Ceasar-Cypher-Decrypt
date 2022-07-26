#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
float chi_square_distance(float histogram1[30], float histogram2[30])
{
	float rez;
	int i;
	rez = 0;
	for (i = 0; i < 26; i++)
	{
		rez = rez + ((histogram2[i] - histogram1[i])* (histogram2[i] - histogram1[i])/histogram1[i]);
	}
	return rez;




}
void get_main_histogram(float histogram[30])
{
	int i;
	float j;
	FILE* fp = fopen("distribution.txt", "r");
	if (fp == NULL) {
		printf("Open failed");
		return 0;
	}
	int it = 0;
	char w[30];
	char percentage[30][30];
	while (!feof(fp)) {
		fscanf(fp, "%s", w);
		strcpy(percentage[it], w);
		it++;
	}
	for (i = 0; i < 26; i++)
	{
		j = atof(percentage[i]);
		histogram[i] = j;
	}
}

char *break_cypher()
{
	int i, j, rez_displacement;
	float main_histogram[30], min_chi_squared_distance, current_chi_squared_distance, total_letters, current_histogram[30];
	char  decypherd_message[99999],encripted_message[99999], c;
	FILE* fptr;
	if ((fptr = fopen("input.txt", "r")) == NULL) {
		printf("Error! File cannot be opened.");
		exit(1);
	}

	// reads text until newline is encountered
	fscanf(fptr, "%[^\n]", encripted_message);
	
	printf("%s", encripted_message);
	fclose(fptr);
	get_main_histogram(&main_histogram);
	for (i = 0; i < 26; i++)
	{
		strcpy(decypherd_message, encripted_message);
		for (j = 0; j < 26; j++)
		{
			current_histogram[j] = 0;
		}
		total_letters = 0;
		for (j = 0; j < strlen(decypherd_message); j++)
		{	

			if (decypherd_message[j] >= 97 && decypherd_message[j] <= 122)
			{
				total_letters++;
				decypherd_message[j] = decypherd_message[j] - (int)i;
				if (decypherd_message[j] < 97)
				{
					decypherd_message[j] = decypherd_message[j] + 122 - 97 + 1;
				}
				c = decypherd_message[j] - 32;
				current_histogram[c - 65]++;

			}
			else if (decypherd_message[j] >= 65 && decypherd_message[j] <= 90)
			{
				total_letters++;
				decypherd_message[j] = decypherd_message[j] - (int)i;
				if (decypherd_message[j] < 65)
				{
					decypherd_message[j] = decypherd_message[j] + 90 - 65 + 1;
				}
				c = decypherd_message[j];
				current_histogram[c - 65]++;


			}
		}
		for (j = 0; j < 26; j++)
		{
			current_histogram[j] = current_histogram[j] * 100 / total_letters;
		}
		if (i == 0)
		{
			rez_displacement = i;
			min_chi_squared_distance = chi_square_distance(main_histogram, current_histogram);
		}
		else
		{
			if (chi_square_distance(main_histogram, current_histogram) < min_chi_squared_distance)
			{
				rez_displacement = i;
				min_chi_squared_distance = chi_square_distance(main_histogram, current_histogram);

			}

		}

	}
	strcpy(decypherd_message, encripted_message);
	for (j = 0; j < strlen(decypherd_message); j++)
	{

		if (decypherd_message[j] >= 97 && decypherd_message[j] <= 122)
		{
			total_letters++;
			decypherd_message[j] = decypherd_message[j] - (int)rez_displacement;
			if (decypherd_message[j] < 97)
			{
				decypherd_message[j] = decypherd_message[j] + 122 - 97 + 1;
			}
			c = decypherd_message[j] - 32;
			current_histogram[c - 65]++;

		}
		else if (decypherd_message[j] >= 65 && decypherd_message[j] <= 90)
		{
			total_letters++;
			decypherd_message[j] = decypherd_message[j] - (int)rez_displacement;
			if (decypherd_message[j] < 65)
			{
				decypherd_message[j] = decypherd_message[j] + 90 - 65 + 1;
			}
			c = decypherd_message[j];
			current_histogram[c - 65]++;


		}
	}
	return decypherd_message;

}

/*EXAMPLE
INPUT:
Uf ime ftq nqef ar fuyqe, uf ime ftq iadef ar fuyqe, uf ime ftq msq ar iuepay, uf ime ftq msq ar raaxuetzqee, uf ime ftq qbaot ar nqxuqr, uf ime ftq qbaot ar uzodqpgxufk, uf ime ftq eqmeaz ar xustf, uf ime ftq eqmeaz ar pmdwzqee, uf ime ftq ebduzs ar tabq, uf ime ftq iuzfqd ar pqebmud.
Output:
It was the best of times, it was the worst of times, it was the age of wisdom, it was the age of foolishness, it was the epoch of belief, it was the epoch of incredulity, it was the season of light, it was the season of darkness, it was the spring of hope, it was the winter of despair.
*/

int main()
{
	char encripted_message[99999],*RESULT;
	printf("Ceasar Cypher Decryptor\n");
	printf("Author-Dobocan Sergiu\n");
	printf("By default this program decodes messages back to english,to change the language, the distribution.txt file must be edited with the respective values of the wanted language. Type your message in the input.txt file on a single line...\nENCRYPTED MESSAGE\n");
	///gets(encripted_message);
	RESULT=break_cypher();
	printf("\n----------------------------------------------------------\nDECRYPTED MESSAGE:\n");
	printf("%s", RESULT);

	return 0;
}

