/** 
 *@file FileSystem 
 *@description Reading infos from csv file and exporting some calculations into a new txt file.
 *@assignment 2
 *@date 25/12/2022
 *@author Ahmed Muaz Atik - ahmedmuaz.atik@stu.fsm.edu.tr
 */
 
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

//Creating enum
typedef enum
{
	Irissetosa = 1,
	Irisversicolor = 2,
	Irisvirginica = 3,
}

species;

//Creating structure
typedef struct IrisDataType
{
	float sepalLengthCm;
	float sepalWidthCm;
	float petalLengthCm;
	float petalWidthCm;
	species specy;

}

IrisDataType;

//Calculates mean of the vector
float mean(float *vec, int size)
{
	float avg = 0;

	int i;

	//Summing up all of the values
	for (i = 0; i < size; i++)
	{
		avg += vec[i];
	}

	//Calculating average
	avg /= size;

	return avg;
}

//Calculates covariance of two vector
float covariance(float *vec1, float *vec2, int size)
{
	float sum = 0;

	int i;

	//Finds sum according to the formula
	for (i = 0; i < size; i++)
	{
		sum = sum + (vec1[i] - mean(vec1, size)) *(vec2[i] - mean(vec2, size));
	}

	return sum / (size - 1);
}

//Returns matrix
float **returnMatrix(int row, int col)
{
	//Creating rows dynamically
	float **matrix = (float **) malloc(sizeof(float*) *row);
	int i;

	//Creating columns dynamically
	for (i = 0; i < row; i++)
	{
		matrix[i] = (float*) malloc(sizeof(float) *col);
	}

	return matrix;
}

//Calculates transpose of the matrix
float **matrixTranspose(float **mat, int row, int col)
{
	//Creating a matrix dynamically that will gonna use at returning
	float **transpose = (float **) malloc(sizeof(float*) *col);

	int i;

	//Creating columns dynamically
	for (i = 0; i < row; i++)
	{
		transpose[i] = (float*) malloc(sizeof(float) *col);
	}

	int j;
	int k;

	//Using transpose formula
	for (j = 0; j < row; j++)
	{
		for (k = 0; k < col; k++)
		{
			transpose[j][k] = mat[j][k];
		}
	}

	return transpose;
}

//Calculates variance of the vector
float variance(float *vec, int size)
{
	float sum = 0;

	int i;

	//Finds sum value according to the variance function
	for (i = 0; i < size; i++)
	{
		sum = sum + (vec[i] - mean(vec, size)) *(vec[i] - mean(vec, size));
	}

	return sum / (size - 1);
}

//Calculates correlation of two vector
float correlation(float *vec, float *vec2, int size)
{
	//Using correlation formula
	float correlation = covariance(vec, vec2, size) /
		(sqrt(covariance(vec, vec, size)) *sqrt(covariance(vec2, vec2, size)));

	return correlation;
}

//Calculates covariance matrix of the matrix
float **covarianceMatrix(float **mat, int row, int col)
{
	//Creating a matrix that will gonna use at returning
	float **covariance_matrix = returnMatrix(row, col);

	//Creating a transpose matrix
	float **transpose = matrixTranspose(mat, row, col);

	int i;
	int j;

	//Finding covariance matrix according to the formula
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			covariance_matrix[i][j] = covariance(transpose[i], transpose[i], col);
		}
	}

	return covariance_matrix;
}

int main()
{
	//Defining variables
	species s;
	char *index;
	int row = 0;
	int temp = 0;

	char buffer[1024];

	//Creating a new file
	FILE * fp;

	//Opening file as a read
	fp = fopen("C:/Users/ahmed/Desktop/FileSystem/Iris.csv", "r");

	//Getting first value of the file
	index = fgets(buffer, 1024, fp);

	//Creating a 2D structure matrix dynamically
	IrisDataType *arr = (IrisDataType*) malloc(sizeof(IrisDataType) *(atoi(index) + 2));

	//Creating a float matrix dynamically
	float **newArr = (float **) malloc(150* sizeof(float*));

	int m;

	//Creating columns dynamically
	for (m = 0; m < 150; m++)
	{
		newArr[m] = (float*) malloc(4* sizeof(float*));
	}

	//If file not exists
	if (!fp)
	{
		printf("Can't open file\n");
	}

	//If file exists
	else
	{
		while (fgets(buffer,
				1024, fp))
		{
			row++;

			//Skipping titles
			if (row == 1)
			{
				continue;
			}

			//Separating the string about "," sign
			char *value = strtok(buffer, ", ");

			temp = 0;

			while (value)
			{
				value = strtok(NULL, ", ");

				if (value != NULL)
				{
					//Assigning values into arrays
					switch (temp)
					{
						case 0:
							arr[row].sepalLengthCm = atof(value);
							break;
						case 1:
							arr[row].sepalWidthCm = atof(value);
							break;
						case 2:
							arr[row].petalLengthCm = atof(value);
							break;
						case 3:
							arr[row].petalWidthCm = atof(value);
							break;
						case 4:
							
							//Comparing strings
							if (strcmp(value, "Iris-setosa\n") == 0)
							{
								s = Irissetosa;
								arr[row].specy = s;
							}
							else if (strcmp(value, "Iris-versicolor\n") == 0)
							{
								s = Irisversicolor;
								arr[row].specy = s;
							}
							else if (strcmp(value, "Iris-virginica\n") == 0)
							{
								s = Irisvirginica;
								arr[row].specy = s;
							}

							printf("%d", s);

							break;
						default:
							break;
					}

					temp++;
				}
			}
		}

		int counter = 0;
		int i, l;

		//Assigning values into newArr
		for (i = 2; i < atoi(index) + 2; i++)
		{
			for (l = 0; l < 4; l++)
			{
				newArr[counter][l] = arr[i].sepalLengthCm;
				l++;
				newArr[counter][l] = arr[i].sepalWidthCm;
				l++;
				newArr[counter][l] = arr[i].petalLengthCm;
				l++;
				newArr[counter][l] = arr[i].petalWidthCm;
				break;
			}

			counter++;
		}

		//Defining float arrays
		float sepalLength[150];
		float sepalWidth[150];
		float petalLength[150];
		float petalWidth[150];

		int z;
		int x;

		//Assigning values from newArr to arrays that already defined above
		for (z = 0; z < 150; z++)
		{
			sepalLength[z] = newArr[z][0];
			sepalWidth[z] = newArr[z][1];
			petalLength[z] = newArr[z][2];
			petalWidth[z] = newArr[z][3];
		}

		//Creating a new file
		FILE * newfp;

		//Opening file as a write
		newfp = fopen("IrisStatistic.txt", "w+");

		//If file not exists
		if (newfp == NULL)
		{
			printf("File couldn't be opened\n");
			exit(1);
		}

		//Defining variables
		char title[] = "\t\tSepalLength,SepalWidth,PetalLength,PetalWidth,SL&SW,SW&PL,PL&PW\n";
		char temp_means[200];
		char temp_variance[200];
		char temp_correlation[200];
		char temp_covariance[5000];
		char means[200];
		char variances[200];
		char correlations[200];
		char covariances[5000];

		//Putting title into the file
		fputs(title, newfp);

		//Converting float to the string
		gcvt(mean(sepalLength, 150), 7, temp_means);
		//Assigning values into the char array
		strcat(means, "MEAN\t\t");
		strcat(means, temp_means);
		strcat(means, ",");

		gcvt(mean(sepalWidth, 150), 7, temp_means);
		strcat(means, temp_means);
		strcat(means, ",");

		gcvt(mean(petalLength, 150), 7, temp_means);
		strcat(means, temp_means);
		strcat(means, ",");

		gcvt(mean(petalWidth, 150), 7, temp_means);
		strcat(means, temp_means);
		strcat(means, "\n");

		//Converting float to the string
		gcvt(variance(sepalLength, 150), 7, temp_variance);
		//Assigning values into the char array
		strcat(variances, "VARIANCE\t");
		strcat(variances, temp_variance);
		strcat(variances, ",");

		gcvt(variance(sepalWidth, 150), 7, temp_variance);
		strcat(variances, temp_variance);
		strcat(variances, ",");

		gcvt(variance(petalLength, 150), 7, temp_variance);
		strcat(variances, temp_variance);
		strcat(variances, ",");

		gcvt(variance(petalWidth, 150), 7, temp_variance);
		strcat(variances, temp_variance);
		strcat(variances, "\n");

		//Converting float to the string
		gcvt(correlation(sepalLength, sepalWidth, 150), 7, temp_correlation);
		//Assigning values into the char array
		strcat(correlations, "CORRELATION\t\t\t\t\t\t");
		strcat(correlations, temp_correlation);
		strcat(correlations, ",");

		gcvt(correlation(sepalWidth, petalLength, 150), 7, temp_correlation);
		strcat(correlations, temp_correlation);
		strcat(correlations, ",");

		gcvt(correlation(petalLength, petalWidth, 150), 7, temp_correlation);
		strcat(correlations, temp_correlation);
		strcat(correlations, "\n");

		//Assigning value into the char array
		strcat(covariances, "COVARIANCE");

		//Assigning covariance matrix of the newArr to the newMatrix
		float **newMatrix = covarianceMatrix(newArr, 150, 4);

		for (x = 0; x < 150; x++)
		{
			strcat(covariances, "\t\t");
			for (z = 0; z < 4; z++)
			{
				//Converting float to the string
				gcvt(newMatrix[x][z], 7, temp_covariance);
				//Assigning values into the char array
				strcat(covariances, temp_covariance);
				strcat(covariances, "  ");
			}

			strcat(covariances, "\n");
		}

		//Putting values into the file
		fputs(means, newfp);
		fputs(variances, newfp);
		fputs(correlations, newfp);
		fputs(covariances, newfp);

		//Closing both files
		fclose(newfp);
		fclose(fp);
	}

	return 0;
}
