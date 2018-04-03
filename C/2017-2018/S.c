#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#define max(x, y) (((x) > (y)) ? (x) : (y))

#define MAX 1000

int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		return 1;
	}

	FILE *fp;
	char c;
	char previous = '\n';
	int charCount[MAX];
	int digits = 0;
	int words = 0;
	int notEmptyLines = 0;
	int commentBlocks = 0;
	int graphCharsInLine = 0;
	char alwaysPrevious = 0;
	char previousPrevious = 0;
	bool didCommentPreviously = false;
	int numberOfGoodCharactersInLine = 0;

	for (int x = 0; x < MAX; x++)
	{
		charCount[x] = 0;
	}

	fp = fopen(argv[1], "r");

	if (fp == 0)
	{
		return 1;
	}

	while ((c = getc(fp)) != EOF)
	{
		c = tolower(c);
	//	printf("%c", c);

		if (alwaysPrevious == '/' && c == '*' && !didCommentPreviously)
		{
			
			if (commentBlocks == 0)
			{
				if (previousPrevious == '\n')
				{
			//		notEmptyLines--;
				}
			}

			numberOfGoodCharactersInLine--;
			didCommentPreviously = true;
			commentBlocks++;
			previous = previousPrevious;
			alwaysPrevious = c;

			continue;
		}

		if (commentBlocks == 0)
		{
			didCommentPreviously = false;

			if (isdigit(c))
			{
				digits++;
			}

			if (isalpha(c) && !isalpha(previous))
			{
				words++;
			}

			if (c == '\n')
			{
				if (numberOfGoodCharactersInLine > 0)
				{
					notEmptyLines++;
				}
				numberOfGoodCharactersInLine = 0;
			}

			if (isgraph(c))
			{
				numberOfGoodCharactersInLine++;
			}

			charCount[c]++;
			previousPrevious = previous;
			previous = c;
		}
		else
		{
			if (alwaysPrevious == '*' && c == '/' && !didCommentPreviously)
			{
				commentBlocks = max(commentBlocks - 1, 0);
				didCommentPreviously = true;		
			}
			else
			{
				didCommentPreviously = false;
			}
		}

	//	alwaysPreviousPrevious = alwaysPrevious;
		alwaysPrevious = c;
	}

	if (numberOfGoodCharactersInLine > 0)
	{
		notEmptyLines++;
	}

	fclose(fp);

	FILE *out = fopen(argv[2], "w");
	if (out == NULL)
	{
		//printf("chujnia");
		return 1;
	}

	for (int x = 'a'; x <= 'z'; x++)
	{
		fprintf(out, "%c : %d\n", toupper(x), charCount[x]);
	}

	fprintf(out, "Cyfr: %d\n", digits);
	fprintf(out, "Wyrazy: %d\n", words);
	fprintf(out, "Linie niepuste: %d\n", notEmptyLines);

	fclose(out);
	// getchar();
	// }
}