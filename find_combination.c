#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_NUMBERS 10000
#define BUFFER_SIZE 100
void find_combinations(float *numbers, int size, float target, float tolerance, FILE *out_file)
{
    float combination[MAX_NUMBERS];
    int i, j, k, bit, found = 0;

    for (i = 1; i < (1 << size); i++)
    {
        float sum = 0;
        int count = 0;

        for (j = 0; j < size; j++)
        {
            bit = 1 << j;
            if (i & bit)
            {
                sum += numbers[j];
                combination[count++] = numbers[j];
            }
        }

        if (fabs(sum - target) <= tolerance)
        {
            found = 1;
            fprintf(out_file, "Found combination: \n");
            for (k = 0; k < count; k++)
            {
                fprintf(out_file, "%.2f\t", combination[k]);
            }
            fprintf(out_file, "\nTotal sum: %.2f\n\n", sum);
        }
    }

    if (!found)
    {
        fprintf(out_file, "Unable to find any combination\n");
    }
}
void remove_commas(char *str)
{
    char *p = str;
    while (*str != '\0')
    {
        if (*str != ',')
        {
            *p++ = *str;
        }
        str++;
    }
    *p = '\0';
}

int main()
{
    FILE *file = fopen("data.txt", "r");
    FILE *out_file = fopen("result.txt", "w");
    float numbers[MAX_NUMBERS];
    int count = 0;
    float target, tolerance;
    int include_negatives;
    char buffer[BUFFER_SIZE];
    if (file == NULL || out_file == NULL)
    {
        printf("Unable to open file\n");
        return 1;
    }

    while (fgets(buffer, BUFFER_SIZE, file) != NULL && count < MAX_NUMBERS / 2)
    {
        remove_commas(buffer);
        numbers[count] = atof(buffer);
        count++;
    }
    fclose(file);

    printf("Include negative values?\n1. Yes\n2. No\n");
    scanf("%d", &include_negatives);

    if (include_negatives == 1)
    {
        for (int i = 0, j = count; i < count && j < MAX_NUMBERS; i++, j++)
        {
            numbers[j] = -numbers[i];
        }
        count *= 2;
    }

    printf("Enter a number:");
    scanf("%f", &target);

    printf("Select the precision level:\n1. Up to 1\n2. Up to 0.1\n3. Up to 0.01\n4. No tolerance\n");
    int choice;
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        tolerance = 1.0;
        break;
    case 2:
        tolerance = 0.1;
        break;
    case 3:
        tolerance = 0.01;
        break;
    case 4:
        tolerance = 0.00;
        break;
    default:
        tolerance = 0.00;
    }

    find_combinations(numbers, count, target, tolerance, out_file);
    fclose(out_file);

    return 0;
}
