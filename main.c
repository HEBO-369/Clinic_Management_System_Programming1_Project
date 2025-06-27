#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

int main()
{
    /****************************************************** scan file doctors **************************************************************/
    // Doctors Data

    FILE *fptr;
    fptr = fopen("doctors.txt", "r");
    int faild = 0 ;
    if (fptr == NULL)
    {
        printf("Could NOT allocate doctors.txt :");
        return 32;
    }


    int MAX_USERS = 10 ;
    int MAX_LENGTH = 350 ;
    char visita[MAX_USERS][80];
    char address[MAX_USERS][80];
    char speciality[MAX_USERS][80];
    char docName[MAX_USERS][80];
    char doctors[MAX_USERS][MAX_LENGTH];

    int counter = 0;
    char line[MAX_LENGTH];
    while (fgets(line, sizeof(line), fptr) != NULL && counter < MAX_USERS )
    {
        if (line[0] == '\n' || strstr(line, "Specialty:") == NULL || strstr(line, "Name:") == NULL || strstr(line, "Address:") == NULL || strstr(line, "Visita:") == NULL)
        {
            faild ++ ;
            continue;
        }
        strcpy(doctors[counter], line);
        counter++;
        //if(counter > MAX_USERS ){printf("our system only support 10 doctors max.");return 1 ;}
    }
    fclose(fptr);
    if (counter == 0)
    {
        printf("the file doctor is empty :(");
        return 32;
    }

    for (int i = 0; i < counter; i++)
    {
        char *start = strstr(doctors[i], "Specialty:") + 10;         // start character pointer searches for the word specialty an returns a pointer to its index
        int z = 0;
        while (*start != '\t' && *start != '\n' && *start != '\0')
        {
            speciality[i][z++] = *start++;                          // the specialty is then stored character by character in the array speciality
        }
        speciality[i][z] = '\0';                                    // '\0' to terminate the string

        start = strstr(doctors[i], "Name:") + 5;                    // same for the word Name:
        z = 0;
        while (*start != '\t' && *start != '\n' && *start != '\0')
        {
            docName[i][z++] = *start++;                             // docName carries the doctors names as a string form the pointer start character by character
        }
        docName[i][z] = '\0';

        start = strstr(doctors[i], "Address:") + 8;
        z = 0;
        while (*start != '\t' && *start != '\n' && *start != '\0')
        {
            address[i][z++] = *start++;                             // same for addresses
        }
        address[i][z] = '\0';

        start = strstr(doctors[i], "Visita:") + 7;
        z = 0;
        while (*start != '\t' && *start != '\n' && *start != '\0')
        {
            visita[i][z++] = *start++;                              // same for visita
        }
        visita[i][z] = '\0';
    }

    char doctors2[MAX_USERS][4][150];                               // Then a 2D array is initialized to store the doctors data combined
    for (int i = 0; i < counter; i++)
    {
        strcpy(doctors2[i][0], docName[i]);
        strcpy(doctors2[i][1], speciality[i]);
        strcpy(doctors2[i][2], address[i]);
        strcpy(doctors2[i][3], visita[i]);
    }

    FILE *pat;
    FILE *pat2;
    int faild1 = 0 ;
    char patients[MAX_USERS][MAX_LENGTH];
    char names[MAX_USERS][40];
    char usernames[MAX_USERS][40];
    char pw[MAX_USERS][40];
    int users = 0;

    pat2 = fopen("patients.txt", "r");                                  // the pointer pat2 checks the existence of the patients file by opening in r mode and returns a NULL if its not found

    if (pat2 == NULL)
    {
        printf("## No patients found in the system :( \nYou should sign up first\n");
        fclose(pat2);
    }
    else                                                                // if it is found another pointer pat opens the file in append+ mode to create a file with the desired name
    {
        fclose(pat2);
        pat = fopen("patients.txt", "a+");

        char line[MAX_LENGTH];
        while (fgets(line, sizeof(line), pat) != NULL )
        {
            if (line[0] == '\n' || strstr(line, "name:") == NULL || strstr(line, "user:") == NULL || strstr(line, "pw:") == NULL)
            {
                faild1 ++ ;
                continue;
            }
            strcpy(patients[users], line);
            users++;
            //if(users > MAX_USERS ){printf("our system only support 10 patients max.");return 1 ;}
        }
        if (users == 0)
        {
            printf("the file patients is empty :)(: you should sign up first \n");
        }

        for (int i = 0; i < users; i++)
        {
            int z = 0;


            if (strstr(patients[i], "name:") != NULL)       // pointer start searches for the names of the patients in the file written after "name:" if it is found
            {
                char *start = strstr(patients[i], "name:") + 5;
                while (*start != '\t' && *start != '\n' && *start != '\0')
                {
                    names[i][z++] = *start++;               // the characters are read one by one and index and pointer start increment by one
                }
                names[i][z] = '\0';
            }


            z = 0;
            if (strstr(patients[i], "user:") != NULL)
            {
                char *start = strstr(patients[i], "user:") + 5;
                while (*start != '\t' && *start != '\n' && *start != '\0')
                {
                    usernames[i][z++] = *start++;
                }
                usernames[i][z] = '\0';
            }


            z = 0;
            if (strstr(patients[i], "pw:") != NULL)
            {
                char *start = strstr(patients[i], "pw:") + 3;
                while (*start != '\t' && *start != '\n' && *start != '\0')
                {
                    pw[i][z++] = *start++;
                }
                pw[i][z] = '\0';
            }
        }
        fclose(pat);
    }

    char patients2[MAX_USERS][3][50];
    for (int i = 0; i < users; i++)
    {
        strcpy(patients2[i][0], names[i]);
        strcpy(patients2[i][1], usernames[i]);
        strcpy(patients2[i][2], pw[i]);
    }
    if ( faild1 != 0 )printf("There is %d corrupt / empty lines in the patients file :( some data may not found.\n",faild1);

    /******************************************************** first menu *********************************************************/
    while (1)
    {
        char c[3];
        printf("[1] Log in \n[2] Sign up \n[3] End program\n");     //main menu options
        fgets(c, sizeof(c), stdin);
        c[strcspn(c, "\n")] = '\0';
        //printf("%d\n%d\n",strlen(c),sizeof(c))  ;                            // clears the \n from the input
        if (strlen(c) == sizeof(c)-1)
        {
            printf("Input is too long! try again.\n");
            while (getchar() != '\n');                              // clears the buffer till the next \n
            continue ;
        }



        if (strcmp(c, "3") != 0 && strcmp(c, "2") != 0 && strcmp(c, "1") != 0)    // if the user inputs an invalid message
        {
            printf("Please click on 1,2 or 3\n");
            continue;
        }
        if (strcmp(c, "3") == 0)         // End Program on pressing 3
        {
            return 0;
        }
        /************************************************************ sign up **********************************************************/
        if (strcmp(c, "2") == 0)
        {
            char user[22];                          //strings for storing users data name - user name - password
            char password[22];
            char name[52];
            char pwcheck[22];
            if (users >= MAX_USERS)
            {
                printf("you cannot sign up as our file has the max(10 patients)\n");   //prevents sign up if number of users stored is 10
                continue;
            }

            bool exit = false;
            while (1)                                       // the user in all parts of the sign up and log in process can enter '0' to go back
            {
                printf("click 0 to back \nenter your name(only letters and space allowed(no double spaces)- max 50): \n");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                if (strcmp(name, "0") == 0)
                {
                    exit = true;
                    break;
                }
                if (strlen(name) == sizeof(name) - 1 )              // if the input from the buffer reaches the maximum size of the string on initialization the name is considered too long
                {
                    printf("Input is too long! try again.\n");
                    while (getchar() != '\n');
                    continue ;
                }
                bool x = false;
                for (int i = 0; i < strlen(name); i++)
                {
                    if ((name[i] != 32 && name[i] < 65 )|| (name[i]> 122 )||(name[i] > 90 && name[i] < 97 ))        // making sure the name is written using upper and lower case letters and a space
                    {
                        printf("The name is rejected.try again. enter only letters\n");
                        x = true;
                        break;
                    }
                }
                if (strlen(name) < 4)
                {
                    printf("Too short name. try again:\n");             // the name can't be too short
                    continue;
                }
                for (int me = 0 ; me < strlen(name); me ++ )
                {

                    if ((name[me]== ' ' && name[me + 1 ]==' ')||(name[0]==' '))           // no 2 adjacent spaces ' ' can be read as a name
                    {
                        printf("The name is rejected.try again:\n");
                        x = true;
                        break;

                    }
                }
                if (x == true)
                {
                    continue;
                }

                break;
            }
            if (exit)
            {
                continue;
            }
            exit = false;
            while (1)
            {
                printf("Click 0 to back \nEnter your user name(no double spaces)- max 20 : \n");      // user name restrictions max 20 letters and no double spaces
                fgets(user, sizeof(user), stdin);
                user[strcspn(user, "\n")] = '\0';
                if (strcmp(user, "0") == 0)
                {
                    exit = true;
                    break;
                }
                if (strlen(user) == sizeof(user) - 1 )
                {
                    printf("Input is too long! try again.\n");                                  // when the user input reaches max number of character the string can hold it is rejected
                    while (getchar() != '\n');
                    continue ;
                }




                if (strlen(user) < 4)
                {
                    printf("Username is too short[min 4 letters]. \nTry again\n");              // the user name can't be too short
                    continue;
                }
                bool skip = false;

                for (int i = 0; i < users; i++)
                {
                    if (strcmp(patients2[i][1], user) == 0)                     // loops the stored user names array to check if the name is already used by another user
                    {
                        printf("the username is used, try again with another username \n");
                        skip = true;
                        break;
                    }
                }
                for (int me = 0 ; me < strlen(user); me ++ )
                {

                    if ((user[me]== ' ' && user[me + 1 ]==' ')||(name[0]==' '))
                    {
                        printf("the user name is rejected.try again:\n");           // checks for double spaces entries
                        skip = true;
                        break;

                    }
                }
                if (skip)
                {
                    continue;
                }
                break;
            }
            if (exit)continue ;
            exit = false;
            while (1)
            {
                printf("Click 0 to back \nEnter the password - max 20: \n");
                fgets(password, sizeof(password), stdin);
                password[strcspn(password, "\n")] = '\0';
                if (strcmp(password, "0") == 0)
                {
                    exit = true;
                    break;
                }
                if (strlen(password) == sizeof(password) - 1 )              // when the password exceeds the string size it is rejected
                {
                    printf("Input is too long! try again.\n");
                    while (getchar() != '\n');
                    continue ;
                }
                if (strlen(password) < 4)
                {
                    printf("The password is too short[min 4 letters]. \ntry again\n");          // length can't be too short
                    continue;
                }
                printf("Click 0 to back \nEnter the password again for check:\n");              // the user is asked to enter the password twice for confirmation
                fgets(pwcheck, sizeof(pwcheck), stdin);
                pwcheck[strcspn(pwcheck, "\n")] = '\0';
                if (strcmp(pwcheck, "0") == 0)
                {
                    exit = true;
                    break;
                }
                if (strlen(pwcheck) == sizeof(pwcheck) - 1 )
                {
                    printf("The passwords are different! please try again\n");                          // to clear the buffer in case of very long entries
                    while (getchar() != '\n');
                    continue ;
                }




                if (strcmp(password, pwcheck) != 0)                                     // different passwords
                {
                    printf("The passwords are different! please try again\n");
                    continue;
                }

                break;
            }
            if (exit)
            {
                continue;
            }
            // signed up user's data are stored in the patients array first
            strcpy(patients2[users][0], name);
            strcpy(patients2[users][1], user);
            strcpy(patients2[users][2], password);
            pat = fopen("patients.txt", "a+");
            // then they are stored in the file in this format
            if (users == 0)
            {
                fprintf(pat, "name:%s\tuser:%s\tpw:%s", name, user, password);
                printf("You have been signed up successfully\nNow you may login.\n");
                users++;
            }
            else
            {
                fprintf(pat, "\nname:%s\tuser:%s\tpw:%s", name, user, password);
                printf("you has signed up successfully.\nnow you can login\n");
                users++;
            }
            fclose(pat);
            continue;
        }


        /**************************************************** log in ***************************************************************/
        if (strcmp(c, "1") == 0)
        {
            if(users==0)
            {
                printf("there is no users yet in the system.sing up first\n");
                continue;
            }
            bool logSuccess = false;
            bool x = false;
            bool exit = false;
            int k;
            char user[22];                                      // strings to store log in data
            char password[22];
            while (1)
            {
                printf("Click 0 to back \nEnter your user name: \n");
                fgets(user, sizeof(user), stdin);                           // taking input from the user
                user[strcspn(user, "\n")] = '\0';
                if (strcmp(user, "0") == 0)
                {
                    exit = true;
                    break;
                }
                if (strlen(user) == sizeof(user) - 1 )
                {
                    printf("Input is too long! try again.\n");
                    while (getchar() != '\n');                                          // clearing the buffer when the input is too long
                    continue ;
                }

                for (int i = 0; i < users; i++)                         // searching for the user in the patients array
                {
                    if (strcmp(patients2[i][1], user) == 0)
                    {
                        x = true;
                        k = i;
                        break;
                    }
                }
                if (x == false)
                {
                    printf("The user name does NOT exist! try again \n");       // NOT found
                    continue;
                }
                break;
            }
            if(exit)continue;
            char numOfTry = 0;
            while (1)                   // if the user is found he is asked to enter the password where he has 3 trials
            {

                if (numOfTry == 3)
                {
                    printf("you have reached the max number of tries.\n");
                    break;
                }
                printf("Click 0 to back \nEnter the password: \n");
                fgets(password, sizeof(password), stdin);                   // password input
                password[strcspn(password, "\n")] = '\0';
                if (strcmp(password, "0") == 0)
                {
                    exit = true;
                    break;
                }
                if (strlen(password) == sizeof(password) - 1 )                      // input size chack
                {
                    printf("Input is too long! try again.\n");
                    while (getchar() != '\n');
                    continue ;
                }
                if (strcmp(patients2[k][2], password) == 0)
                {
                    printf("Welcome, %s! what do you want to do\n", patients2[k][0]);       // welcome the user when he enters the password correctly
                    logSuccess = true;
                    break;
                }
                else
                {
                    char n[3];
                    printf("wrong password. do you want to :\n1: try again\npress any other key to go to menu\n");  //the user is given a choice to try again or exit if the password is wrong
                    fgets(n, sizeof(n), stdin);
                    n[strcspn(n, "\n")] = '\0';
                    if (strlen(n) == sizeof(n) - 1 )
                    {
                        printf("wrong pw. try again\n");
                        while (getchar() != '\n');
                        continue ;
                    }
                    if (strcmp(n, "1") != 0)
                        break;
                    if (strcmp(n, "1") == 0)
                    {
                        numOfTry++;
                        continue;
                    }
                }
            }
            if(exit)continue;
            if ( faild != 0 )printf("There is %d corrupt / empty lines in the doctor file :( some data may not found.\n",faild);

            /************************************************************ main program **********************************************************/
            while (logSuccess)
            {
                char choose[3];
                char name1[50];                             //string to carry the users input to search according to his choice
                char speciality1[50];
                char clinic1[50];
                char visita1[50];
                printf("[1] See all doctors. \n[2] Search for specific value.\n[3] Log out.\n");            //list of options after log in
                fgets(choose, sizeof(choose), stdin);
                choose[strcspn(choose, "\n")] = '\0';
                if (strlen(choose) == sizeof(choose) - 1 )
                {
                    printf("Input is too long! try again.\n");
                    while (getchar() != '\n');
                    continue ;
                }
                if (strcmp(choose, "3") != 0 && strcmp(choose, "2") != 0 && strcmp(choose, "1") != 0)       // checks for wrong input from the user
                {
                    printf("please choose between 1 - 3 \n");
                    continue;
                }
                if (strcmp(choose, "1") == 0)                       // displaying all doctors data when entering 1
                {
                    for (int i = 0; i < counter; i++)
                    {

                        printf("#%d_\nName:%s\n", i + 1, doctors2[i][0]);
                        printf("Specialty:%s\n", doctors2[i][1]);
                        printf("Address:%s\n", doctors2[i][2]);
                        printf("Visita:%s\n\n",  doctors2[i][3]);

                    }

                    printf("All doctors are printed \nWhat do you want to do next , %s ? \n",patients2[k][0]);
                    continue;
                }
                if (strcmp(choose, "3") == 0)
                {
                    logSuccess = false;
                    continue;
                }
                if (strcmp(choose, "2") == 0)         // option 2 searching for a specific data
                {

                    while (1)
                    {
                        char b[3];
                        printf("[1] Search for name.\n[2] Search for specialty.\n[3] Search for clinic address.\n[4] Search for visita.\n[5] Back\n");
                        fgets(b, sizeof(b), stdin);
                        b[strcspn(b, "\n")] = '\0';
                        if (strlen(b) == sizeof(b) - 1 )
                        {
                            printf("Input is too long! try again.\n");
                            while (getchar() != '\n');
                            continue ;
                        }
                        if (strcmp(b, "3") != 0 && strcmp(b, "2") != 0 && strcmp(b, "1") != 0 && strcmp(b, "5") != 0 && strcmp(b, "4") != 0)  // cases of wrong entries
                        {
                            printf("Please choose between 1 - 5 \n");
                            continue;
                        }
                        if (strcmp(b, "1") == 0)
                        {
                            while(1)
                            {
                                printf("Enter 0 to back \nEnter the Name you want to search: \n");
                                fgets(name1, sizeof(name1), stdin);
                                name1[strcspn(name1, "\n")] = '\0';
                                if (strcmp(name1, "0") == 0)break;
                                if (strlen(name1) == sizeof(name1) - 1 )
                                {
                                    printf("Input is too long! try again.\n");
                                    while (getchar() != '\n');
                                    continue ;
                                }
                                bool found = false;
                                for (int i = 0; i < counter; i++)
                                {
                                    if (strcmp(name1, doctors2[i][0]) == 0)                     // searching the name in the data
                                    {
                                        found = true;
                                        printf("#%d_\nName:%s\n", i + 1, doctors2[i][0]);
                                        printf("Specialty:%s\n", doctors2[i][1]);
                                        printf("Address:%s\n", doctors2[i][2]);
                                        printf("Visita:%s\n\n",  doctors2[i][3]);
                                    }
                                }
                                if (found == false)                                     // if the name is not found
                                {
                                    printf("The name is not found!\nTry again.\n");
                                    continue;
                                }
                                break ;
                            }

                        }
                        if (strcmp(b, "2") == 0)                            // searching for a specialty
                        {
                            while(1)
                            {
                                printf("Enter 0 to back \nEnter the specialty :\n");
                                fgets(speciality1, sizeof(speciality1), stdin);
                                speciality1[strcspn(speciality1, "\n")] = '\0';
                                if (strcmp(speciality1, "0") == 0)break;
                                if (strlen(speciality1) == sizeof(speciality1) - 1 )
                                {
                                    printf("Input is too long! try again.\n");
                                    while (getchar() != '\n');
                                    continue ;
                                }
                                bool found = false;
                                for (int i = 0; i < counter; i++)
                                {
                                    if (strcmp(doctors2[i][1], speciality1) == 0)
                                    {
                                        found = true;
                                        printf("#%d_\nName:%s\n", i + 1, doctors2[i][0]);               //displaying all doctors with this specialty
                                        printf("Specialty:%s\n", doctors2[i][1]);
                                        printf("Address:%s\n", doctors2[i][2]);
                                        printf("Visita:%s\n\n",  doctors2[i][3]);

                                    }
                                }
                                if (found == false)
                                {
                                    printf("This specialty is NOT found!\nTry again\n");            // if it is not found
                                    continue;
                                }
                                break ;
                            }
                        }
                        if (strcmp(b, "3") == 0)
                        {
                            while (1)
                            {
                                printf("Enter 0 to back \nEnter the clinic's address :\n");
                                fgets(clinic1, sizeof(clinic1), stdin);
                                clinic1[strcspn(clinic1, "\n")] = '\0';
                                if (strcmp(clinic1, "0") == 0)break;
                                if (strlen(clinic1) == sizeof(clinic1) - 1 )
                                {
                                    printf("Input is too long! try again.\n");
                                    while (getchar() != '\n');
                                    continue ;
                                }
                                bool found = false;
                                for (int i = 0; i < counter; i++)
                                {
                                    if (strcmp(doctors2[i][2], clinic1) == 0)
                                    {
                                        found = true;
                                        printf("#%d_\nName:%s\n", i + 1, doctors2[i][0]);               // displaying all doctors with this address
                                        printf("Specialty:%s\n", doctors2[i][1]);
                                        printf("Address:%s\n", doctors2[i][2]);
                                        printf("Visita:%s\n\n",  doctors2[i][3]);

                                    }
                                }
                                if (found == false)
                                {
                                    printf("The clinic's address is not found!!\nTry again\n");
                                    continue;
                                }
                                break;
                            }
                        }
                        if (strcmp(b, "4") == 0)
                        {
                            while(1)
                            {
                                printf("Enter 0 to back \nEnter the visita: \n");
                                fgets(visita1, sizeof(visita1), stdin);
                                visita1[strcspn(visita1, "\n")] = '\0';
                                if (strcmp(visita1, "0") == 0)break;
                                if (strlen(visita1) == sizeof(visita1) - 1 )
                                {
                                    printf("Input is too long! try again.\n");
                                    while (getchar() != '\n');
                                    continue ;
                                }
                                bool found = false;
                                for (int i = 0; i < counter; i++)
                                {
                                    if (strcmp(doctors2[i][3], visita1) == 0)
                                    {
                                        found = true;
                                        printf("#%d_\nName:%s\n", i + 1, doctors2[i][0]);               // displaying all doctors with this visita
                                        printf("Specialty:%s\n", doctors2[i][1]);
                                        printf("Address:%s\n", doctors2[i][2]);
                                        printf("Visita:%s\n\n",  doctors2[i][3]);

                                    }
                                }
                                if (found == false)
                                {
                                    printf("Ths visita does NOT exist!!\nTry again\n");
                                    continue;
                                }
                                break;
                            }
                        }
                        if (strcmp(b, "5") == 0)
                        {

                            break;
                        }
                    }
                }
            }
        }
    }
    return 0;
}
