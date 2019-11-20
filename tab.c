#include <stdio.h>
#include <string.h>   /* for all the new-fangled string functions */
#include <stdlib.h>     /* malloc, free, rand */



int Fsize=50; /*maximum formula length*/
int inputs =20;/* number of formulas expected in input.txt*/
int i;/* in case you need it */
int ThSize=100;/* maximum size of set of formulas*/
int TabSize=500; /*maximum length of tableau queue*/

int i;
int j;

int splitCounter;



//Delete the outmost braces if it exist, to help function 'isPropositional()' run properly
char* deleteOuterBrace(char *g)
{
  //Create new variable with same value to avoid changing in original value
  char* temp = strdup(g);

  char scanner=*temp;
  
  if(scanner=='('&& *(temp+strlen(temp)-1) ==')' )
  {

    int braceStack=1;

    for (int i = 1; i <strlen(temp); i++)
    {

      scanner=*(temp+i);

      if (scanner=='(')
      {
        braceStack++;
      }else if (scanner==')')
      {
        if (braceStack==0)
        {
          return temp;
        }
        braceStack--;
      }

    }

    if(braceStack==0)
    {
        temp++;
        *(temp+strlen(temp)-1)='\0';
    }

  }

  return temp;

}

//Return location of middle operator(Which is the binary operator)
int getMiddleOperator(char* g)
{
  //Use braceStack to find the middle operator
  int braceStack;
  for (int i = 0; i <=strlen(g); i++)
  {
    if (*(g+i)=='(')
    {
      braceStack++;
    }
    if (*(g+i)==')')
    {
      if (braceStack==0)
      {
        //Invalid formula, visualize it
        char* temp=strdup(g);
        *(temp+i)='\0';
        printf("%s\033[0;31m)\033[0m",temp);
        return 0;
      }
      braceStack--;
    }


    char g_now=*(g+i);

    if (braceStack==0)
    {
      if (g_now=='^'||g_now=='v'||g_now=='>')
      {
        return i;
      }
    }
  }
  return 0;
}

// //Find number of operator(Excluded from negation), if number > 0 && isPropositional then it is binary
// int isBinary(char *g){
//   char* temp = strdup(deleteOuterBrace(g));
//   if (getMiddleOperator(temp)!=0)
//   {
//     return 1;
//   }
//   return 0;
// }

//put all your functions here.  You will need
int isPropositional(char *g,int counter)
{
  char* temp = strdup(g);

  //Detect outer braces
  while (*temp=='-')
  {
    temp++;
  }
  
  // if(strlen(temp)>2)
  // {
  //   if (*temp!='('|| *(temp+strlen(temp)-1)!=')')
  //   {
  //     printf("\033[0;31m(\033[0m%s\033[0;31m)\033[0m\n",g);
  //     return 0;
  //   }
  // }

  temp=deleteOuterBrace(temp);

  //Visualize the data for test
  char* align; 
  align=(char*)malloc(counter*sizeof(char)); 
 
  for (size_t j = 0; j <= counter; j++)
  {    
    *(align+j)='=';
    if (j==counter)
    {
      *(align+j+1)='\0';
    }
  }
  // printf("%d%s%s\n",counter,align,temp); 

  if(strlen(temp)<=2)
  {
    if(strcmp(temp,"-p")==1||strcmp(temp,"-q")==1||strcmp(temp,"-r")==1||strcmp(temp,"p")==1||strcmp(temp,"q")==1||strcmp(temp,"r")==1)
    {
      return 1;
    }
    // printf("\033[0;31m%s\033[0m\n",g);
    return 0;
  }

  int midPoint=getMiddleOperator(temp);
  if (midPoint==0)
  {
    return 0;
  }

  //Split to two sub-formula
  *(temp+midPoint)='\0';
  int leftFormula = isPropositional(temp,counter+1);
  int rightFormula = isPropositional(temp+midPoint+1,counter+1);
  return (leftFormula && rightFormula);

}

int isNegation(char *g){
    if (*g=='-')
    {
      return isPropositional(g+1,0);
    }
    return 0;
}

int parse(char *g) {

  if(strlen(g)<3)
  {
    if(strcmp(g,"p")==1||strcmp(g,"q")==1||strcmp(g,"r")==1)
    {
      // printf("It is a proposition\n");
      return 1;
    }
    if(strcmp(g,"-p")==1||strcmp(g,"-q")==1||strcmp(g,"-r")==1)
    {
      // printf("It is Negation");
      return 2;
    }
  }

  if(isNegation(g)==1)
  {
    // printf("It is Negation");
    return 2;
  }

  //If formula is proposition && not in above situation(No operator), then it is binary
  if (isPropositional(g,0)==1)
  {
      // printf("It is Binary");
      return 3;
  }

  // printf("It is a not a formula\n");
  return 0;
}
  
/*which returns 1 if a proposition, 2 if neg, 3 if binary, ow 0
Of course you will almost certainly need other functions.*/


//For binary formulas you will also need functions that return the first part and the second part of the binary formula.

char *partone(char *g)
{
  char* temp=deleteOuterBrace(strdup(g));
  int midPoint=getMiddleOperator(temp);

  //Split to two sub-formula
  *(temp+midPoint)='\0';

  return temp;
}

char *parttwo(char *g)
{
  char* temp=deleteOuterBrace(strdup(g));
  int midPoint=getMiddleOperator(temp);

  return (temp+midPoint+1);
}


int arrayLength_2D(char** array) 
{
  int length=0;
  while(array[length]!="\0")
  {
      length++;
  }
  return length;
}

int arrayLength_2D_Int(int** array) 
{
  int length=0;
  while(array[length][0]!=-1)
  {
      length++;
  }
  return length;
}
 
int arrayLength(char* array) 
{
  int length=0;
  while(array[length]!='\0')
  {
      length++;
  }
  return length;
}

int arrayLength_Int(int* array) 
{
  int length=0;
  while(array[length]!=-1)
  {
      length++;
  }
  return length;
}


int countFromHead(char* input, char symbol)
{
  char* output = strdup(input);
  int counter = 0;
  for (size_t i = 0; i < arrayLength(input); i++)
  {
    if (input[i]==symbol)
    {
      counter++;
    }
  }
  return counter;
}

int isContradiction(char* input_1, char* input_2){
  
  //Delete * from head
  input_1 = countFromHead(input_1, '*') +input_1;
  input_2 = countFromHead(input_2, '*') +input_2;

  if(input_1[0] == '-')
  {
    if(strcmp(input_1+1, input_2) == 0)
    {
      return 1;
    }
  }
  if (input_2[0] == '-')
  {
    if(strcmp(input_1, input_2+1) == 0)
    {
      return 1;
    }
  }
  return 0;

}

int closed(char** tableau) {

  int numberOfPaths = 1;
  int numberOfClosedPaths = 0;
  int** stringStack = (int**) malloc((100)*sizeof(int*));
  for (size_t i = 0; i < 100; i++)
  {
    stringStack[i] = (int*) malloc((100)*sizeof(int));
    for (size_t j = 0; j < 100; j++)
    {
      stringStack[i][j] = -1;
    }
  }
  int currentStackIndex=0;
  int numberOfstars;
  for (size_t i = 0; i < arrayLength_2D(tableau); i++)
  {
      numberOfstars = countFromHead(tableau[i],'*');
      printf("\nCurrentLevel: %d      NextLevel: %d", currentStackIndex, numberOfstars);

      if (numberOfstars!=0)
      {
        if (numberOfstars < currentStackIndex)  //Backtraking(When walk to the end of path)
        {
          
          numberOfPaths++;
          currentStackIndex = numberOfstars;

          for (size_t j = 0; j < arrayLength_Int(stringStack[currentStackIndex]); j++)  
          {
            stringStack[currentStackIndex][j] =  stringStack[currentStackIndex-1][j];
          }

          int arrLength = arrayLength_Int(stringStack[currentStackIndex]);
          stringStack[currentStackIndex][arrLength] = i;
          stringStack[currentStackIndex][1+arrLength] = -1;

          for (size_t j = 0; j < arrayLength_Int(stringStack[currentStackIndex]); j++)  //Check if the tableau closed at this stage
          {
            for (size_t k = 0; k < arrayLength_Int(stringStack[currentStackIndex]); k++)
            {
              if (isContradiction(tableau[stringStack[currentStackIndex][j]] , tableau[stringStack[currentStackIndex][k]] ) == 1 )  //Return closed if find contradiction
              {
                numberOfClosedPaths++;
                goto next_1;
              }
            }
          }
          next_1:
          ;
        }
        else if (numberOfstars == currentStackIndex)   
        {

          numberOfPaths++;
          for (size_t j = 0; j < arrayLength_Int(stringStack[currentStackIndex]); j++)  
          {
            stringStack[currentStackIndex][j] =  stringStack[currentStackIndex-1][j];
          }

          int arrLength = arrayLength_Int(stringStack[currentStackIndex]);
          stringStack[currentStackIndex][arrLength] = i;
          stringStack[currentStackIndex][1+arrLength] = -1;

          for (size_t j = 0; j < arrayLength_Int(stringStack[currentStackIndex]); j++)  //Check if the tableau closed at this stage
          {
            for (size_t k = 0; k < arrayLength_Int(stringStack[currentStackIndex]); k++)
            {
              if (isContradiction(tableau[stringStack[currentStackIndex][j]] , tableau[stringStack[currentStackIndex][k]] ) == 1 )  //Return closed if find contradiction
              {
                numberOfClosedPaths++;
                goto next_2;
              }
            }
          }
          next_2:
          ;
        }
        else
        {
          currentStackIndex++;
          int arrSize = arrayLength_Int(stringStack[currentStackIndex]);
          for (int m = 0; m < arrSize ; m++)
          {
            stringStack[currentStackIndex][m] = -1;
          }
          

          for (size_t j = 0; j < arrayLength_Int(stringStack[currentStackIndex-1]); j++)  
          {
            stringStack[currentStackIndex][j] =  stringStack[currentStackIndex-1][j];
          }
          stringStack[currentStackIndex][arrayLength_Int(stringStack[currentStackIndex])] = -1;
          
        }

        int arrLength = arrayLength_Int(stringStack[currentStackIndex]);
        stringStack[currentStackIndex][arrLength] = i;
        stringStack[currentStackIndex][1+arrLength] = -1;
      }

      else
      {
          int arrLength = arrayLength_Int(stringStack[currentStackIndex]);
          stringStack[currentStackIndex][arrLength] = i;
          stringStack[currentStackIndex][1+arrLength] = -1;
      }

      outerloop:
      {
        for (size_t j = 0; j < arrayLength_Int(stringStack[currentStackIndex]); j++)  //Check if the tableau closed at this stage
        {
          for (size_t k = 0; k < arrayLength_Int(stringStack[currentStackIndex]); k++)
          {
            if (isContradiction(tableau[stringStack[currentStackIndex][j]] , tableau[stringStack[currentStackIndex][k]] ) == 1 )  //Return closed if find contradiction
            {
              numberOfClosedPaths++;
              goto next_3;
            }
          }
        }
      }

      next_3:
      

          for (size_t j = 0; j < arrayLength_Int(stringStack[currentStackIndex]); j++)
          {
            printf("\nLevel: %i      String: %s", currentStackIndex, tableau[stringStack[currentStackIndex][j]]);
          }
           printf("\n");
         
  }


  if (numberOfPaths <= numberOfClosedPaths)
  {
    printf("\nTableau closed, formula not satisfiable. numberOfPaths:%d    numberOfClosedPaths:%d   ",numberOfPaths, numberOfClosedPaths);
    return 1;
  }
  
  printf("\nTableau not closed, formula satisfiable.");
  return 0;
  

}


char* simplifyNegation(char* input)
{
  int sumOfNegation=0;
  for (size_t i = 0; input[i]=='-' ; i++)
  {
    sumOfNegation++;
  }
  if(sumOfNegation%2 != 0)
  {
    return input + sumOfNegation - 1; //Return string start with -
  }
  return input + sumOfNegation;     //Return string start without -
}

char* addAtHead(char* input, char symbol, int amount)
{
  char* output = (char*) malloc((arrayLength(input)+amount)*sizeof(char));
  for (size_t i = 0; i < amount; i++)
  {
      *(output+i)=symbol;
  }
  strcpy(output+amount,input);
  return output;
}

int printTableau(char** tab)
{

  for(size_t i=0; i <arrayLength_2D(tab);i++) {
    printf("\n\033[0;31mTableau: ######### %s #########\033[0m", tab[i]);
  }
  printf("\n", tab[i]);

}

char** constructTableau(char** input, int index, int counter){

    int arrLength = arrayLength_2D(input);

    char* string;

    for (size_t i = 0; i < arrayLength(input[index]); i++)
    {
      if (input[index][i]!='*')
      {
        string = simplifyNegation( strdup(input[index]+i) );
        break;
      }
    }

    char binaryOp;    
    char* L_Part;
    char* R_Part;
    char* New_L_Part;
    char* New_R_Part;
    if(string[0]=='-')
    {
      if(parse(string+1)!=3) 
      {
        return input;
      }
      char* temp = deleteOuterBrace(string+1);
      binaryOp = temp[getMiddleOperator(temp)];    
      L_Part = partone(temp);
      R_Part = parttwo(temp);
      if (binaryOp=='^')
      {
        binaryOp = 'v';
        New_L_Part = addAtHead(L_Part,'-',1);
        New_R_Part = addAtHead(R_Part,'-',1);
      }
      else if (binaryOp=='v')
      {
        binaryOp = '^';
        New_L_Part = addAtHead(L_Part,'-',1);
        New_R_Part = addAtHead(R_Part,'-',1);
      }
      else  //=='>'
      {
        binaryOp = '^';
        New_L_Part = L_Part;
        New_R_Part = addAtHead(R_Part,'-',1);
      }
    }
    else
    {
      if(parse(string)!=3) 
      {
        return input;
      }
      L_Part = partone(string);
      R_Part = parttwo(string);
      char* temp = deleteOuterBrace(string);
      binaryOp = temp[getMiddleOperator(temp)];    
      New_R_Part = R_Part;
      New_L_Part = L_Part;
      if (binaryOp=='>')
      {
        binaryOp = 'v';
        New_R_Part = R_Part;
        New_L_Part = addAtHead(L_Part,'-',1);
      }
    }

    printf("\n\nL_Part: >>>>>>>>>> %s <<<<<<<<<<", New_L_Part);
    printf("\nR_Part: >>>>>>>>>> %s <<<<<<<<<<", New_R_Part);
    printf("\nbinaryOp: ========== %c ==========\n", binaryOp);
    
    if(binaryOp == '^')
    {
      input[arrLength] = New_L_Part;
      char* temp_New_L_Part =strdup(deleteOuterBrace(New_L_Part));

      input[arrLength+1] = New_R_Part;
      input[arrLength+2]="\0";

      constructTableau(input, arrLength, counter);

      if ( temp_New_L_Part[getMiddleOperator( temp_New_L_Part )] =='^' )
      {
        constructTableau(input, arrLength+1, counter);
      }
    }
    //else binaryOp == 'v'
    else
    {
      if(index != arrLength-1)
      {
        input[arrLength] = addAtHead(New_L_Part,'*', counter+1);
        input[arrLength+1] = "\0";
        constructTableau(input, arrLength-1, counter+1);

        int oldArrLength=arrLength;
        arrLength = arrayLength_2D(input);
        input[arrLength] = addAtHead(New_R_Part,'*', counter+1);
        input[arrLength+1] = "\0";
        constructTableau(input, oldArrLength-1, counter+1);
        
        arrLength = arrayLength_2D(input);
        input[arrLength]="\0";
      }
      else
      {
        input[arrLength] = addAtHead(New_L_Part,'*', counter+1);
        input[arrLength+1] = "\0";
        constructTableau(input, arrLength, counter+1);

        arrLength = arrayLength_2D(input);
        input[arrLength] = addAtHead(New_R_Part,'*', counter+1);
        input[arrLength+1] = "\0";
        constructTableau(input, arrLength, counter+1);
        
        arrLength = arrayLength_2D(input);
        input[arrLength]="\0";
      }

    }
    return input;

}




/*You should not need to alter the program below.*/
int main()
{ /*input 10 strings from "input.txt" */
    char *name = malloc(Fsize);

    FILE *fp, *fpout;

  /* reads from input.txt, writes to output.txt*/
    if ((  fp=fopen("input.txt","r"))==NULL){
        printf("Error opening file");exit(1);}
    if ((  fpout=fopen("output.txt","w"))==NULL){printf("Error opening file");exit(1);}

    int j;
    
  for(j=0;j<inputs;j++)
  {
      fscanf(fp, "%s",name);/*read formula*/
      int type = parse(name);
        printf("\x1B[32m");
        printf("\n\nOriginal string: %s\n",name);
        printf("\033[0m");
      switch (type)
      {
          case(0): fprintf(fpout, "%s is not a formula.  \n", name);break;
          case(1): fprintf(fpout, "%s is a proposition. \n ", name);break;
          case(2): fprintf(fpout, "%s is a negation.  \n", name);break;
          case(3):fprintf(fpout, "%s is a binary. The first part is %s and the second part is %s  \n", name, partone(name), parttwo(name));break;
          default:fprintf(fpout, "What the f***!  ");
      }
      if (type!=0)
      {
          char** name_ = (char**) malloc((100)*sizeof(char*)); //Prevent name from changing
          for (size_t i = 0; i < 100; i++)
          {
            name_[i]=(char*) malloc((100)*sizeof(char));
          }
          name_[0]=strdup(name);
          name_[1]="\0";
          char** tab = constructTableau(name_,0,0); 
          printf("\n\033[0;31mTableau_Size: ######### %d #########\033[0m", arrayLength_2D(tab));
          printTableau(tab);

          if (closed(tab))  fprintf(fpout, "%s is not satisfiable.\n", name);
          else fprintf(fpout, "%s is satisfiable.\n", name);
          free(name_);
          free(tab);
      }
      else  fprintf(fpout, "I told you, %s is not a formula.\n", name);
  }

 
    fclose(fp);
    fclose(fpout);
    free(name);


  return(0);
}




