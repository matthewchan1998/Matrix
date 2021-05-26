//  main.c
//
//  Created by Matthew Chan on 7/4/2018.
//  Copyright © 2018 Matthew Chan. All rights reserved.

#include <stdio.h>
#include <stdlib.h>

struct matrix
{
    char name;              //to hold the 1 character name of the matrix
    int mValues[10][10];    //to hold the values in the matrix, up to 10 rows x 10 columns
    int nrows;              //to hold the number of rows used in mValues
    int ncols;              //to hole the number of columns used in mValues
};

int clean_input(void);
void matrixInput(struct matrix *mat);
void matrixDisplay(struct matrix mat);
void matrixTranspose(struct matrix A, struct matrix *B);
void matrixDeterminant(struct matrix m1, struct matrix *m2, int * determinant);
void appMatrix(struct matrix m1, struct matrix *m2);

int main()
{
    int options, determinant, hold_f;   //Holds scanf return value
    char hold_c;                        //Holds last character from user input.
    struct matrix mat;                  //Name for the four matrix
    struct matrix transpose;
    struct matrix mat2x2;
    struct matrix add;
    
    matrixInput(&mat);      //To input the size and name of matrix, and read the values in the file
    matrixDisplay(mat);     //Display the matrix with its name and size
    
    //Gets input from user
    printf("\nPlease select one of the following option:\n(1)Transpose\n(2)2x2 Subset with determinant\n(3)Add rows or columns\n(4)EXIT\n");
    do{
        hold_f = scanf("%d%c", &options, &hold_c);   //Scans input from user
        while (hold_f !=2 || hold_c!='\n') {   //While scanf did not read 2 objects or the user inputed a number and then a character (eg. 12te)
            clean_input();
            printf("\nYou have typed non numeric characters.\n"
                   "Please select one of the following option:\n(1)Transpose\n(2)2x2 Subset with determinant\n(3)Add rows or columns\n(4)EXIT\n");
            hold_f = scanf("%d%c", &options, &hold_c);
        }
        if(options<=0 || options>4) {    //Set the range for options
            printf("\nInvalid options\n"
                   "Please select one of the following option:\n(1)Transpose\n(2)2x2 Subset with determinant\n(3)Add rows or columns\n(4)EXIT\n");
        } else {     //If user typed in correctly, do the switch cases.
            switch(options)
            {
                case 1:
                    printf("\nFinding the transpose of matrix...\n");
                    matrixTranspose(mat, &transpose);
                    matrixDisplay(transpose);
                    printf("\nStarting new matrix...\n");
                    return main();
                case 2:
                    printf("\nFinding the 2x2 subset and determinant...\n");
                    if (mat.nrows==1 && mat.ncols==1)  //When row and column equal to 1
                    {
                        matrixDeterminant(mat, &mat2x2, &determinant);
                        printf("\nThis is a 1x1 matrix and the determinant is %d.\nStarting new matrix...\n",determinant);
                        main();  //return to main
                    }
                    else if (mat.nrows==1 || mat.ncols==1)  //When either row or column equal to 1
                    {
                        matrixDeterminant(mat, &mat2x2, &determinant);
                        printf("\nThere's no subset as original matrix has rows/columns equal to 1.\nStarting new matrix...\n");
                        main();  //return to main
                    }
                    else if (mat.nrows==2 && mat.ncols==2)  //When row and column equal to 2
                    {
                        matrixDeterminant(mat, &mat2x2, &determinant);
                        printf("\nThis is already a 2x2 matrix and the determinant is %d.\nStarting new matrix...\n",determinant);
                        main();  //return to main
                    }
                    else
                    {
                        matrixDeterminant(mat, &mat2x2, &determinant);
                        matrixDisplay(mat2x2);
                        printf("The determinant is:%d\n",determinant);
                        printf("\nStarting new matrix...\n");
                        return main();
                    }
                case 3:
                    if (mat.nrows==10 || mat.ncols==10) {       //Max row/columns detected
                        printf("\nThe matrix already has max no. of rows/columns, starting new matrix...\n");
                        return main();
                    }
                    else
                    {
                        printf("\nAdding rows/columns to matrix...\n");
                        appMatrix(mat, &add);
                        printf("\nStarting new matrix...\n");
                        return main();
                    }
                case 4:
                    printf("Terminating...\n");
                    exit(0);
            }
        }
    }while(1);
}

int clean_input(void) {     //Clear the invalid input
    while (getchar()!='\n');
    return 1;
}

void matrixInput(struct matrix *mat)
{
    int r, c, hold_f; //Holds scanf return value
    char hold_c;      //Holds last character from user input.
    
    do{
        printf("Please enter a CAPITAL letter for the name of matrix:");    //Gets input from user
    } while (((scanf("%[A-Z]%c", &mat->name, &hold_c)!=2 || hold_c!='\n') && clean_input()));    //Scanf for A-Z only and did not read 2 objects
    
    printf("\nPlease enter number of Rows of matrix(1-10):");   //Gets input from user
    do{
        hold_f = scanf("%d%c", &r, &hold_c);   //Scans input from user
        while (hold_f !=2 || hold_c!='\n') {   //While scanf did not read 2 objects or the user inputed a number and then a character (eg. 12te)
            clean_input();
            printf("\nYou have typed non numeric characters.\n"
                   "Please enter number of Rows of matrix(1-10):");    //Ask user to type a valid value
            hold_f = scanf("%d%c", &r, &hold_c);
        }
        if(r<=0 || r>10) {    //Set the range for rows as required
            printf("\nInvalid number of Rows\n"
                   "Please enter number of Rows of matrix(1-10):");
        } else {     //If user typed in correctly, exit do-while.
            mat->nrows = r;     //Assign number of rows
            break;
        }
    }while(1);
    
    printf("\nPlease enter number of Columns of matrix(1-10):");    //Gets input from user
    do{
        hold_f = scanf("%d%c", &c, &hold_c);   //Scans input from user
        while (hold_f !=2 || hold_c!='\n') {   //While scanf did not read 2 objects or the user inputed a number and then a character (eg. 12te)
            clean_input();
            printf("\nYou have typed non numeric characters.\n"
                   "Please enter number of Columns of matrix(1-10):");    //Ask user to type a valid value
            hold_f = scanf("%d%c", &c, &hold_c);
        }
        if(c<=0 || c>10) {    //Set the range for columns as required
            printf("\nInvalid number of Columns\n"
                   "Please enter number of Columns of matrix(1-10):");
        } else {     //If user typed in correctly, exit do-while.
            mat->ncols = c;     //Assign number of columns
            break;
        }
    }while(1);
    
    FILE *fin;      //Open file
    fin=fopen("matrix1.txt","r");
    if (fin == NULL) {
        printf("Oops, this file doesn't exist!\n");
        exit(0);    //Exit if file could not be found
    }
    else {
        printf("\nPopulating matrix... ");
        for(r = 0; r < 10; r++)
        {
            for(c = 0; c < 10; c++)
            {
                fscanf(fin,"%d",&mat->mValues[r][c]);   //Read the values in the file and assign to rows and columns
            }
        }
        printf("\n");
    }
}

void matrixDisplay(struct matrix mat)
{
    int r, c;
    printf("\nYour matrix %c has populated with %d rows and %d columns. Values are:\n",mat.name,mat.nrows,mat.ncols);
    for(r = 0; r < mat.nrows; r++)
    {
        for(c = 0; c < mat.ncols; c++)
        {
            printf("%d\t", mat.mValues[r][c]);  //Print out the matrix
        }
        printf("\n");
    }
}

void matrixTranspose(struct matrix A, struct matrix *B)
{
    int r, c;
    char hold_c;   //Holds last character from user input.
    do{
        printf("\nPlease enter a CAPITAL letter for the name of transpose matrix:");    //Gets input from user
        
    } while (((scanf("%[A-Z]%c", &B->name, &hold_c)!=2 || hold_c!='\n') && clean_input()));    //Scanf for A-Z only and did not read 2 objects
    B->nrows = A.ncols;     //New matrix has rows equal to original matrix's columns
    B->ncols = A.nrows;     //New matrix has columns equal to original matrix's rows
    for (r = 0; r < A.nrows; r++)
    {
        for (c = 0; c < A.ncols; c++)
        {
            B->mValues[c][r]= A.mValues[r][c];   //Assign the values for transpose
        }
    }
    return;
}

void matrixDeterminant(struct matrix m1, struct matrix *m2, int *determinant)
{
    int r, c, hold_f; //Holds scanf return value
    char hold_c;   //Holds last character from user input.
    
    if (m1.nrows==1 && m1.ncols==1)         //When row and column equal to 1
    {
        *determinant = m1.mValues[0][0];
    }
    else if (m1.nrows==1 || m1.ncols==1)    //When either row or column equal to 1
    {
        return;
    }
    else if (m1.nrows==2 && m1.ncols==2)    //When row and column equal to 2
    {
        *determinant = (m1.mValues[0][0])*(m1.mValues[1][1])-(m1.mValues[0][1])*(m1.mValues[1][0]);
    }
    else
    {
        do{
            printf("Please enter a CAPITAL letter for the name of 2x2 subset matrix:");    //Gets input from user
            
        } while (((scanf("%[A-Z]%c", &m2->name, &hold_c)!=2 || hold_c!='\n') && clean_input()));    //Scanf for A-Z only and did not read 2 objects
        
        printf("\nPlease chose the row number of the original matrix(1-%d rows):",(m1.nrows-1));
        do{
            hold_f = scanf("%d%c", &r, &hold_c);   //Gets input from user
            while (hold_f !=2 || hold_c!='\n') {   //While scanf did not read 2 objects or the user inputed a number and then a character (eg. 12te)
                clean_input();
                printf("\nYou have typed non numeric characters.\n"
                       "Please chose the row number of the original matrix(1-%d rows):",(m1.nrows-1));    //Ask user to type a valid value
                hold_f = scanf("%d%c", &r, &hold_c);
            }
            if(r<=0 || r>m1.nrows-1) {    //Set the range for rows as required
                printf("\nInvalid number of Rows\n"
                       "Please chose the row number of the original matrix(1-%d rows):",(m1.nrows-1));    //Ask user to type a valid value
            } else {     //If user typed in correctly, assign the no. of rows to 2
                m2->nrows = 2;
                break;
            }
        }while(1);
        
        printf("\nPlease chose the column number of the original matrix(1-%d cols):",(m1.ncols-1));
        do{
            hold_f = scanf("%d%c", &c, &hold_c);   //Gets input from user
            while (hold_f !=2 || hold_c!='\n') {   //While scanf did not read 2 objects or the user inputed a number and then a character (eg. 12te)
                clean_input();
                printf("\nYou have typed non numeric characters.\n"
                       "Please chose the column number of the original matrix(1-%d cols):",(m1.ncols-1));   //Ask user to type a valid value
                hold_f = scanf("%d%c", &c, &hold_c);
            }
            if(c<=0 || c>m1.ncols-1) {    //Set the range for columns as required
                printf("\nInvalid number of Columns\n"
                       "Please chose the column number of the original matrix(1-%d cols):",(m1.ncols-1));   //Ask user to type a valid value
                
            } else {     //If user typed in correctly, assign the no. of columns to 2
                m2->ncols = 2;
                break;
            }
        }while(1);
        
        printf("\nYou have choosen %c[%d][%d], finding 2x2 subset...\n",m1.name,r,c);
        m2->mValues[0][0] = m1.mValues[r-1][c-1];
        m2->mValues[0][1] = m1.mValues[r-1][c];
        m2->mValues[1][0] = m1.mValues[r][c-1];
        m2->mValues[1][1] = m1.mValues[r][c];
        *determinant = (m2->mValues[0][0])*(m2->mValues[1][1])-(m2->mValues[0][1])*(m2->mValues[1][0]);
    }
}

void appMatrix(struct matrix m1, struct matrix *m2)
{
    int r, c, hold_f, new_r, new_c;     //Holds scanf return value, new columns and rows
    char hold_c;   //Holds last character from user input
    FILE *fin;
    fin=fopen("/Users/Matthew/Google Drive/Sheffield/Learning/ACS130 Intro to System Engin and Software/Assignment 4/Assignment 4/matrix1.txt","r");
    if (fin == NULL) {
        printf("Oops, this file doesn't exist!\n");
        exit(0);
    }
    {
        printf("Please enter a CAPITAL letter for the name of the new matrix:");    //Gets input from user
        
    } while (((scanf("%[A-Z]%c", &m2->name, &hold_c)!=2 || hold_c!='\n') && clean_input()));    //Scanf for A-Z only and did not read 2 objects
    
    printf("\nPlease enter how many number of rows to add(0-%d rows):",(10-m1.nrows));
    do{
        hold_f = scanf("%d%c", &new_r, &hold_c);   //Gets input from user
        while (hold_f !=2 || hold_c!='\n') {   //While scanf did not read 2 objects or the user inputed a number and then a character (eg. 12te)
            clean_input();
            printf("\nYou have typed non numeric characters.\n"
                   "Please enter how many number of rows to add(0-%d rows):",(10-m1.nrows));    //Ask user to type a valid value
            hold_f = scanf("%d%c", &new_r, &hold_c);
        }
        if(new_r<0 || new_r>(11-m1.nrows)) {    //Set the range for rows as required
            printf("\nInvalid number of Rows\n"
                   "Please enter how many number of rows to add(0-%d rows):",(10-m1.nrows));    //Ask user to type a valid value
        } else {     //If user typed in correctly, scan values in file to new rows
            m2->nrows = m1.nrows + new_r;
            for (r=0; r<m2->nrows; r++)
            {
                for (c=0; c<m1.ncols; c++)
                {
                    if (r >= m1.nrows)      //Only input values after the last row of the original matrix
                    {
                        fscanf(fin, "%d", &m2->mValues[r][c]);
                    }
                }
            }
            break;
        }
    }while(1);
    
    printf("\nPlease enter how many number of columns to add(0-%d cols):",(10-m1.ncols));
    do{
        hold_f = scanf("%d%c", &new_c, &hold_c);   //Gets input from user
        while (hold_f !=2 || hold_c!='\n') {   //While scanf did not read 2 objects or the user inputed a number and then a character (eg. 12te)
            clean_input();
            printf("\nYou have typed non numeric characters.\n"
                   "Please enter how many number of columnss to add(0-%d cols):",(10-m1.ncols));   // ask user to type a valid value
            hold_f = scanf("%d%c", &new_c, &hold_c);
        }
        if(new_c<0 || new_c>(11-m1.ncols)) {    //Set the range for columns as required
            printf("\nInvalid number of Columns\n"
                   "Please enter how many number of columnss to add(0-%d cols):",(10-m1.ncols));   // ask user to type a valid value
            
        } else {     //If user typed in correctly,scan values in file to columns
            m2->ncols = m1.ncols + new_c;
            for (r=0; r<m1.nrows; r++)
            {
                for (c=0; c<m2->ncols; c++)
                {
                    if (c >= m1.ncols)      //Only input values after the last column of the original matrix
                    {
                        fscanf(fin, "%d", &m2->mValues[r][c]);
                    }
                }
            }
            break;
        }
    }while(1);
    fclose(fin);  //Close file
    
    for (r=0; r<m2->nrows; r++)
    {
        for (c=0; c<m2->ncols; c++)
        {
            m2->mValues[r][c] = m1.mValues[r][c];
        }
    }
    return;
}
