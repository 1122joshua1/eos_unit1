#include "shell.hh"
#include <errno.h>
#include<cstring>
#include <bits/stdc++.h> 
#include  <stdio.h>
#include  <string.h>
#include  <sys/types.h>
#include <sys/wait.h>


int main()
{ std::string input;

  // ToDo: Vervang onderstaande regel: Laad prompt uit bestand
  std::string prompt;
  char bytepr[1];
  int prompfd = syscall(SYS_open, "prompt.txt", O_RDONLY);
	while(syscall(SYS_read, prompfd, bytepr, 1)) {                  
    prompt+=bytepr; 
}  

  while(true)
  { std::cout << prompt;                   // Print het prompt
    std::getline(std::cin, input);         // Lees een regel
    if (input == "new_file") new_file();   // Kies de functie
    else if (input == "ls") list();        //   op basis van
    else if (input == "src") src();        //   de invoer
    else if (input == "find") find();
    else if (input == "python") python();
    else if (input == "exit") return 0;
    else if (input == "quit") return 0;
    else if (input == "error") return 1;

    if (std::cin.eof()) return 0; } }      // EOF is een exit

void new_file() // ToDo: Implementeer volgens specificatie.
{ 	std::string bestandsnaam;	

				std::cout<<"hoe mag het bestand heten?"<<std::endl;
				std::string invoernaam;
				std::getline(std::cin, invoernaam);
				char bruikbaarnaam[invoernaam.size()+1] ;
				invoernaam.copy(bruikbaarnaam, invoernaam.size()+1);
				bruikbaarnaam[invoernaam.size()] = '\0';
	int fd = syscall(SYS_creat, bruikbaarnaam, 0666);			//maakt bestand waar iedereen aan kan werken

	std::cout<<bestandsnaam;
				std::cout<<"wat moet er in het bestand komen te staan?"<<std::endl;
				std::string invoerr;
				std::string woorden;
				while (std::getline(std::cin, woorden))
{
				if(std::cin.eof()||woorden ==  ""){break;}
   				invoerr += woorden + '\n'; 
}
				char bruikbaar[invoerr.size()+1] ;
				invoerr.copy(bruikbaar, invoerr.size()+1);
				bruikbaar[invoerr.size()] = '\0';	

	auto buffer = syscall(SYS_write, fd,bruikbaar, invoerr.size());


	syscall(SYS_close, fd);
}

void list() // ToDo: Implementeer volgens specificatie.
	{
				int pid = fork();
				if (pid == 0)
				{ 

				  char *args[] = {"/bin/ls","-la", (char *) 0 };
				  execv("/bin/ls", args);
				}
				else
				{ 

				  int exit_status;
				  wait(&exit_status);
				}
}

void find() // ToDo: Implementeer volgens specificatie.
{
				std::cout<<"waarop moet gefilterd worden?"<<std::endl;
				std::string invoerr;
				std::getline(std::cin, invoerr);
				char bruikbaar[invoerr.size()+1] ;
				invoerr.copy(bruikbaar, invoerr.size()+1);
				bruikbaar[invoerr.size()] = '\0';	
		int link[2];
    if (pipe(link) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
		int pid = fork();
				if (pid == 0)
				{ 
				    dup2 (link[1], STDOUT_FILENO);
				    close(link[0]);
		
				 	 char *args[] = {"/bin/ls","-la", (char *) 0 };
					  execv("/bin/ls", args);

				}
				else
				{ 

				  int exit_status;
				  wait(&exit_status);
				}

	pid = fork();
				if (pid == 0)
				{ 

				dup2 (link[0], STDIN_FILENO);
				    close(link[0]);
				    close(link[1]);

				  char *args[] = {"/bin/grep",bruikbaar, (char *) 0 };
				  execv("/bin/grep", args);
				}
				else
				{ 

				  int exit_status;
				  wait(&exit_status);

				}

}


void python() // ToDo: Implementeer volgens specificatie.
{ 
			
				int pid = fork();
				if (pid == 0)
				{ 

				  char *args[] = {"python3", (char *) 0 };
				  execv("/usr/bin/python3", args);
				}
				else
				{ 

				  int exit_status;
				  wait(&exit_status);
				 std::cout<<"exitcode  "<<exit_status<<std::endl;
				}
 }

void src() // Voorbeeld: Gebruikt SYS_open en SYS_read om de source van de shell (shell.cc) te printen.
{ int fd = syscall(SYS_open, "shell.cc", O_RDONLY, 0755); // Gebruik de SYS_open call om een bestand te openen.
  char byte[1];                                           // 0755 zorgt dat het bestand de juiste rechten krijgt (leesbaar is).
  while(syscall(SYS_read, fd, byte, 1))                   // Blijf SYS_read herhalen tot het bestand geheel gelezen is,
    std::cout << byte; }                                  //   zet de gelezen byte in "byte" zodat deze geschreven kan worden.

