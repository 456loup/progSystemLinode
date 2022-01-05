#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h> 
#include <dirent.h>
#include <string.h> 
#include <sys/stat.h>
#include <sys/wait.h>

/*
  CHEAT SHEET 
 sscanf(s, "%f", &x); /* lecture dans la chaîne 
printf("Vous avez saisi : %f\n", x);
return 0;
*/



extern char **environ;
void enleverEspaceFinRetour(char ligne[]){

    for(int i = 0 ; ligne[i] != '\0' ; i++){
        if(/* ligne[i] == ' ' ||*/   ligne[i] == '\n'){
	    ligne[i] = '\0'; 
	} 
    }
}

void infoProcessus(){

    char buffer[500]; 
    char resultat[500]; 
    printf(" on est dans le processus %d  entrez le nom du repertoire  " , getpid());
    fgets(buffer , 500 , stdin);
    enleverEspaceFinRetour(buffer); 
    if( (chdir(buffer)) != 0){
        printf(" NOM DU REPERTOIRE ERRONE "); 
	exit(1); 
    }
    printf(" CHANGEMENT REUSSI REPERTOIRE COURANT %s " , getcwd(resultat , 500));   
}

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

void processus(){

    pid_t proc = fork(); 

    if(proc == 0){
    
        printf(" je suis le processus fils de %d et je suis %d " , getppid() , getpid());
	execl("/usr/bin/date" , "/usr/bin/date" , NULL); 
	printf("Fin du processus fils"); 
    }else{
        printf(" je suis le processus pere  %d et je suis le pere de %d \n" , getpid() , proc);
    }
}

void testExecvp(){

    char *cmd = "ls"; 
    char *argv[2]; 
    argv[0] = "ls"; 
    argv[1] = NULL; 

    execvp(cmd , argv);  

}

void Texecvp(){

    char buffer[100];
    char *litteral; 

    printf(" entrez la commande : "); 
    fgets(buffer , 100 , stdin); 
    for(int i = 0 ; i < 100 ; i++){
        if(buffer[i] == ' ' || buffer[i] ==  '\n'){
	    buffer[i] = '\0';
	    break;  
	} 
    }
    char *argv[2]; 
    argv[0] = buffer; 
    argv[1] = NULL;
    execvp(buffer , argv); 
     
}

void entrerCommandeSansArgument(){

    pid_t proc = fork(); 
    char buffer[100];
    char *chaineLitterale; 
    int i = 0; 

    if(proc == 0){
        printf("entrez la commande sans arguments"); 
	fgets(buffer , 100 , stdin); 
        for(i = 0 ; i < 100  ; i++){
	    if(buffer[i] == '\n' || buffer[i] == ' '){
	        buffer[i] = '\0'; 
		break; 
	    }
	} 
	printf("\n\n WHATEVER%struc  \n\n " , buffer);
        char *argv[2]; 
	argv[0] = buffer; 
	argv[1] = NULL; 	
	execvp(buffer , argv); 	
    }else{
	wait(NULL);   
        printf(" on est dans le processus pere le prog va s arreter ");  
    }

}

void copieRep(char repSource[] , char repDest[]){

    char tampon[500]; 
    char tampon2[500]; 
    int desc = 0;  
    DIR *dirSource; 
    DIR *dirDest;
    struct dirent *ent;
    struct stat st;  
     

    if( (dirSource = opendir(repSource)) == NULL){
        fprintf( stderr ,  " Le repertoire source %s est incorrect   " , repSource );   
        exit(1); 	
    }

    if( (dirDest = opendir(repDest)) == NULL){
        mkdir(repDest ,  S_IRWXU);
        dirDest = opendir(repDest); 	
    }

    /*   */
    while( (ent = readdir(dirSource)) != NULL){
    
        viderChaineCarac(tampon);	
	strcpy(tampon , repDest);
        strcat(tampon , "/");
	strcat(tampon , ent->d_name);

        viderChaineCarac(tampon2); 
	strcpy(tampon2 , repSource); 
	strcat(tampon2 , "/"); 
	strcat(tampon2 , ent->d_name); 

        lstat(tampon2 , &st);
        if(strcmp(ent->d_name , "..") != 0 && strcmp(ent->d_name , ".") != 0){  	
            if( S_ISREG(st.st_mode)){
	        copieFichier(tampon2 , tampon);  
	    }else if(S_ISDIR(st.st_mode)){
	        printf(" VOUS DEVEZ LE FAIRE %s" , tampon); 
	        copieRep(tampon2 , tampon); 
	    }
	}
    }

    closedir(dirSource); 
    closedir(dirDest); 
}


void processusParallele(){

    char *env = getenv("HOME");
    int i = 0; 

    for(i = 0 ; environ[i] != NULL ; i++){
        printf("\n %s " , environ[i]); 
    }

    printf("\n\n"); 
}

void sousTraitUpperCase(){

    char buffer[500];
    while(1){
        pid_t proc = fork();
        if(proc == 0){     
            for(int i = 0 ; buffer[i] != '\0' && buffer[i] >= 65 && buffer[i] <= 122 || buffer[i] == ' '  ; i++){
	        printf("%c" , buffer[i]-32); 
	    }
	    exit(0); 
        }else{
	    wait(NULL); 
            printf(" entrez une chaine quelconque :  ");
	    fgets(buffer , 500 , stdin);
        }    
    }
}


void testFork(){

    printf(" HALLO WORKD "); 
    fork(); 
    fork(); 


}

int main(int argc , char **argv){


   sousTraitUpperCase(); 
   //testFork(); 
   //infoProcessus(); 
   //copieFichier(argv[1] , argv[2]); 
   //copieRep(argv[1] , argv[2]);  
   //processusParallele();
   //processus(); 
   //testExecvp();  
   //entrerCommandeSansArgument();
   //Texecvp(); 
}

