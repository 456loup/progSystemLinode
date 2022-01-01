#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h> 
#include <dirent.h>
#include <string.h> 
#include <sys/stat.h>

void viderChaineCarac(char chaine[]){
    for(int i = 0 ; chaine[i] != '\0' ; i++){
        chaine[i] = ' '; 
    }
}

void testEcritureRep(){

    DIR *d1; 
    mkdir("repertoireTest" , S_IRWXU);
    int truc = open("repertoireTest/fic1" , O_WRONLY | O_CREAT , 00 );
    char *mssg = "coucou"; 
    write(truc , mssg , strlen(mssg));
}

void copieFichier(char *fichierSrc , char *fichierDest){

    int d1 = 0; 
    int d2 = 0; 
    int nbOctetsLu = 0; 
    char caracLu = ' '; 
    char caracEcrit = ' '; 
    if( (d1 = open(fichierSrc , O_RDONLY , 00  )) < 0){
        printf(" Le fichier source n existe pas "); 
        exit(-1); 	
    }
    d2 = open(fichierDest , O_WRONLY | O_CREAT , 00); 
    while( (nbOctetsLu = read(d1 , &caracLu , 1)) > 0){

	caracEcrit = caracLu; 
        write(d2 ,&caracEcrit , 1);      
    } 
    close(d1); 
    close(d2); 
}

void copieRep(char *repSource , char *repDest){

    char repSource[500]; 
    char repDest[500];
    char tampon[500];  
    DIR *dirSource; 
    DIR *dirDest;
    struct dirent ent;
    struct stat st;  
     

    if( (dirSource = opendir(repSource)) == NULL){
        fprintf( stderr ,  " Le repertoire source %s est incorrect   " , repSource );   
        exit(1); 	
    }

    if( (dirDest = opendir(repDest)) == NULL){
        mkdir(repDest ,  S_IRWXU);
        dirDest = opendir(repDest); 	
    }


    while( (ent = readdir(dirSource) != NULL)){
    
        viderChaineCarac(tampon); 
	strcpy(	
    
    
    }
   
     
    
    
}

int main(int argc , char **argv){

   copieFichier(argv[1] , argv[2]);  

}

