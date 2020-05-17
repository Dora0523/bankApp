/* program to implement a simple banking application 
 *************************************************************
 * Author          Dept.            Date            Notes
 *************************************************************
 * Xinchen Hou   Stats&CompSci    March 07 2020     Initial version
 * Xinchen Hou   Stats&CompSci    March 08 2020     Case -w,-d
 * Xinchen Hou   Stats&CompSci    March 09 2020     Fix bugs 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ########################## FUNCTIONS #####################
   // ## -a => create ##
   int create(FILE* r, FILE* w, char Number[], char Name[]){
	   while (! feof(r)){
              int Num;

	      char line[100];
	      fgets(line,99,r);
	      if (line[0] == 'A'){
		      sscanf(line,"%*c %*c,%d,%*s %*s",&Num);}

	    // if account number exist, return error code 50
	      if (Num == (atoi(Number))){
		      fprintf(stderr,"Error, account number %d already exists\n",Num);
		      return 50;   }
	     
	   
	   }
	    
	   // else create account, append to file 
            char newAct[100];
            sprintf(newAct,"AC,%s,%s\n",Number,Name);
	    fputs(newAct,w);
	    fclose(w);
	    fclose(r);
   }


  // ## -d ==> deposit ##
  
    int deposit(FILE* r, FILE* w, char Number[], char date[], char amt[] ){
          int i = 0; // i = 0 if account dne
        //loop through file
	  while (! feof(r)){
            int Num;
            char line[100];
            fgets(line,99,r);
            if (line[0] == 'A'){
                      sscanf(line,"%*c %*c,%d,%*s %*s",&Num);
                      if (Num == (atoi(Number))){i=1;
	    }
          }
	  }
          //if account dne, return error code 50
          if (i == 0){
                  fprintf(stderr,"Error, account number %s does not exists\n",Number);
                  return 50;
          }
	  // else make deposit
          char deposit[100];
          sprintf(deposit,"TX,%s,%s,%s\n",Number,date,amt);
          fputs(deposit,w);
          fclose(w);
          fclose(r);
  }

   
   
   // ## -w ==> withdraw  ##
   int withdraw(FILE* r, FILE* w, char Number[], char date[], char amt[]){
          int i = 0; // i = 0 if account dne
	  float balance = 0.0;
	  //loop through file
	  for(;;){  
	    int Num;
	    int n;
	    float b=0.0;

	    char line[100];
	    char l[100];
	    char l2[100];
	    fgets(line,99,r);
	    if (feof(r)){break;} //break if end of file
	    if (line[0] == 'A'){ // AC...
                      sscanf(line,"%*c %*c,%d,%*s,%*s",&Num);}
	    if (Num == (atoi(Number))){i=1;}// Account Exist
	    
	    if (line[0] == 'T'){ //TX...
		      sscanf(line,"%*c %*c,%d,%s",&n,l);
	    
	    if (n == (atoi(Number))) {
		    sprintf(l2,"%s",l+11);//balance in array form                     
		    sscanf(l2,"%f",&b);//b = last balance
		    //balance = balance+b;
		    balance = balance + b;
		    }	   


	    }}
	  //if account dne, return error code 50
	  if (i == 0){
		  fprintf(stderr,"Error, account number %s does not exists\n",Number);
		  return 50;
	  }

	  // else 
	  // if balance < amt, return error code 60 
	  if (balance - atoi(amt) < 0) {

	fprintf(stderr,"Error, account number %s has only %.2f\n",Number,balance);
		return 60;} 
	  


	  // withdraw money

	  char withdraw[100];
          sprintf(withdraw,"TX,%s,%s,-%s\n",Number,date,amt);
          fputs(withdraw,w);
          fclose(w);
          fclose(r);
  
   
    }


//######################################  MAIN ###########################################
int main(int argc, char* argv[])
{
        int a = argc;
//check usage
        // no args input => return 1
	if (a == 1) { 
	fprintf(stderr,"Error, incorrect usage!\n-a ACCTNUM Name\n-d ACCTNUM DATE AMOUNT\n-w ACCTNUM DATE AMOUNT\n");
	return 1;}
        
	
	char* s = argv[1];
	char c = s[1];
         
	//###### -a ACCTNUM NAME ######
        if ( c =='a' ){
           if (a != 4) { 
		   fprintf(stderr,"Error, incorrect usage!\n-a ACCTNUM NAME\n");
	           return 1;}

           int acctnum = atoi(argv[2]);
           char* name = argv[3];

	   if (acctnum == 0) {
		   fprintf(stderr,"Error, incorrect usage!\n-a ACCTNUM NAME\n");
	                   return 1;}
	}
        //##### -d ACCTNUM DATE AMOUNT #####
	if (c == 'd'){
	   if (a != 5){
		   fprintf(stderr,"Error, incorrect usage!\n-d ACCTNUM DATE AMOUNT\n")
			   ;
	           return 1;}

	   int acctnum = atoi(argv[2]);
	   char* date = argv[3];
	   int amt = atoi(argv[4]);

	   if (acctnum == 0 || amt == 0) {
		   fprintf(stderr,"Error, incorrect usage!\n-d ACCTNUM DATE AMOUNT\n")
			   ;
	           return 1;}
	}


	 //#### -w ACCTNUM DATE AMOUNT ####
         if (c == 'w'){
		 if (a!=5){
	           fprintf(stderr,"Error, incorrect usage!\n-w ACCTNUM DATE AMOUNT\n");
	           return 1;}

		 int acctnum=atoi(argv[2]);
		 char* date = argv[3];
		 int amt = atoi(argv[4]);

           if (acctnum == 0 || amt == 0) {
                   fprintf(stderr,"Error, incorrect usage!\n-w ACCTNUM DATE AMOUNT\n")
                           ;
                   return 1;}
        }



        FILE* r = fopen ( "bankdata.csv","rt");
	FILE* w = fopen( "bankdata.csv","at");

    // if unable to locate bankdata.csv  return ErrorCode 100
	if (r == NULL) {
		fprintf(stderr,"Error, unable to locate the data file bankdata.csv\n");
		return 100;
	}

	// determine instruction using switch
	int re;
	switch (c){
		case ('a'): 
		       	re = create(r,w,argv[2],argv[3]);
			if (re != 0) {return re;}
			break;
		case ('d'):
		        re = deposit(r,w,argv[2],argv[3],argv[4]);
			if (re != 0) {return re;}
			break;
		case ('w'):
		        re = withdraw(r,w,argv[2],argv[3],argv[4]);
			if (re != 0) {return re;}
			break;
	}



	return 0;
}
